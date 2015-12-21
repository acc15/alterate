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
    scalar_iterator(const value_type& value = value_type(), difference_type position = 0) :
            _value(value),
            _position(position)
    {
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

template <typename ArrayType>
struct array_iterator_factory {

    enum { ARRAY_SIZE = std::extent<ArrayType>::value };

    typedef typename std::add_pointer<
            typename std::add_const<typename std::remove_extent<ArrayType>::type>::type>::type const_iterator;

    static const_iterator begin(const ArrayType& v) {
        return v;
    }

    static const_iterator end(const ArrayType& v, size_t /*unused*/) {
        return v + ARRAY_SIZE;
    }
};

template <typename PointerType>
struct pointer_iterator_factory {

    typedef typename std::add_pointer<
            typename std::add_const<typename std::remove_pointer<PointerType>::type>::type>::type const_iterator;

    static const_iterator begin(const PointerType& v) {
        return v;
    }

    static const_iterator end(const PointerType& v, size_t size) {
        return v + size;
    }
};


template <typename ContainerType>
struct container_iterator_factory {

    typedef typename ContainerType::const_iterator const_iterator;

    static const_iterator begin(const ContainerType& v) {
        return v.begin();
    }

    static const_iterator end(const ContainerType& v, size_t) {
        return v.end();
    }
};

/*
template <typename ScalarType>
struct scalar_iterator_factory {

    typedef scalar_iterator<const ScalarType> const_iterator;

    static const_iterator begin(const ScalarType& v) {
        return const_iterator(v, 0);
    }

    static const_iterator end(const ScalarType& v, size_t size) {
        return const_iterator(v, static_cast<const_iterator::difference_type>(size));
    }

};

// metafunction
template <typename ContainerType>
struct get_iterator_factory {

    typedef typename std::conditional<std::is_array<ContainerType>::value, array_iterator_factory<ContainerType>,
            typename std::conditional<std::is_pointer<ContainerType>::value, pointer_iterator_factory<ContainerType>,
            typename std::conditional<std::is_scalar<ContainerType>::value, scalar_iterator_factory<ContainerType>,
            container_iterator_factory<ContainerType> >::type >::type >::type value;

};

template <typename ContainerType>
struct iterator_factory: get_iterator_factory<ContainerType>::value {

    typedef typename get_iterator_factory<ContainerType>::value factory_type;
    typedef typename factory_type::const_iterator const_iterator;

};
*/
}