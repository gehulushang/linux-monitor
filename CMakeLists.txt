cmake_minimum_required(VERSION 3.5.1)
project( "system monitor" VERSION 2020 LANGUAGES CXX )
message( "                                                              " )
message( "##############################################################" )
message( "#                                                            #" )
message( "#                  Linux System Monitor                      #" )
message( "#                      Jianfeng zhu                          #" )
message( "#                                                            #" )
message( "##############################################################" )
message( "                                                              " )
# add_definitions("-Wall -g")
add_definitions("-Wall -O2")
# add_definitions(-std=c++14)

# set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-7/root/bin/g++")
set(CMAKE_THIRDPARTY_DIRECTORY ${PROJECT_SOURCE_DIR}/..)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
link_directories(
)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)