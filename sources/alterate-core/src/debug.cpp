#include <alterate/debug.h>

#ifndef _NDEBUG
#include <ctime>

namespace alterate {

    std::string debug_time() {
        time_t raw_time;
        time(&raw_time);
        tm* local_time = localtime(&raw_time);
        char buf[32];
        strftime(buf, 32, "%F %X", local_time);
        return std::string(buf);
    }

}

#endif


