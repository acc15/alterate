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
