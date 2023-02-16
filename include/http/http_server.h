//
// Created by OaixNait on 2022/7/6.
//

#ifndef HTTPSERVER_HTTP_SERVER_H
#define HTTPSERVER_HTTP_SERVER_H
#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "config/http_config.h"
#include "mongoose/mongoose.h"

// 定义http返回callback
typedef void OnRspCallback(mg_connection *c, const std::string &);
// 定义http请求handler
using ReqHandler = std::function<std::string(const std::string &, const std::string &, 
                                             mg_connection *con, OnRspCallback)>;

class HttpServer {
public:
    HttpServer();

    ~HttpServer() = default;

    void Init();
    bool Close();
    [[noreturn]] bool Start();

    bool AddHandlers();

    void RemoveHandler(const std::string &url);

    void AddHandler(const std::string &url, const ReqHandler &req_handler);

    static std::string s_web_dir; 
    static const char *s_debug_level;
    static mg_http_serve_opts s_server_option;
    static std::unordered_map<std::string, ReqHandler> s_handler_map;

private:

    mg_mgr m_mgr;
    std::string m_port;
    std::string m_root_dir_;
    static std::unordered_set<mg_connection *> s_websocket_session_set;

    static int IsWebsocket(const mg_connection *connection);

    static void BroadcastWebsocketMsg(const std::string &msg);

    static void SendWebsocketMsg(mg_connection *connection, const std::string &msg);

    static void OnHttpWebsocketEvent(mg_connection *connection, int event_type, 
                                     void *event_data, void *fn_data);

    static void HandleHttpEvent(mg_connection *connection, 
                                mg_http_message *http_req);

    static void SendHttpRsp(mg_connection *connection, const std::string &rsp);

    static void HandleWebsocketMessage(mg_connection *connection, 
                                       int event_type, mg_ws_message *ws_msg);
};


#endif //HTTPSERVER_HTTP_SERVER_H
