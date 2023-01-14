#ifndef LINUX_MONITOR_H
#define LINUX_MONITOR_H

#include <memory>
#include <unordered_map>
#include "module/usage.h"
#include "component/base_component.h"
#include "component/memory_component.h"
#include "component/system_component.h"
#include "component/network_component.h"


class LinuxMonitor {
public:
    LinuxMonitor();

    ~LinuxMonitor();

    static LinuxMonitor& GetInstance();

    void Run(std::string param);

private:

    std::shared_ptr<BaseComponent> component_;


};
#endif