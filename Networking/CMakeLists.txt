cmake_minimum_required(VERSION 3.22.1)

add_library(networking
    NetworkStream.cpp
    TcpListener.cpp
)

target_include_directories(networking PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
