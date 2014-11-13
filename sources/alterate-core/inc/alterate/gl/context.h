#pragma once

#include <alterate/gl/gl_inc.h>

#include <alterate/dimension.h>
#include <alterate/gl/color.h>

namespace alterate {
namespace gl {

class context {
private:
    dimension _size;

public:
    context& clear_color(const color& color);
    context& clear();

    void on_size(const dimension& size);

};

}
}
