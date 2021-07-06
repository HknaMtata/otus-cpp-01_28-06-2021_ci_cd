cmake_minimum_required(VERSION 3.2)

add_executable(ip-test ip_test.cpp)
target_link_libraries(ip-test ip gtest)
add_test(NAME IpUnitTest COMMAND ip-test)

# TODO: how to test with md5sum?
# file(COPY ip_filter.tsv DESTINATION test_data)
# add_test(NAME IpFilterTest COMMAND ...)