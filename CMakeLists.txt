cmake_minimum_required(VERSION 3.8)
project(hdpro)

include_directories(include)

add_definitions(-DHDPRO_EXPORTS)

add_library(hdpro SHARED
    src/hdpro_impl.cpp
    include/HDPRO.h
)

target_include_directories(hdpro PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(DemoApp demo/demo.cpp)
target_link_libraries(DemoApp PRIVATE hdpro)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/Debug)