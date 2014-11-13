#pragma once

#include <alterate/timing/clock.h>

namespace alterate {
namespace timing {

class timer {
private:
    bool            _set = false;
    clock           _clock;
    clock::instant  _last_time;

public:

    float reset();
    void stop();

};


}
}
