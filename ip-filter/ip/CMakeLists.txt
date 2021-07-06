cmake_minimum_required(VERSION 3.2)

add_library(ip ipv4.cpp)
target_include_directories(ip PUBLIC .)