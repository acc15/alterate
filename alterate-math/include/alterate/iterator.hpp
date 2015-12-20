#pragma once

#include <cstddef>
#include <boost/iterator/iterator_facade.hpp>

namespace alterate {

template <typename ScalarType>
class scalar_iterator : public boost::iterator_facade<
        scalar_iterator<ScalarType>,
        ScalarType,
        boost::random_access_traversal_tag>
{
private:
    typedef boost::iterator_facade<
        scalar_iterator<ScalarType>,
        ScalarType,
        boost::random_access_traversal_tag
    > iterator_facade_type;

public:

    typedef ScalarType                                         value_type;
    typedef typename iterator_facade_type::difference_type     difference_type;
    typedef typename iterator_facade_type::reference           reference;

private:
    value_type      _value;
    difference_type _position;

public:
    scalar_iterator(const value_type& value = value_type(), size_t position = 0) : _value(value), _position(position) {
    }

private:
    friend class boost::iterator_core_access;

    reference dereference() const {
        return const_cast<reference>(_value);
    }

    bool equal(scalar_iterator const& other) const {
        return _value == other._value && _position == other._position;
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

    difference_type distance_to(scalar_iterator const& other) const {
        return other._position - _position;
    }
};

template <typename T>
struct container_iterator_factory {

    typedef T container_type;
    typedef typename container_type::const_iterator const_iterator;

    static const_iterator begin(const T& container) {
        return container.begin();
    }

    static const_iterator end(const T& container, size_t /*size*/) {
        return container.end();
    }

};



}