#include <iostream>
#include <string>

#include <GL/gl.h>

#include <alterate/engine.h>

class alterate2048: public alterate::engine_object {

public:
    virtual void on_update(float seconds) {
        glRotatef(seconds * 50.f, 0.f, 0.f, 1.f);
    }

    virtual void on_draw(alterate::gl::context &context) {
        context.clear_color(alterate::gl::color::BLACK).clear();
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
    }

};


alterate::engine_object* alterate_init(alterate::engine& e) {

    std::cout << "in alterate-2048" << std::endl;

    return new alterate2048();
}


