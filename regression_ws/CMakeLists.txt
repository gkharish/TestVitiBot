cmake_minimum_required(VERSION 3.8)
project(regression_ws)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(regression_node src/linear_regression.cpp)
target_include_directories(regression_node PUBLIC include/)


add_library(ransac src/ransac.cpp)
target_include_directories(ransac PUBLIC include/)

add_executable(ransac_node src/ransac_main.cpp)
target_include_directories(ransac_node PUBLIC include/)
target_link_libraries(ransac_node PRIVATE  ransac)

# TEST
enable_testing()

add_executable(level1_test test/level1.cpp)
target_include_directories(level1_test PUBLIC include/)
target_link_libraries(level1_test PRIVATE GTest::GTest GTest::Main ransac)

add_test(simpleTest level1_test COMMAND level1_test)