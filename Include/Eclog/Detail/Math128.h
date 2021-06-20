// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_MATH128_H_
#define ECLOG_CPP_DETAIL_MATH128_H_

#include <Eclog/IntTypes.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1500) && defined(_M_X64)
#define ECLOG_HAS_UMUL128
#include <intrin.h>
#endif

namespace vallest {
namespace eclog {
namespace detail {

	inline uint64_t mulAdd64to128(uint64_t a, uint64_t b, uint64_t c, uint64_t* high)
	{
#if defined(ECLOG_HAS_UMUL128)
		uint64_t low = _umul128(a, b, high) + c;

		if (low < c) {
			++*high;
		}

		return low;
#elif defined(ECLOG_HAS_INT128)
		uint128_t n = (uint128_t)(a) * (uint128_t)(b) + c;

		*high = (uint64_t)(n >> 64);

		return (uint64_t)(n);
#else
		uint64_t al = ECLOG_LOW32(a);
		uint64_t ah = ECLOG_HIGH32(a);
		uint64_t bl = ECLOG_LOW32(b);
		uint64_t bh = ECLOG_HIGH32(b);

		uint64_t p0 = al * bl;
		uint64_t p1 = al * bh;
		uint64_t p2 = ah * bl;
		uint64_t p3 = ah * bh;

		uint32_t carry = ECLOG_HIGH32((uint64_t)ECLOG_HIGH32(p0) + ECLOG_LOW32(p1) + ECLOG_LOW32(p2));

		*high = p3 + ECLOG_HIGH32(p1) + ECLOG_HIGH32(p2) + carry;

		uint64_t low = p0 + (p1 << 32) + (p2 << 32) + c;

		if (low < c) {
			++*high;
		}

		return low;
#endif
	}

	inline uint64_t add64to128(uint64_t a, uint64_t b, uint64_t* high)
	{
		uint64_t low = a + b;

		*high = (low < a) ? 1 : 0;

		return low;
	}

	inline uint64_t add128(uint64_t al, uint64_t ah, uint64_t bl, uint64_t bh, uint64_t* high)
	{
		uint64_t low = al + bl;

		*high = ah + bh + ((low < al) ? 1 : 0);

		return low;
	}

	inline uint64_t subtract128(uint64_t al, uint64_t ah, uint64_t bl, uint64_t bh, uint64_t* high)
	{
		uint64_t low = al - bl;

		*high = ah - bh - ((low > al) ? 1 : 0);

		return low;
	}

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_MATH128_H_

