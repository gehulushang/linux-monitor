
#include "linux_monitor.h"

enum mode {Help, Cpu, Disk, Net, Mem, Sys, Thread, Version};
std::unordered_map<std::string, mode> modeMap {{"h", mode::Help},{"?", mode::Help},
                                        {"d", mode::Disk},{"c", mode::Cpu},
                                        {"i", mode::Net},{"m", mode::Mem},
                                        {"s", mode::Sys},{"t", mode::Thread},
                                        {"v", mode::Version},};

LinuxMonitor::LinuxMonitor() {}

LinuxMonitor::~LinuxMonitor() {}

LinuxMonitor& LinuxMonitor::GetInstance() {
    static LinuxMonitor instance;
    return instance;
}

void LinuxMonitor::Run(std::string param) {
    component_ = std::make_shared<BaseComponent>();
    
    switch(modeMap[param]){
        case mode::Mem :
            component_ = std::make_shared<MemoryComponent>();
            break;
        // case mode::Cpu :
        //     instance.component_ = std::make_shared<MemoryComponent>();
        //     break;
        case mode::Sys :
            component_ = std::make_shared<SystemComponent>();
            break;
        // case mode::Disk :
        //     instance.component_ = std::make_shared<>();
        //     break;
        case mode::Net :
            component_ = std::make_shared<NetworkComponent>();
            break;
        default :
            break;
        };
    component_->ExportInfo();
}


  