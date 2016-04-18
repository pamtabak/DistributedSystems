cmake_minimum_required(VERSION 3.5)
project(SignalReceiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SignalException.h SignalHandler.cpp SignalHandler.h)
add_executable(SignalReceiver ${SOURCE_FILES})