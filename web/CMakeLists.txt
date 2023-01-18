cmake_minimum_required(VERSION 3.16)
project(httpserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(httpserver main.cpp mongoose/mongoose.c mongoose/mongoose.h httpserver/http_server.cpp httpserver/http_server.h httpserver/handler.cpp httpserver/handler.h jsoncpp/json/json.h jsoncpp/json/value.h jsoncpp/lib/json_reader.cpp jsoncpp/lib/json_writer.cpp jsoncpp/lib/json_value.cpp)