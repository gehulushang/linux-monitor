#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include <string>
#include <chrono>
#include <iostream>

class TimeUtil {
public:
    TimeUtil() {}

    ~TimeUtil() {}

    std::int64_t GetTimestamp() {
        std::chrono::milliseconds ms;
        std::chrono::nanoseconds ns;
        ns = std::chrono::system_clock::now().time_since_epoch();
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(ns);
        return ms.count();
    }

    std::string GetDatetime() {
        std::chrono::system_clock::time_point now;
        now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::string datetime = std::ctime(&now_time);
        return datetime;
    }

    std::int16_t GetYear() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return 1900 + ltm->tm_year;
    }

    std::int16_t GetMonth() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return 1 + ltm->tm_mon;
    }

    std::int16_t GetMDay() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_mday;
    }

    std::int16_t GetWDay() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_wday;
    }

    std::int16_t GetYDay() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_yday;
    }

    std::int16_t GetHour() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_hour;
    }

    std::int16_t GetMinute() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_min;
    }

    std::int16_t GetSecond() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_sec;
    }

private:
    

};

#endif