#pragma once

#include <memory>

#include <alterate/timing/timer.h>
#include <alterate/gl/context.h>

namespace alterate
{

class engine;

class engine_object {
public:
    virtual ~engine_object();

    virtual void on_update(float seconds);
    virtual void on_draw(gl::context& context);
    virtual void on_attach(engine& engine);
    virtual void on_detach(engine& engine);
    virtual void on_size(const dimension& size);

};


class engine {
private:
    static engine       _instance;

    gl::context         _context;
    timing::timer       _timer;

    std::unique_ptr<engine_object> _root;

    engine();
    void on_update();
    void on_draw();

public:

    void set_root(std::unique_ptr<engine_object>& obj);

    void on_initial_size(const dimension& size);
    void on_size(const dimension& size);
    void on_frame();

    static engine& get();
};

}
