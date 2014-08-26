project(alterate-test)
cmake_minimum_required(VERSION 2.8)

set(BOOST_DIR "D:/MyProgs/Libs/C++/boost_1_56_0" CACHE PATH "Boost library")
set(GTEST_DIR "D:/MyProgs/Libs/C++/gtest-1.7.0" CACHE PATH "Google Test")

set(ALTERATE_DIR "../alterate")

include_directories("${BOOST_DIR}" "${GTEST_DIR}/include" "${ALTERATE_DIR}/include")

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

