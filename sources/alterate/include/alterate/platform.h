#pragma once

#define ALTERATE_WINDOWS 0
#define ALTERATE_ANDROID 1
#define ALTERATE_LINUX 2
#define ALTERATE_MACOS 3
#define ALTERATE_IOS 4

//#define ALTERATE_PLATFORM ALTERATE_LINUX

#ifndef ALTERATE_PLATFORM
#  if defined(_WIN32)
#    define ALTERATE_PLATFORM ALTERATE_WINDOWS
#  elif defined(__ANDROID__)		// must come before __linux__ as Android also #defines __linux__
#    define ALTERATE_PLATFORM ALTERATE_ANDROID
#  elif defined(__linux__)
#    define ALTERATE_PLATFORM ALTERATE_LINUX
#  else
#    error Can't detect platform ID
// #elif defined(__MACH__)
// #include <TargetConditionals.h>
// #if (TARGET_OS_IPHONE == 1)
// #define PLATFORM_ID		PLATFORM_IOS
// #else
// #define PLATFORM_ID		PLATFORM_MACOS
// #endif
#  endif
#endif

namespace alterate {

#if (ALTERATE_PLATFORM == ALTERATE_WINDOWS)
#  pragma message("Compiling for Windows")
#elif (ALTERATE_PLATFORM == ALTERATE_ANDROID)
#  pragma message("Compiling for Android OS")
#elif (ALTERATE_PLATFORM == ALTERATE_LINUX)
#  pragma message("Compiling for Linux")
#elif (ALTERATE_PLATFORM == ALTERATE_LINUX)
#  pragma message("Compiling for MacOS")
#elif (ALTERATE_PLATFORM == ALTERATE_LINUX)
#  pragma message("Compiling for IOS")
#else
#  error Unknown ALTERATE_PLATFORM (possible values: ALTERATE_WINDOWS, ALTERATE_ANDROID, ALTERATE_LINUX, ALTERATE_MACOS and ALTERATE_IOS)
#endif

	enum platform_t {
		WINDOWS = ALTERATE_WINDOWS,
		ANDROID = ALTERATE_ANDROID,
		LINUX = ALTERATE_LINUX,
		IOS = ALTERATE_IOS,
		MACOS = ALTERATE_MACOS
	};

#define ALTERATE_CURRENT_PLATFORM (static_cast<platform_t>(ALTERATE_PLATFORM));

	inline platform_t get_current_platform() {
		return ALTERATE_CURRENT_PLATFORM;
	}

}