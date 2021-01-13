cmake_minimum_required(VERSION 3.17)
project(crypt)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(./crypt/src LIB_SRC_FILE)

add_library(crypt SHARED ${LIB_SRC_FILE})

add_executable(test main.cpp)

target_link_libraries(test crypt)