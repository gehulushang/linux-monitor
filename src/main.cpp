#include <memory>
#include <unordered_map>
#include "linux_monitor.h"
#include "module/usage.h"

int main(int argc, char* argv[]) {
    MonitorUsage usage(argc, argv);
    usage.PrintUsage();
    LinuxMonitor instance = LinuxMonitor::GetInstance();
    instance.Run(usage.GetParam());
}