#ifndef MEMORY_COMPONENT_H
#define MEMORY_COMPONENT_H

#include <cmath>
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "model/model.h"
#include "model/constant.h"
#include "component/base_component.h"


class MemoryComponent : public BaseComponent {
public:
    MemoryComponent();

    ~MemoryComponent();

    MemoryInfo GetMemoryInfo();

    void SetMemoryInfo(MemoryInfo memory_info);

    void ExportInfo();

    std::string GetJsonInfo();


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