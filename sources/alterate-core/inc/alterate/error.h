#pragma once

#include <exception>

namespace alterate {

    inline std::out_of_range make_out_of_range_error() {
        return std::out_of_range("index out of range");
    }

}
