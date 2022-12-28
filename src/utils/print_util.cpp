#include "utils/print_util.h"

PrintUtil::PrintUtil(): fixed_(false), precision_(DEFAULT_PRECISION), width_(0) {}

PrintUtil::~PrintUtil() {}

void PrintUtil::SetW(const int width) {
    width_ = width;
}

void PrintUtil::SetPrecision(const int precision) {
    precision_ = precision;
}

void PrintUtil::SetFixed(bool fixed) {
    fixed_ = fixed;
}

void PrintUtil::prefix(const std::string prefix) {
    std::cout << prefix;
    if (fixed_) {
        std::cout << std::fixed;
    }
    std::cout << std::setw(width_) << std::setprecision(precision_);
}