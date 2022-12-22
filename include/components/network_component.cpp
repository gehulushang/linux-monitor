#ifndef NETWORK_COMPONENT_H
#define NETWORK_COMPONENT_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "../utils/file_util.h"
#include "../utils/string_util.h"
#include "../utils/time_util.h"

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


class NetworkComponent {
public:
    NetworkComponent() {}

    ~NetworkComponent() {}

    NetworkInfo GetNetworkInfo() {
        parse_network_info();

        return network_info_;
    }


    void PrintInfo() {
        NetworkInfo info = GetNetworkInfo();
        std::cout << tutil_.GetDatetime() << std::endl;
     
        std::cout << "Total:" << std::endl;
        std::cout << "Details:" << std::endl;
        for (auto item : info.cards) {
            std::cout << item.name << ": flags=" << std::endl;
        }

    }

private:

    FileUtil futil_;
    StringUtil sutil_;
    TimeUtil tutil_;

    NetworkInfo network_info_;

    std::int16_t parse_network_info() {
        std::int16_t res{0};
        std::vector<std::string> strs = futil_.ListDir(SYS_CLS_NET);

        for (auto item : strs) {
            NetcardInfo card;
            card.name = item;


            network_info_.cards.push_back(card);
        }
        return res;
    }

};
#endif

int main() {
    NetworkComponent component;

    component.PrintInfo();

}