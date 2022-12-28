#include "component/system_component.h"

SystemComponent::SystemComponent(): BaseComponent() {}

SystemComponent::~SystemComponent() {}

SysVersion SystemComponent::GetSysVersion() {
    parse_sys_version();

    return sys_version_;
}

void SystemComponent::ExportInfo() {
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



std::int16_t SystemComponent::parse_sys_version() {
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
