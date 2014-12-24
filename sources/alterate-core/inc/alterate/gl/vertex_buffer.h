#pragma once

#include <algorithm>

#include <alterate/iterator/iterator_factory.h>

#include <alterate/gl/type_info.h>
#include <alterate/gl/vertex_buffer_layout.h>

namespace alterate {
namespace gl {

class grow_strategy {
public:
    size_t suggest_capacity(size_t current, size_t required);
};

class vertex_buffer_data: public vertex_buffer_layout {
protected:
    unsigned char*              _data;
    size_t                      _position;

    vertex_buffer_data(const vertex_buffer_layout& layout);

public:
    const void* data(size_t attr, size_t vertex = 0) const;
    void* data(size_t attr, size_t vertex = 0);
    size_t count() const;
    size_t size() const;
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

    void resize(size_t new_size) {
        size_t new_capacity = _strategy.suggest_capacity(_capacity, new_size);
        BOOST_ASSERT_MSG(new_capacity >= new_size, "Suggested capacity is less then required capacity.");
        if (new_capacity == _capacity) {
            return;
        }

        unsigned char* new_data = new_capacity > 0 ? _allocator.allocate(new_capacity) : nullptr;
        if (_data != nullptr) {
            if (new_data != nullptr) {
                std::copy(_data, _data + std::min(_capacity, new_capacity), new_data);
            }
            _allocator.deallocate(_data, _capacity);
        }

        _data = new_data;
        _capacity = new_capacity;
    }

public:
    vertex_buffer(const vertex_buffer_layout& layout) : vertex_buffer_data(layout), _capacity(0) {
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

    template <typename Vector>
    vertex_buffer& put_all(const Vector& vec) {
        typedef typename Vector::value_type value_type;
        size_t new_position = _position + sizeof(value_type) * vec.size();
        resize(new_position);
        std::copy(vec.begin(), vec.end(), reinterpret_cast<value_type*>(_data + _position));
        _position = new_position;
        return *this;
    }

    size_t attribute_index() const {
        return attribute_by_offset(_position);
    }

    vertex_buffer& clear(size_t reserve_vertex_count = 0) {
        _position = 0;
        resize(reserve_vertex_count * stride());
        return *this;
    }

    size_t capacity() const {
        return _capacity;
    }

};

}
}
