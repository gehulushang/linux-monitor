#ifndef MEMORY_COMPONENT_H
#define MEMORY_COMPONENT_H

#include <cmath>
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "../utils/file_util.h"
#include "../utils/string_util.h"
#include "../utils/time_util.h"

#define PROC_MEMINFO "/proc/meminfo"

struct MemoryInfo {
    std::int32_t mem_total;
    std::int32_t mem_used;
    std::int32_t mem_free;
    std::int32_t mem_shared;
    std::int32_t mem_cache;
    std::int32_t mem_avail;
    std::int32_t swap_total;
    std::int32_t swap_used;
    std::int32_t swap_free;

    MemoryInfo() {
        mem_total = 0;
        mem_used = 0;
        mem_free = 0;
        mem_shared = 0;
        mem_cache = 0;
        mem_avail = 0;
        swap_total = 0;
        swap_used = 0;
        swap_free = 0;
    }

};


class MemoryComponent {
public:
    MemoryComponent() {}

    ~MemoryComponent() {}

    MemoryInfo GetMemoryInfo() {
        parse_memory_info();

        return memory_info_;
    }

    void SetMemoryInfo(MemoryInfo memory_info) {
        memory_info_.mem_total    = memory_info.mem_total;
        memory_info_.mem_used     = memory_info.mem_used;
        memory_info_.mem_free     = memory_info.mem_free;
        memory_info_.mem_shared   = memory_info.mem_shared;
        memory_info_.mem_cache    = memory_info.mem_cache;
        memory_info_.mem_avail    = memory_info.mem_avail;

        memory_info_.swap_total   = memory_info.swap_total;
        memory_info_.swap_used    = memory_info.swap_used;
        memory_info_.swap_free    = memory_info.mem_free;
    }

    void PrintInfo() {
        MemoryInfo mem = GetMemoryInfo();
        std::cout << tutil_.GetDatetime() << std::endl;
        std::cout << std::fixed << std::setw(19) << "total" 
                  << std::setw(12) << "used" 
                  << std::setw(12) << "free" 
                  << std::setw(12) << "shared" 
                  << std::setw(12) << "buff/cache" 
                  << std::setw(12) << "available" 
                  << std::endl;

        std::cout << "Mem: " << std::fixed << std::setw(14) << mem.mem_total 
                  << std::setw(12) << mem.mem_used
                  << std::setw(12) << mem.mem_free
                  << std::setw(12) << mem.mem_shared
                  << std::setw(12) << mem.mem_cache
                  << std::setw(12) << mem.mem_avail
                  << std::endl;

        std::cout << "Swap: " << std::fixed << std::setw(13) << mem.swap_total
                  << std::setw(12) << mem.swap_used
                  << std::setw(12) << mem.swap_free
                  << std::endl;
    }


private:

    FileUtil futil_;
    StringUtil sutil_;
    TimeUtil tutil_;

    MemoryInfo memory_info_;

    const std::string KMemTotal      = "MemTotal";
    const std::string KMemFree       = "MemFree";
    const std::string KMemAvailable  = "MemAvailable";
    const std::string KSwapTotal     = "SwapTotal";
    const std::string KSwapFree      = "SwapFree";

    std::int16_t parse_memory_info() {
        std::int16_t res{0};

        std::string content = futil_.GetContent(PROC_MEMINFO);
        std::vector<std::string> strs = sutil_.Split(content, "\n");

        memory_info_.mem_total = parse_memory_item(strs, KMemTotal);
        memory_info_.mem_free = parse_memory_item(strs, KMemFree);
        memory_info_.mem_avail = parse_memory_item(strs, KMemAvailable);

        memory_info_.swap_total = parse_memory_item(strs, KSwapTotal);
        memory_info_.swap_free = parse_memory_item(strs, KSwapFree);

        return res;
    }

    std::int32_t parse_memory_item(const std::vector<std::string> rawlines, 
                                   const std::string key) {
        std::int32_t res{0};
        std::string line = sutil_.GrepOne(rawlines, key);
        if (!std::isnan(res)) {
            res = sutil_.ParseUInt(line);
        }
        return res;
    }


};

#endif

int main() {
    MemoryComponent component;

    component.PrintInfo();

}