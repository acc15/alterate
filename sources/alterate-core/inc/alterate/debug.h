#pragma once

#ifndef NDEBUG
#   include <cstdlib>
#   include <iostream>
#   define ALTERATE_ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" << #condition << "` failed in " << __FILE__ << "(" << __LINE__ << "): " << message << std::endl; \
            std::abort(); \
        } \
    } while (false)
#   define ALTERATE_DEBUG(message) \
    do { \
        std::cout << "DEBUG[" << debug_time() << "][" << __FILE__ << "(" << __LINE__ << ")]: " << message << std::endl; \
    } while (false)

    namespace alterate {

        std::string debug_time();

    }

#else
#   define ALTERATE_ASSERT(condition, message) do {} while (false)
#   define ALTERATE_DEBUG(message) do {} while (false)
#endif

