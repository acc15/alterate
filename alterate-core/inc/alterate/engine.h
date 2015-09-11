#pragma once

#include <memory>

#include <alterate/dimension.h>
#include <alterate/timing/timer.h>
#include <alterate/gl/context.h>

namespace alterate
{

class engine;

class engine_handler {
public:
    virtual ~engine_handler();

    virtual void on_update(float seconds);
    virtual void on_draw(gl::context& context);
    virtual void on_attach();
    virtual void on_detach();
    virtual void on_size(const dimension& size);

};


class engine {
private:
    static engine           _instance;

    gl::context             _context;
    timing::timer<float>    _timer;
    dimension               _screen_size;

    engine_handler*          _handler;

    engine();
    virtual ~engine();

    void on_update();
    void on_draw();

public:

    template <typename T, typename... Args>
    T* init(Args... args) {
        BOOST_ASSERT_MSG(_handler == nullptr, "Handler already set");
        T* h = new T(std::forward<Args>(args)...);
        _handler = h;
        _handler->on_attach();
        _handler->on_size(_screen_size);
        return h;
    }

    void terminate();

    void on_initial_size(const dimension& size);
    void on_size(const dimension& size);
    void on_frame();

    gl::context& get_context();

    bool is_initialized() const;
    const dimension& get_screen_size() const;

    static engine& get();
};

}
