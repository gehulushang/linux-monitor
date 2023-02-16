#ifndef MONITOR_WEB_URLS_H
#define MONITOR_WEB_URLS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "handlers/handler.h"

namespace linux_monitor {

namespace web {

typedef std::unordered_map<std::string, ReqHandler> req_handler_map;

req_handler_map handler_map {
    {"/api/test", test},
    {"/api/monitor/memory", get_memory},
};

}

}


#endif