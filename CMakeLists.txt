cmake_minimum_required(VERSION 3.14)
project(http-get)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(http-get src/main.cpp)
target_include_directories(http-get PRIVATE ./inc)