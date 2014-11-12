#pragma once

#if __cplusplus < 201103L
#   error "Only C++11 compilers supported"
#endif


// Handle non c++0x compliant compilers
#include <boost/config.hpp>

// To make size_t and ptrdiff_t defined
#include <cstddef>

namespace alterate
{

    typedef unsigned char   byte_t;

// Use size_t to represent counts, unsigned indexes and so on
// Use standardized (in C99) bool primitive

//    typedef unsigned int    uint_t;
//    typedef unsigned short  ushort_t;
//    typedef unsigned long   ulong_t;

//    typedef signed int      int_t;
//    typedef signed short    short_t;
//    typedef signed char     byte_t;
//    typedef signed long     long_t;

//#ifdef ALTERATE_DOUBLE
//    typedef double          fp_t;
//#else
//    typedef double          fp_t;
//#endif

}

