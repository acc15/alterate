project(alterate CXX)
cmake_minimum_required(VERSION 2.8)

enable_testing()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(BOOST_ROOT "" CACHE PATH "Boost library")
find_package(Boost REQUIRED COMPONENTS chrono system)
include_directories(${Boost_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(ALTERATE_ROOT "alterate-core")
include_directories(${ALTERATE_ROOT}/inc)

add_subdirectory(alterate-core)
add_subdirectory(alterate-test)
add_subdirectory(alterate-main)
add_subdirectory(demos/alterate-2048)
add_subdirectory(demos/alterate-pong)
