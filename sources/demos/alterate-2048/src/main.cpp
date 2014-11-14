#include <iostream>
#include <string>

#include <GL/gl.h>

#include <alterate/engine.h>

alterate::engine_object* alterate_init(alterate::engine& e) {

    std::cout << "in alterate-2048" << std::endl;

    return new alterate::engine_object();
}



//#if BOOST_OS_WINDOWS
//int CALLBACK WinMain(
//    _In_  HINSTANCE hInstance,
//    _In_  HINSTANCE hPrevInstance,
//    _In_  LPSTR lpCmdLine,
//    _In_  int nCmdShow
//    )
//#else
//int main()
//#endif
//{
//    GLFWwindow* window;

//    /* Initialize the library */
//    if (!glfwInit()) {
//        return -1;
//    }

//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "alterate2048", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }

//    alterate::engine::get().on_size(get_window_size(window));
//    glfwSetWindowSizeCallback(window, &on_size_callback);
//    glfwMakeContextCurrent(window);

//    while (!glfwWindowShouldClose(window)) {
//        alterate::engine::get().on_frame();
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//}

