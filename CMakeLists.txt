cmake_minimum_required(VERSION 3.14)
project(http-get)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
set(MIDDLEWARE_DIR ${CMAKE_SOURCE_DIR}/middlewares)

set(LIBCURL_DIR ${MIDDLEWARE_DIR}/curl)
set(ARGPARSE_DIR ${MIDDLEWARE_DIR}/argparse)

add_subdirectory(${LIBCURL_DIR})
add_subdirectory(${ARGPARSE_DIR})

find_package(CURL REQUIRED)
add_executable(http-get 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/http_get.cpp
    )

target_include_directories(http-get PRIVATE 
    ${INC_DIR}
    ${LIBCURL_DIR}
    ${ARGPARSE_DIR}
)

target_link_libraries(http-get PRIVATE 
    CURL::libcurl
    argparse
    )