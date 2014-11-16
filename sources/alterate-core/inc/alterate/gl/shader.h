#pragma once

#include <alterate/gl/gl_inc.h>

namespace alterate {
namespace gl {

class shader {
private:
    const char* _source;
    const int   _type;
    GLuint      _id = 0;

public:
    shader(int type, const char* source);
    GLuint create();
};



}
}
