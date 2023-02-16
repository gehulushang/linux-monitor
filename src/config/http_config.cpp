
#include <iostream>
#include "json/json.h"
#include "config/http_config.h"

HttpConfig::HttpConfig() {
    port_ = ":7999";
    debug_level_ = 2;
    homepage_ = "./index";
}

HttpConfig::~HttpConfig() {}

bool HttpConfig::Init() {
    bool result{true};
    std::string json_path{"../conf/linux_monitor.json"};
    std::ifstream ifs(json_path, std::ifstream::in);
    Json::Value json_val;
    if (!ifs.is_open()) {
        std::cout << "open " << json_path << " failed" << std::endl;
        ifs.close();
        return false;
    }
    Json::Reader reader;
    if (!reader.parse(ifs, json_val, false)) {
        std::cout << "parse failed " << std::endl;
    }
    ifs.close();
    auto raw_port = json_val["http"]["port"].asString();
    auto raw_homepage = json_val["http"]["homepage"].asString();
    auto raw_debug_level = json_val["http"]["debug_level"].asInt();
    SetPort(raw_port);
    SetHomepage(raw_homepage);
    SetDebugLevel(raw_debug_level);
    return result;
}

HttpConfig& HttpConfig::GetInstance() {
    static HttpConfig instance;
    instance.Init();
    return instance;
}


std::string HttpConfig::GetPort() {
    return port_;
}

std::string HttpConfig::GetHomepage() {
    return homepage_;
}


std::string HttpConfig::GetDebugLevelStr() {
    return std::to_string(debug_level_);
}

void HttpConfig::SetPort(std::string port) {
    port_ = ":" + port;
}

void HttpConfig::SetHomepage(std::string homepage) {
    homepage_ = "./" + homepage;
}

void HttpConfig::SetDebugLevel(std::int8_t debug_level) {
    debug_level_ = debug_level;
}