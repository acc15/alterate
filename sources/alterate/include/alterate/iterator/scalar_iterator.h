#pragma once

#include <boost/iterator/iterator_facade.hpp>

#include <alterate/types.h>

namespace alterate {
    namespace iterator {

        template <typename ScalarType>
        class scalar_iterator : public boost::iterator_facade<
                scalar_iterator<ScalarType>,
                ScalarType, 
                boost::random_access_traversal_tag> 
        {
        private:
            size_t      position;
            value_type  value;

        public:
            scalar_iterator(const value_type& value = value_type(), size_t position = 0) :
                scalar_iterator::value(value),
                scalar_iterator::position(position) {
            }

        private:
            friend class boost::iterator_core_access;

            reference dereference() const {
                return const_cast<reference>(value);
            }

            bool_t equal(scalar_iterator const& other) const {
                return value == other.value && position == other.position;
            }

            void increment() {
                ++position;
            }

            void decrement() {
                --position;
            }

            void advance(difference_type n) {
                position += n;
            }

            difference_type distance_to(scalar_iterator const& other) const {
                return other.position - position;
            }
        };

    }
}
