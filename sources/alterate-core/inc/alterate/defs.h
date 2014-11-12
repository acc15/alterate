#pragma once

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

#ifdef BOOST_NO_CXX11_NULLPTR
    class nullptr_t
    {
    public:
        template<class T> inline operator T*() const { return 0; }
        template<class C, class T> inline operator T C::*() const { return 0; }

    private:
        void operator&() const;  // Can't take address of nullptr
    };
#endif

}

#ifdef BOOST_NO_CXX11_NULLPTR
const alterate::nullptr_t nullptr = {};
#endif

