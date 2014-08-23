#pragma once

#include <type_traits>

#include <alterate/types.h>
#include <alterate/iterator/scalar_iterator.h>

namespace alterate {
    namespace iterable {
        
        template <typename ContainerType, typename SizeType> 
        struct base_iterator_provider {
            typedef ContainerType container_type;
            typedef SizeType size_type;
        };

        template <typename ArrayType, typename SizeType>
        struct array_iterator_provider: base_iterator_provider<ArrayType, SizeType> {

            enum {
                ARRAY_SIZE = std::extent<ArrayType>::value
            };

            typedef typename std::add_pointer< 
                typename std::add_const<typename std::remove_extent<container_type>::type>::type>::type iterator;

            static iterator begin(container_type const& v) {
                return v;
            }

            static iterator end(container_type const& v, 
                                size_type const& unused) {
                return v + ARRAY_SIZE;
            }
        };

        template <typename PointerType, typename SizeType>
        struct pointer_iterator_provider: base_iterator_provider<PointerType, SizeType> {

            typedef typename std::add_pointer<
                typename std::add_const<typename std::remove_pointer<container_type>::type>::type>::type iterator;

            static iterator begin(container_type const& v) {
                return v;
            }

            static iterator end(container_type const& v, 
                                size_type const& size) {
                return v + size;
            }
        };


        template <typename ContainerType, typename SizeType>
        struct container_iterator_provider: base_iterator_provider<ContainerType, SizeType> {

            typedef typename container_type::const_iterator iterator;

            static iterator begin(container_type const& v) {
                return v.begin();
            }

            static iterator end(container_type const& v, size_type const& size) {
                return v.end();
            }
        };                                                                                                             

        template <typename ScalarType, typename SizeType>
        struct scalar_iterator_provider : base_iterator_provider<ScalarType, SizeType> {

            typedef scalar_iterator<const ScalarType, size_type > iterator;

            static iterator begin(container_type const& v) {
                return iterator(v, 0);
            }

            static iterator end(container_type const& v, size_type const& size) {
                return iterator(v, size);
            }

        };

        template <typename ContainerType, typename SizeType>
        struct iterator_provider : public 
            std::conditional <
                std::is_array<ContainerType>::value, array_iterator_provider<ContainerType, SizeType>,
            typename std::conditional <
                std::is_pointer<ContainerType>::value, pointer_iterator_provider<ContainerType, SizeType>,
            typename std::conditional <
                std::is_scalar<ContainerType>::value, scalar_iterator_provider<ContainerType, SizeType>,
            container_iterator_provider<ContainerType, SizeType> > ::type > ::type > ::type {

        };

    }

}