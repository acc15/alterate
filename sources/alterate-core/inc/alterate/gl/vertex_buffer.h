#pragma once

#include <alterate/gl/type_info.h>
#include <alterate/gl/vertex_buffer_layout.h>

namespace alterate {
namespace gl {

class grow_strategy {
public:
    size_t compute_capacity(size_t current, size_t required);
};

class vertex_buffer_data: public vertex_buffer_layout {
protected:
    unsigned char*              _data;

    vertex_buffer_data(const vertex_buffer_layout& layout);

public:
    const void* data(size_t attr, size_t item = 0) const;
    void* data(size_t attr, size_t item = 0);
};

template <typename Strategy = grow_strategy, typename Allocator = std::allocator<unsigned char> >
class vertex_buffer: public vertex_buffer_data {
public:
    typedef Strategy                            strategy;
    typedef Allocator                           allocator;

private:
    strategy                    _strategy;
    allocator                   _allocator;

    size_t                      _capacity;
    size_t                      _position;

    void resize(size_t new_size) {
        size_t computed_capacity = std::max(_strategy.compute_capacity(_capacity, new_size), new_size);
        if (computed_capacity == _capacity) {
            return;
        }

        unsigned char* new_data = computed_capacity > 0 ? _allocator.allocate(computed_capacity) : nullptr;
        if (_data != nullptr) {
            if (new_data != nullptr) {
                std::copy(_data, _data + std::min(_capacity, computed_capacity), new_data);
            }
            _allocator.deallocate(_data, _capacity);
        }

        _data = new_data;
        _capacity = computed_capacity;
    }

public:
    vertex_buffer(const vertex_buffer_layout& layout) : vertex_buffer_data(layout), _position(0), _capacity(0) {
    }

    ~vertex_buffer() {
        if (_data != nullptr) {
            _allocator.deallocate(_data, _capacity);
        }
    }

    template <typename T>
    vertex_buffer& put(const T& value) {
        BOOST_ASSERT_MSG(type_info<T>::is_compatible(attribute_type(attribute_by_offset(_position))),
                         "Specified type of value didn't match buffer layout");
        resize(_position + sizeof(T));
        *reinterpret_cast<T*>(_data + _position) = value;
        _position += sizeof(T);
        return *this;
    }

    size_t attribute_index() const {
        return attribute_by_offset(_position);
    }

    vertex_buffer& clear(size_t reserve_count = 0) {
        _position = 0;
        resize(reserve_count * stride());
    }

    size_t element_count() const {
        return _position / stride();
    }

    size_t attribute_size() const {
        return _position;
    }

    size_t capacity() const {
        return _capacity;
    }

};

}
}
