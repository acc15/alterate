#include <alterate/gl/vertex_buffer_layout.h>
#include <alterate/gl/type_info.h>

namespace alterate {
namespace gl {

vertex_buffer_layout::vertex_buffer_layout() {
}

vertex_buffer_layout::vertex_buffer_layout(const std::initializer_list<layout_attribute>& attrs) {
    for (const layout_attribute& attr: attrs) {
        register_attribute(attr.type, attr.next_offset);
    }
}

vertex_buffer_layout& vertex_buffer_layout::register_attribute(GLenum type, size_t size) {
    size_t prev_offset = _attrs.empty() ? 0 : _attrs.back().next_offset;
    _attrs.push_back({ type, prev_offset + get_type_size(type) * size });
    return *this;
}

size_t vertex_buffer_layout::attribute_size(size_t attr) const {
    check_attr(attr);
    size_t offset_diff = _attrs[attr].next_offset;
    if (attr > 0) {
        offset_diff -= _attrs[attr-1].next_offset;
    }
    return offset_diff;
}

size_t vertex_buffer_layout::element_count(size_t attr) const {
    check_attr(attr);
    return attribute_size(attr) / get_type_size(_attrs[attr].type);
}

GLenum vertex_buffer_layout::attribute_type(size_t attr) const {
    check_attr(attr);
    return _attrs[attr].type;
}

size_t vertex_buffer_layout::attribute_offset(size_t attr) const {
    if (attr == 0) {
        return 0;
    }
    return _attrs[attr-1].next_offset;
}

size_t vertex_buffer_layout::attribute_offset(size_t attr, size_t vertex) const {
    return stride() * vertex + attribute_offset(attr);
}

size_t vertex_buffer_layout::stride() const {
    return _attrs.empty() ? 0 : _attrs.back().next_offset;
}

size_t vertex_buffer_layout::attribute_count() const {
    return _attrs.size();
}

size_t vertex_buffer_layout::attribute_by_offset(size_t offset) const {
    if (_attrs.empty()) {
        return no_value;
    }
    offset %= stride();
    for (size_t i=0; i<_attrs.size(); i++) {
        if (offset < _attrs[i].next_offset) {
            return i;
        }
    }
    return no_value;
}

}
}
