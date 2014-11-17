#include <alterate/timing/clock.h>

namespace alterate {
namespace timing {
#if BOOST_OS_WINDOWS

clock::clock() {
    QueryPerformanceFrequency(&_freq);
}

void clock::get_instant(instant& value) {
    QueryPerformanceCounter(&value);
}

float clock::compute_diff_in_seconds(const instant& i1, const instant& i2) {
    return static_cast<float>(i1.QuadPart - i2.QuadPart) / _freq.QuadPart;
}

int64_t clock::compute_diff_in_nanos(const instant& t1, const instant& t2) const {
    return (i1.QuadPart - i2.QuadPart) * 1000000000L / _freq.QuadPart;
}

#elif BOOST_OS_MACOS or BOOST_OS_IOS

clock::clock() {
    mach_timebase_info(&_timebase);
}

void clock::get_instant(instant& value) {
    value = mach_absolute_time();
}

float clock::compute_diff_in_seconds(const instant& i1, const instant& i2) {
    if (i1 > i2) {
        return static_cast<float>(i1 - i2) * _timebase.num / _timebase.denum;
    } else {
        return -static_cast<float>(i2 - i1) * _timebase.num / _timebase.denum;
    }
}

int64_t clock::compute_diff_in_nanos(const instant& t1, const instant& t2) const {
    return (t1.tv_sec - t2.tv_sec) * 1000000000L + (t1.tv_nsec - t2.tv_nsec);
}

#else

void clock::get_instant(instant& i) const {
    clock_gettime(CLOCK_MONOTONIC, &i);
}

float clock::compute_diff_in_seconds(const instant& t1, const instant& t2) const {
    return (t1.tv_sec - t2.tv_sec) + (t1.tv_nsec - t2.tv_nsec) * 1e-9;
}

int64_t clock::compute_diff_in_nanos(const instant& t1, const instant& t2) const {
    return (t1.tv_sec - t2.tv_sec) * 1000000000L + (t1.tv_nsec - t2.tv_nsec);
}

#endif

}
}
