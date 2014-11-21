#include <alterate/gl/context.h>

namespace alterate {
namespace gl {

context& context::clear_color(const color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    return *this;
}

context& context::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    return *this;
}

void context::on_size(const dimension& size) {
    _size = size;
    glViewport(0, 0, _size.x, _size.y);
}


bool context::is_live(void* obj) {
    return _live_objects.find(obj) != _live_objects.end();
}

void context::mark_live(void* obj) {
    _live_objects.insert(obj);
}

void context::mark_dead(void* obj) {
    _live_objects.erase(obj);
}


}
}
