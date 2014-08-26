project(alterate CXX)
cmake_minimum_required(VERSION 2.8)

set(BOOST_DIR "D:/MyProgs/Libs/C++/boost_1_56_0")
include_directories("${BOOST_DIR}")

include_directories("include")

set (SRC_LIST 
    "include/alterate/error.h"
    "include/alterate/platform.h"
    "include/alterate/types.h"
    "include/alterate/functional/functional.h"
    "include/alterate/functional/functors.h"
    "include/alterate/iterator/iterator_provider.h"
    "include/alterate/iterator/random_access_iterator_support.h"
    "include/alterate/iterator/scalar_iterator.h"
    "include/alterate/math/basic_vec.h"
    "include/alterate/math/vec.h"
    "include/alterate/math/vector_support.h"
    "dummy.cpp")
add_executable(${PROJECT_NAME} ${SRC_LIST})

