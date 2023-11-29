cmake_minimum_required(VERSION 3.22.1)

project(simplewebserver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(sws main.cpp)

add_subdirectory(Networking)
add_subdirectory(Server)
add_subdirectory(Worker)

target_link_libraries(libServer libNetworking)
target_link_libraries(libWorker libNetworking)
target_link_libraries(sws libServer libNetworking libWorker)
