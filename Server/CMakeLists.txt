cmake_minimum_required(VERSION 3.22.1)

add_library(server
    Server.cpp
)

target_include_directories(server PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
