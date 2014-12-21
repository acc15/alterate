#pragma once

#include <alterate/defs.h>
#include <alterate/gl/gl_inc.h>

namespace alterate {
namespace gl {

//template <GLenum Type> struct type_info { typedef std::nullptr_t type; };
//template <> struct type_info<GL_BYTE> { typedef GLbyte type; };
//template <> struct type_info<GL_UNSIGNED_BYTE> { typedef GLubyte type; };
//template <> struct type_info<GL_SHORT> { typedef GLshort type; };
//template <> struct type_info<GL_UNSIGNED_SHORT> { typedef GLushort type; };
//template <> struct type_info<GL_FIXED> { typedef GLfixed type; };
//template <> struct type_info<GL_INT> { typedef GLint type; };
//template <> struct type_info<GL_UNSIGNED_INT> { typedef GLuint type; };
//template <> struct type_info<GL_FLOAT> { typedef GLfloat type; };
//template <> struct type_info<GL_DOUBLE> { typedef GLdouble type; };


template <typename T> struct type_info {
    static bool is_compatible(GLenum type) { return false; }
};
template <> struct type_info<GLbyte> {
    static bool is_compatible(GLenum type) { return type == GL_BYTE; }
};
template <> struct type_info<GLubyte> {
    static bool is_compatible(GLenum type) { return type == GL_UNSIGNED_BYTE; }
};
template <> struct type_info<GLshort> {
    static bool is_compatible(GLenum type) { return type == GL_SHORT; }
};
template <> struct type_info<GLushort> {
    static bool is_compatible(GLenum type) { return type == GL_UNSIGNED_SHORT; }
};
template <> struct type_info<GLint> {
    static bool is_compatible(GLenum type) { return type == GL_INT || type == GL_FIXED; }
};
template <> struct type_info<GLuint> {
    static bool is_compatible(GLenum type) { return type == GL_UNSIGNED_INT; }
};
template <> struct type_info<GLfloat> {
    static bool is_compatible(GLenum type) { return type == GL_FLOAT; }
};
template <> struct type_info<GLdouble> {
    static bool is_compatible(GLenum type) { return type == GL_DOUBLE; }
};

}
}
