#include <alterate/gl/vertex_buffer_layout.h>

namespace alterate {
namespace gl {

size_t vertex_buffer_layout::get_type_size(GLenum type) {
    switch (type) {
    case GL_FLOAT:          return sizeof(GLfloat);
    case GL_BYTE:           return sizeof(GLbyte);
    case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);

    case GL_SHORT:          return sizeof(GLshort);
    case GL_UNSIGNED_SHORT: return sizeof(GLushort);

    case GL_INT:            return sizeof(GLint);
    case GL_UNSIGNED_INT:   return sizeof(GLuint);

    case GL_FIXED:          return sizeof(GLfixed);
    }
}

vertex_buffer_layout::vertex_buffer_layout() {
}

vertex_buffer_layout::vertex_buffer_layout(const std::initializer_list<vertex_buffer_layout::layout_attribute>& attrs) {
    for (const vertex_buffer_layout::layout_attribute& attr: attrs) {
        attribute(attr.type, attr.next_offset);
    }
}

vertex_buffer_layout& vertex_buffer_layout::attribute(GLenum type, size_t size) {
    size_t prev_offset = _attrs.empty() ? 0 : _attrs.back().next_offset;
    _attrs.push_back({ type, prev_offset + get_type_size(type) * size });
    return *this;
}

size_t vertex_buffer_layout::size(size_t attr) const {
    check_attr(attr);
    size_t offset_diff = _attrs[attr].next_offset;
    if (attr > 0) {
        offset_diff -= _attrs[attr-1].next_offset;
    }
    return offset_diff;
}

size_t vertex_buffer_layout::count(size_t attr) const {
    check_attr(attr);
    return size(attr) / get_type_size(_attrs[attr].type);
}

GLenum vertex_buffer_layout::type(size_t attr) const {
    check_attr(attr);
    return _attrs[attr].type;
}

size_t vertex_buffer_layout::offset(size_t attr) const {
    if (attr == 0) {
        return 0;
    }
    return _attrs[attr-1].next_offset;
}

size_t vertex_buffer_layout::offset(size_t attr, size_t index) const {
    return stride() * index + offset(attr);
}

size_t vertex_buffer_layout::stride() const {
    return _attrs.empty() ? 0 : _attrs.back().next_offset;
}

size_t vertex_buffer_layout::attribute_by_offset(size_t offset) const {
    if (_attrs.empty()) {
        return -1;
    }
    offset %= stride();
    for (size_t i=0; i<_attrs.size(); i++) {
        if (offset < _attrs[i].next_offset) {
            return i;
        }
    }
}

}
}
