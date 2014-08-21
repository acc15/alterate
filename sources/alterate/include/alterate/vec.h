#pragma once

#include "types.h"

#include <alterate/patterns/crtp_support.h>
#include <alterate/iterator/iterator_provider.h>
#include <alterate/functional/functors.h>
#include <alterate/functional/functional.h>

#include <array>

namespace alterate {

    template <typename DerivedType, typename BaseType>
    struct basic_vec : BaseType, private crtp_support<DerivedType> {
        basic_vec() {
            std::fill(begin(), end(), value_type());
        }

        template <typename U>
        basic_vec(U const& v) {
            *this = v;
        }

        template <typename U>
        basic_vec(std::initializer_list<U> const& l) {
            *this = l;
        }

        template <typename U, typename Func>
        derived_type& transform(U const& v, Func const& func) {
            typedef alterate::iterable::iterator_provider<U, size_type> iterator_provider;
            alterate::functional::transform_safe(begin(), end(), 
                iterator_provider::begin(v), iterator_provider::end(v, size()), begin(), func);
            return get_this();
        }

        template <typename Result, typename U, typename Func>
        Result accumulate(U const& v, Func const& func, Result init) const {
            typedef alterate::iterable::iterator_provider<U, size_type> iterator_provider;
            return alterate::functional::accumulate_safe(begin(), end(), 
                iterator_provider::begin(v), iterator_provider::end(v, size()), func, init);
        }

        value_type const& comp(uint_t i) const {
            return get_this()[i];
        }

        template <typename U>
        derived_type& comp(uint_t i, U const& v) {
            get_this()[i] = static_cast<value_type>(v);
            return get_this();
        }

        derived_type& negate() {
            std::for_each(begin(), end(), alterate::functional::negate());
            return get_this();
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
            return dot(get_this());
        }

        value_type length() const {
            return sqrt(length_square());
        }

        derived_type& normalize() {
            return get_this() /= length();
        }

        template <typename U>
        derived_type& resize(U const& to_length) {
            return get_this() *= (to_length / length());
        }

        template <typename U>
        derived_type& operator=(U const& v) {
            return transform(v, alterate::functional::return_2nd());
        }

        template <typename U>
        derived_type& operator +=(U const& v) {
            return transform(v, alterate::functional::sum());
        }

        template <typename U>
        derived_type& operator -=(U const& v) {
            return transform(v, alterate::functional::subtract());
        }

        template <typename U>
        derived_type& operator *=(U const& v) {
            return transform(v, alterate::functional::multiply());
        }

        template <typename U>
        derived_type& operator /=(U const& v) {
            return transform(v, alterate::functional::divide());
        }

        template <typename U>
        derived_type operator +(U const& v) const {
            return make_copy() += v;
        }

        template <typename U>
        derived_type operator -(U const& v) const {
            return make_copy() -= v;
        }

        template <typename U>
        derived_type operator *(U const& v) const {
            return make_copy() *= v;
        }

        template <typename U>
        derived_type operator /(U const& v) const {
            return make_copy() /= v;
        }

        template <typename U>
        derived_type& operator=(std::initializer_list<U> const& v) {
            return transform(v, alterate::functional::return_2nd());
        }

        template <typename U>
        derived_type& operator+=(std::initializer_list<U> const& v) {
            return transform(v, alterate::functional::sum());
        }

        template <typename U>
        derived_type& operator-=(std::initializer_list<U> const& v) {
            return transform(v, alterate::functional::subtract());
        }

        template <typename U>
        derived_type& operator*=(std::initializer_list<U> const& v) {
            return transform(v, alterate::functional::multiply());
        }

        template <typename U>
        derived_type& operator/=(std::initializer_list<U> const& v) {
            return transform(v, alterate::functional::divide());
        }

        template <typename U>
        derived_type operator+(std::initializer_list<U> const& v) const {
            return derived_copy() += v;
        }

        template <typename U>
        derived_type operator-(std::initializer_list<U> const& v) const {
            return derived_copy() -= v;
        }

        template <typename U>
        derived_type operator*(std::initializer_list<U> const& v) const {
            return derived_copy() *= v;
        }

        template <typename U>
        derived_type operator/(std::initializer_list<U> const& v) const {
            return derived_copy() /= v;
        }

        derived_type operator-() const {
            return derived_copy().negate();
        }
    };

    template <uint_t Count, typename T = sp_t>
    class vec : public basic_vec<std::array<T, Count>, vec<Count, T>> {
    public:
        vec() : basic_vec() {
        }

        template <typename U>
        vec(U const& v) : basic_vec(v) {
        }

        template <typename U>
        vec(std::initializer_list<U> const& l) : basic_vec(l) {
        }
    };

}
