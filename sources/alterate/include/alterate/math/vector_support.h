#pragma once

#include <alterate/meta/crtp_support.h>
#include <alterate/iterator/iterator_provider.h>
#include <alterate/functional/functors.h>
#include <alterate/functional/functional.h>

namespace alterate {
    namespace math {

        template <typename DerivedType, typename BaseType>
        struct vector_support : BaseType, protected alterate::meta::crtp_support < DerivedType > {

            typedef typename BaseType::value_type   value_type;
            typedef typename BaseType::size_type    size_type;
            
            vector_support() {
            }

            template <typename U>
            vector_support(U const& v) {
                set(v);
            }

            template <typename U>
            vector_support(std::initializer_list<U> const& l) {
                set(l);
            }

            template <typename U>
            derived_type& set(U const& value) {
                return transform(value, alterate::functional::return_2nd());
            }
            
            template <typename Func>
            derived_type& for_each(Func const& func) {
                std::for_each(begin(), end(), func);
                return derived();
            }

            template <typename Func>
            derived_type const& for_each(Func const& func) const {
                std::for_each(begin(), end(), func);
                return derived();
            }

            template <typename U, typename Func>
            derived_type& transform(U const& v, Func const& func) {
                typedef alterate::iterable::iterator_provider<U, size_type> iterator_provider;
                alterate::functional::transform_safe(begin(), end(),
                    iterator_provider::begin(v), iterator_provider::end(v, size()), begin(), func);
                return derived();
            }

            template <typename Result, typename U, typename Func>
            Result accumulate(U const& v, Func const& func, Result init) const {
                typedef alterate::iterable::iterator_provider<U, size_type> iterator_provider;
                return alterate::functional::accumulate_safe(begin(), end(),
                    iterator_provider::begin(v), iterator_provider::end(v, size()), func, init);
            }

            derived_type& negate() {
                return for_each(alterate::functional::negate());
            }

            value_type const& comp(size_type const& i) const {
                return derived()[i];
            }

            template <typename U>
            derived_type& comp(size_type const& i, U const& v) {
                derived()[i] = static_cast<value_type>(v);
                return derived();
            }

            template <typename U>
            derived_type& operator=(U const& v) {
                return set(v);
            }

            template <typename U>
            derived_type& operator=(std::initializer_list<U> const& v) {
                return set(v);
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
                return derived_copy() += v;
            }

            template <typename U>
            derived_type operator -(U const& v) const {
                return derived_copy() -= v;
            }

            template <typename U>
            derived_type operator *(U const& v) const {
                return derived_copy() *= v;
            }

            template <typename U>
            derived_type operator /(U const& v) const {
                return derived_copy() /= v;
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
    }
}