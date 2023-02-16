#ifndef JSON_UTIL_H
#define JSON_UTIL_H

#include "json/json.h"

class JsonAdapter {
public:
    JsonAdapter();

    ~JsonAdapter();

    std::string GetStringVal(const Json::Value json, const std::string key);

    Json::Value File2Json(const std::string json_path);

    bool Json2File(const Json::Value json, const std::string json_path);

    Json::Value Str2Json(const std::string &str);

    std::string Json2Str(const Json::Value json);

    std::vector<std::string> GetPrimaryKeys(const Json::Value json);

private:
    Json::Reader reader_;

};
#endif