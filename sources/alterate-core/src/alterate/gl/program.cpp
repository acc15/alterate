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
        glAttachShader(_id, shader_id);
    }

    // bind attributes..
    //glBindAttribLocation(program_id, 0, "vPosition");

    // Link the program
    glLinkProgram(_id);

    GLint linked;
    glGetProgramiv(_id, GL_LINK_STATUS, &linked);
    if (!linked) {
        std::cerr << "Unable to link program: " << alterate::gl::get_program_info_log(_id) << std::endl;
        glDeleteProgram(_id);
        _id = 0;
        return false;
    }

    alterate::engine::get().get_context().mark_live(this);
    return true;
}


}
}
