#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

#include <GL/gl.h>

#include <alterate/engine.h>

extern alterate::engine_object* alterate_init(alterate::engine& e);


void on_size_callback(GLFWwindow*, int w, int h) {
    alterate::engine::get().on_size(alterate::dimension(w,h));
}

alterate::dimension get_window_size(GLFWwindow* wnd) {
    int x, y;
    glfwGetWindowSize(wnd, &x, &y);
    return alterate::dimension(x,y);
}

#if BOOST_OS_WINDOWS
int CALLBACK WinMain(
    _In_  HINSTANCE hInstance,
    _In_  HINSTANCE hPrevInstance,
    _In_  LPSTR lpCmdLine,
    _In_  int nCmdShow
    )
#else
int main()
#endif
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

    alterate::engine_object* root = alterate_init(alterate::engine::get());
    if (root == nullptr) {
        glfwTerminate();
        return -1;
    }

    alterate::engine::get().set_root(*root);
    while (!glfwWindowShouldClose(window)) {
        alterate::engine::get().on_frame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

