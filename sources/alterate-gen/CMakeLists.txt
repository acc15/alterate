project(alterate-gen)
cmake_minimum_required(VERSION 2.8)

include_directories(${ALTERATE_ROOT}/inc)

set(SRC_DIR src)
set(SRC_LIST
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/rc.cpp
    ${SRC_DIR}/path.h
    ${SRC_DIR}/path.cpp
    ${SRC_DIR}/rc_args.h
    ${SRC_DIR}/rc_args.cpp
    ${SRC_DIR}/rc.h)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
