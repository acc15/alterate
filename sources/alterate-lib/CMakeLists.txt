project(alterate-lib)
cmake_minimum_required(VERSION 2.8)

set(BOOST_ROOT "" CACHE PATH "Boost library")
find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIR})

set(INC_DIR inc)
set(SRC_DIR src)
include_directories(${INC_DIR})

set(SRC_LIST ${INC_DIR}/alterate/types.h)
add_custom_target(${PROJECT_NAME} SOURCES ${SRC_LIST})
#add_executable(${PROJECT_NAME} ${SRC_LIST})
