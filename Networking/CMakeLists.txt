cmake_minimum_required(VERSION 3.22.1)

add_library(libNetworking
    TcpListener.cpp
)

target_include_directories(libNetworking PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
