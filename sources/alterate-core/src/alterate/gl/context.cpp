#include <boost/assert.hpp>

#include <alterate/gl/context.h>

namespace alterate {
namespace gl {

context::binder::binder(program &prg) : _prg(prg), _uniform_index(0) {
}

GLint context::binder::next_uniform_location() {
    GLint loc = _prg.get_uniform_location(_uniform_index);
    ++_uniform_index;
    return loc;
}

context::binder& context::binder::uniform(GLfloat v0) {
    glUniform1f(next_uniform_location(), v0);
    return *this;
}

context::binder& context::binder::uniform(GLfloat v0, GLfloat v1) {
    glUniform2f(next_uniform_location(), v0, v1);
    return *this;
}

context::binder& context::binder::uniform(GLfloat v0, GLfloat v1, GLfloat v2) {
    glUniform3f(next_uniform_location(), v0, v1, v2);
    return *this;
}

context::binder& context::binder::uniform(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform4f(next_uniform_location(), v0, v1, v2, v3);
    return *this;
}

context::binder& context::binder::uniform(GLint v0) {
    glUniform1i(next_uniform_location(), v0);
    return *this;
}

context::binder& context::binder::uniform(GLint v0, GLint v1) {
    glUniform2i(next_uniform_location(), v0, v1);
    return *this;
}

context::binder& context::binder::uniform(GLint v0, GLint v1, GLint v2) {
    glUniform3i(next_uniform_location(), v0, v1, v2);
    return *this;
}

context::binder& context::binder::uniform(GLint v0, GLint v1, GLint v2, GLint v3) {
    glUniform4i(next_uniform_location(), v0, v1, v2, v3);
    return *this;
}

context::binder& context::binder::uniform(GLsizei size, GLsizei count, const GLfloat* value) {
    switch (size) {
    case 1: glUniform1fv(next_uniform_location(), count, value); break;
    case 2: glUniform2fv(next_uniform_location(), count, value); break;
    case 3: glUniform3fv(next_uniform_location(), count, value); break;
    case 4: glUniform4fv(next_uniform_location(), count, value); break;
    default:
        // print assertion failure
        BOOST_ASSERT_MSG(size >= 1 && size <= 4, "glUniformXfv called with incorrect size. Only 1,2,3,4 is allowed");
        break;
    }
    return *this;
}

context::binder& context::binder::uniform(GLsizei size, GLsizei count, const GLint* value) {
    switch (size) {
    case 1: glUniform1iv(next_uniform_location(), count, value); break;
    case 2: glUniform2iv(next_uniform_location(), count, value); break;
    case 3: glUniform3iv(next_uniform_location(), count, value); break;
    case 4: glUniform4iv(next_uniform_location(), count, value); break;
    default:
        // print assertion failure
        BOOST_ASSERT_MSG(size >= 1 && size <= 4, "glUniformXiv called with incorrect size. Only 1,2,3,4 is allowed");
        break;
    }
    return *this;
}

context::binder& context::binder::uniform(const matrix<2>& m) {
    glUniformMatrix2fv(next_uniform_location(), 1, GL_FALSE, m.data);
    return *this;
}

context::binder& context::binder::uniform(const matrix<3>& m) {
    glUniformMatrix3fv(next_uniform_location(), 1, GL_FALSE, m.data);
    return *this;
}

context::binder& context::binder::uniform(const matrix<4>& m) {
    glUniformMatrix4fv(next_uniform_location(), 1, GL_FALSE, m.data);
    return *this;
}

context& context::clear_color(const color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    return *this;
}

context& context::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    return *this;
}

context::binder context::use(program &prg) {
    glUseProgram(prg.create());
    return binder(prg);
}



}
}
