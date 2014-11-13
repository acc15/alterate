#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

#include <GL/gl.h>

#include <alterate/engine.h>
using namespace std;

void on_size_callback(GLFWwindow*, int w, int h) {
    alterate::engine::get().on_size(alterate::dimension(w,h));
}

alterate::dimension get_window_size(GLFWwindow* wnd) {
    int x, y;
    glfwGetWindowSize(wnd, &x, &y);
    return alterate::dimension(x,y);
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "alterate2048", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    alterate::engine::get().on_size(get_window_size(window));
    glfwSetWindowSizeCallback(window, &on_size_callback);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        alterate::engine::get().on_frame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

