project(alterate-core)
cmake_minimum_required(VERSION 2.8)

set(RAPIDJSON_ROOT "" CACHE PATH "RapidJSON library")
include_directories(${RAPIDJSON_ROOT}/include)

set(INC_DIR inc)
set(SRC_DIR src)
include_directories(${INC_DIR})

set(SRC_LIST
    ${INC_DIR}/alterate/types.h
    ${INC_DIR}/alterate/debug.h
    ${INC_DIR}/alterate/platform.h
    ${INC_DIR}/alterate/iterator/scalar_iterator.h
    ${INC_DIR}/alterate/math/basic_vec.h
    ${INC_DIR}/alterate/math/vec.h
    ${INC_DIR}/alterate/resource.h
    ${INC_DIR}/alterate/bundle.h
    ${INC_DIR}/alterate/gl/color.h
    ${SRC_DIR}/resource.cpp
    ${SRC_DIR}/bundle.cpp
    ${SRC_DIR}/debug.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
