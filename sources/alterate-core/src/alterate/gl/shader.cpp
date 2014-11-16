#include <iostream>

#include <boost/assert.hpp>

#include <alterate/gl/shader.h>
#include <alterate/engine.h>
#include <alterate/gl/util.h>

namespace alterate {
namespace gl {

shader::shader(int type, const char* source) : _source(source), _type(type) {}

void shader::remove() {
    BOOST_ASSERT_MSG(_id != 0, "Attempt to delete shader which wasn't created");
    glDeleteShader(_id);
    _id = 0;
}

GLuint shader::create() {

    if (alterate::engine::get().get_context().is_live(this)) {
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

    alterate::engine::get().get_context().mark_live(this);
    return _id;
}

}
}
