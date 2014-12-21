project(alterate-test)
cmake_minimum_required(VERSION 2.8)

set(GTEST_ROOT "" CACHE PATH "Google Test library")
add_subdirectory(${GTEST_ROOT} gtest)
include_directories(${GTEST_ROOT}/include)
include_directories(${ALTERATE_ROOT}/inc)

### To link using static runtime libraries
if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

set(SRC_DIR src)
set(SRC_LIST
    ${SRC_DIR}/test_utils.h
    ${SRC_DIR}/sandbox.cpp
    ${SRC_DIR}/matrix_test.cpp
    ${SRC_DIR}/iterator_factory_test.cpp
    ${SRC_DIR}/generic_vector_support_test.cpp
    ${SRC_DIR}/scalar_iterator_test.cpp
    ${SRC_DIR}/random_access_iterator_support_test.cpp
    ${SRC_DIR}/vertex_buffer_layout_test.cpp
    ${SRC_DIR}/vertex_buffer_test.cpp
)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} alterate-core)

add_test(AllTests ${PROJECT_NAME})
