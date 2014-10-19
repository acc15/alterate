#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <alterate/types.h>
#include <alterate/debug.h>

#include "resources.h"

using namespace std;
using namespace alterate;

//void app_init(alterate::engine& engine) {


//}

//void app_destroy(alterate::engine& engine) {


//}


int main()
{
    bundle app_strings = load_bundle(alterate2048::resources::APP_STRINGS);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, app_strings["window.title"].c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

