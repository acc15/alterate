#pragma once

#include <vector>

#include <alterate/gl/shader.h>

namespace alterate {
namespace gl {

class program {
private:

    std::vector<shader*> _shaders;
    GLuint               _id;

    std::vector<const GLchar*> _attributes;
    std::vector<const GLchar*> _uniforms;

    std::vector<GLint> _uniform_locations;

    GLuint cleanup();

public:

    program& add_shader(shader& shader);
    program& add_attribute(const GLchar* attribute_name);
    program& add_uniform(const GLchar* uniform_name);

    GLuint create();

};

}
}
