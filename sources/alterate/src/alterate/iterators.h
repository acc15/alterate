#pragma once

#include "types.h"
#include <type_traits>

namespace alterate {
    namespace detail {

        template <typename T>
        struct array_iterator_provider {

            typedef typename std::extent<T, 0> extent;
            typedef typename std::add_pointer< typename std::add_const< typename std::remove_extent<T>::type >::type >::type iterator;

            static iterator begin(T const& v) {
                return v;
            }

            static iterator end(T const& v, uint_t size) {
                return v + extent::value;
            }
        };

        template <typename T>
        struct pointer_iterator_provider {

            typedef typename std::add_pointer< typename std::add_const< typename std::remove_pointer<T>::type >::type >::type iterator;

            static iterator begin(T const& v) {
                return v;
            }

            static iterator end(T const& v, uint_t size) {
                return v + size;
            }
        };


        template <typename T>
        struct container_iterator_provider {

            typedef typename T::const_iterator iterator;

            static iterator begin(T const& v) {
                return v.begin();
            }

            static iterator end(T const& v, uint_t size) {
                return v.end();
            }
        };

        template <typename T>
        struct scalar_iterator_provider {

            class iterator {
            private:
                uint_t _pos;
                T const& _value;

            public:
                iterator(T const& v, uint_t pos) : _pos(pos), _value(v) {
                }

                iterator& operator--(int dummy) {
                    --_pos;
                    return *this;
                }

                iterator& operator++(int dummy) {
                    ++_pos;
                    return *this;
                }

                iterator& operator=(iterator const& i) {
                    _pos = i._pos;
                    return *this;
                }

                bool_t operator==(iterator const& i) const {
                    return _pos == i._pos;
                }

                bool_t operator!=(iterator const& i) const {
                    return _pos != i._pos;
                }

                T const& operator*() {
                    return _value;
                }

            };

            static iterator begin(T const& v) {
                return iterator(v, 0);
            }

            static iterator end(T const& v, uint_t size) {
                return iterator(v, size);
            }

        };

        template <typename T>
        struct iterator_for : public std::conditional<std::is_array<T>::value, array_iterator_provider<T>,
            typename std::conditional<std::is_pointer<T>::value, pointer_iterator_provider<T>,
            typename std::conditional<std::is_scalar<T>::value, scalar_iterator_provider<T>,
            container_iterator_provider<T> >::type >::type >::type {
        };

    }
}