cmake_minimum_required(VERSION 3.5.1)
project( "httpserver" VERSION 2020 LANGUAGES CXX C)
message( "                                                              " )
message( "##############################################################" )
message( "#                                                            #" )
message( "#                 C++ Web base on Mongoose                   #" )
message( "#                      Jianfeng Zhu                          #" )
message( "#                                                            #" )
message( "##############################################################" )
message( "                                                              " )
# add_definitions("-Wall -g")
add_definitions("-Wall -O2")
# add_definitions(-std=c++14)

set(CMAKE_THIRDPARTY_DIRECTORY ${PROJECT_SOURCE_DIR}/..)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/third/jsoncpp
    ${PROJECT_SOURCE_DIR}/third/mongoose
)

add_subdirectory(${PROJECT_SOURCE_DIR}/third/jsoncpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/third/mongoose)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)