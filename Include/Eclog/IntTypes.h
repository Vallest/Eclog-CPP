// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_INTTYPES_H_
#define ECLOG_CPP_INTTYPES_H_

#define ECLOG_HIGH32(n) (uint32_t)((n) >> 32)
#define ECLOG_LOW32(n) (uint32_t)((n) & 0xffffffff)
#define ECLOG_MAKE64(high, low) ((((uint64_t)(high)) << 32) | ((uint64_t)(low)))

#if defined(_MSC_VER)
	#if _MSC_VER >= 1600
		#include <stdint.h>
	#endif
#else
	#include <stdint.h>
#endif

#if __SIZEOF_INT128__ == 16
	#define ECLOG_HAS_INT128
#endif

namespace eclog {

#if defined(_MSC_VER) && !defined(_STDINT)
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;
	typedef unsigned __int64 uint64_t;
#else
	typedef ::uint16_t uint16_t;
	typedef ::uint32_t uint32_t;
	typedef ::uint64_t uint64_t;
#endif

#ifdef ECLOG_HAS_INT128
	typedef unsigned __int128 uint128_t;
#endif

} // eclog

#endif // ECLOG_CPP_INTTYPES_H_

