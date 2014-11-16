#include <iostream>

#include <alterate/gl/program.h>
#include <alterate/engine.h>
#include <alterate/gl/util.h>

namespace alterate {
namespace gl {


program& program::add_shader(shader& shader) {
    _shaders.push_back(&shader);
    return *this;
}

program& program::add_attribute(const GLchar* attribute_name) {
    _attributes.push_back(attribute_name);
    return *this;
}

program& program::add_uniform(const GLchar* uniform_name) {
    _uniforms.push_back(uniform_name);
    return *this;
}

GLuint program::cleanup() {
    _uniform_locations.clear();
    glDeleteProgram(_id);
    return _id = 0;
    for (shader* shader: _shaders) {
        shader->remove();
    }

}

GLuint program::create() {

    if (alterate::engine::get().get_context().is_live(this)) {
        return _id;
    }

    _id = glCreateProgram();
    if (_id == 0) {
        std::cerr << "Unable to create program: " << alterate::gl::get_gl_error_as_string() << std::endl;
        return 0;
    }

    for (shader* shader: _shaders) {
        const GLuint shader_id = shader->create();
        if (shader_id == 0) {
            std::cerr << "Unable to compile one of program shader" << std::endl;
            return cleanup();
        }
        glAttachShader(_id, shader_id);

        GLenum error_code = glGetError();
        if (error_code != GL_NO_ERROR) {
            std::cerr << "Unable to attach shader(" << shader_id << ") to program(" << _id << "): " << get_gl_error_as_string(error_code) << std::endl;
            return cleanup();
        }

    }

    for (GLuint i=0; i<_attributes.size(); i++) {
        const GLchar* name = _attributes[i];
        glBindAttribLocation(_id, i, name);
    }

    // Link the program
    glLinkProgram(_id);

    GLint linked;
    glGetProgramiv(_id, GL_LINK_STATUS, &linked);
    if (!linked) {
        std::cerr << "Unable to link program: " << alterate::gl::get_program_info_log(_id) << std::endl;
        return cleanup();
    }

    glValidateProgram(_id);

    GLint valid;
    glGetProgramiv(_id, GL_VALIDATE_STATUS, &valid);
    if (!valid) {
        std::cerr << "Unable to validate program: " << alterate::gl::get_program_info_log(_id) << std::endl;
        return cleanup();
    }

    for (GLuint i=0; i<_uniforms.size(); i++) {
        const GLchar* name = _uniforms[i];
        GLint location = glGetUniformLocation(_id, name);
        if (location == -1) {
            std::cerr << "Unable to get uniform location \"" << name << "\": " << alterate::gl::get_gl_error_as_string() << std::endl;
            return cleanup();
        }
        _uniform_locations.push_back(location);
    }

    alterate::engine::get().get_context().mark_live(this);
    return _id;
}


}
}
