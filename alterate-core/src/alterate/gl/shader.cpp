#include <iostream>

#include <boost/assert.hpp>

#include <alterate/gl/shader.h>
#include <alterate/engine.h>
#include <alterate/gl/util.h>

namespace alterate {
namespace gl {

shader::shader(int type, const char* source) : _source(source), _type(type) {}

shader::~shader() {
    remove();
}

void shader::remove() {
    // Its assumed that
    // if _id is zero or even
    // if OpenGL wasnt initialized then nothing bad will happen.
    if (_id != 0) {
        glDeleteShader(_id);
    }
    _id = 0;
}

GLuint shader::create() {
    if (glIsShader(_id)) {
        return _id;
    }

    _id = glCreateShader(_type);
    if(_id == 0) {
        std::cerr << "Unable to create shader: " << alterate::gl::get_gl_error_as_string() << std::endl;
        return 0;
    }

    glShaderSource(_id, 1, &_source, NULL);
    glCompileShader(_id);

    GLint compiled;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
        std::cerr << "Unable to compile shader: " << alterate::gl::get_shader_info_log(_id) << ". Shader source: " << _source << std::endl;
        glDeleteShader(_id);
        return _id = 0;
    }
    return _id;
}

}
}
