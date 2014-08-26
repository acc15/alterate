#pragma once

#include <array>

#include <alterate/types.h>
#include <alterate/error.h>
#include <alterate/math/basic_vec.h>
#include <alterate/iterator/random_access_iterator_support.h>

namespace alterate {
    namespace math {
   
        template <typename ValueType, size_t Size>
        struct vec_storage : std::array < ValueType, Size > {
        };
        
        // Boost.Preprocessor can solve following code duplication
        // but it will be very hard to support those macro-spagetti-mix

        template <typename ValueType>
        struct vec_storage<ValueType, 1> : alterate::iterator::random_access_iterator_support< vec_storage<ValueType, 1> , ValueType> {
            value_type x;

            size_t size() const { return 1; }
            
            value_type& operator[](size_t i) {
                switch (i) {
                case 0: return x;
                default: throw make_out_of_range_error();
                }
            }
            
            const value_type& operator[](size_t i) const {
                switch (i) {
                case 0: return x;
                default: throw make_out_of_range_error();
                }
            }
        };
        
        template <typename ValueType>
        struct vec_storage<ValueType, 2> : alterate::iterator::random_access_iterator_support < vec_storage<ValueType, 2>, ValueType > {
            value_type x;
            value_type y;

            size_t size() const { return 2; }

            value_type& operator[](size_t i) {
                switch (i) {
                case 0: return x;
                case 1: return y;
                default: throw make_out_of_range_error(); 
                }
            }

            const value_type& operator[](size_t i) const {
                switch (i) {
                case 0: return x;
                case 1: return y;
                default: throw make_out_of_range_error();
                }
            }
        };
        
        template <typename ValueType>
        struct vec_storage<ValueType, 3> : alterate::iterator::random_access_iterator_support < vec_storage<ValueType, 3>, ValueType > {
            value_type x;
            value_type y;
            value_type z;

            size_t size() const { return 3; }

            value_type& operator[](size_t i) {
                switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: throw make_out_of_range_error();
                }
            }

            const value_type& operator[](size_t i) const {
                switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: throw make_out_of_range_error();
                }
            }
        };

        template <typename ValueType>
        struct vec_storage<ValueType, 4> : alterate::iterator::random_access_iterator_support < vec_storage<ValueType, 4>, ValueType > {
            value_type x;
            value_type y;
            value_type z;
            value_type w;

            size_t size() const { return 4; }

            value_type& operator[](size_t i) {
                switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: throw make_out_of_range_error();
                }
            }

            const value_type& operator[](size_t i) const {
                switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: throw make_out_of_range_error();
                }
            }
        };

        template <typename T, size_t Count>
        class vec : public basic_vec<vec<T, Count>, vec_storage<T, Count>> {
        public:
            vec() {
            }

            template <typename U>
            vec(U const& v) : basic_vec(v) {
            }

            template <typename U>
            vec(std::initializer_list<U> const& l) : basic_vec(l) {
            }

        };

    }
} 