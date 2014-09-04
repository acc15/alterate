project(alterate-test)
cmake_minimum_required(VERSION 2.8)

set(GTEST_ROOT "" CACHE PATH "Google Test library")
set(BOOST_ROOT "" CACHE PATH "Boost library")

enable_testing()

find_package(GTest REQUIRED)
include_directories("${GTEST_INCLUDE_DIRS}")

find_package(Boost REQUIRED)
include_directories("${Boost_INCLUDE_DIRS}")

set(ALTERATE_DIR "../alterate")
include_directories("${ALTERATE_DIR}/include")

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} debug "${GTEST_LIBRARY_DEBUG}" optimized "${GTEST_LIBRARY_DEBUG}")
target_link_libraries(${PROJECT_NAME} debug "${GTEST_MAIN_LIBRARY_DEBUG}" optimized "${GTEST_MAIN_LIBRARY}")

add_test(alterate-test-all alterate-test)