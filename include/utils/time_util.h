#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include <string>
#include <chrono>
#include <iostream>

class TimeUtil {
public:
    TimeUtil();

    ~TimeUtil();

    std::int64_t GetTimestamp();

    std::string GetDatetime();

    std::int16_t GetYear();

    std::int16_t GetMonth();

    std::int16_t GetMDay();

    std::int16_t GetWDay();

    std::int16_t GetYDay();

    std::int16_t GetHour();

    std::int16_t GetMinute();

    std::int16_t GetSecond();

private:
    

};

#endif