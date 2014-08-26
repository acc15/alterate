#pragma once

#include <type_traits>

#include <alterate/types.h>
#include <alterate/iterator/scalar_iterator.h>

namespace alterate {
    namespace iterator {
        
        template <typename ArrayType>
        struct array_iterator_provider {

            enum {
                ARRAY_SIZE = std::extent<ArrayType>::value
            };

            typedef typename std::add_pointer< 
                typename std::add_const<typename std::remove_extent<ArrayType>::type>::type>::type iterator;

            static iterator begin(const ArrayType& v) {
                return v;
            }

            static iterator end(const ArrayType& v, size_t unused) {
                return v + ARRAY_SIZE;
            }
        };

        template <typename PointerType>
        struct pointer_iterator_provider {

            typedef typename std::add_pointer<
                typename std::add_const<typename std::remove_pointer<PointerType>::type>::type>::type iterator;

            static iterator begin(const PointerType& v) {
                return v;
            }

            static iterator end(const PointerType& v, size_t size) {
                return v + size;
            }
        };


        template <typename ContainerType>
        struct container_iterator_provider {

            typedef typename ContainerType::const_iterator iterator;

            static iterator begin(const ContainerType& v) {
                return v.begin();
            }

            static iterator end(const ContainerType& v, size_t size) {
                return v.end();
            }
        };                                                                                                             

        template <typename ScalarType>
        struct scalar_iterator_provider {

            typedef scalar_iterator<const ScalarType> iterator;

            static iterator begin(const ScalarType& v) {
                return iterator(v, 0);
            }

            static iterator end(const ScalarType& v, size_t size) {
                return iterator(v, size);
            }

        };

        template <typename ContainerType>
        struct iterator_provider : public std::conditional <
                std::is_array<ContainerType>::value, array_iterator_provider<ContainerType>,
            typename std::conditional <
                std::is_pointer<ContainerType>::value, pointer_iterator_provider<ContainerType>,
            typename std::conditional <
                std::is_scalar<ContainerType>::value, scalar_iterator_provider<ContainerType>,
            container_iterator_provider<ContainerType> > ::type > ::type > ::type {

        };

    }

}