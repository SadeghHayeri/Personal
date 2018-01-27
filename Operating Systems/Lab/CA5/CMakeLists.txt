cmake_minimum_required(VERSION 3.8)
project(CA5)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp TLB.cpp TLB.h Page_table.cpp Page_table.h Memory.cpp Memory.h config.h exception.h)
add_executable(CA5 ${SOURCE_FILES} TLB.cpp TLB.h)