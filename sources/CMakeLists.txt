project(alterate)
cmake_minimum_required(VERSION 2.8)

set(BOOST_ROOT "" CACHE PATH "Boost library")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(ALTERATE_ROOT "alterate-core")
include_directories(${ALTERATE_ROOT}/inc)

add_subdirectory(alterate-core)
add_subdirectory(alterate-gen)
add_subdirectory(demos/alterate2048)
