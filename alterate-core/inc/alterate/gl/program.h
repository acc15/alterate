#pragma once

#include <vector>

#include <alterate/gl/shader.h>

namespace alterate {
namespace gl {

class program {
private:
    GLuint                              _id = 0;

    std::vector<alterate::gl::shader*>  _shaders;

    std::vector<const GLchar*>          _attributes;
    std::vector<const GLchar*>          _uniforms;
    std::vector<GLint>                  _uniform_locations;

    GLuint cleanup();

public:

    ~program();

    program& shader(alterate::gl::shader& s);
    program& attribute(const GLchar* attribute_name);
    program& uniform(const GLchar* uniform_name);

    GLuint create();
    void remove();

    GLint get_uniform_location(size_t index) const;

};

}
}
