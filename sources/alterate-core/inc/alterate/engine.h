#pragma once

#include <alterate/timing/timer.h>
#include <alterate/gl/context.h>

namespace alterate
{

class engine {
private:
    static engine       _instance;

    gl::context         _context;
    timing::timer       _timer;

    engine();

    void on_update();
    void on_draw();

public:

    void on_frame();
    void on_size(const dimension& size);

    static engine& get();
};

}
