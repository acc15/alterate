#include <alterate/gl/vertex_buffer.h>

namespace alterate {
namespace gl {

size_t grow_strategy::compute_capacity(size_t current, size_t required) {
    return current < required ? required * 2 : current;
}

vertex_buffer_data::vertex_buffer_data(const vertex_buffer_layout& layout) : vertex_buffer_layout(layout), _data(nullptr) {}

const void* vertex_buffer_data::data(size_t attr, size_t item) const {
    return _data + offset(attr, item);
}

void* vertex_buffer_data::data(size_t attr, size_t item) {
    return _data + offset(attr, item);
}

}
}
