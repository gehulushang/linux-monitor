#include "utils/string_util.h"

StringUtil::StringUtil() {}

StringUtil::~StringUtil() {}

std::int16_t StringUtil::Replace(std::string& raw_str, const std::string oldvalue, 
                                            const std::string newvalue) {
    std::int16_t result{0};

    while(raw_str.find(oldvalue) != std::string::npos) {
        int pos = raw_str.find(oldvalue);
        raw_str.replace(pos, oldvalue.size(), newvalue);
    }
    return result;
}

std::vector<std::string> StringUtil::Split(const std::string raw_str, 
                                const std::string seperator) {
    std::vector<std::string> results;

    std::string::size_type len, sep_pos;
    sep_pos = raw_str.find(seperator);
    len = 0;
    while (std::string::npos != sep_pos) {
        results.push_back(raw_str.substr(len, sep_pos - len));
        len = sep_pos + seperator.size();
        sep_pos = raw_str.find(seperator, len);
    }
    if (len != raw_str.length())
        results.push_back(raw_str.substr(len));

    return results;
}

std::string StringUtil::GrepOne(const std::vector<std::string> strs, 
                    const std::string pattern) {
    std::string result{""};
    for (auto item : strs) {
        if (std::string::npos != item.find(pattern)) {
            result = item;
            break;
        }
    }
    return result;
}

std::vector<std::string> StringUtil::GrepAll(const std::vector<std::string> strs, 
                                    const std::string pattern) {
    std::vector<std::string> results;
    for (auto item : strs) {
        if (std::string::npos != item.find(pattern)) {
            results.push_back(item);
        }
    }
    return results;
}

std::vector<std::string> StringUtil::Egrep(const std::vector<std::string> strs, 
                                    const std::string pattern) {
    std::vector<std::string> results;
    for (auto item : strs) {
        if (std::string::npos == item.find(pattern)) {
            results.push_back(item);
        }
    }
    return results;
}

bool StringUtil::EndsWith(const std::string raw_str, const std::string postfix) {
    bool res = false;
    int pos = raw_str.find(postfix);
    int size_diff = raw_str.size() - postfix.size();
    if (pos >= 0 && pos == size_diff) {
        res = true;
    }
    return res;
}

bool StringUtil::StartsWith(const std::string raw_str, const std::string prefix) {
    bool res = true;
    int pos = raw_str.find(prefix);
    if (pos != 0) {
        res = false;
    }
    return res;
}

std::vector<std::uint64_t> StringUtil::ParseUInts(const std::string raw_str) {
    std::vector<std::uint64_t> res;

    int len = raw_str.size();
    int i = 0, j = 0;
    while (i < len) {
        if (raw_str[i] >= '0' && raw_str[i] <= '9') {
            j = i;
            int sublen = 0;
            while (raw_str[i] >= '0' && raw_str[i] <= '9') {
                i ++;
                sublen ++;
            }
            std::string sub_str = raw_str.substr(j, sublen);
            std::uint64_t num = 0.0;
            std::stringstream ssin(sub_str);
            ssin >> num;
            res.push_back(num);
        } else {
            i ++;
        }
    }
    return res;
}

std::uint64_t StringUtil::ParseUInt(const std::string raw_str) {
    std::uint64_t res;

    int len = raw_str.size();
    int i = 0, j = 0;
    while (i < len) {
        if (raw_str[i] >= '0' && raw_str[i] <= '9') {
            j = i;
            int sublen = 0;
            while (raw_str[i] >= '0' && raw_str[i] <= '9') {
                i ++;
                sublen ++;
            }
            std::string sub_str = raw_str.substr(j, sublen);
            std::stringstream ssin(sub_str);
            ssin >> res;
            break;
        } else {
            i ++;
        }
    }
    return res;
}

std::vector<double> StringUtil::ParseNums(const std::string raw_str) {
    std::vector<double> res;
    std::vector<std::string> strs = Split(raw_str, " ");
    for (auto item : strs) {
        if (IsNum(item)) {
            res.push_back(ToNum(item));
        }
    }
    return res;
}

// double StringUtil::ParseNum(const std::string raw_str) {
//     double res;
//     std::vector<std::string> strs = Split(raw_str, " ");
//     for (auto item : strs) {
//         if (IsNum(item)) {
//             res = ToNum(item);
//             break;
//         }
//     }
//     return res;
// }

bool StringUtil::IsNum(const std::string raw_str) {
    bool res = true;
    std::stringstream ssin(raw_str);  
    double dou;  
    char ch;  
    if (!(ssin >> dou) || (ssin >> ch)) {
        res = false;
    }

    return res;
}

double StringUtil::ToNum(const std::string raw_str) {
    double res{0.0};
    std::stringstream ssin(raw_str);  
    if (IsNum(raw_str)) {
        ssin >> res;
    }
    return res;
}

std::string StringUtil::rm_left_char(const std::string raw_str) {
    std::string res{""};
    int str_len = raw_str.size();
    int idx = 0;
    while (idx < str_len) {
        if (raw_str[idx] >= '0' && raw_str[idx] <= '9') {
            break;
        }
        idx ++;
    }
    res = raw_str.substr(idx, str_len - idx);
    return res;
}

std::string StringUtil::rm_right_char(const std::string raw_str) {
    std::string res{""};

    int str_len = raw_str.size();
    int idx = str_len - 1;
    while (idx >= 0) {
        if (raw_str[idx] >= '0' && raw_str[idx] <= '9') {
            break;
        }
        idx --;
    }
    res = raw_str.substr(0, idx + 1);
    return res;
}

std::string StringUtil::rm_side_char(const std::string raw_str) {
    std::string res{""};
    res = rm_right_char(rm_left_char(raw_str));
    return res;
}