// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_UTILITY_H_
#define ECLOG_CPP_UTILITY_H_

namespace vallest {
namespace eclog {

	template<typename T1, typename T2>
	struct Pair {
	public:
		typedef T1 FirstType;
		typedef T2 SecondType;

	public:
		Pair()
		{
		}

		Pair(const T1& arg1, const T2& arg2) : first(arg1), second(arg2)
		{
		}

		template<typename U1, typename U2>
		Pair(const Pair<U1, U2>& other) : first(other.first), second(other.second)
		{
		}

	public:
		T1 first;
		T2 second;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_UTILITY_H_

