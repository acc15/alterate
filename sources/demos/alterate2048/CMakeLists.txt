project(alterate2048)
cmake_minimum_required(VERSION 2.8)

set(GLFW_ROOT "" CACHE PATH "GLFW library root directory")
add_subdirectory(${GLFW_ROOT} glfw)
include_directories(${GLFW_ROOT}/include)

set(SRC_DIR src)
set(RES_DIR res)

set(RES_REL_LIST
    app.strings
    version.txt
    super_file.txt
    shaders/position.vert
    shaders/position.frag)

foreach(RES_REL_FILE ${RES_REL_LIST})
    list(APPEND RES_LIST ${RES_DIR}/${RES_REL_FILE})
endforeach(RES_REL_FILE)

set(RES_OBJ ${CMAKE_CURRENT_BINARY_DIR}/resources.o)
set(RES_CPP ${CMAKE_CURRENT_BINARY_DIR}/resources.cpp)
set(RES_H ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/resources.h)

add_custom_command(OUTPUT ${RES_CPP} ${RES_H} ${RES_OBJ}
    COMMAND alterate-gen -n alterate2048::resources -h ${RES_H} -c ${RES_CPP} -o ${RES_OBJ} ${RES_REL_LIST}
    DEPENDS ${RES_LIST}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${RES_DIR})

set(SRC_DIR src)
add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${RES_H}
    ${RES_CPP}
    ${RES_OBJ}
    ${RES_LIST})

target_link_libraries(${PROJECT_NAME} alterate-core glfw ${GLFW_LIBRARIES})

