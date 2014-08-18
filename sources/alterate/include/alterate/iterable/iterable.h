#pragma once

#include <alterate/types.h>
#include <alterate/iterable/scalar_iterator.h>
#include <type_traits>

namespace alterate {
    namespace iterable {

        template <typename ContainerType, typename SizeType>
        struct base_iterable_provider {

            typedef ContainerType                           iterable_type;
            typedef SizeType                                size_type;

        };

        template <typename ContainerType, typename SizeType>
        struct direct_iterable_provider : base_iterable_provider < ContainerType, SizeType > {

            typedef typename ContainerType::const_iterator  const_iterator;
            typedef iterable_type const&                    return_type;

            static return_type make_iterable(iterable_type const& value, SizeType const& dummy) {
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

        template <typename ScalarType, typename SizeType>
        struct scalar_iterable_provider : base_iterable_provider < ScalarType, SizeType > {

            typedef scalar_iterable<iterable_type, size_type>           return_type;
            typedef typename return_type::const_iterator                const_iterator;

            static return_type make_iterable(iterable_type const& value, SizeType const& size) {
                return return_type(value, size);
            }

        };

        template <typename ContainerType, typename SizeType = ::alterate::uint_t>
        struct iterable_traits {

            typedef direct_iterable_provider<ContainerType, SizeType>   provider_type;
            typedef typename provider_type::iterable_type   iterable_type;
            typedef typename provider_type::return_type     return_type;
            typedef typename provider_type::const_iterator  const_iterator;

        };


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
        struct iterator_for : public std::conditional < std::is_array<T>::value, array_iterator_provider<T>,
            typename std::conditional < std::is_pointer<T>::value, pointer_iterator_provider<T>,
            typename std::conditional < std::is_scalar<T>::value, scalar_iterator_provider<T>,
            container_iterator_provider<T> > ::type > ::type > ::type {
        };

        template <typename ContainerType, typename SizeType = alterate::uint_t>
        typename alterate::iterable::iterable_traits<ContainerType, SizeType>::return_type make_iterable(ContainerType const& value, SizeType const& size = 0) {
            return alterate::iterable::iterable_traits<ContainerType, SizeType>::provider_type::make_iterable(value, size);
        }
    }

}