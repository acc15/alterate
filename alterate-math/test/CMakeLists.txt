cmake_minimum_required(VERSION 2.8)
project(alterate-math-test CXX)

enable_testing()

find_package(Boost REQUIRED)

set(GMOCK_ROOT "" CACHE PATH "Path to googlemock source tree (it should include gtest)")

include(ExternalProject)
ExternalProject_Add(googlemock PREFIX gmock SOURCE_DIR "${GMOCK_ROOT}" INSTALL_COMMAND "")
ExternalProject_Get_Property(googlemock binary_dir)
add_library(gmock UNKNOWN IMPORTED)
add_library(gmock_main UNKNOWN IMPORTED)
set_target_properties(gmock PROPERTIES IMPORTED_LOCATION ${binary_dir}/libgmock.a)
set_target_properties(gmock_main PROPERTIES IMPORTED_LOCATION ${binary_dir}/libgmock_main.a)
add_dependencies(gmock googlemock)
add_dependencies(gmock_main googlemock)


if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wextra -pedantic -Werror -Wno-missing-braces")
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