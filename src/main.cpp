
#include "module/usage.h"

int main(int argc, char* argv[]) {
    MonitorUsage usage(argc, argv);
    usage.PrintUsage();
}
  