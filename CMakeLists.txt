cmake_minimum_required(VERSION 3.25)
project(simple_webserver)

set(CMAKE_CXX_STANDARD 17)

add_executable(simple_webserver main.cpp common.cpp common.h)
