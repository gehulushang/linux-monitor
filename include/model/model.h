#include <string>
#include <vector>

struct SysDistributor {
    std::string id;
    std::string description;
    std::string release_version;
    std::string code_name;
};

struct SysVersion {
    std::string os;
    std::string kernel_version;
    std::string gcc_version;
    std::string time_info;
    std::string hostname;
    SysDistributor distributor;
};

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
};

struct ProcessorInfo {
    std::int32_t index;
    std::string vendor_id;
    std::int32_t cou_family;
    std::int32_t model;
    std::string model_name; 
    std::int32_t stepping;
    std::string microcode;
    float frequency;                // MHz
    std::int32_t cache_size;        // KB
    std::int32_t physical_id;
    std::int32_t siblings;
    std::int32_t core_id;
    std::int32_t cpu_cores;

};


struct CPUInfo {
    
    std::vector<ProcessorInfo> processors;
};

struct DeviceIOInfo {
    std::string name;
    float tps;
    float kb_read_rate;
    float kb_wrtn_rate;
    std::int16_t kb_read;
    std::int16_t kb_wrtn;
};

struct SysIOInfo {
    float user_pct;
    float nice_pct;
    float system_pct;
    float iowait_pct;
    float steal_pct;
    float idle_pct;
    std::vector<DeviceIOInfo> deviceIO_list;
};

struct NetcardInfo {
    std::int16_t status;
    std::string name;
    std::string inet;
    std::string netmask;
};

struct NetworkInfo {
    bool alive;
    bool networking;
    std::vector<std::int32_t> used_ports;
    std::vector<NetcardInfo> cards;
};