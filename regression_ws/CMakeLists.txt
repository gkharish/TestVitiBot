cmake_minimum_required(VERSION 3.8)
project(regression_ws)

set(CMAKE_CXX_STANDARD 17)


add_executable(regrssion_node src/linear_regression.cpp)
target_include_directories(regrssion_node PUBLIC include/)