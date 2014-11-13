#pragma once

#include <boost/predef.h>

#if BOOST_OS_WINDOWS

#include <windows.h>

namespace alterate {
namespace timing {
class clock {
private:
    LARGE_INTEGER _freq;

public:
    typedef LARGE_INTEGER instant;

    clock();

    void get_instant(instant& value);
    float compute_diff(const instant& i1, const instant& i2);
};
}
}

#elif BOOST_OS_MACOS or BOOST_OS_IOS

#include <mach/mach_time.h>

namespace alterate {
namespace timing {
class clock {
private:
    mach_timebase_info_data_t _timebase;

public:
    typedef uint64_t instant;

    clock();

    void get_instant(instant& value);
    float compute_diff(const instant& i1, const instant& i2);
};
}
}

#else

#include <time.h>

namespace alterate {
namespace timing {
class clock {
public:
    typedef timespec instant;
    void get_instant(instant& value);
    float compute_diff(const instant& i1, const instant& i2);
};
}
}

#endif
