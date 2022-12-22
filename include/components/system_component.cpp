#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "../utils/file_util.h"
#include "../utils/string_util.h"
#include "../utils/time_util.h"

#define PROC_VERSION    "/proc/version"
#define LSB_RELEASE     "/etc/lsb-release"
#define REDHAT_RELEASE  "/etc/redhat-release"
#define ETC_HOSTNAME    "/etc/hostname"

struct SysDistributor {
    std::string id;
    std::string description;
    std::string release_version;
    std::string code_name;
};

struct SysVersion {
    std::string os;
    std::string kernel_version;
    std::string gcc_version;
    std::string time_info;
    std::string hostname;
    SysDistributor distributor;
};

class SystemComponent {
public:
    SystemComponent() {}

    ~SystemComponent() {}

    SysVersion GetSysVersion() {
        parse_sys_version();

        return sys_version_;
    }

    void PrintInfo() {
        SysVersion sversion = GetSysVersion();
        std::cout << tutil_.GetDatetime() << std::endl;

        std::cout << std::setw(10) << "System"     << std::endl;
        std::cout << std::setw(12) << "os: "       << sversion.os << std::endl;
        std::cout << std::setw(12) << "kernel: "   << sversion.kernel_version << std::endl;
        std::cout << std::setw(12) << "gcc: "      << sversion.gcc_version << std::endl;
        std::cout << std::setw(12) << "time: "     << sversion.time_info << std::endl;
        std::cout << std::setw(12) << "hostname: " << sversion.hostname << std::endl;
        
        std::cout << "----------------------------" << std::endl;

        std::cout << std::setw(10) << "Distributor" << std::endl;
        std::cout << std::setw(12) << "id: "        << sversion.distributor.id << std::endl;
        std::cout << std::setw(12) << "kernel: "    << sversion.distributor.description << std::endl;
        std::cout << std::setw(12) << "version: "   << sversion.distributor.release_version << std::endl;
        std::cout << std::setw(12) << "codename: "  << sversion.distributor.code_name << std::endl;
    }

private:

    FileUtil futil_;
    TimeUtil tutil_;
    StringUtil sutil_;

    SysVersion sys_version_;

    std::int16_t parse_sys_version() {
        std::int16_t res{0};
        std::string raw_proc_version = futil_.GetContent(PROC_VERSION);

        std::vector<std::string> strs = sutil_.Split(raw_proc_version, " ");

        if (strs.size() > 6) {
            sys_version_.os                 = strs[0];
            sys_version_.kernel_version     = strs[2];
            sys_version_.gcc_version        = strs[6];
        }
        return res;
    }

};
#endif

int main() {
    SystemComponent component;

    component.PrintInfo();
}