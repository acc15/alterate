#pragma once

#include <cstdint>

namespace alterate {

struct dimension {
    uint32_t cx, cy;
    dimension();
    dimension(uint32_t cx, uint32_t cy);
};

}
