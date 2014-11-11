#pragma once

#include <alterate/iterator/iterator_factory.h>
#include <alterate/math/functional.h>

namespace alterate {
namespace math {

template <typename VectorType>
class vector_support {
protected:
    typedef VectorType vector_type;

    vector_type& vector() {
        return *static_cast<vector_type*>(this);
    }

    const vector_type& vector() const {
        return *static_cast<const vector_type*>(this);
    }

    vector_type copy_vector() const {
        return vector_type(vector());
    }

public:
    typedef typename VectorType::value_type   value_type;

    vector_support() {
    }

    template <typename U>
    vector_support(const U& v) {
        *this = v;
    }

    template <typename U>
    vector_support(const std::initializer_list<U>& l) {
        *this = l;
    }

    template <typename Func>
    vector_type& for_each(const Func& func) {
        std::for_each(begin(), end(), func);
        return vector();
    }

    template <typename Func>
    vector_type const& for_each(const Func& func) const {
        std::for_each(begin(), end(), func);
        return vector();
    }

    template <typename U, typename Func>
    vector_type& transform(const U& v, const Func& func) {
        typedef alterate::iterator::iterator_factory<U> iterator_factory;
        alterate::math::transform_safe(begin(), end(),
            iterator_factory::begin(v), iterator_factory::end(v, size()), begin(), func);
        return vector();
    }

    template <typename Result, typename U, typename Func>
    Result accumulate(const U& v, const Func& func, const Result& init = Result()) const {
        typedef alterate::iterator::iterator_factory<U> iterator_factory;
        return alterate::math::accumulate_safe(begin(), end(),
            iterator_factory::begin(v), iterator_factory::end(v, size()), func, init);
    }

    vector_type& negate() {
        return for_each(alterate::math::negate());
    }

    template <typename U>
    vector_type& operator=(const U& v) {
        return transform(v, alterate::math::return_2nd());
    }

    template <typename U>
    vector_type& operator=(const std::initializer_list<U>& v) {
        return transform(v, alterate::math::return_2nd());
    }

    template <typename U>
    vector_type& operator +=(const U& v) {
        return transform(v, alterate::math::sum());
    }

    template <typename U>
    vector_type& operator -=(const U& v) {
        return transform(v, alterate::math::subtract());
    }

    template <typename U>
    vector_type& operator *=(const U& v) {
        return transform(v, alterate::math::multiply());
    }

    template <typename U>
    vector_type& operator /=(const U& v) {
        return transform(v, alterate::math::divide());
    }

    template <typename U>
    vector_type operator +(const U& v) const {
        return copy_vector() += v;
    }

    template <typename U>
    vector_type operator -(const U& v) const {
        return copy_vector() -= v;
    }

    template <typename U>
    vector_type operator *(const U& v) const {
        return copy_vector() *= v;
    }

    template <typename U>
    vector_type operator /(const U& v) const {
        return copy_vector() /= v;
    }

    template <typename U>
    vector_type& operator+=(const std::initializer_list<U>& v) {
        return transform(v, alterate::math::sum());
    }

    template <typename U>
    vector_type& operator-=(const std::initializer_list<U>& v) {
        return transform(v, alterate::math::subtract());
    }

    template <typename U>
    vector_type& operator*=(const std::initializer_list<U>& v) {
        return transform(v, alterate::math::multiply());
    }

    template <typename U>
    vector_type& operator/=(const std::initializer_list<U>& v) {
        return transform(v, alterate::math::divide());
    }

    template <typename U>
    vector_type operator+(const std::initializer_list<U>& v) const {
        return copy_vector() += v;
    }

    template <typename U>
    vector_type operator-(const std::initializer_list<U>& v) const {
        return copy_vector() -= v;
    }

    template <typename U>
    vector_type operator*(const std::initializer_list<U>& v) const {
        return copy_vector() *= v;
    }

    template <typename U>
    vector_type operator/(const std::initializer_list<U>& v) const {
        return copy_vector() /= v;
    }

    vector_type operator-() const {
        return copy_vector().negate();
    }

};

}
}
