#include <array>

#include <alterate/math/vector_support.h>
#include <alterate/iterator/random_access_iterator_support.h>

#include <alterate/error.h>

namespace alterate {
namespace math {

template <size_t Count, typename T>
struct vec: std::array<T, Count>, vector_support< vec<Count,T>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<Count,T>, T >   vector_support_type;
    typedef std::array<T, Count>                container_type;

    vec() {
    }

    template <typename U>
    vec(const U& p) : container_type(), vector_support_type(p) {
    }

    template <typename U>
    vec(const std::initializer_list<U>& l) : container_type(), vector_support_type(l) {
    }

};

template <typename T>
struct vec<1,T> : alterate::iterator::random_access_iterator_support<vec<1,T>, T>, vector_support<vec<1,T>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<1,T>, T >       vector_support_type;

    value_type x;

    vec() {
    }

    template <typename U>
    vec(const U& v) : vector_support_type(v) {
    }

    template <typename U>
    vec(const std::initializer_list<U>& l) : vector_support_type(l) {
    }

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

template <typename T>
struct vec<2,T> : alterate::iterator::random_access_iterator_support<vec<2,T>, T>, vector_support<vec<2,T>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<2,T>, T >       vector_support_type;

    value_type x;
    value_type y;

    vec() {
    }

    template <typename U>
    vec(const U& v) : vector_support_type(v) {
    }

    template <typename U>
    vec(const U& x, const U& y) : x(x), y(y) {
    }

    template <typename U>
    vec(const std::initializer_list<U>& l) : vector_support_type(l) {
    }

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

template <typename T>
struct vec<3,T> : alterate::iterator::random_access_iterator_support<vec<3,T>, T>, vector_support<vec<3,T>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<3,T>, T >       vector_support_type;

    value_type x;
    value_type y;
    value_type z;

    vec() {
    }

    template <typename U>
    vec(const U& v) : vector_support_type(v) {
    }

    template <typename U>
    vec(const U& x, const U& y) : x(x), y(y), z() {
    }

    template <typename U>
    vec(const U& x, const U& y, const U& z) : x(x), y(y), z(z) {
    }

    template <typename U>
    vec(const std::initializer_list<U>& l) : vector_support_type(l) {
    }

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

template <typename T>
struct vec<4,T> : alterate::iterator::random_access_iterator_support<vec<4,T>, T>, vector_support<vec<4,T>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<4,T>, T >       vector_support_type;

    value_type x;
    value_type y;
    value_type z;
    value_type w;

    vec() {
    }

    template <typename U>
    vec(const U& v) : vector_support_type(v) {
    }

    template <typename U>
    vec(const U& x, const U& y) : x(x), y(y), z(), w() {
    }

    template <typename U>
    vec(const U& x, const U& y, const U& z) : x(x), y(y), z(z), w() {
    }

    template <typename U>
    vec(const U& x, const U& y, const U& z, const U& w) : x(x), y(y), z(z), w(w) {
    }

    template <typename U>
    vec(const std::initializer_list<U>& l) : vector_support_type(l) {
    }

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

}
}
