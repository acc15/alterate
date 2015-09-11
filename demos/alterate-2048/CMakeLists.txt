project(alterate-2048)
cmake_minimum_required(VERSION 2.8)

#set(GLFW_ROOT "" CACHE PATH "GLFW library root directory")
#add_subdirectory(${GLFW_ROOT} glfw)
#include_directories(${GLFW_ROOT}/include)

set(SRC_DIR src)
add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp)


### To hide console in Windows
if(WIN32) # Check if we are on Windows
	if(MSVC) # Check if we are using the Visual Studio compiler
	    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif()
endif()

#target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} alterate-main)

