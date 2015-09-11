#include <stdexcept>

#include <boost/assert.hpp>

#include <alterate/gl/context.h>

namespace alterate {
namespace gl {

context::binder::binder(program &prg) : _prg(prg), _uniform_index(0), _attr_index(0), _vertex_count(no_value) {
}

GLint context::binder::next_uniform_location() {
    GLint loc = _prg.get_uniform_location(_uniform_index);
    ++_uniform_index;
    return loc;
}

GLint context::binder::next_attribute() {
    GLint attr_index = _attr_index;
    ++_attr_index;
    return attr_index;
}

void context::binder::adjust_vertex_count(size_t count) {
    if (_vertex_count > count) {
        _vertex_count = count;
    }
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
    default: throw std::invalid_argument("size");
    }
    return *this;
}

context::binder& context::binder::uniform(GLsizei size, GLsizei count, const GLint* value) {
    switch (size) {
    case 1: glUniform1iv(next_uniform_location(), count, value); break;
    case 2: glUniform2iv(next_uniform_location(), count, value); break;
    case 3: glUniform3iv(next_uniform_location(), count, value); break;
    case 4: glUniform4iv(next_uniform_location(), count, value); break;
    default: throw std::invalid_argument("size");
    }
    return *this;
}

context::binder& context::binder::uniform(const mat2& m) {
    glUniformMatrix2fv(next_uniform_location(), 1, GL_FALSE, m.data);
    return *this;
}

context::binder& context::binder::uniform(const mat3& m) {
    glUniformMatrix3fv(next_uniform_location(), 1, GL_FALSE, m.data);
    return *this;
}

context::binder& context::binder::uniform(const mat4& m) {
    glUniformMatrix4fv(next_uniform_location(), 1, GL_FALSE, m.data);
    return *this;
}

context::binder& context::binder::attribute(GLfloat v0) {
    glDisableVertexAttribArray(_attr_index);
    glVertexAttrib1f(_attr_index, v0);
    ++_attr_index;
    return *this;
}

context::binder& context::binder::attribute(GLfloat v0, GLfloat v1) {
    glDisableVertexAttribArray(_attr_index);
    glVertexAttrib2f(_attr_index, v0, v1);
    ++_attr_index;
    return *this;
}

context::binder& context::binder::attribute(GLfloat v0, GLfloat v1, GLfloat v2) {
    glDisableVertexAttribArray(_attr_index);
    glVertexAttrib3f(_attr_index, v0, v1, v2);
    ++_attr_index;
    return *this;
}

context::binder& context::binder::attribute(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glDisableVertexAttribArray(_attr_index);
    glVertexAttrib4f(_attr_index, v0, v1, v2, v3);
    ++_attr_index;
    return *this;
}

context::binder& context::binder::attribute(const vertex_buffer_data& buf, size_t vertex) {
    return attribute(buf, _attr_index, vertex);
}

context::binder& context::binder::attribute(const vertex_buffer_data& buf, size_t attr, size_t vertex) {
    glEnableVertexAttribArray(_attr_index);
    glVertexAttribPointer(_attr_index,
                          buf.element_count(attr),
                          buf.attribute_type(attr),
                          false,
                          buf.stride(),
                          buf.data(attr, vertex));
    ++_attr_index;
    adjust_vertex_count(buf.count() - vertex);
    return *this;
}

context::binder& context::binder::attributes(const vertex_buffer_data& buf, size_t vertex) {
    for (size_t i=0; i<buf.attribute_count(); i++) {
        attribute(buf, i, vertex);
    }
    return *this;
}

void context::binder::draw(GLenum what, size_t start, size_t count) {
    if (count == no_value) {
        count = _vertex_count != no_value ? _vertex_count : 0;
    }
    glDrawArrays(what, start, count);
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
