cmake_minimum_required(VERSION 3.5)
project(SignalSender)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SignalSender.cpp SignalSender.h SignalException.h)
add_executable(SignalSender ${SOURCE_FILES})