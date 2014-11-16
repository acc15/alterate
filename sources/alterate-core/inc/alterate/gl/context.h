#pragma once

#include <alterate/gl/gl_inc.h>

#include <alterate/dimension.h>
#include <alterate/gl/color.h>

#include <unordered_set>

namespace alterate {
namespace gl {

class context {
private:
    dimension _size;

    std::unordered_set<void*> _live_objects;

public:
    context& clear_color(const color& color);
    context& clear();

    void on_size(const dimension& size);

    bool is_live(void* obj);
    void mark_live(void* obj);
    void mark_dead(void* obj);

};

}
}
