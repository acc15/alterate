cmake_minimum_required(VERSION 2.8)
project(alterate-math-test CXX)

enable_testing()

find_package(Boost REQUIRED)

include(ExternalProject)

ExternalProject_Add(googletest
        PREFIX gmock
        URL https://github.com/google/googletest/archive/release-1.7.0.zip
        DOWNLOAD_NAME "gtest-1.7.0.zip"
        INSTALL_COMMAND "")

ExternalProject_Add(googlemock
        DEPENDS googletest
        PREFIX gmock
        URL https://github.com/google/googlemock/archive/release-1.7.0.zip
        DOWNLOAD_NAME "gmock-1.7.0.zip"
        INSTALL_COMMAND "")

ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/include)
ExternalProject_Get_Property(googlemock source_dir binary_dir)
set(GMOCK_INCLUDE_DIR ${source_dir}/include)
set(GMOCK_LIBRARIES ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX})
set(GMOCK_MAIN_LIBRARIES ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX})

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wextra -pedantic -Werror -Wno-missing-braces")
    if (NOT MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()
endif()

set(INCLUDE_DIR "../include")

include_directories(${Boost_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
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
add_dependencies(alterate-math-test googlemock)

## Link test executable against gtest & gtest_main
target_link_libraries(alterate-math-test ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})
#
add_test(NAME alterate-math-test COMMAND alterate-math-test)
