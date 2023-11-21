cmake_minimum_required(VERSION 3.22.1)

add_library(libServer SHARED
    Server.cpp
)

target_include_directories(libServer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/>
)
