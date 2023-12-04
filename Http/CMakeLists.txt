cmake_minimum_required(VERSION 3.22.1)

add_library(libHttp SHARED
    HttpParser.cpp
)

target_include_directories(libHttp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
