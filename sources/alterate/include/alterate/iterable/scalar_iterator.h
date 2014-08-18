#pragma once

#include <alterate/types.h>

namespace alterate {
    namespace iterable {

        template <typename ScalarType, typename SizeType = ::alterate::uint_t>
        class scalar_iterator : public std::iterator < std::random_access_iterator_tag, ScalarType, SizeType > {
        public:
            typedef ScalarType scalar_type;
            typedef SizeType size_type;

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

            scalar_iterator operator-(scalar_iterator const& i) {
                return scalar_iterator(value, position - i.position);
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

            scalar_type const& operator*() {
                return value;
            }

            scalar_type const* operator->() {
                return &value;
            }

        };

    }
}