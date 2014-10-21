#pragma once

#define ALTERATE_PLATFORM_WINDOWS 0
#define ALTERATE_PLATFORM_ANDROID 1
#define ALTERATE_PLATFORM_LINUX 2
#define ALTERATE_PLATFORM_MACOS 3
#define ALTERATE_PLATFORM_IOS 4

//#define ALTERATE_PLATFORM ALTERATE_PLATFORM_LINUX

#ifndef ALTERATE_PLATFORM
#   if defined(ALTERATE_WINDOWS)
#       define ALTERATE_PLATFORM ALTERATE_PLATFORM_WINDOWS
#   elif defined(ALTERATE_ANDROID)
#       define ALTERATE_PLATFORM ALTERATE_PLATFORM_ANDROID
#   elif defined(ALTERATE_LINUX)
#       define ALTERATE_PLATFORM ALTERATE_PLATFORM_LINUX
#   elif defined(ALTERATE_IOS)
#       define ALTERATE_PLATFORM ALTERATE_PLATFORM_IOS
#   elif defined(ALTERATE_MACOS)
#       define ALTERATE_PLATFORM ALTERATE_PLATFORM_MACOS
#   else
#       if defined(_WIN32)
#           define ALTERATE_PLATFORM ALTERATE_PLATFORM_WINDOWS
#       elif defined(__ANDROID__) or defined(ALTERATE_ANDROID)
#           define ALTERATE_PLATFORM ALTERATE_PLATFORM_ANDROID
#       elif defined(__linux__) or defined(ALTERATE_LINUX)
#           define ALTERATE_PLATFORM ALTERATE_PLATFORM_LINUX
#       elif defined(__MACH__)
#           include <TargetConditionals.h>
#           if (TARGET_OS_IPHONE == 1)
#               define ALTERATE_PLATFORM        PLATFORM_IOS
#           else
#               define ALTERATE_PLATFORM        PLATFORM_MACOS
#           endif
#       else
#           error "Can't detect platform ID"
#       endif
#   endif
#endif

#if (ALTERATE_PLATFORM == ALTERATE_PLATFORM_WINDOWS)
#   ifndef ALTERATE_WINDOWS
#       define ALTERATE_WINDOWS
#   endif
#   pragma message("Compiling for Windows")
#elif (ALTERATE_PLATFORM == ALTERATE_PLATFORM_ANDROID)
#   ifndef ALTERATE_ANDROID
#       define ALTERATE_ANDROID
#   endif
#   pragma message("Compiling for Android OS")
#elif (ALTERATE_PLATFORM == ALTERATE_PLATFORM_LINUX)
#   ifndef ALTERATE_LINUX
#       define ALTERATE_LINUX
#   endif
#   pragma message("Compiling for Linux")
#elif (ALTERATE_PLATFORM == ALTERATE_PLATFORM_IOS)
#   ifndef ALTERATE_IOS
#       define ALTERATE_IOS
#   endif
#   pragma message("Compiling for iOS")
#elif (ALTERATE_PLATFORM == ALTERATE_PLATFORM_MACOS)
#   ifndef ALTERATE_MACOS
#       define ALTERATE_MACOS
#   endif
#   pragma message("Compiling for MacOS")
#else
#   error "Unknown ALTERATE_PLATFORM (possible values: ALTERATE_PLATFORM_WINDOWS, ALTERATE_PLATFORM_ANDROID, ALTERATE_PLATFORM_LINUX, ALTERATE_PLATFORM_MACOS and ALTERATE_PLATFORM_IOS)"
#endif

namespace alterate {
namespace platform {

enum platform_t {
    WINDOWS = ALTERATE_PLATFORM_WINDOWS,
    ANDROID = ALTERATE_PLATFORM_ANDROID,
    LINUX = ALTERATE_PLATFORM_LINUX,
    IOS = ALTERATE_PLATFORM_IOS,
    MACOS = ALTERATE_PLATFORM_MACOS
};

#define ALTERATE_CURRENT_PLATFORM (static_cast< ::alterate::platform::platform_t >(ALTERATE_PLATFORM))

inline platform_t get_current_platform() {
    return ALTERATE_CURRENT_PLATFORM;
}

}
}
