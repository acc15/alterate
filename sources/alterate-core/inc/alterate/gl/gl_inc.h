#pragma once

#include <boost/predef.h>

#if BOOST_OS_LINUX
#   include <GL/glew.h>
#endif

#if BOOST_OS_WINDOWS
#   include <windows.h>
#endif
#include <GL/gl.h>
