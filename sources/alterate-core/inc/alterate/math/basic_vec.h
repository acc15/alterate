#pragma once

#include <alterate/defs.h>
#include <alterate/math/vector_support.h>

namespace alterate {
namespace math {

template <typename VectorType, typename ContainerType>
class basic_vec: public vector_support<VectorType, ContainerType> {
private:
    typedef vector_support<VectorType, ContainerType>   support_type;
    typedef VectorType                                  vector_type;
    typedef ContainerType                               container_type;

public:
    typedef typename container_type::value_type         value_type;

    basic_vec() : support_type() {
    }

    template <typename U>
    basic_vec(U const& v) : support_type(v) {
    }

    template <typename U>
    basic_vec(std::initializer_list<U> const& l) : support_type(l) {
    }

    template <typename U>
    value_type dot(U const& v) const {
        return accumulate(v, alterate::math::multiply(), value_type());
    }

    template <typename U>
    value_type dot(std::initializer_list<U> const& v) const {
        return accumulate(v, alterate::math::multiply(), value_type());
    }

    value_type length_square() const {
        return dot(support_type::vector());
    }

    value_type length() const {
        return sqrt(length_square());
    }

    vector_type& normalize() {
        return support_type::vector() /= length();
    }

    template <typename U>
    vector_type& resize(U const& to_length) {
        return support_type::vector() *= (to_length / length());
    }

};

}
}
