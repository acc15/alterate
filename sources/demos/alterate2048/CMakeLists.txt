project(alterate2048)
cmake_minimum_required(VERSION 2.8)

set(ALTERATE_ROOT "../../alterate-lib")
set(GLFW_ROOT "" CACHE PATH "GLFW library root directory")

add_subdirectory(${GLFW_ROOT} glfw)

include_directories(${ALTERATE_ROOT}/inc)
include_directories(${GLFW_ROOT}/include)

set(SRC_DIR src)
set(RES_DIR res)

set(RES_OBJ ${CMAKE_CURRENT_BINARY_DIR}/resources.o)
set(RES_LIST app.strings shaders/position.vert shaders/position.frag)
add_custom_command(
    OUTPUT ${RES_OBJ}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${RES_DIR}
    COMMAND ld -r -b binary -o ${RES_OBJ} ${RES_LIST})

set(SRC_LIST ${SRC_DIR}/main.cpp ${RES_OBJ})
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

