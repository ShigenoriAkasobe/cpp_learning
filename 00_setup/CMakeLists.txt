cmake_minimum_required(VERSION 3.16)
project(00_setup)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(00_setup main.cpp)

add_test(NAME 00_setup_test COMMAND 00_setup)
