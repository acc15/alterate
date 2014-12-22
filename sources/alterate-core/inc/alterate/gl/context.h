#pragma once

#include <alterate/gl/gl_inc.h>

#include <alterate/dimension.h>
#include <alterate/gl/color.h>
#include <alterate/gl/program.h>
#include <alterate/gl/vertex_buffer.h>

#include <alterate/math/matrix.h>

#include <unordered_set>

namespace alterate {
namespace gl {

typedef math::matrix< GLfloat, 2, 2, math::column_major_order > mat2;
typedef math::matrix< GLfloat, 3, 3, math::column_major_order > mat3;
typedef math::matrix< GLfloat, 4, 4, math::column_major_order > mat4;

class context {
public:

    class binder {
        program& _prg;

        size_t _uniform_index;
        size_t _attr_index;
        size_t _vertex_count;

        GLint next_uniform_location();
        GLint next_attribute();

        void adjust_vertex_count(size_t count);

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

        binder& uniform(const mat2& m);
        binder& uniform(const mat3& m);
        binder& uniform(const mat4& m);

        binder& attribute(GLfloat v0);
        binder& attribute(GLfloat v0, GLfloat v1);
        binder& attribute(GLfloat v0, GLfloat v1, GLfloat v2);
        binder& attribute(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
        binder& attribute(const vertex_buffer_data& buf, size_t vertex = 0);
        binder& attribute(const vertex_buffer_data& buf, size_t attr, size_t vertex = 0);
        binder& attributes(const vertex_buffer_data& buf, size_t vertex = 0);

        void draw(GLenum what, size_t start = 0, size_t count = no_value);

    };

    context& clear_color(const color& color);
    context& clear();

    binder use(program& prg);

};

}
}
