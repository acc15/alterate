#include <array>

#include <alterate/math/vector_support.h>
#include <alterate/iterator/random_access_iterator_support.h>

#include <alterate/error.h>

namespace alterate {
namespace math {

template <typename T, size_t Count>
struct vec: std::array<T, Count>, vector_support< vec<T, Count>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<T, Count>, T >  vector_support_type;
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
struct vec<T,1> : alterate::iterator::random_access_iterator_support<vec<T,1>, T>, vector_support<vec<T,1>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<T,1>, T >       vector_support_type;

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
        return (&x)[i];
    }

    const value_type& operator[](size_t i) const {
        return (&x)[i];
    }

};

template <typename T>
struct vec<T,2> : alterate::iterator::random_access_iterator_support<vec<T,2>, T>, vector_support<vec<T,2>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<T,2>, T >       vector_support_type;

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
        return (&x)[i];
    }

    const value_type& operator[](size_t i) const {
        return (&x)[i];
    }
};

template <typename T>
struct vec<T,3> : alterate::iterator::random_access_iterator_support<vec<T,3>, T>, vector_support<vec<T,3>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<T,3>, T >       vector_support_type;

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
        return (&x)[i];
    }

    const value_type& operator[](size_t i) const {
        return (&x)[i];
    }
};

template <typename T>
struct vec<T,4> : alterate::iterator::random_access_iterator_support<vec<T,4>, T>, vector_support<vec<T,4>, T> {

    typedef T                                   value_type;
    typedef vector_support< vec<T,4>, T >       vector_support_type;

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
        return (&x)[i];
    }

    const value_type& operator[](size_t i) const {
        return (&x)[i];
    }
};

}
}
