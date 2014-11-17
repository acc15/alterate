#pragma once

#include <alterate/timing/clock.h>

namespace alterate {
namespace timing {

class timer {
private:
    bool            _started = false;
    clock           _clock;
    clock::instant  _last_time;

public:

    bool is_started() const;
    void start();
    float reset();

    int64_t get_time_in_nanos() const;

    // if (!is_started()) {
    //     start();
    //     return 0;
    // }
    // current_time = now();
    // result = current_time - last_time;
    // last_time = current_time;
    // return result;

    void stop();

};


}
}
