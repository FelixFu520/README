cmake_minimum_required(VERSION 3.5)
project(DEMO)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl -pthread")

# find opencv
find_package(OpenCV 4.4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(demo main-0033.cpp)
target_link_libraries(demo  ${OpenCV_LIBS})
