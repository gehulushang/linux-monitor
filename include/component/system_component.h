#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "model/model.h"
#include "model/constant.h"
#include "component/base_component.h"

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