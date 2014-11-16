#include <alterate/gl/util.h>

namespace alterate {
namespace gl {

const char* get_gl_error_as_string(GLenum error_code) {
    switch (error_code) {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
    default: return "GL_UNKNOWN_ERROR";
    }
}

const char* get_gl_error_as_string() {
    return get_gl_error_as_string(glGetError());
}

std::string get_shader_info_log(GLuint shader_id) {
    GLint info_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_length);
    if (info_length <= 1) {
        return "";
    }

    std::string message(info_length, char());
    glGetShaderInfoLog(shader_id, info_length, NULL, &message[0]);

    // remove zero-terminator char
    message.resize(info_length-1);

    return message;
}

std::string get_program_info_log(GLuint program_id) {
    GLint info_length = 0;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_length);
    if (info_length <= 1) {
        return "";
    }

    std::string message(0, info_length);
    glGetProgramInfoLog(program_id, info_length, NULL, &message[0]);

    message.resize(message.length()-1);
    return message;
}


}
}
