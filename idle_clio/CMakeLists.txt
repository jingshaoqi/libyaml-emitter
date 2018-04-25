#set debug
project(libyaml_emitter_test C)
cmake_minimum_required(VERSION 2.8)

#set c++11 and debug
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0")

#add_definitions(-DCONFIG_DIR="/usr/local/etc/knot")
#add_definitions(-DSTORAGE_DIR="/usr/local/var/lib/knot")
#add_definitions(-DRUN_DIR="/usr/local/var/run/knot")
#add_definitions(-DPACKAGE_VERSION="2.4.0")

set(SOURCE_ROOT_DIR "/home/verycloud/libyaml-emitter")


#set compiler gcc
set(CMAKE_C_COMPILER gcc)
#add_compile_options(-std=c++11)

#set build output dir
set(PROJECT_BINARY_DIR ${SOURCE_ROOT_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#include directories
#include_directories(
#../
#../knot/src
#../knot/libtap
#)
include_directories(
../
)

#link directories
link_directories(${PROJECT_SOURCE_DIR}/../)
#link_directories(/home/verycloud/ts-gslb/knot/libtap/.libs/)
#aux_source_directory(. SRC_LIST)
#set(EXE_NAME libyaml_emitter_test})

link_directories(/usr/lib64)
link_directories(/usr/local/lib)
link_directories(/usr/lib)
link_directories(/home/verycloud/libyaml/src/.libs/)

add_executable(libyaml_emitter_test ${SOURCE_ROOT_DIR}/libyaml-emitter.c)
#add_executable(libyaml_emitter_test ${SOURCE_ROOT_DIR}/tests/contrib/test_random.c)

#link static libraries
#target_link_libraries(libyaml_emitter_test ${SOURCE_ROOT_DIR}/src/.libs/libcontrib.a)
#target_link_libraries(libyaml_emitter_test /home/verycloud/libyaml/src/.libs/libyaml.a)
target_link_libraries(libyaml_emitter_test libyaml.a)

#link dynamic libraries
#target_link_libraries(libyaml_emitter_test gnutls lmdb pthread nettle -ldl -lurcu)

#set library name libknot.so
#set(SO_NAME knot)

#set library output directory
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../ccc_lib)

#add library
#add_library(${SO_NAME} SHARED ${SOURCE_FILES})
#set_target_properties(${EXE_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(libyaml_emitter_test PROPERTIES LINKER_LANGUAGE C)
#set exe output directory
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# message
message(STATUS "PROJECT_NAME is:" ${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR is:" ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_BINARY_DIR is:" ${PROJECT_BINARY_DIR})
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY is:" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message(STATUS "CMAKE_CURRENT_BINARY_DIR  is:" ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR is:" ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "CMAKE_INCLUDE_PATH  is:" ${CMAKE_INCLUDE_PATH})
message(STATUS "CMAKE_LIBRARY_PATH is:" ${CMAKE_LIBRARY_PATH})
message(STATUS "CMAKE_PREFIX_PATH  is:" ${CMAKE_PREFIX_PATH})
message(STATUS "CMAKE_ROOT is:" ${CMAKE_ROOT})
message(STATUS "CMAKE_CXX_FLAGS  is:" ${CMAKE_CXX_FLAGS})
message(STATUS "CMAKE_C_COMPILER  is:" ${CMAKE_C_COMPILER})
message(STATUS "CMAKE_CXX_COMPILER  is:" ${CMAKE_CXX_COMPILER})
message(STATUS "CMAKE_SHARED_LINKER_FLAGS is:" ${CMAKE_SHARED_LINKER_FLAGS})
message(STATUS "CMAKE_VERSION  is:" ${CMAKE_VERSION})
message(STATUS "CMAKE_GENERATOR  is:" ${CMAKE_GENERATOR})
message(STATUS "CMAKE_BINARY_DIR  is:" ${CMAKE_BINARY_DIR})
message(STATUS "CMAKE_COMMAND is:" ${CMAKE_COMMAND})
message(STATUS "CMAKE_FILES_DIRECTORY  is:" ${CMAKE_FILES_DIRECTORY})
message(STATUS "CMAKE_SOURCE_DIR is:" ${CMAKE_SOURCE_DIR})

