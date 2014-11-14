#include <alterate/engine.h>

#include <GL/gl.h>

extern void alterate_init();

namespace alterate {

void engine_object::on_update(float /*seconds*/) {

}

void engine_object::on_draw(gl::context& /*context*/) {

}

void engine_object::on_attach(engine& /*engine*/) {

}

void engine_object::on_detach(engine& /*engine*/) {

}

void engine_object::on_size(const dimension& /*size*/) {

}



engine::engine() {
}

void engine::on_update() {
    float seconds = _timer.reset();
    _root->on_update(seconds);

    //glRotatef(_timer.reset() * 50.f, 0.f, 0.f, 1.f);
}

void engine::on_draw() {
    _root->on_draw(_context);
    //_context.clear_color(gl::color::BLACK).clear();
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.f, 0.f, 0.f);
//    glVertex3f(-0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 1.f, 0.f);
//    glVertex3f(0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 0.f, 1.f);
//    glVertex3f(0.f, 0.6f, 0.f);
//    glEnd();
}

void engine::on_size(const dimension& size) {
    _context.on_size(size);
    if (_root != nullptr) {
        _root->on_size(size);
    }
}

void engine::on_frame() {
    on_update();
    on_draw();
}

void engine::set_root(engine_object &obj) {
    _root = &obj;
}

engine engine::_instance;

engine& engine::get() {
    return _instance;
}

}

//extern void alterate_init(alterate::engine& engine);

//int main()
//{

//    alterate_init(alterate::engine::get());

//    //GLFWwindow* window;

//    /* Initialize the library */
//    //if (!glfwInit()) {
//    //    return -1;
//    //}

//    /* Create a windowed mode window and its OpenGL context */
//    //window = glfwCreateWindow(640, 480, "alterate2048", NULL, NULL);
//    //if (!window) {
//    //    glfwTerminate();
////        return -1;
////    }

////    alterate::engine::get().on_size(get_window_size(window));
////    glfwSetWindowSizeCallback(window, &on_size_callback);
////    glfwMakeContextCurrent(window);

////    while (!glfwWindowShouldClose(window)) {
////        alterate::engine::get().on_frame();
////        glfwSwapBuffers(window);
////        glfwPollEvents();
////    }
////    glfwTerminate();
//    return 0;
//}
