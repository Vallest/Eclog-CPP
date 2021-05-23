// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_INTEGERCONVERSION_H_
#define ECLOG_CPP_DETAIL_INTEGERCONVERSION_H_

#include <Eclog/Detail/TypeTraits.h>
#include <Eclog/Detail/CharType.h>
#include <Eclog/Detail/Algorithm.h>
#include <Eclog/Detail/Limits.h>

#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable: 4146)
#endif

namespace eclog {

	namespace detail {

		template<typename IntType>
		inline IntType stringToSignedInteger(const char* str, const char** outStr = 0, int* outError = 0)
		{
			bool negative = false;

			if (*str == '+') {
				++str;
			}
			else if (*str == '-') {
				++str;
				negative = true;
			}

			typename detail::RemoveCV<IntType>::Type result = 0;

			const typename detail::RemoveCV<IntType>::Type n = negative ? detail::minValue<IntType>() / 10 : detail::maxValue<IntType>() / 10;
			const int m = (int)(negative ? -(detail::minValue<IntType>() % 10) : detail::maxValue<IntType>() % 10);

			int error = 0;

			for (;;)
			{
				char ch = *str;

				if (detail::isDigit(ch))
				{
					char d = ch - '0';

					if (negative)
					{
						if (result < n || (result == n && d > m)) {
							error = -1;
						}

						result = result * 10 - d;
					}
					else
					{
						if (result > n || (result == n && d > m)) {
							error = 1;
						}

						result = result * 10 + d;
					}

					++str;
				}
				else
				{
					break;
				}
			}

			if (outStr) {
				*outStr = str;
			}

			if (outError) {
				*outError = error;
			}

			return result;
		}

		template<typename UIntType>
		inline UIntType stringToUnsignedInteger(const char* str, const char** outStr = 0, int* outError = 0)
		{
			bool negative = false;

			if (*str == '+') {
				++str;
			}
			else if (*str == '-') {
				++str;
				negative = true;
			}

			typename detail::RemoveCV<UIntType>::Type result = 0;

			const typename detail::RemoveCV<UIntType>::Type n = detail::maxValue<UIntType>() / 10;
			const int m = (int)(detail::maxValue<UIntType>() % 10);

			int error = 0;

			for (;;)
			{
				char ch = *str;

				if (detail::isDigit(ch))
				{
					char d = ch - '0';

					if (result > n || (result == n && d > m)) {
						error = 1;
					}

					result = result * 10 + d;
					++str;
				}
				else
				{
					break;
				}
			}

			if (outStr) {
				*outStr = str;
			}

			if (outError) {
				*outError = error;
			}

			return negative ? -result : result;
		}

		template<typename IntType>
		inline void integerToString(IntType value, char* buffer)
		{
			char* p = buffer;

			if (value == 0)
			{
				p[0] = '0';
				p[1] = 0;
				return;
			}

			bool negative = false;

			if (value < 0)
			{
				value = -value;
				negative = true;
			}

			while (value)
			{
				*p++ = '0' + (char)(value % 10);
				value /= 10;
			}

			if (negative) {
				*p++ = '-';
			}

			detail::reverse(buffer, p);

			*p = 0;
		}

	} // detail

} // eclog

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

#endif // ECLOG_CPP_DETAIL_INTEGERCONVERSION_H_

