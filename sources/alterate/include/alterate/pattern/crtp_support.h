#pragma once

namespace alterate {
    namespace pattern {
        
        template <typename Derived>
        struct crtp_support {
        
            typedef Derived derived_type;
            
            derived_type& derived() {
                return *static_cast<derived_type*>(this);
            }

            derived_type const& derived() const {
                return *static_cast<const derived_type *>(this);
            }

            derived_type derived_copy() const {
                return derived_type(derived());
            }
            
        };
        
    }
}