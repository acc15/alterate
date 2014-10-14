#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <alterate/types.h>

#include "resources.h"

using namespace std;
using namespace alterate;


int main()
{
    std::string app_name = resources::load_string(alterate2048::resources::APP_STRINGS);
    std::string vert_shader = resources::load_string(alterate2048::resources::SHADERS_POSITION_VERT);
    std::string frag_shader = resources::load_string(alterate2048::resources::SHADERS_POSITION_FRAG);

    std::cout << app_name << std::endl;
    std::cout << vert_shader << std::endl;
    std::cout << frag_shader << std::endl;

//    char* begin = &_binary_app_strings_start;
//    char* end = &_binary_app_strings_end;

//    GLFWwindow* window;

//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;

//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }

//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);

//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */

//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);

//        /* Poll for and process events */
//        glfwPollEvents();
//    }

//    glfwTerminate();
    return 0;
}

