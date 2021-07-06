cmake_minimum_required(VERSION 3.2)

add_executable(ip-filter ip_filter.cpp)
target_link_libraries(ip-filter PUBLIC ip)