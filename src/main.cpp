#include <memory>
#include "module/usage.h"
#include "component/base_component.h"
#include "component/memory_component.h"
#include "component/system_component.h"
#include "component/network_component.h"

class LinuxMonitor {
public:
    LinuxMonitor() {}

    ~LinuxMonitor() {}

    static LinuxMonitor& GetInstance() {
        static LinuxMonitor instance;
        return instance;
    }

    void Run() {
        LinuxMonitor instance = LinuxMonitor::GetInstance();
        instance.component_ = std::make_shared<NetworkComponent>();
        instance.component_->ExportInfo();
    }

private:

    std::shared_ptr<BaseComponent> component_;


};

int main(int argc, char* argv[]) {
    MonitorUsage usage(argc, argv);
    usage.PrintUsage();
    LinuxMonitor instance = LinuxMonitor::GetInstance();
    instance.Run();
}
  