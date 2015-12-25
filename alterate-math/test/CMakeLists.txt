cmake_minimum_required(VERSION 2.8)
project(alterate-math-test CXX)

enable_testing()

find_package(Boost REQUIRED)

find_path(GMOCK_ROOT src/gmock-all.cc DOC "Path to googlemock source tree (it should include gtest)")
if (NOT GMOCK_ROOT)
    message(FATAL_ERROR "googlemock ${GMOCK_ROOT} not found. Set GMOCK_ROOT variable")
endif()

find_path(GMOCK_INCLUDE_DIR NAMES gmock/gmock.h PATHS "${GMOCK_ROOT}/include")
if (NOT GMOCK_INCLUDE_DIR)
    message(FATAL_ERROR "googlemock headers not found. Set GMOCK_INCLUDE_DIR variable")
endif()

find_path(GTEST_INCLUDE_DIR NAMES gtest/gtest.h PATHS "${GMOCK_ROOT}/gtest/include")
if (NOT GTEST_INCLUDE_DIR)
    message(FATAL_ERROR "googletest headers not found. Set GTEST_INCLUDE_DIR variable")
endif()

add_subdirectory(${GMOCK_ROOT} gmock)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wextra -pedantic -Werror -Wno-missing-braces")
    if (NOT MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()
endif()

set(INCLUDE_DIR "../include")

include_directories(${Boost_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
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