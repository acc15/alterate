project(alterate-core)
cmake_minimum_required(VERSION 2.8)

set(INC_DIR inc)
set(SRC_DIR src)
include_directories(${INC_DIR})

set(SRC_LIST
    ${INC_DIR}/alterate/defs.h
    ${INC_DIR}/alterate/error.h
    ${INC_DIR}/alterate/print.h
    ${INC_DIR}/alterate/iterator/scalar_iterator.h
    ${INC_DIR}/alterate/iterator/random_access_iterator.h
    ${INC_DIR}/alterate/iterator/random_access_iterator_support.h
    ${INC_DIR}/alterate/iterator/iterator_factory.h
    ${INC_DIR}/alterate/math/functional.h
    ${INC_DIR}/alterate/math/generic_vector_support.h
    ${INC_DIR}/alterate/math/vector_support.h
    ${INC_DIR}/alterate/math/vec.h
    ${INC_DIR}/alterate/gl/color.h)
#add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
add_custom_target(${PROJECT_NAME} SOURCES ${SRC_LIST})
