#pragma once

#include <string>

#include <alterate/gl/gl_inc.h>

namespace alterate {
namespace gl {

const char* get_gl_error_as_string(GLenum error_code);
const char* get_gl_error_as_string();

std::string get_shader_info_log(GLuint shaderId);
std::string get_program_info_log(GLuint programId);


}
}
