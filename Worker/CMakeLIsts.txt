cmake_minimum_required(VERSION 3.22.1)

add_library(libWorker SHARED
    Worker.cpp
)

target_include_directories(libWorker PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/>
)
