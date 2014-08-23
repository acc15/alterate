#pragma once

#include <type_traits>

namespace alterate {
    namespace meta {
        
        template <typename Type, typename SourceType>
        struct copy_const : std::conditional<std::is_const<SourceType>::value, const Type, Type> {
        };

        template <typename ContainerType>
        struct value_type_of : copy_const < typename ContainerType::value_type, ContainerType > {
        };

    }
}