#pragma once

#include <alterate/gl/type_info.h>
#include <alterate/gl/vertex_buffer_layout.h>

namespace alterate {
namespace gl {

class grow_strategy {
public:
    size_t compute_capacity(size_t current, size_t required) {
        return current < required ? required * 2 : current;
    }
};


template <typename Strategy = grow_strategy, typename Allocator = std::allocator<unsigned char> >
class vertex_buffer {
public:
    typedef Strategy                            strategy;
    typedef Allocator                           allocator;
    typedef typename allocator::pointer    pointer;

private:
    vertex_buffer_layout    _layout;
    strategy                _strategy;
    allocator               _allocator;

    pointer                 _data;
    size_t                  _capacity;
    size_t                  _position;

    void resize(size_t new_size) {
        size_t computed_capacity = _strategy.compute_capacity(_capacity, new_size);
        if (computed_capacity == _capacity) {
            return;
        }

        pointer new_data = _allocator.allocate(computed_capacity);
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
    vertex_buffer(const vertex_buffer_layout& layout) : _layout(layout), _position(0), _capacity(0), _data(nullptr) {
    }

    ~vertex_buffer() {
        if (_data != nullptr) {
            _allocator.deallocate(_data, _capacity);
        }
    }

    const void* data() const {
        return _data;
    }

    void* data() {
        return _data;
    }

    const vertex_buffer_layout& layout() const {
        return _layout;
    }

    template <typename T>
    vertex_buffer& put(const T& value) {
        BOOST_ASSERT_MSG(type_info<T>::is_compatible(_layout.type(_layout.attribute_by_offset(_position))),
                         "Specified type of value didn't match buffer layout");
        resize(_position + sizeof(T));
        *reinterpret_cast<T*>(_data + _position) = value;
        _position += sizeof(T);
        return *this;
    }

    size_t attribute_index() const {
        return _layout.attribute_by_offset(_position);
    }

    template <typename T>
    T* attribute(size_t attr, size_t index) {
        return reinterpret_cast<T*>(_data + _layout.offset(attr, index));
    }

    template <typename T>
    const T* attribute(size_t attr, size_t index) const {
        return reinterpret_cast<const T*>(_data + _layout.offset(attr, index));
    }

    vertex_buffer& clear() {
        resize(0);
        _position = 0;
    }

    size_t count() const {
        return _position / _layout.stride();
    }

    size_t size() const {
        return _position;
    }

    size_t capacity() const {
        return _capacity;
    }

};

}
}
