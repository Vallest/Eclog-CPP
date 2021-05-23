// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_LIMITS_H_
#define ECLOG_CPP_DETAIL_LIMITS_H_

#include <limits>

namespace eclog {

	namespace detail {

		template<typename T>
		inline T minValue()
		{
			return std::numeric_limits<T>::min();
		}

		template<typename T>
		inline T maxValue()
		{
			return std::numeric_limits<T>::max();
		}

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_LIMITS_H_

