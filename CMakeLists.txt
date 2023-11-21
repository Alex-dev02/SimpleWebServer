cmake_minimum_required(VERSION 3.22.1)

project(simplewebserver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0")

add_subdirectory(Networking)
add_subdirectory(Server)

add_executable(simplewebserver main.cpp)
