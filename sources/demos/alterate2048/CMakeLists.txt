project(alterate2048)
cmake_minimum_required(VERSION 2.8)

set(GLFW_ROOT "" CACHE PATH "GLFW library root directory")
add_subdirectory(${GLFW_ROOT} glfw)
include_directories(${GLFW_ROOT}/include)

set(SRC_DIR src)
add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} alterate-core glfw ${GLFW_LIBRARIES})

