cmake_minimum_required(VERSION 3.8)
project(radar_span)

set(CMAKE_CXX_STANDARD 17)


add_executable(radar_span_obstacle src/radar_span.cpp)
target_include_directories(radar_span_obstacle PUBLIC 
                            include/)

