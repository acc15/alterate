#include <alterate/engine.h>

#include <GL/gl.h>

namespace alterate {

engine::engine() {
}

void engine::on_update() {
    glRotatef(_timer.reset() * 50.f, 0.f, 0.f, 1.f);
}

void engine::on_draw() {
    _context.clear_color(gl::color::BLACK).clear();
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
}

void engine::on_size(const dimension& size) {
    _context.on_size(size);
}

void engine::on_frame() {
    on_update();
    on_draw();
}

engine engine::_instance;

engine& engine::get() {
    return _instance;
}

}
