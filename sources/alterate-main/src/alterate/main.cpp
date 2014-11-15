#include <iostream>
#include <string>

#include <alterate/engine.h>
#include <alterate/system.h>

#include <GLFW/glfw3.h>

extern std::unique_ptr<alterate::engine_object>  alterate_init(alterate::engine& e);


void on_size_callback(GLFWwindow*, int w, int h) {
    alterate::engine::get().on_size(alterate::dimension(w,h));
}

alterate::dimension get_window_size(GLFWwindow* wnd) {
    int x, y;
    glfwGetWindowSize(wnd, &x, &y);
    return alterate::dimension(x,y);
}

std::string last_error_description;
int last_error_code;

void error_callback(int error_code, const char* error_message) {
    last_error_code = error_code;
    last_error_description = error_message;
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
    glfwSetErrorCallback(&error_callback);

    /* Initialize the library */
    if (!glfwInit()) {
        std::cerr << "Can't initialize GLFW (" << last_error_code << "): " << last_error_description << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, alterate::get_executable_name().c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "Can't create GLFW window (" << last_error_code << "): " << last_error_description << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        std::cerr << "Can't initialize GLEW: " << glewGetErrorString(glewStatus) << std::endl;
        return -1;
    }

    alterate::engine::get().on_initial_size(get_window_size(window));
    glfwSetWindowSizeCallback(window, &on_size_callback);

    std::unique_ptr<alterate::engine_object> root = alterate_init(alterate::engine::get());
    if (!root) {
        glfwTerminate();
        return -1;
    }

    alterate::engine::get().set_root(root);
    while (!glfwWindowShouldClose(window)) {
        alterate::engine::get().on_frame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

