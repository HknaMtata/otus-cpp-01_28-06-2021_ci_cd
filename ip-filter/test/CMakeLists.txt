cmake_minimum_required(VERSION 3.2)

add_executable(ip-test ip_test.cpp)
target_link_libraries(ip-test ip gtest)
add_test(NAME IpUnitTest COMMAND ip-test)

file(COPY ip_filter.tsv DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data)
add_test(
    NAME IpFilterTest
    COMMAND bash -c "test \"$(cat test_data/ip_filter.tsv | ip-filter | md5sum | awk '{print $1}')\" == 24e7a7b2270daee89c64d3ca5fb3da1a || exit -1"
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)