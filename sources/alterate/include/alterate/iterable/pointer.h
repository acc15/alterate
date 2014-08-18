#pragma once

namespace alterate {
    namespace iterable {

        template <typename Type, typename SizeType>
        class pointer_iterable {
        public:
            typedef Type        value_type;
            typedef SizeType    size_type;

        private:
            value_type const* ptr;
            size_type size;

        public:
            typedef value_type const* const_iterator;

            pointer_iterable(value_type const* ptr, size_type size) : pointer_iterable::ptr(ptr), pointer_iterable::size(size) {
            }

            const_iterator cbegin() const {
                return ptr;
            }

            const_iterator cend() const {
                return ptr + size;
            }
        };

    }
}