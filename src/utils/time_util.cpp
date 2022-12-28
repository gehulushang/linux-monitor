#include "utils/time_util.h"

TimeUtil::TimeUtil() {}

TimeUtil::~TimeUtil() {}

std::int64_t TimeUtil::GetTimestamp() {
    std::chrono::milliseconds ms;
    std::chrono::nanoseconds ns;
    ns = std::chrono::system_clock::now().time_since_epoch();
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(ns);
    return ms.count();
}

std::string TimeUtil::GetDatetime() {
    std::chrono::system_clock::time_point now;
    now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string datetime = std::ctime(&now_time);
    return datetime;
}

std::int16_t TimeUtil::GetYear() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}

std::int16_t TimeUtil::GetMonth() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return 1 + ltm->tm_mon;
}

std::int16_t TimeUtil::GetMDay() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return ltm->tm_mday;
}

std::int16_t TimeUtil::GetWDay() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return ltm->tm_wday;
}

std::int16_t TimeUtil::GetYDay() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return ltm->tm_yday;
}

std::int16_t TimeUtil::GetHour() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return ltm->tm_hour;
}

std::int16_t TimeUtil::GetMinute() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return ltm->tm_min;
}

std::int16_t TimeUtil::GetSecond() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return ltm->tm_sec;
}