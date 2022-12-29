
#include "model/model.h"

SysDistributor::SysDistributor():
    id{""}, description{""}, release_version{""}, code_name{""} {}

SysVersion::SysVersion():
    os{""}, kernel_version{""}, gcc_version{""}, time_info{""}, hostname{""} {}

MemoryInfo::MemoryInfo():  
    mem_total{0}, mem_used{0}, mem_free{0},
    mem_shared{0}, mem_cache{0}, mem_avail{0},
    swap_total{0}, swap_used{0}, swap_free{0} {}

// ProcessorInfo::ProcessorInfo(): 
//     index{0}, vendor_id{""}, cou_family{0}, 
//     model{0}, model_name{""}, stepping{0},
//     microcode{""}, frequency{0.0}, cache_size{0},
//     physical_id{0}, siblings{0}, core_id{0}, cpu_cores{0} {}

// DeviceIOInfo::DeviceIOInfo(): 
//     name{""}, tps{0.0}, kb_read_rate{0.0}, 
//     kb_wrtn_rate{0.0}, kb_read{0}, kb_wrtn{0} {}

// SysIOInfo::SysIOInfo(): 
//     user_pct{0.0}, nice_pct{0.0}, system_pct{0.0},
//     iowait_pct{0.0}, steal_pct{0.0}, idle_pct{0.0} {}

NetcardInfo::NetcardInfo():
    status{0}, name{""}, inet{""}, netmask{""} {}

NetworkInfo::NetworkInfo():
    alive{false}, networking{false} {}