//
// Created by OaixNait on 2022/7/14.
//

#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include "handler.h"
#include "../jsoncpp/json/json.h"



class JsonAdapter {
public:
    JsonAdapter() {}

    ~JsonAdapter() = default;

    // std::string GetStringVal(const std::string key) {
    //     std::string result{""};
    //     try {
    //         result = root_[key].asString();
    //     } catch (std::exception e) {
    //         std::cout << "unmatched key or wrong return type" << std::endl;
    //     } catch (...) {
    //         std::cout << "internal error" << std::endl;
    //     }
    //     return result;
    // }

    Json::Value File2Json(const std::string json_path) {
        std::ifstream ifs(json_path, std::ifstream::in);
        Json::Value json;
        if (!ifs.is_open()) {
            std::cout << "open " << json_path << " failed" << std::endl;
            ifs.close();
            return json;
        }
        Json::Reader reader;
        if (!reader_.parse(ifs, json, false)) {
            std::cout << "parse failed " << std::endl;
        }
        ifs.close();
        return json;
    }

    bool Json2File(Json::Value json, const std::string json_path) {
        bool result = false;
        std::string str = Json2Str(json);
        std::ofstream ofs(json_path);
        if(!ofs.is_open()) {
            return result;
        }
        ofs << str;
        ofs.close();
        result = true;
        return result;
    }

    Json::Value Str2Json(const std::string &str) {
        Json::Value json;
        bool result = false;
        if (reader_.parse(str, json) && !str.empty()) {
            result = true;
        }
        return json;
    }

    std::string Json2Str(Json::Value json) {
        Json::StreamWriterBuilder writerBuilder;
        std::unique_ptr<Json::StreamWriter> json_write(writerBuilder.newStreamWriter());
        std::ostringstream ss;
        json_write->write(json, &ss);
        return ss.str();
    }

    std::vector<std::string> GetPrimaryKeys(Json::Value json) {
        std::vector<std::string> keys;
        Json::Value::Members members = json.getMemberNames();
        for (auto it = members.begin(); it != members.end(); ++ it) {  
            keys.push_back(*it);
        }
        return keys;
    }

private:
    Json::Reader reader_;
};


std::string test(const std::string &url, const std::string &body, 
                 mg_connection *con, OnRspCallback rsp_callback) {

    auto response = R"({"name":"James","nickname":"goodboy"})";

    JsonAdapter jsoner;
    Json::Value json = jsoner.Str2Json(body);

    std::cout << "key: " << json["key"].asString() << std::endl;

    std::string json_path{"test.json"};

    rsp_callback(con, jsoner.Json2Str(jsoner.File2Json(json_path)));
    for (auto item : jsoner.GetPrimaryKeys(jsoner.File2Json(json_path))) {
        std::cout << item << std::endl;
    }

    std::cout << jsoner.File2Json(json_path).isNull() << std::endl;
    std::cout << jsoner.Str2Json(response).isNull() << std::endl;

    return response;
}

#include "handler.h"
