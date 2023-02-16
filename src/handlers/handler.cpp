//
// Created by OaixNait on 2022/7/14.
//

#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include "module/linux_monitor.h"
#include "handlers/handler.h"
#include "utils/json_util.h"

std::string test(const std::string &url, const std::string &body, 
                 mg_connection *con, OnRspCallback rsp_callback) {

    auto response = R"({"name":"James","nickname":"goodboy"})";

    JsonAdapter jsoner;

    std::cout << "key: " << jsoner.GetStringVal(jsoner.Str2Json(body), "key") << std::endl;

    rsp_callback(con, response);
    return response;
}


std::string get_memory(const std::string &url, const std::string &body, 
                 mg_connection *con, OnRspCallback rsp_callback) {
    auto response = R"({"result":""})";

    JsonAdapter jsoner;
    LinuxMonitor instance = LinuxMonitor::GetInstance();

    Json::Value json_val = jsoner.Str2Json(body);
    std::string mode = jsoner.GetStringVal(json_val, "mode");
    std::string keyword = jsoner.GetStringVal(json_val, "keyword");
    Json::Value json_resp = jsoner.Str2Json(response);

    json_resp["result"] = jsoner.Str2Json(instance.Run(keyword));

    rsp_callback(con, jsoner.Json2Str(json_resp));
    return jsoner.Json2Str(json_resp);


}