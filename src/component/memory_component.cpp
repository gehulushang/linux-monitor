#include "json/json.h"
#include "utils/json_util.h"
#include "component/memory_component.h"

MemoryComponent::MemoryComponent() : BaseComponent() {}

MemoryComponent::~MemoryComponent() {}

MemoryInfo MemoryComponent::GetMemoryInfo() {
    parse_memory_info();

    return memory_info_;
}

void MemoryComponent::SetMemoryInfo(MemoryInfo memory_info) {
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

void MemoryComponent::ExportInfo() {
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


std::string MemoryComponent::GetJsonInfo() {
    auto raw_men_info = R"({"mem":{"mem_used":"0", "mem_avail":"0"}, "swap":{"swap_used":"0", "swap_free":"0"}})";
    // auto json_info = R"({"result":""})";
    MemoryInfo mem = GetMemoryInfo();
    JsonAdapter jsoner;
    Json::Value json_men_info = jsoner.Str2Json(raw_men_info);
    json_men_info["mem"]["mem_used"] = std::to_string(mem.mem_used);
    json_men_info["mem"]["mem_avail"] = std::to_string(mem.mem_avail);

    json_men_info["swap"]["swap_used"] = std::to_string(mem.swap_used);
    json_men_info["swap"]["swap_free"] = std::to_string(mem.swap_free);

    std::string res;
    res = jsoner.Json2Str(json_men_info);
    return res;
}

std::int16_t MemoryComponent::parse_memory_info() {
    std::int16_t res{0};

    std::string content = futil_.GetContent(PROC_MEMINFO);
    std::vector<std::string> strs = sutil_.Split(content, "\n");

    memory_info_.mem_total = parse_memory_item(strs, KMemTotal);
    memory_info_.mem_free = parse_memory_item(strs, KMemFree);
    memory_info_.mem_avail = parse_memory_item(strs, KMemAvailable);

    memory_info_.swap_total = parse_memory_item(strs, KSwapTotal);
    memory_info_.swap_free = parse_memory_item(strs, KSwapFree);
    memory_info_.swap_used = memory_info_.swap_total - memory_info_.swap_free;

    return res;
}

std::int32_t MemoryComponent::parse_memory_item(const std::vector<std::string> rawlines, 
                                const std::string key) {
    std::int32_t res{0};
    std::string line = sutil_.GrepOne(rawlines, key);
    if (!std::isnan(res)) {
        res = sutil_.ParseUInt(line);
    }
    return res;
}