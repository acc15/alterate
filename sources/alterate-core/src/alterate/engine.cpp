#include <boost/assert.hpp>

#include <alterate/engine.h>

#include <GL/gl.h>

extern void alterate_init();

namespace alterate {

engine_handler::~engine_handler() {
}

void engine_handler::on_update(float /*seconds*/) {

}

void engine_handler::on_draw(gl::context& /*context*/) {

}

void engine_handler::on_attach() {

}

void engine_handler::on_detach() {

}

void engine_handler::on_size(const dimension& /*size*/) {

}


engine engine::_instance;


engine::engine() : _handler(nullptr) {
}

engine::~engine() {
    if (_handler != nullptr) {
        delete _handler;
    }
}

void engine::on_initial_size(const dimension &size) {
    glViewport(0, 0, _size.x, _size.y);
}

void engine::on_update() {
    float seconds = _timer.reset();
    _handler->on_update(seconds);
}

void engine::on_draw() {
    _handler->on_draw(_context);
}

void engine::on_size(const dimension& size) {
    on_initial_size(size);
    _handler->on_size(size);
}

void engine::on_frame() {
    on_update();
    on_draw();
}

void engine::terminate() {
    BOOST_ASSERT_MSG(_handler != nullptr, "Engine handler not set");
    _handler->on_detach();
    delete _handler;
    _handler = nullptr;
}

gl::context& engine::get_context() {
    return _context;
}

bool engine::is_initialized() const {
    return _handler != nullptr;
}

engine& engine::get() {
    return _instance;
}

}
