#pragma once

#include <GL/gl.h>

namespace alterate {
namespace gl {

class color {
public:
    GLclampf r;
    GLclampf g;
    GLclampf b;
    GLclampf a;

    color(const GLclampf& r, const GLclampf& g, const GLclampf& b, const GLclampf& a) : r(r), g(g), b(b), a(a) {}
    color(const GLclampf& r, const GLclampf& g, const GLclampf& b) : r(r), g(g), b(b), a(1.f) {}

    static const color RED;
    static const color GREEN;
    static const color BLUE;
    static const color BLACK;
    static const color WHITE;

};

}
}
