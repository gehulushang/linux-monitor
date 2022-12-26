#ifndef MONITOR_USAGE_H
#define MONITOR_USAGE_H

#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

#include "../utils/string_util.h"
#include "../utils/print_util.h"

static std::map<std::string, std::string> kParamsMap{
    {"c","cpu"},
    {"s","sys"},
    {"m","mem"},
    {"d","disk"},
    {"t","thread"},
    {"i","net"},
    {"h","help"},
    {"?","help"},
    {"v","version"},
};

class MonitorUsage {
public:
    MonitorUsage(int argc, char* argv[]) {
        ParseParams(argc, argv);
    }

    ~MonitorUsage() {
        reset();
    }

    int GetParamsCnt();

    std::vector<std::string> GetParams();

    std::int16_t ParseParams(const int argc, char* argv[]);

    std::int16_t PrintUsage();

    void Usage(const std::string param);

    static void Usages();

private:

    PrintUtil putil_;
    StringUtil sutil_;

    std::string param_;
    std::string raw_param_;
    int params_cnt_;
    bool param_valid_;
    std::vector<std::string> raw_params_;
    const static int kParamIdx{2};
    const static int kMinParamLength{2};

    void reset();

    std::int16_t extract_key_param();

    std::string parse_key_param(std::string str);

    bool is_param_valid(std::string &str);

};
#endif