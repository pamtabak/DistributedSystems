cmake_minimum_required(VERSION 3.5)
project(rpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES server.cc client.cc)
add_executable(rpc ${SOURCE_FILES})