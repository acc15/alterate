#pragma once

#include <alterate/iterator/iterator_provider.h>
#include <alterate/functional/functors.h>
#include <alterate/functional/functional.h>

namespace alterate {
    namespace math {

        template <typename VectorType, typename StorageType>
        class vector_support : public StorageType {
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
            typedef typename StorageType::value_type   value_type;
            typedef typename StorageType::size_type    size_type;
            
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
            vector_type& set(U const& value) {
                return transform(value, alterate::functional::return_2nd());
            }
            
            template <typename Func>
            vector_type& for_each(Func const& func) {
                std::for_each(begin(), end(), func);
                return vector();
            }

            template <typename Func>
            vector_type const& for_each(Func const& func) const {
                std::for_each(begin(), end(), func);
                return vector();
            }

            template <typename U, typename Func>
            vector_type& transform(U const& v, Func const& func) {
                typedef alterate::iterable::iterator_provider<U, size_type> iterator_provider;
                alterate::functional::transform_safe(begin(), end(),
                    iterator_provider::begin(v), iterator_provider::end(v, size()), begin(), func);
                return vector();
            }

            template <typename Result, typename U, typename Func>
            Result accumulate(U const& v, Func const& func, Result init) const {
                typedef alterate::iterable::iterator_provider<U, size_type> iterator_provider;
                return alterate::functional::accumulate_safe(begin(), end(),
                    iterator_provider::begin(v), iterator_provider::end(v, size()), func, init);
            }

            vector_type& negate() {
                return for_each(alterate::functional::negate());
            }

            value_type const& comp(size_type const& i) const {
                return (*this)[i];
            }

            template <typename U>
            vector_type& comp(size_type const& i, U const& v) {
                (*this)[i] = static_cast<value_type>(v);
                return vector();
            }

            template <typename U>
            vector_type& operator=(U const& v) {
                return set(v);
            }

            template <typename U>
            vector_type& operator=(std::initializer_list<U> const& v) {
                return set(v);
            }

            template <typename U>
            vector_type& operator +=(U const& v) {
                return transform(v, alterate::functional::sum());
            }

            template <typename U>
            vector_type& operator -=(U const& v) {
                return transform(v, alterate::functional::subtract());
            }

            template <typename U>
            vector_type& operator *=(U const& v) {
                return transform(v, alterate::functional::multiply());
            }

            template <typename U>
            vector_type& operator /=(U const& v) {
                return transform(v, alterate::functional::divide());
            }

            template <typename U>
            vector_type operator +(U const& v) const {
                return copy_vector() += v;
            }

            template <typename U>
            vector_type operator -(U const& v) const {
                return copy_vector() -= v;
            }

            template <typename U>
            vector_type operator *(U const& v) const {
                return copy_vector() *= v;
            }

            template <typename U>
            vector_type operator /(U const& v) const {
                return copy_vector() /= v;
            }

            template <typename U>
            vector_type& operator+=(std::initializer_list<U> const& v) {
                return transform(v, alterate::functional::sum());
            }

            template <typename U>
            vector_type& operator-=(std::initializer_list<U> const& v) {
                return transform(v, alterate::functional::subtract());
            }

            template <typename U>
            vector_type& operator*=(std::initializer_list<U> const& v) {
                return transform(v, alterate::functional::multiply());
            }

            template <typename U>
            vector_type& operator/=(std::initializer_list<U> const& v) {
                return transform(v, alterate::functional::divide());
            }

            template <typename U>
            vector_type operator+(std::initializer_list<U> const& v) const {
                return copy_vector() += v;
            }

            template <typename U>
            vector_type operator-(std::initializer_list<U> const& v) const {
                return copy_vector() -= v;
            }

            template <typename U>
            vector_type operator*(std::initializer_list<U> const& v) const {
                return copy_vector() *= v;
            }

            template <typename U>
            vector_type operator/(std::initializer_list<U> const& v) const {
                return copy_vector() /= v;
            }

            vector_type operator-() const {
                return copy_vector().negate();
            }

        };
    }
}