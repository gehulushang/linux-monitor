#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class StringUtil {
public:
    StringUtil();

    ~StringUtil();

    std::int16_t Replace(std::string& raw_str, const std::string oldvalue, 
                                               const std::string newvalue);

    std::vector<std::string> Split(const std::string raw_str, 
                                   const std::string seperator);

    std::string GrepOne(const std::vector<std::string> strs, 
                        const std::string pattern);

    std::vector<std::string> GrepAll(const std::vector<std::string> strs, 
                                     const std::string pattern);

    std::vector<std::string> Egrep(const std::vector<std::string> strs, 
                                     const std::string pattern);

    bool EndsWith(const std::string raw_str, const std::string postfix);

    bool StartsWith(const std::string raw_str, const std::string prefix);

    std::vector<std::uint64_t> ParseUInts(const std::string raw_str);

    std::uint64_t ParseUInt(const std::string raw_str);

    std::vector<double> ParseNums(const std::string raw_str);

    // double ParseNum(const std::string raw_str);

    bool IsNum(const std::string raw_str);

    double ToNum(const std::string raw_str);

private:

    std::string rm_left_char(const std::string raw_str);

    std::string rm_right_char(const std::string raw_str);

    std::string rm_side_char(const std::string raw_str);

};

#endif



