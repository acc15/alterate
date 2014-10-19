#include <alterate/debug.h>

#ifndef _NDEBUG

#ifdef _MSC_VER
#   define _CRT_SECURE_NO_WARNINGS
#endif
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


