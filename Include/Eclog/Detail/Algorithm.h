// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_ALGORITHM_H_
#define ECLOG_CPP_DETAIL_ALGORITHM_H_

#include <Eclog/Detail/Utility.h>

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T>
	inline T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	inline T max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <typename Iterator, typename OutputIterator>
	inline void copy(Iterator first, Iterator last, OutputIterator first2)
	{
		while (first != last)
		{
			*first2 = *first;
			++first2;
			++first;
		}
	}

	template <typename Iterator>
	inline void reverse(Iterator first, Iterator last)
	{
		while (first != last && first != --last)
		{
			swap(*first, *last);
			++first;
		}
	}

	template<class Iterator>
	inline void rotate(Iterator first, Iterator mid, Iterator last)
	{
		reverse(first, mid);
		reverse(mid, last);
		reverse(first, last);
	}

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_ALGORITHM_H_

