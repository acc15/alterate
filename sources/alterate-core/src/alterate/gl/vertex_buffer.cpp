#include <alterate/gl/vertex_buffer.h>

namespace alterate {
namespace gl {

size_t grow_strategy::suggest_capacity(size_t current, size_t required) {
    return current < required ? required * 2 : current;
}

vertex_buffer_data::vertex_buffer_data(const vertex_buffer_layout& layout) : vertex_buffer_layout(layout), _data(nullptr), _position(0) {}

const void* vertex_buffer_data::data(size_t attr, size_t vertex) const {
    return _data + attribute_offset(attr, vertex);
}

void* vertex_buffer_data::data(size_t attr, size_t vertex) {
    return _data + attribute_offset(attr, vertex);
}

size_t vertex_buffer_data::count() const {
    return _position / stride();
}

size_t vertex_buffer_data::size() const {
    return _position;
}


}
}
