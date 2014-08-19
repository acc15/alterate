#pragma once

#include <alterate/types.h>

namespace alterate {
    namespace iterable {

        template <typename ScalarType, typename SizeType = ::alterate::uint_t, typename OffsetType = ::alterate::int_t>
        class scalar_iterator : public std::iterator < std::random_access_iterator_tag, ScalarType, OffsetType > {
        public:
            typedef ScalarType  scalar_type;
            typedef SizeType    size_type;
            typedef OffsetType  offset_type;

        private:
            scalar_type value;
            size_type position;

        public:
            scalar_iterator() : value(), position(0) {
            }
            
            scalar_iterator(scalar_type const& value, size_type const& position = 0) :
                scalar_iterator::value(value),
                scalar_iterator::position(position) {
            }

            scalar_iterator& operator++(int dummy) {
                ++position;
                return *this;
            }

            scalar_iterator& operator++() {
                ++position;
                return *this;
            }

            scalar_iterator& operator--(int dummy) {
                --position;
                return *this;
            }

            scalar_iterator& operator--() {
                --position;
                return *this;
            }

            scalar_iterator operator+(size_type const& offset) {
                return scalar_iterator(value, position + offset);
            }

            scalar_iterator operator-(size_type const& offset) {
                return scalar_iterator(value, position - offset);
            }

            offset_type operator-(scalar_iterator const& i) {
                return position - i.position;
            }

            scalar_iterator& operator=(scalar_iterator const& i) {
                position = i.position;
                return *this;
            }

            scalar_iterator& operator+=(size_type const& offset) {
                position += offset;
                return *this;
            }

            scalar_iterator& operator-=(size_type const& offset) {
                position -= offset;
                return *this;
            }

            scalar_iterator& operator-=(scalar_iterator const& i) {
                position -= i.position;
                return *this;
            }

            bool_t operator>(scalar_iterator const& i) const {
                return position > i.position;
            }

            bool_t operator>=(scalar_iterator const& i) const {
                return position >= i.position;
            }

            bool_t operator<(scalar_iterator const& i) const {
                return position < i.position;
            }

            bool_t operator<=(scalar_iterator const& i) const {
                return position <= i.position;
            }

            bool_t operator==(scalar_iterator const& i) const {
                return value == i.value && position == i.position;
            }

            bool_t operator!=(scalar_iterator const& i) const {
                return value != i.value || position != i.position;
            }

            scalar_type& operator*() {
                return value;
            }

            scalar_type* operator->() {
                return &value;
            }
            
            scalar_type& operator[](size_type const& offset) {
                return value;
            }

        };

        template <typename ScalarType, typename SizeType>
        class scalar_iterable {
        public:
            typedef ScalarType scalar_type;
            typedef SizeType size_type;

        private:
            scalar_type value;
            size_type size;

        public:
            typedef scalar_iterator<scalar_type, size_type> const_iterator;

            scalar_iterable(scalar_type const& value, size_type const& size) :
                scalar_iterable::value(value),
                scalar_iterable::size(size) {
            }

            const_iterator cbegin() const {
                return scalar_iterator<scalar_type, size_type>(value);
            }

            const_iterator cend() const {
                return scalar_iterator<scalar_type, size_type>(value, size);
            }
        };


    }
}
