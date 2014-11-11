project(alterate-core)
cmake_minimum_required(VERSION 2.8)

set(INC_DIR inc)
set(SRC_DIR src)
include_directories(${INC_DIR})

set(SRC_LIST
    ${INC_DIR}/alterate/defs.h
    ${INC_DIR}/alterate/platform.h
    ${INC_DIR}/alterate/iterator/scalar_iterator.h
    ${INC_DIR}/alterate/iterator/iterator_factory.h
    ${INC_DIR}/alterate/math/functional.h
    ${INC_DIR}/alterate/math/vector_support.h
    ${INC_DIR}/alterate/math/basic_vec.h
    ${INC_DIR}/alterate/math/vec.h
    ${INC_DIR}/alterate/gl/color.h)
#add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
add_custom_target(${PROJECT_NAME} SOURCES ${SRC_LIST})
