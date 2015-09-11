project(alterate CXX)
cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0054 NEW)

enable_testing()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -std=c++11 -Wall -pedantic -Werror=return-type")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(BOOST_ROOT "" CACHE PATH "Boost library")
find_package(Boost REQUIRED COMPONENTS chrono system)
include_directories(${Boost_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(ALTERATE_ROOT sources/alterate-core)
include_directories(${ALTERATE_ROOT}/inc)

add_subdirectory(sources/alterate-core)
add_subdirectory(sources/alterate-test)
add_subdirectory(sources/alterate-main)
add_subdirectory(sources/demos/alterate-2048)
add_subdirectory(sources/demos/alterate-pong)
