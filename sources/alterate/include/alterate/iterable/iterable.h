#pragma once

#include <alterate/types.h>
#include <alterate/iterable/pointer.h>
#include <alterate/iterable/scalar.h>
#include <type_traits>

namespace alterate {
    namespace iterable {

        template <typename ContainerType, typename SizeType>
        struct base_iterable_provider {

            typedef ContainerType                                       container_type;
            typedef SizeType                                            size_type;

        };

        template <typename ContainerType, typename SizeType>
        struct direct_iterable_provider : base_iterable_provider < ContainerType, SizeType > {

            typedef typename container_type::const_iterator             const_iterator;
            typedef container_type                                      iterable_type;
            typedef iterable_type const&                                return_type;

            static return_type make_iterable(container_type const& value, SizeType const& dummy) {
                return value;
            }
        };

        template <typename ArrayType, typename SizeType>
        struct array_iterable_provider : base_iterable_provider < ArrayType, SizeType > {
            enum {
                ARRAY_SIZE = std::extent<container_type>::value
            };

            typedef typename std::remove_extent<container_type>::type   value_type;

            typedef pointer_iterable<const value_type, size_type>             iterable_type;
            typedef typename iterable_type::const_iterator              const_iterator;
            typedef iterable_type                                       return_type;

            static return_type make_iterable(container_type const& value, size_type const& size) {
                return iterable_type(value, ARRAY_SIZE);
            }
        };

        template <typename PointerType, typename SizeType>
        struct pointer_iterable_provider : base_iterable_provider < PointerType, SizeType > {

            typedef typename std::remove_cv<typename std::remove_pointer<container_type>::type>::type  value_type;
            typedef pointer_iterable<value_type, size_type>                         iterable_type;
            typedef typename iterable_type::const_iterator                          const_iterator;
            typedef iterable_type                                                   return_type;

            static return_type make_iterable(container_type const& value, size_type const& size) {
                return iterable_type(value, size);
            }
        };

        template <typename ScalarType, typename SizeType>
        struct scalar_iterable_provider : base_iterable_provider<ScalarType, SizeType> {

            typedef scalar_iterable<container_type, size_type>          iterable_type;
            typedef typename iterable_type::const_iterator              const_iterator;
            typedef iterable_type                                       return_type;

            static return_type make_iterable(container_type const& value, size_type const& size) {
                return iterable_type(value, size);
            }

        };

        template <typename ContainerType, typename SizeType = ::alterate::uint_t>
        struct iterable_traits {

            typedef ContainerType                                       container_type;
            typedef SizeType                                            size_type;

            typedef typename std::conditional<std::is_array<container_type>::value, array_iterable_provider<container_type, size_type>,
                    typename std::conditional<std::is_pointer<container_type>::value, pointer_iterable_provider<container_type, size_type>,
                    typename std::conditional<std::is_scalar<container_type>::value, scalar_iterable_provider<container_type, size_type>,
                             direct_iterable_provider<container_type, size_type> >::type >::type >::type provider_type;
            
            typedef typename provider_type::iterable_type               iterable_type;
            typedef typename provider_type::return_type                 return_type;
            typedef typename provider_type::const_iterator              const_iterator;

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