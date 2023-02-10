//
// Created by OaixNait on 2022/7/14.
//

#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include "handlers/handler.h"
#include "json/json.h"



class JsonAdapter {
public:
    JsonAdapter() {}

    ~JsonAdapter() = default;

    std::string GetStringVal(const Json::Value json, const std::string key) {
        std::string result{""};
        try {
            result = json[key].asString();
        } catch (std::exception e) {
            std::cout << "unmatched key or wrong return type" << std::endl;
        } catch (...) {
            std::cout << "internal error" << std::endl;
        }
        return result;
    }

    Json::Value File2Json(const std::string json_path) {
        std::ifstream ifs(json_path, std::ifstream::in);
        Json::Value json;
        if (!ifs.is_open()) {
            std::cout << "open " << json_path << " failed" << std::endl;
            ifs.close();
            return json;
        }
        if (!reader_.parse(ifs, json, false)) {
            std::cout << "parse failed " << std::endl;
        }
        ifs.close();
        return json;
    }

    bool Json2File(const Json::Value json, const std::string json_path) {
        bool result = false;
        std::string str = Json2Str(json);
        std::ofstream ofs(json_path);
        if (!ofs.is_open()) {
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

    std::string Json2Str(const Json::Value json) {
        Json::StreamWriterBuilder builder;
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        std::ostringstream ss;
        writer->write(json, &ss);
        return ss.str();
    }

    std::vector<std::string> GetPrimaryKeys(const Json::Value json) {
        std::vector<std::string> keys;
        Json::Value::Members members = json.getMemberNames();
        for (auto it = members.begin(); it != members.end(); ++ it) {  
            keys.push_back(*it);
        }
        return keys;
    }

    // template<typename T> bool Serialize(T& obj, const std::string& json_str) {


    // }

    // template<typename T> bool Deserialize(T& obj, const std::string& json_str) {


    // }

private:
    Json::Reader reader_;
};


std::string test(const std::string &url, const std::string &body, 
                 mg_connection *con, OnRspCallback rsp_callback) {

    auto response = R"({"name":"James","nickname":"goodboy"})";

    JsonAdapter jsoner;

    std::cout << "key: " << jsoner.GetStringVal(jsoner.Str2Json(body), "key") << std::endl;

    // rsp_callback(con, jsoner.Json2Str(jsoner.File2Json("test.json")));
    rsp_callback(con, response);
    return response;
}
