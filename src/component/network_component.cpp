#include "component/network_component.h"


NetworkComponent::NetworkComponent(): BaseComponent() {}

NetworkComponent::~NetworkComponent() {}

NetworkInfo NetworkComponent::GetNetworkInfo() {
    parse_network_info();

    return network_info_;
}


void NetworkComponent::ExportInfo() {
    NetworkInfo info = GetNetworkInfo();
    std::cout << tutil_.GetDatetime() << std::endl;
    
    std::cout << "Total:" << std::endl;
    std::cout << "Details:" << std::endl;
    for (auto item : info.cards) {
        std::cout << item.name << ": flags=" << std::endl;
    }

}


std::int16_t NetworkComponent::parse_network_info() {
    std::int16_t res{0};
    std::vector<std::string> strs = futil_.ListDir(SYS_CLS_NET);

    for (auto item : strs) {
        NetcardInfo card;
        card.name = item;


        network_info_.cards.push_back(card);
    }
    return res;
}