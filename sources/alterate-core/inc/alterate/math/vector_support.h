#pragma once

#include <alterate/math/generic_vector_support.h>

namespace alterate {
namespace math {

template <typename VectorType, typename ValueType>
class vector_support: public generic_vector_support<VectorType, ValueType> {
private:
    typedef generic_vector_support<VectorType, ValueType>   generic_vector_support_type;

public:
    typedef VectorType                                      vector_type;
    typedef ValueType                                       value_type;

    vector_support() {
    }

    template <typename U>
    vector_support(U const& v) : generic_vector_support_type(v) {
    }

    template <typename U>
    vector_support(std::initializer_list<U> const& l) : generic_vector_support_type(l) {
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
        return dot(generic_vector_support_type::vector());
    }

    value_type length() const {
        return sqrt(length_square());
    }

    vector_type& normalize() {
        return generic_vector_support_type::vector() /= length();
    }

    template <typename U>
    vector_type& resize(U const& to_length) {
        return generic_vector_support_type::vector() *= (to_length / length());
    }

};

}
}
