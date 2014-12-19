#include <iostream>
#include <string>

#include <alterate/engine.h>
#include <alterate/system.h>

#include <GLFW/glfw3.h>

extern void alterate_init(alterate::engine& e);


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

    const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    const int width = 640, height = 480;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(width, height, alterate::get_executable_name().c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "Can't create GLFW window (" << last_error_code << "): " << last_error_description << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, (vid_mode->width - width) / 2, (vid_mode->height - height)/2);

    glfwMakeContextCurrent(window);

    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        std::cerr << "Can't initialize GLEW: " << glewGetErrorString(glewStatus) << std::endl;
        return -1;
    }

    alterate::engine& engine = alterate::engine::get();

    engine.on_initial_size(get_window_size(window));
    glfwSetWindowSizeCallback(window, &on_size_callback);

    alterate_init(engine);
    if (!engine.is_initialized()) {
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        engine.on_frame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    engine.terminate();
    glfwTerminate();
    return 0;
}

