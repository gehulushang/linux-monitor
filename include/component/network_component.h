#ifndef NETWORK_COMPONENT_H
#define NETWORK_COMPONENT_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "model/model.h"
#include "model/constant.h"
#include "component/base_component.h"


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