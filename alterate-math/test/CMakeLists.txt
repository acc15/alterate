cmake_minimum_required(VERSION 2.8)
project(alterate-math-test CXX)

enable_testing()

find_package(Boost REQUIRED)

set(GMOCK_ROOT "" CACHE PATH "Path to googlemock source tree (it should include gtest)")
add_subdirectory(${GMOCK_ROOT} gmock)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wextra -Wconversion -pedantic -Werror -Wno-missing-braces")
    if (NOT MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()
endif()

set(INCLUDE_DIR "../include")

include_directories(${Boost_INCLUDE_DIR}
        ${GMOCK_ROOT}/include
        ${GMOCK_ROOT}/gtest/include
        ${INCLUDE_DIR})

set(INCLUDE_FILES
        ${INCLUDE_DIR}/alterate/algorithm.hpp
        ${INCLUDE_DIR}/alterate/iterator/scalar_iterator.hpp
        ${INCLUDE_DIR}/alterate/iterator/iterator_factory.hpp)
set(SRC_FILES
        alterate/algorithm.cpp
        alterate/iterator/scalar_iterator.cpp
        alterate/iterator/iterator_factory.cpp)

add_executable(alterate-math-test ${SRC_FILES} ${INCLUDE_FILES})

# Link test executable against gtest & gtest_main
target_link_libraries(alterate-math-test gmock gmock_main)

add_test(NAME alterate-math-test COMMAND alterate-math-test)