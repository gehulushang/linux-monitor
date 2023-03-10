//
// Created by OaixNait on 2022/7/6.
//

#include <utility>
#include "urls/urls.h"
#include "http/http_server.h"
#include "handlers/handler.h"

mg_http_serve_opts HttpServer::s_server_option;
std::unordered_map<std::string, ReqHandler> HttpServer::s_handler_map;
std::unordered_set<mg_connection *> HttpServer::s_websocket_session_set;

HttpServer::HttpServer() {
    m_root_dir_ = "./index";
}

void HttpServer::Init() {
    auto config = HttpConfig::GetInstance();

    m_port = config.GetPort();
    m_root_dir_ = config.GetHomepage();
    s_server_option.root_dir = m_root_dir_.c_str();

    // other http setting
    // eanble CORS，for homepage loading only 
    // s_server_option.extra_headers = "Access-Control-Allow-Origin: *";
}

[[noreturn]] bool HttpServer::Start() {
    auto config = HttpConfig::GetInstance();
    mg_log_set(config.GetDebugLevelStr().c_str());

    mg_mgr_init(&m_mgr);
    mg_connection *connection = mg_http_listen(&m_mgr, m_port.c_str(), 
                                HttpServer::OnHttpWebsocketEvent, &m_mgr);
    if (connection == nullptr) {
        MG_ERROR(("Cannot listen on %s. Use http://ADDR:PORT or :PORT",
                m_port.c_str()));
        exit(EXIT_FAILURE);
    }
    // for both http and websocket
    // mg_set_protocol_http_websocket(connection);

    MG_INFO(("Mongoose version : v%s", MG_VERSION));
    MG_INFO(("Listening on     : %s", m_port.c_str()));
    MG_INFO(("Web root         : [%s]", s_server_option.root_dir));
    // loop
    while (true)
        mg_mgr_poll(&m_mgr, 500); // ms
    MG_INFO(("Exiting on signal"));
    mg_mgr_free(&m_mgr);
}

bool HttpServer::AddHandlers() {
    bool result = true;
    for (auto item : linux_monitor::web::handler_map) {
        AddHandler(item.first, item.second);
    }
    return result;
}

void HttpServer::OnHttpWebsocketEvent(mg_connection *connection, int event_type, 
                                      void *event_data, void *fn_data) {
    // 区分http和websocket
    // 1,设置local dir，在Init已经设置过。
    // 改了个宏定义
    if (event_type == MG_EV_HTTP_MSG) {
        auto *http_req = (mg_http_message *) event_data;
        HandleHttpEvent(connection, http_req);
    } else if (event_type == MG_EV_WS_OPEN || event_type == MG_EV_WS_MSG) {
        auto *ws_message = (mg_ws_message *) event_data;
        HandleWebsocketMessage(connection, event_type, ws_message);
    } else if (event_type == MG_EV_CLOSE) {
        // free(fn_data);
    }
}

// ---- simple http ---- //
static bool route_check(mg_http_message *http_msg, char *route_prefix) {
    if (mg_vcmp(&http_msg->uri, route_prefix) == 0)
        return true;
    else
        return false;

    // TODO: 还可以判断 GET, POST, PUT, DELTE等方法
    // mg_vcmp(&http_msg->method, "GET");
    // mg_vcmp(&http_msg->method, "POST");
    // mg_vcmp(&http_msg->method, "PUT");
    // mg_vcmp(&http_msg->method, "DELETE");
}

void HttpServer::AddHandler(const std::string &url, 
                            const ReqHandler &req_handler) {
    if (s_handler_map.find(url) != s_handler_map.end())
        return;

    s_handler_map.insert(std::make_pair(url, req_handler));
}

void HttpServer::RemoveHandler(const std::string &url) {
    auto it = s_handler_map.find(url);
    if (it != s_handler_map.end())
        s_handler_map.erase(it);
}

void HttpServer::SendHttpRsp(mg_connection *connection, const std::string &rsp) {

    bool cors_enable = true;
    if (cors_enable) {
        mg_printf(connection, "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/plain\n"
                 "Cache-Control: no-cache\n"
                 "Content-Length: %d\n"
                 "Access-Control-Allow-Origin: *\n\n"
                 "%s\n", rsp.length(), rsp.c_str());
    } else {
        mg_printf(connection, "%s", 
                  "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
    }

    mg_http_printf_chunk(connection, rsp.c_str());
    mg_http_printf_chunk(connection, "");
    mg_send(connection, "", 0);
}

void HttpServer::HandleHttpEvent(mg_connection *connection, 
                                 mg_http_message *http_req) {
    std::string msg   = std::string(http_req->message.ptr, http_req->message.len);
    std::string url   = std::string(http_req->uri.ptr, http_req->uri.len);
    std::string body  = std::string(http_req->body.ptr, http_req->body.len);

    MG_INFO(("%.*s %.*s", (int) http_req->method.len, http_req->method.ptr,
            (int) http_req->uri.len, http_req->uri.ptr));
    MG_INFO(("%s", body.c_str()));
    auto it = s_handler_map.find(url);
    if (it != s_handler_map.end()) {
        ReqHandler handle_func = it->second;
        handle_func(url, body, connection, &HttpServer::SendHttpRsp);
    } else {
        ReqHandler handle_func = ReqHandler(
            [](const std::string&, const std::string&, 
                mg_connection *con, OnRspCallback rsp_callback) {
                // while (1);
                auto response = R"("Welcome to linux monitor")";
                rsp_callback(con, response);
                return response;
            });
        handle_func(url, body, connection, &HttpServer::SendHttpRsp);
    }

}

// ---- websocket ---- //
int HttpServer::IsWebsocket(const mg_connection *connection) {
    return connection->is_websocket;
    // return connection->flags & MG_F_IS_WEBSOCKET;
}

void HttpServer::HandleWebsocketMessage(mg_connection *connection, 
                                        int event_type, mg_ws_message *ws_msg) {
    //  TODO
    // (event_type == MG_EV_WS_OPEN) {
    //     printf("client websocket connected\n");
    //     // 获取连接客户端的IP和端口
    //     char addr[32];
    //     mg_sock_addr_to_str(&connection->sa, addr, sizeof(addr), 
    //                         MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
    //     printf("client addr: %s\n", addr);

    //     // 添加 session
    //     s_websocket_session_set.insert(connection);

    //     SendWebsocketMsg(connection, "client websocket connected");
    // } else if (event_type == MG_EV_WS_MSG) {
    //     mg_str received_msg = {
    //             (char *) ws_msg->data, ws_msg->size
    //     };

    //     char buff[1024] = {0};
    //     // must use strncpy, specifiy memory pointer and length
    //     strncpy(buff, received_msg.p, received_msg.len); 

    //     // do sth to process request
    //     printf("received msg: %s\n", buff);
    //     SendWebsocketMsg(connection, "send your msg back: " + std::string(buff));
    //     //BroadcastWebsocketMsg("broadcast msg: " + std::string(buff));
    // } else if (event_type == MG_EV_CLOSE) {
    //     if (IsWebsocket(connection)) {
    //         printf("client websocket closed\n");
    //         // 移除session
    //         if (s_websocket_session_set.find(connection) != s_websocket_session_set.end())
    //             s_websocket_session_set.erase(connection);
    //     }
    // }
}

void HttpServer::SendWebsocketMsg(mg_connection *connection, 
                                  const std::string &msg) {
    mg_ws_send(connection, msg.c_str(), strlen(msg.c_str()),WEBSOCKET_OP_TEXT);
}

void HttpServer::BroadcastWebsocketMsg(const std::string& msg) {
    for (mg_connection *connection: s_websocket_session_set)
        mg_ws_send(connection, msg.c_str(), strlen(msg.c_str()),WEBSOCKET_OP_TEXT);
}

bool HttpServer::Close() {
    mg_mgr_free(&m_mgr);
    return true;
}