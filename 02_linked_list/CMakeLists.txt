cmake_minimum_required(VERSION 3.30)
project(02_linked_list)

set(CMAKE_CXX_STANDARD 20)
# 添加Google Test
find_package(GTest REQUIRED)

add_executable(02_linked_list main.cpp
        solution.cpp
        solution.h)

# 添加测试可执行文件
add_executable(
        tests
        test/test.cpp
)

# 链接Google Test到测试程序
target_link_libraries(
        tests
        GTest::gtest_main
)

# 包含头文件目录
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)