#pragma once

namespace alterate {

	// signed integer (8 bit)
	typedef signed char         byte_t;

	// unsigned integer (8 bit)
	typedef unsigned char       ubyte_t;

	// signed integer (16 bit)
	typedef signed short        short_t;

	// unsigned integer (16 bit)
	typedef unsigned short      ushort_t;

	// signed integer (32 bit)
	typedef signed long         int_t;

	// unsigned integer (32 bit)
	typedef unsigned long       uint_t;

	// signed integer (64 bit)
	typedef signed long long    long_t;

	// unsigned integer (64 bit)
	typedef unsigned long long  ulong_t;

	// boolean type (may vary 8, 16, 32 bits)
	typedef bool                bool_t;

	// single precision floating-point (32 bit)
	typedef float				sp_t;

	// double precision floating-point (64 bit)
	typedef double				dp_t;


	typedef char				ch_t;

	typedef wchar_t				wch_t;

#ifdef _UNICODE
#	ifndef _T
#		define _T(x) L ## x
#	endif
	typedef wchar_t             uch_t;
#else
#	ifndef _T
#		define _T(x) x
#	endif
	typedef char                uch_t;
#endif

}