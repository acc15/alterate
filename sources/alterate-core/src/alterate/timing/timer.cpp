#include <alterate/timing/timer.h>

namespace alterate {
namespace timing {

float timer::reset() {
    if (!_set) {
        _clock.get_instant(_last_time);
        _set = true;
        return 0;
    }

    clock::instant t;
    _clock.get_instant(t);

    float result = _clock.compute_diff(t, _last_time);
    _last_time = t;
    return result;
}

void timer::stop() {
    _set = false;
}

}
}

