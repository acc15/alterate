#pragma once

#include <algorithm>

#include <alterate/iterator/iterator_factory.h>
#include <alterate/math/functional.h>

namespace alterate {
namespace math {

template <typename VectorType, typename ValueType>
class generic_vector_support {
public:
    typedef ValueType                               value_type;
    typedef VectorType                              vector_type;

protected:
    vector_type& get_this() {
        return *static_cast<vector_type*>(this);
    }

    const vector_type& get_this() const {
        return *static_cast<const vector_type*>(this);
    }

    vector_type copy_vector() const {
        return vector_type(get_this());
    }

public:

    generic_vector_support() {
    }

    template <typename U>
    generic_vector_support(const U& v) {
        *this = v;
    }

    template <typename Func>
    vector_type& for_each(const Func& func) {
        std::for_each(get_this().begin(), get_this().end(), func);
        return get_this();
    }

    template <typename Func>
    vector_type const& for_each(const Func& func) const {
        std::for_each(get_this().begin(), get_this().end(), func);
        return get_this();
    }

    template <typename U, typename Func>
    vector_type& transform(const U& v, const Func& func) {
        typedef alterate::iterator::iterator_factory<U> iterator_factory;
        alterate::math::transform_safe(get_this().begin(), get_this().end(),
            iterator_factory::begin(v), iterator_factory::end(v, get_this().size()), get_this().begin(), func);
        return get_this();
    }

    template <typename U, typename Func>
    value_type accumulate(const U& v, const Func& func, const value_type& initial = value_type()) const {
        typedef alterate::iterator::iterator_factory<U> iterator_factory;
        return alterate::math::accumulate_safe(get_this().begin(), get_this().end(),
            iterator_factory::begin(v), iterator_factory::end(v, get_this().size()), func, initial);
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
