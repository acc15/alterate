project(alterate-core)
cmake_minimum_required(VERSION 2.8)

set(BOOST_ROOT "" CACHE PATH "Boost library")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(INC_DIR inc)
set(SRC_DIR src)
include_directories(${INC_DIR})

set(SRC_LIST ${INC_DIR}/alterate/types.h ${INC_DIR}/alterate/platform.h ${INC_DIR}/alterate/string.h ${INC_DIR}/alterate/resource.h ${SRC_DIR}/resource.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
