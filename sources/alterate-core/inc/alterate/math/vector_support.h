#pragma once

#include <alterate/iterator/iterator_factory.h>
#include <alterate/math/functional.h>

namespace alterate {
namespace math {

template <typename VectorType, typename ContainerType>
class vector_support: public ContainerType {
private:
    typedef VectorType                              vector_type;
    typedef ContainerType                           container_type;

protected:
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
    typedef typename container_type::value_type     value_type;

    vector_support() : container_type() {
    }

    template <typename U>
    vector_support(const U& v) : container_type() {
        *this = v;
    }

    template <typename U>
    vector_support(const std::initializer_list<U>& l) : container_type() {
        *this = l;
    }

    template <typename Func>
    vector_type& for_each(const Func& func) {
        std::for_each(vector().begin(), vector().end(), func);
        return vector();
    }

    template <typename Func>
    vector_type const& for_each(const Func& func) const {
        std::for_each(vector().begin(), vector().end(), func);
        return vector();
    }

    template <typename U, typename Func>
    vector_type& transform(const U& v, const Func& func) {
        typedef alterate::iterator::iterator_factory<U> iterator_factory;
        alterate::math::transform_safe(vector().begin(), vector().end(),
            iterator_factory::begin(v), iterator_factory::end(v, vector().size()), vector().begin(), func);
        return vector();
    }

    template <typename U, typename Func>
    value_type accumulate(const U& v, const Func& func, const value_type& initial = value_type()) const {
        typedef alterate::iterator::iterator_factory<U> iterator_factory;
        return alterate::math::accumulate_safe(vector().begin(), vector().end(),
            iterator_factory::begin(v), iterator_factory::end(v, vector().size()), func, initial);
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
