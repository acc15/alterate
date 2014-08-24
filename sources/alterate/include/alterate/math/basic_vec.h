#pragma once

#include <alterate/math/vector_support.h>

namespace alterate {
    namespace math {

        template <typename VectorType, typename StorageType>
        class basic_vec : public vector_support < VectorType, StorageType > {
        public:

            basic_vec() {
            }

            template <typename U>
            basic_vec(U const& v) : vector_support(v) {
            }

            template <typename U>
            basic_vec(std::initializer_list<U> const& l) : vector_support(l) {
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
                return dot(vector());
            }

            value_type length() const {
                return sqrt(length_square());
            }

            vector_type& normalize() {
                return vector() /= length();
            }

            template <typename U>
            vector_type& resize(U const& to_length) {
                return vector() *= (to_length / length());
            }
        };


    }
}