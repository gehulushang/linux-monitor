#ifndef MEMORY_COMPONENT_H
#define MEMORY_COMPONENT_H

#include <cmath>
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "component/base_component.h"

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


class MemoryComponent : public BaseComponent {
public:
    MemoryComponent();

    ~MemoryComponent();

    MemoryInfo GetMemoryInfo();

    void SetMemoryInfo(MemoryInfo memory_info);

    void ExportInfo();


private:

    MemoryInfo memory_info_;

    const std::string KMemTotal      = "MemTotal";
    const std::string KMemFree       = "MemFree";
    const std::string KMemAvailable  = "MemAvailable";
    const std::string KSwapTotal     = "SwapTotal";
    const std::string KSwapFree      = "SwapFree";

    std::int16_t parse_memory_info();

    std::int32_t parse_memory_item(const std::vector<std::string> rawlines, 
                                   const std::string key);


};

#endif