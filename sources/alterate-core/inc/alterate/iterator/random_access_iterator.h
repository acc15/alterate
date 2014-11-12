#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/assert.hpp>

#include <alterate/iterator/random_access_iterator.h>

namespace alterate {
namespace iterator {

template <typename ContainerType, typename ValueType>
class random_access_iterator: public boost::iterator_facade<
    random_access_iterator<ContainerType, ValueType>,
    ValueType,
    boost::random_access_traversal_tag>
{
private:
    typedef boost::iterator_facade<
        random_access_iterator<ContainerType, ValueType>,
        ValueType,
        boost::random_access_traversal_tag>                 iterator_facade_type;
    typedef ContainerType                                   container_type;

public:
    typedef ValueType                                       value_type;
    typedef typename iterator_facade_type::reference        reference;
    typedef typename iterator_facade_type::difference_type  difference_type;

private:
    container_type* _container_ptr;
    size_t _position;

public:
    random_access_iterator(size_t position = size_t()) : _container_ptr(nullptr), _position(position) {
    }

    random_access_iterator(container_type& container, size_t position = size_t()) : _container_ptr(&container), _position(position) {
    }

private:
    friend class boost::iterator_core_access;

    reference dereference() const {
        BOOST_ASSERT_MSG(_container_ptr != nullptr,
            "Attempt to dereference default constructed alterate::iterator::random_access_iterator");
        return (*_container_ptr)[_position];
    }

    bool equal(const random_access_iterator& other) const {
        return _container_ptr == other._container_ptr && _position == other._position;
    }

    void increment() {
        ++_position;
    }

    void decrement() {
        --_position;
    }

    void advance(difference_type n) {
        _position += n;
    }

    difference_type distance_to(random_access_iterator const& other) const {
        return other._position - _position;
    }
};


}
}
