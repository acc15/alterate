project(alterate-test)
cmake_minimum_required(VERSION 2.8)
                        
set(BOOST_DIR "" CACHE PATH "Boost library")

set(GTEST_ROOT "" CACHE PATH "Google Test library")
find_package(GTest REQUIRED)

set(ALTERATE_DIR "../alterate")

include_directories("${BOOST_DIR}" "${ALTERATE_DIR}/include" "${GTEST_INCLUDE_DIRS}")

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

