#include <boost/assert.hpp>

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
}

void engine::on_draw() {
    _root->on_draw(_context);
}

void engine::on_size(const dimension& size) {
    //BOOST_ASSERT_MSG(_root != nullptr, "Root object not set");
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
