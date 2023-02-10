#include <memory>
#include <unordered_map>
#include "linux_monitor.h"
#include "module/usage.h"
#include "ipc/future_task.h"

int main(int argc, char* argv[]) {
    FutTask task;
    MonitorUsage usage(argc, argv);
    usage.PrintUsage();
    LinuxMonitor instance = LinuxMonitor::GetInstance();
    instance.Run(usage.GetParam());
    task.Run();
}