project(alterate-rc)
cmake_minimum_required(VERSION 2.8)

set(ALTERATE_ROOT "../alterate-core")
set(BOOST_ROOT "" CACHE PATH "Boost library")

find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${ALTERATE_ROOT}/inc)

set(SRC_DIR src)
set(SRC_LIST ${SRC_DIR}/main.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
