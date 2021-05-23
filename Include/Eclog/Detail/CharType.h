// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_CHARTYPE_H_
#define ECLOG_CPP_DETAIL_CHARTYPE_H_

namespace eclog {

	namespace detail {

		inline bool isBetween(int ch, int lower, int upper)
		{
			return (ch >= lower && ch <= upper);
		}

		inline bool isLower(int ch)
		{
			return isBetween(ch, 'a', 'z');
		}

		inline bool isUpper(int ch)
		{
			return isBetween(ch, 'A', 'Z');
		}

		inline bool isDigit(int ch)
		{
			return isBetween(ch, '0', '9');
		}

		inline bool isAlpha(int ch)
		{
			return (isLower(ch) || isUpper(ch));
		}

		inline bool isAlphanum(int ch)
		{
			return (isAlpha(ch) || isDigit(ch));
		}

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_CHARTYPE_H_

