#pragma once

#include <alterate/gl/gl_inc.h>

#include <alterate/dimension.h>
#include <alterate/gl/color.h>
#include <alterate/gl/program.h>

#include <alterate/math/matrix.h>

#include <unordered_set>

namespace alterate {
namespace gl {

template <size_t Size>
using matrix = math::matrix< GLfloat, Size, Size, math::column_major_order >;

// template <typename Vector, typename Layout>
// class vertex_buffer {
//    vertex_buffer_attribute get_attribute(size_t index);
//    template <typename T>
//    vertex_buffer& put(const T& value) {
//      _buffer.resize(_buffer.size() + sizeof(T));
//      *static_cast<T*>(&_buffer[_offset]) = value;
//    }
//    size_t size() const { return _buffer.size(); }
//    size_t count() const { _buffer.size() / _layout.stride(); }
// }

// class vertex_buffer_attribute

//template <size_t Count>
//class vertex_buffer_layout {

//  attribute(GLenum type = GL_FLOAT, GLint size = 4, GLboolean normalize = GL_FALSE);

//  const attribute_layout& get_attribute_layout(size_t index) const;
//  size_t stride() const;
//
//
//};

//vertex_buffer_layout<
//    layout_attribute<GL_FLOAT, 4,
//    layout_attribute<GL_INT, 4,
//    layout_attribute<GL_INT, 2
//    > > > layout;


//vertex_buffer_layout<
//    layout_attribute<GL_FLOAT, 4,
//    layout_attribute<GL_INT, 4,
//    layout_attribute<GL_INT, 2
//    > > > layout;


class context {
public:

    class binder {
        program& _prg;

        size_t _uniform_index;

        GLint next_uniform_location();

    public:

        binder(program& prg);

        binder& uniform(GLfloat v0);
        binder& uniform(GLfloat v0, GLfloat v1);
        binder& uniform(GLfloat v0, GLfloat v1, GLfloat v2);
        binder& uniform(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

        binder& uniform(GLint v0);
        binder& uniform(GLint v0, GLint v1);
        binder& uniform(GLint v0, GLint v1, GLint v2);
        binder& uniform(GLint v0, GLint v1, GLint v2, GLint v3);

        binder& uniform(GLsizei size, GLsizei count, const GLfloat* value);
        binder& uniform(GLsizei size, GLsizei count, const GLint* value);

        binder& uniform(const matrix<2>& m);
        binder& uniform(const matrix<3>& m);
        binder& uniform(const matrix<4>& m);

//      glDisableVertexAttribArray();
//        binder& attribute(GLfloat v0);
//        binder& attribute(GLfloat v0, GLfloat v1);
//        binder& attribute(GLfloat v0, GLfloat v1, GLfloat v2);
//        binder& attribute(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

//      glEnableVertexAttribArray();
        // Take size, type, normalization and stride from vertex_buffer_layout
        //binder& attribute(const vertex_buffer& buf, size_t index);

    };

    context& clear_color(const color& color);
    context& clear();

    binder use(program& prg);

};

}
}
