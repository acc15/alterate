#include <stdexcept>

#include <alterate/gl/type_info.h>

namespace alterate {
namespace gl {


size_t get_type_size(GLenum type) {
    switch (type) {
    case GL_FLOAT:          return sizeof(GLfloat);
    case GL_BYTE:           return sizeof(GLbyte);
    case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);

    case GL_SHORT:          return sizeof(GLshort);
    case GL_UNSIGNED_SHORT: return sizeof(GLushort);

    case GL_INT:            return sizeof(GLint);
    case GL_UNSIGNED_INT:   return sizeof(GLuint);

    case GL_FIXED:          return sizeof(GLfixed);
    default:                throw std::invalid_argument("type");
    }
}

}
}
