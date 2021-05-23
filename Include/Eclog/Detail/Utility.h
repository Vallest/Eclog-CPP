// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_UTILITY_H_
#define ECLOG_CPP_DETAIL_UTILITY_H_

#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		template<typename T>
		inline void swap(T& a, T& b)
		{
			T t = a;
			a = b;
			b = t;
		}

		template<typename T, size_t Size>
		inline size_t arraySize(const T(&)[Size])
		{
			return Size;
		}

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_UTILITY_H_

