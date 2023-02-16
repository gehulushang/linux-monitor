#ifndef HTTP_CONFIGURATION_H
#define HTTP_CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>

struct WebConfig {
    std::string port_;
    std::int8_t debug_level_;
    std::string homepage_;
};

struct MonitorConfig {

};

class HttpConfig {
public:
    HttpConfig();

    ~HttpConfig();

    bool Init();

    static HttpConfig& GetInstance();

    std::string GetPort();

    std::string GetHomepage();

    std::string GetDebugLevelStr();

    void SetPort(std::string port);

    void SetHomepage(std::string homepage);

    void SetDebugLevel(std::int8_t debug_level);

private:

    std::string port_;
    std::int8_t debug_level_;
    std::string homepage_;

};
#endif