cmake_minimum_required(VERSION 2.6)
project(elog_test)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(SRC_LIST  sess_test.cpp)
include_directories(../../include ../../../efnfw)
add_definitions("-Wall -g")
link_directories(../../lib /usr/local/lib)
link_directories(../../../efnfw/lib)
link_libraries(libcommon.a json libefnfw.a hiredis protobuf pthread)
add_executable(elog_test ${SRC_LIST})
