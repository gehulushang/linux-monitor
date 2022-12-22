#include <fstream>
#include <iostream>
#include <sstream>

#include "model/model.h"


#define PROC_VERSION "/proc/version"
#define PROC_CPUINFO "/proc/cpuinfo"
#define PROC_MEMINFO "/proc/meminfo"

std::string getRawProcInfo(const std::string proc) {
    std::ifstream ifs(proc.c_str(), std::ios::in);

    if (!ifs.is_open()) {
        std::cout << "open " << proc << " failed " << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string raw_info(buffer.str());
    ifs.close();
    return raw_info;

}

void parseDiskInfo() {

    return ;
}

void parseProcessInfo() {

    return ;
}

void parseNetInfo() {

    return ;
}

void parseMemInfo() {
    std::string raw_info(getRawProcInfo(PROC_MEMINFO));
    return ;
}

void parseCpuInfo() {
    std::string raw_info(getRawProcInfo(PROC_CPUINFO));
    return ;
}

void parseProcVersion() {
    std::string raw_info(getRawProcInfo(PROC_VERSION));
	int version_pos = raw_info.rfind("Linux version");
	int gcc_pos = raw_info.rfind("gcc version");
	int time_pos = raw_info.rfind("SMP");

    std::cout << raw_info.substr(version_pos, gcc_pos) << std::endl;
	std::cout << raw_info.substr(gcc_pos, time_pos) << std::endl;
    std::cout << raw_info.substr(time_pos, raw_info.size()) << std::endl;
    return;
}

static void usage(void) {
    std::cout << "System Monitor\n" << std::endl;
    
    std::cout << 
        "  -c|--cpu                 for cpu info\n" << 
        "  -s|--sys                 for sys info\n" << 
        "  -m|--mem                 for mem info\n" << 
        "  -t|--top                 for threads info\n" << 
        "  -i|--net                 for net info\n" << 
        "  -?|-h|--help             This information.\n" << 
        "  -V|--version             version.\n"
        << std::endl;
};

int main() {
    /* daemon */
    // daemon(1, 0); 
    // usage();

    parseProcVersion();
}
  