cmake_minimum_required(VERSION 2.8)
project(alterate-math-test CXX)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wextra -Wconversion -pedantic -Werror -Wno-missing-braces")
    if (NOT MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()
endif()

set(INCLUDE_DIR "../include")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${INCLUDE_DIR} ${GTEST_INCLUDE_DIR})

set(INCLUDE_FILES ${INCLUDE_DIR}/alterate/algorithm.hpp)
set(SRC_FILES alterate/algorithm.cpp)

add_executable(alterate-math-test ${SRC_FILES} ${INCLUDE_FILES})

# Link test executable against gtest & gtest_main
target_link_libraries(alterate-math-test ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG})

add_test(NAME alterate-math-test COMMAND alterate-math-test)