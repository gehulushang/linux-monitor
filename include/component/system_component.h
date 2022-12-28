#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "component/base_component.h"


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

class SystemComponent : public BaseComponent {
public:
    SystemComponent();

    ~SystemComponent();

    SysVersion GetSysVersion();

    void ExportInfo();

private:

    SysVersion sys_version_;

    std::int16_t parse_sys_version();

};
#endif