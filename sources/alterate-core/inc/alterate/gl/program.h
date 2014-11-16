#pragma once

#include <vector>

#include <alterate/gl/shader.h>

namespace alterate {
namespace gl {

class program {
private:

    std::vector<shader*> _shaders;
    GLuint               _id;

public:

    program& add_shader(shader& shader);
    GLuint create();

};

}
}
