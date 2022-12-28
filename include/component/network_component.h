#ifndef NETWORK_COMPONENT_H
#define NETWORK_COMPONENT_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "component/base_component.h"

#define PROC_NET "/proc/net"
#define SYS_CLS_NET "/sys/class/net"

struct NetcardInfo {
    std::int16_t status;
    std::string name;
    std::string inet;
    std::string netmask;
    NetcardInfo() {
        status = 0;
    }
};

struct NetworkInfo {
    bool alive;
    bool networking;
    std::vector<std::int32_t> used_ports;
    std::vector<NetcardInfo> cards;
};


class NetworkComponent : public BaseComponent {
public:
    NetworkComponent();

    ~NetworkComponent();

    NetworkInfo GetNetworkInfo();


    void ExportInfo();

private:

    NetworkInfo network_info_;

    std::int16_t parse_network_info();

};
#endif