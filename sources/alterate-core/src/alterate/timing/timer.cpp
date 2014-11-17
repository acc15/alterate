#include <alterate/timing/timer.h>

namespace alterate {
namespace timing {

bool timer::is_started() const {
    return _started;
}

void timer::start() {
    _clock.get_instant(_last_time);
    _started = true;
}

int64_t timer::get_time_in_nanos() const {
    clock::instant t;
    _clock.get_instant(t);
    int64_t diff = _clock.compute_diff_in_nanos(t, _last_time);
    return diff;
}

float timer::reset() {
    if (!_started) {
        start();
        return 0;
    }

    clock::instant t;
    _clock.get_instant(t);

    float result = _clock.compute_diff_in_seconds(t, _last_time);
    _last_time = t;
    return result;
}

void timer::stop() {
    _started = false;
}

}
}

