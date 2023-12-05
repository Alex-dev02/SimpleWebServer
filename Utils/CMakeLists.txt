cmake_minimum_required(VERSION 3.22.1)

add_library(libUtils SHARED
    Utils.cpp
)

target_include_directories(libUtils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
