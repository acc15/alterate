project(alterate-core)
cmake_minimum_required(VERSION 2.8)

set(INC_DIR inc)
set(SRC_DIR src)
include_directories(${INC_DIR})

set(SRC_LIST
    ${INC_DIR}/alterate/system.h
    ${SRC_DIR}/alterate/system.cpp

    ${INC_DIR}/alterate/gl/gl_inc.h

    ${INC_DIR}/alterate/gl/util.h
    ${SRC_DIR}/alterate/gl/util.cpp

    ${INC_DIR}/alterate/dimension.h
    ${SRC_DIR}/alterate/dimension.cpp

    ${INC_DIR}/alterate/gl/color.h
    ${SRC_DIR}/alterate/gl/color.cpp

    ${INC_DIR}/alterate/gl/context.h
    ${SRC_DIR}/alterate/gl/context.cpp

    ${INC_DIR}/alterate/timing/clock.h
    ${SRC_DIR}/alterate/timing/clock.cpp

    ${INC_DIR}/alterate/timing/timer.h
    ${SRC_DIR}/alterate/timing/timer.cpp

    ${INC_DIR}/alterate/engine.h
    ${SRC_DIR}/alterate/engine.cpp

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
    ${INC_DIR}/alterate/math/vec.h)


add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY})
