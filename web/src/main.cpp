
#include <memory>
#include "http/http_server.h"

int main(int argc, char *argv[]) {
    auto http_server = std::make_unique<HttpServer>();
    http_server->Init();
    http_server->AddHandlers();
    http_server->Start();
    return 0;
}