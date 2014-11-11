#pragma once

#include <GL/gl.h>

namespace alterate {

template <typename T>
class color {

public:
    T red;
    T green;
    T blue;
    T alpha;

    color(const T& red, const T& green, const T& blue, const T& alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

    static const color RED;
};

template <typename T> const color<T> color<T>::RED(1.f, 0.f, 0.f, 1.f);


typedef color<GLclampf> gl_color;

}

