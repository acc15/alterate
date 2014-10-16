#pragma once

#include <boost/config.hpp>

namespace alterate
{

    typedef unsigned int    uint_t;
    typedef unsigned short  ushort_t;
    typedef unsigned char   ubyte_t;
    typedef unsigned long   ulong_t;

    typedef signed int      int_t;
    typedef signed short    short_t;
    typedef signed char     byte_t;
    typedef signed long     long_t;

    typedef char            ch_t;
    typedef wchar_t         wch_t;

    typedef bool            bool_t;

#if defined(ALTERATE_UNICODE) or defined(UNICODE) or defined(_UNICODE)
    typedef wch_t           tch_t;
#else
    typedef ch_t            tch_t;
#endif

    typedef float           sp_t;
    typedef double          dp_t;

#ifdef ALTERATE_DOUBLE
    typedef dp_t            fp_t;
#else
    typedef sp_t            fp_t;
#endif

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

