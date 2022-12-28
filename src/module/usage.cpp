

#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

#include "module/usage.h"

int MonitorUsage::GetParamsCnt() {
    return params_cnt_;
}

std::vector<std::string> MonitorUsage::GetParams() {
    return raw_params_;
}

std::int16_t MonitorUsage::ParseParams(const int argc, char* argv[]) {
    std::int16_t res{0};
    reset();
    params_cnt_ = argc;
    for (int i = 0; i < argc; i++) {
        raw_params_.push_back(argv[i]);
    }
    return res;
}

std::int16_t MonitorUsage::PrintUsage(void) {
    std::int16_t res{0};
    extract_key_param();

    if (param_valid_) {
        Usage(param_);
        return res;
    }
    
    putil_.PrintError("Can not parse param: ", raw_param_);
    putil_.PrintHint("Please read following usages: ");
    Usages();
    return res;
}

void MonitorUsage::Usage(const std::string param) {
    putil_.PrintInfo("Command line with -", param, " will get ", 
                        kParamsMap[param], " information");
}

void MonitorUsage::Usages() {
    std::cout << "System Monitor\n" << std::endl;

    for (auto it = kParamsMap.begin(); it != kParamsMap.end(); it++) { 
        std::cout << "  -" << it->first << "|--" 
                  << std::left << std::setw(15) << it->second
                  << "for " << it->second << " info" << std::endl;
    }

}

void MonitorUsage::reset() {
    param_ = "";
    raw_param_ = "";
    param_valid_ = false;
    params_cnt_ = 0;
    raw_params_.clear();
}

std::int16_t MonitorUsage::extract_key_param() {
    std::int16_t res{0};
    if (params_cnt_ >= kParamIdx) {
        param_ = parse_key_param(raw_params_[kParamIdx-1]);
    }
    return res;
}

std::string MonitorUsage::parse_key_param(std::string str) {
    std::string res{""};
    param_valid_ = is_param_valid(str);
    if (param_valid_) {
        res = str.substr(1, 1);
    }
    return res;
}

bool MonitorUsage::is_param_valid(std::string &str) {
    bool valid{false};
    raw_param_ = str;
    sutil_.Replace(str, "--", "-");
    if (sutil_.StartsWith(str, "-") && str.size() >= kMinParamLength) {
        for (auto it = kParamsMap.begin(); it != kParamsMap.end(); it++) {
            sutil_.Replace(str, it->second, it->first);
            if (str.substr(1, 1) == it->first) {
                valid = true;
                break;
            }
        }
    }
    return valid;
}