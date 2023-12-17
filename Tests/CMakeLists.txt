cmake_minimum_required(VERSION 3.22.1)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  helloWorldTest
  UnitTests/HelloWorldTest.cpp
)
target_link_libraries(helloWorldTest gtest_main)

include(GoogleTest)
gtest_discover_tests(helloWorldTest)