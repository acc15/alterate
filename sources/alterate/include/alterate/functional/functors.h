#pragma once

namespace alterate {
    namespace functional {

        struct return_2nd {
            template <typename T, typename U>
            T operator()(T i1, U i2) const {
                return static_cast<T>(i2);
            }
        };

        struct negate {
            template <typename T>
            void operator()(T& i1) const {
                i1 = -i1;
            }
        };

        struct sum {
            template <typename T, typename U>
            T operator()(T i1, U i2) const {
                return static_cast<T>(i1 + i2);
            }
        };

        struct subtract {
            template <typename T, typename U>
            T operator()(T i1, U i2) const {
                return static_cast<T>(i1 - i2);
            }
        };

        struct multiply {
            template <typename T, typename U>
            T operator()(T i1, U i2) const {
                return static_cast<T>(i1 * i2);
            }
        };

        struct divide {
            template <typename T, typename U>
            T operator()(T i1, U i2) const {
                return static_cast<T>(i1 / i2);
            }
        };

    }
}