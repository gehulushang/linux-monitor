#ifndef PRINT_UTIL_H
#define PRINT_UTIL_H

#include <string>
#include <iomanip>
#include <iostream>

#define DEFAULT_PRECISION 6
#define ERROR_PREFIX      "\033[0m\033[1;31m"
#define INFO_PREFIX       "\033[0m\033[1;32m"
#define HINT_PREFIX       "\033[0m\033[1;34m"

class PrintUtil {
public:
    PrintUtil(): fixed_(false), precision_(DEFAULT_PRECISION), width_(0) {}

    ~PrintUtil() {}

    void SetW(const int width) {
        width_ = width;
    }

    void SetPrecision(const int precision) {
        precision_ = precision;
    }

    void SetFixed(bool fixed) {
        fixed_ = fixed;
    }

    template <typename ...Args>
        void PrintPlain(const Args& ...args) {
            print_impl(args...);
            std::cout << std::endl;
        }

    template <typename ...Args>
        void PrintError(const Args& ...args) {
            prefix(ERROR_PREFIX);
            print_impl(args...);
            std::cout << "\033[0m" << std::endl;
        }

    template <typename ...Args>
        void PrintInfo(const Args& ...args) {
            prefix(INFO_PREFIX);
            print_impl(args...);
            std::cout << "\033[0m" << std::endl;
        }

    template <typename ...Args>
        void PrintHint(const Args& ...args) {
            prefix(HINT_PREFIX);
            print_impl(args...);
            std::cout << "\033[0m" << std::endl;
        }


private:
    template <typename Arg0>
        void print_impl(const Arg0& arg0) {
            std::cout << arg0;
        }

    template <typename Arg0, typename ...Args>
        void print_impl(const Arg0& arg0, const Args& ...args) {
            print_impl(arg0);
            print_impl(args...);
        }
    
    void prefix(const std::string prefix) {
        std::cout << prefix;
        if (fixed_) {
            std::cout << std::fixed;
        }
        std::cout << std::setw(width_) << std::setprecision(precision_);
    }

    bool fixed_;
    int precision_;
    int width_;

};
#endif


int main() {
    PrintUtil util;
    std::cout << std::fixed;
    util.SetW(20);
    util.PrintHint(1.23234223432424);

}