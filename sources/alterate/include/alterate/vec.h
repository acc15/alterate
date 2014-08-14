#pragma once

#include "types.h"

#include "../../src/alterate/iterators.h"
#include "../../src/alterate/functors.h"
#include "../../src/alterate/functional.h"

#include <array>

namespace alterate {

	template <typename TBase, typename TFinal>
	class basic_vec : public TBase {
	public:
		typedef TBase                               storage_type;
		typedef TFinal                              return_type;
		typedef typename TBase::value_type          value_type;

	private:
		return_type& get_this() {
			return *reinterpret_cast<return_type*>(this);
		}

		return_type const& get_this() const {
			return *reinterpret_cast<return_type const *>(this);
		}

		return_type make_copy() const {
			return return_type(get_this());
		}

	public:
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
		return_type& transform(U const& v, Func const& func) {
			typedef detail::iterator_for<U> iter;
			detail::transform_safe(begin(), end(), iter::begin(v), iter::end(v, size()), begin(), func);
			return get_this();
		}

		template <typename Result, typename U, typename Func>
		Result accumulate(U const& v, Func const& func, Result init) const {
			typedef detail::iterator_for<U> iter;
			return detail::accumulate_safe(begin(), end(), iter::begin(v), iter::end(v, size()), func, init);
		}

		value_type const& comp(uint_t i) const {
			return get_this()[i];
		}

		template <typename U>
		return_type& comp(uint_t i, U const& v) {
			get_this()[i] = static_cast<value_type>(v);
			return get_this();
		}

		return_type& negate() {
			std::for_each(begin(), end(), detail::negate());
			return get_this();
		}

		template <typename U>
		value_type dot(U const& v) const {
			return accumulate(v, detail::multiply(), value_type());
		}

		template <typename U>
		value_type dot(std::initializer_list<U> const& v) const {
			return accumulate(v, detail::multiply(), value_type());
		}

		value_type length_square() const {
			return dot(get_this());
		}

		value_type length() const {
			return sqrt(length_square());
		}

		return_type& normalize() {
			return get_this() /= length();
		}

		template <typename U>
		return_type& resize(U const& to_length) {
			return get_this() *= (to_length / length());
		}

		template <typename U>
		return_type& operator=(U const& v) {
			return transform(v, detail::return_2nd());
		}

		template <typename U>
		return_type& operator +=(U const& v) {
			return transform(v, detail::sum());
		}

		template <typename U>
		return_type& operator -=(U const& v) {
			return transform(v, detail::subtract());
		}

		template <typename U>
		return_type& operator *=(U const& v) {
			return transform(v, detail::multiply());
		}

		template <typename U>
		return_type& operator /=(U const& v) {
			return transform(v, detail::divide());
		}

		template <typename U>
		return_type operator +(U const& v) const {
			return make_copy() += v;
		}

		template <typename U>
		return_type operator -(U const& v) const {
			return make_copy() -= v;
		}

		template <typename U>
		return_type operator *(U const& v) const {
			return make_copy() *= v;
		}

		template <typename U>
		return_type operator /(U const& v) const {
			return make_copy() /= v;
		}


		template <typename U>
		return_type& operator=(std::initializer_list<U> const& v) {
			return transform(v, detail::return_2nd());
		}

		template <typename U>
		return_type& operator+=(std::initializer_list<U> const& v) {
			return transform(v, detail::sum());
		}

		template <typename U>
		return_type& operator-=(std::initializer_list<U> const& v) {
			return transform(v, detail::subtract());
		}

		template <typename U>
		return_type& operator*=(std::initializer_list<U> const& v) {
			return transform(v, detail::multiply());
		}

		template <typename U>
		return_type& operator/=(std::initializer_list<U> const& v) {
			return transform(v, detail::divide());
		}

		template <typename U>
		return_type operator+(std::initializer_list<U> const& v) const {
			return make_copy() += v;
		}

		template <typename U>
		return_type operator-(std::initializer_list<U> const& v) const {
			return make_copy() -= v;
		}

		template <typename U>
		return_type operator*(std::initializer_list<U> const& v) const {
			return make_copy() *= v;
		}

		template <typename U>
		return_type operator/(std::initializer_list<U> const& v) const {
			return make_copy() /= v;
		}

		return_type operator-() const {
			return make_copy().negate();
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