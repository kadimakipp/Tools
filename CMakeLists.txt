cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


add_definitions(-std=c++14)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O2")


project(XLOG)

set(SPD_INCLUDE_DIR /home/kipp/workspace/kipp_study/3rdparty/spdlog/include)
include_directories(${SPD_INCLUDE_DIR})


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/xlog)
file(GLOB xlog_file xlog/*.hpp xlog/*.cpp)


add_executable(xlog xlog_test.cpp ${xlog_file} )
target_link_libraries(xlog)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spdlog_example)
add_subdirectory(spdlog_example example)
