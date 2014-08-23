#pragma once

#include <array>

#include <alterate/types.h>
#include <alterate/math/vector_support.h>

namespace alterate {
    namespace math {
        template <typename T, uint_t Count>
        class vec : public alterate::math::vector_support < vec<T, Count>, std::array<T, Count> > {
        public:
            vec() {
            }

            template <typename U>
            vec(U const& v) : vector_support(v) {
            }

            template <typename U>
            vec(std::initializer_list<U> const& l) : vector_support(l) {
            }

            template <typename U>
            value_type dot(U const& v) const {
                return accumulate(v, alterate::functional::multiply(), value_type());
            }

            template <typename U>
            value_type dot(std::initializer_list<U> const& v) const {
                return accumulate(v, alterate::functional::multiply(), value_type());
            }

            value_type length_square() const {
                return dot(derived());
            }

            value_type length() const {
                return sqrt(length_square());
            }

            derived_type& normalize() {
                return derived() /= length();
            }

            template <typename U>
            derived_type& resize(U const& to_length) {
                return derived() *= (to_length / length());
            }
        };

    }
}