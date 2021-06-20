// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include <Eclog/IntTypes.h>
#include <Eclog/Detail/DoubleConversion.h>
#include <Eclog/Detail/BigInteger.h>
#include <Eclog/Detail/Binary64.h>
#include <Eclog/Detail/CharType.h>
#include <Eclog/Detail/Algorithm.h>

#include <string.h> // memcpy, memmove, strncmp
#include <math.h> // ceil

namespace vallest {
namespace eclog {
namespace detail {

	static double stringToDoubleApprox(const char* decimals, int length, int decimalPointOff, int exponent)
	{
		static const double fastPosTens[] = {
			1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15
		};

		static const double binaryPosTens[] = {
			1e16, 1e32, 1e64, 1e128, 1e256
		};

		static const double binaryNegTens[] = {
			1e-16, 1e-32, 1e-64, 1e-128, 1e-256
		};

		uint64_t sigDecimals = 0;
		int count = 0;

		for (int i = 0; i < length && count < 19; ++i)
		{
			if (detail::isDigit(decimals[i]))
			{
				sigDecimals = sigDecimals * 10 + (decimals[i] - '0');
				++count;
			}
		}

		double b = (double)sigDecimals;

		exponent += decimalPointOff - count;

		if (exponent > 0)
		{
			if (exponent & 0xf) {
				b *= fastPosTens[exponent & 0xf];
			}

			if (exponent >>= 4)
			{
				for (int i = 0; exponent > 0; ++i, exponent >>= 1)
				{
					if (exponent & 1) {
						b *= binaryPosTens[i];
					}
				}
			}
		}
		else if (exponent < 0)
		{
			exponent = -exponent;

			if (exponent & 0xf) {
				b /= fastPosTens[exponent & 0xf];
			}

			if (exponent >>= 4)
			{
				for (int i = 0; exponent > 0; ++i, exponent >>= 1)
				{
					if (exponent & 1)
					{
						b *= binaryNegTens[i];
					}
				}
			}
		}

		return b;
	}

	static double stringToDoubleBigInt(double b, const char* decimals, int length, int decimalPointOff, int exponent)
	{
		detail::Binary64 b64(b);

		if (b64.isInfinity()) {
			b = b64.previousValue();
		}

		int count = (decimalPointOff > 0 && decimalPointOff < length) ? length - 1 : length;

		for (;;)
		{
			b64.assign(b);

			if (b64.isInfinity()) {
				break;
			}

			detail::BigInteger dInt(decimals, length);
			int dExp = exponent + decimalPointOff - count;

			detail::BigInteger bInt(b64.significand());
			int bExp = b64.exponent();

			detail::BigInteger hInt(1);
			int hExp = bExp - 1;

			int dsExp2 = 0;
			int dsExp5 = 0;
			int bsExp2 = 0;
			int bsExp5 = 0;
			int hsExp2 = 0;
			int hsExp5 = 0;

			if (dExp >= 0) {
				dsExp2 += dExp;
				dsExp5 += dExp;
			}
			else {
				bsExp2 -= dExp;
				bsExp5 -= dExp;
				hsExp2 -= dExp;
				hsExp5 -= dExp;
			}

			if (bExp >= 0) {
				bsExp2 += bExp;
			}
			else {
				dsExp2 -= bExp;
				hsExp2 -= bExp;
			}

			if (hExp >= 0) {
				hsExp2 += hExp;
			}
			else {
				dsExp2 -= hExp;
				bsExp2 -= hExp;
			}

			int commonExp2 = detail::min(dsExp2, detail::min(bsExp2, hsExp2));

			dsExp2 -= commonExp2;
			bsExp2 -= commonExp2;
			hsExp2 -= commonExp2;

			dInt.multiplyPow5(dsExp5);
			dInt.multiplyPow2(dsExp2);

			bInt.multiplyPow5(bsExp5);
			bInt.multiplyPow2(bsExp2);

			hInt.multiplyPow5(hsExp5);
			hInt.multiplyPow2(hsExp2);

			int cmp = bInt.difference(dInt);

			if (cmp > 0)
			{
				if (b64.lowerBoundaryIsCloser()) {
					hInt.shiftRight(1);
				}

				cmp = bInt.compare(hInt);

				if (cmp < 0)
				{
					break;
				}
				else if (cmp == 0)
				{
					if (b64.significand() & 1) {
						b = b64.previousValue();
					}

					break;
				}
				else
				{
					b = b64.previousValue();
				}
			}
			else if (cmp < 0)
			{
				cmp = bInt.compare(hInt);

				if (cmp < 0)
				{
					break;
				}
				else if (cmp == 0)
				{
					if (b64.significand() & 1) {
						b = b64.nextValue();
					}

					break;
				}
				else
				{
					b = b64.nextValue();
				}
			}
			else
			{
				break;
			}
		}

		return b;
	}

	double stringToDouble(const char* str, const char** outStr, int* outError)
	{
		bool negative = false;

		if (*str == '-')
		{
			negative = true;
			++str;
		}
		else if (*str == '+')
		{
			++str;
		}

		if (strncmp(str, "inf", 3) == 0)
		{
			if (outStr) {
				*outStr = str + 3;
			}

			return negative ? detail::Binary64::negInfinity() : detail::Binary64::infinity();
		}
		else if (strncmp(str, "nan", 3) == 0)
		{
			if (outStr) {
				*outStr = str + 3;
			}

			return negative ? detail::Binary64::negNan() : detail::Binary64::nan();
		}

		const char* decimals = 0;
		const char* decimalPoint = 0;

		for (;;)
		{
			if (detail::isDigit(*str))
			{
				if (decimals == 0 && *str != '0') {
					decimals = str;
				}

				++str;
			}
			else if (*str == '.' && decimalPoint == 0)
			{
				decimalPoint = str;
				++str;
			}
			else
			{
				break;
			}
		}

		int length = decimals ? (int)(str - decimals) : 0;

		int decimalPointOff;

		if (decimalPoint && decimals)
		{
			if (decimalPoint < decimals) {
				decimalPointOff = (int)(decimalPoint - decimals + 1);
			}
			else {
				decimalPointOff = (int)(decimalPoint - decimals);
			}
		}
		else
		{
			decimalPointOff = length;
		}

		const int maxLength = (decimalPointOff > 0 && decimalPointOff < 780) ? 781 : 780;

		if (length > maxLength) {
			length = maxLength;
		}

		if (length > 0)
		{
			while (decimals[length - 1] == '0' || decimals[length - 1] == '.') {
				--length;
			}
		}

		if (length == 0)
		{
			if (outStr) {
				*outStr = str;
			}

			return negative ? -0.0 : 0.0;
		}

		const int minExp = -324 - decimalPointOff + 1;
		const int maxExp = 308 - decimalPointOff + 1;

		int exponent = 0;

		if (*str == 'e' || *str == 'E')
		{
			++str;

			bool negExp = false;

			if (*str == '-')
			{
				negExp = true;
				++str;
			}
			else if (*str == '+')
			{
				++str;
			}

			const int n = negExp ? minExp / 10 : maxExp / 10;
			const int m = negExp ? -(minExp % 10) : maxExp % 10;

			for (;;)
			{
				if (detail::isDigit(*str))
				{
					char d = *str - '0';

					if (negExp)
					{
						if (exponent < n || (exponent == n && d > m))
						{
							if (outStr) {
								*outStr = str;
							}

							if (outError) {
								*outError = -1;
							}

							return negative ? -0.0 : 0.0;
						}

						exponent = exponent * 10 - d;
					}
					else
					{
						if (exponent > n || (exponent == n && d > m))
						{
							if (outStr) {
								*outStr = str;
							}

							if (outError) {
								*outError = 1;
							}

							return negative ? detail::Binary64::negInfinity() : detail::Binary64::infinity();
						}

						exponent = exponent * 10 + d;
					}

					++str;
				}
				else
				{
					break;
				}
			}
		}

		double b = stringToDoubleApprox(decimals, length, decimalPointOff, exponent);

		b = stringToDoubleBigInt(b, decimals, length, decimalPointOff, exponent);

		if (outStr) {
			*outStr = str;
		}

		if (b == 0.0)
		{
			if (outError) {
				*outError = -1;
			}
		}
		else if (detail::Binary64(b).isInfinity())
		{
			if (outError) {
				*outError = 1;
			}
		}

		return negative ? -b : b;
	}

	static int estimatePower(const detail::Binary64& b64)
	{
		uint64_t significand = b64.significand();
		int exponent = b64.exponent();

		while ((significand & detail::Binary64::hidden_bit) == 0)
		{
			significand = significand << 1;
			--exponent;
		}

		double log2 = 0.3010299956639812;
		double result = log2 * (detail::Binary64::significand_size - 1 + exponent) - 1e-5;

		return (int)ceil(result);
	}

	static void initValues(double d, detail::BigInteger& numerator, detail::BigInteger& denominator,
		detail::BigInteger& deltaMinus, detail::BigInteger& deltaPlus, int& power)
	{
		detail::Binary64 b64(d);

		power = estimatePower(b64);

		if (b64.exponent() > 0)
		{
			numerator.assign(b64.significand());
			numerator.multiplyPow2(b64.exponent());

			denominator.assign(1);
			denominator.multiplyPow10(power);

			numerator.shiftLeft(1);
			denominator.shiftLeft(1);

			deltaMinus.assign(1);
			deltaMinus.multiplyPow2(b64.exponent());

			deltaPlus.assign(1);
			deltaPlus.multiplyPow2(b64.exponent());
		}
		else if (power > 0)
		{
			numerator.assign(b64.significand());

			denominator.assign(1);
			denominator.multiplyPow5(power);
			denominator.multiplyPow2(-b64.exponent() + power);

			numerator.shiftLeft(1);
			denominator.shiftLeft(1);

			deltaMinus.assign(1);
			deltaPlus.assign(1);
		}
		else
		{
			numerator.assign(1);
			numerator.multiplyPow10(-power);

			deltaMinus.assign(numerator);
			deltaPlus.assign(numerator);

			numerator.multiply(b64.significand());

			denominator.assign(1);
			denominator.multiplyPow2(-b64.exponent());

			numerator.shiftLeft(1);
			denominator.shiftLeft(1);
		}

		if (b64.lowerBoundaryIsCloser())
		{
			numerator.shiftLeft(1);
			denominator.shiftLeft(1);
			deltaPlus.shiftLeft(1);
		}

		bool isEven = (b64.significand() & 1) == 0;

		bool inRange;

		if (isEven) {
			inRange = numerator.plusCompare(deltaPlus, denominator) >= 0;
		}
		else {
			inRange = numerator.plusCompare(deltaPlus, denominator) > 0;
		}

		if (!inRange)
		{
			numerator.multiply(10);
			deltaMinus.multiply(10);
			deltaPlus.multiply(10);

			power = power - 1;
		}
	}

	static int selectNotation(int power)
	{
		return (power >= -4 && power < 17) ? 1 : 0;
	}

	static void formatDecimal(char* buffer, int& count, int power)
	{
		if (count == 0)
		{
			memcpy(buffer, "0", 2);
			count = 1;
			return;
		}
		else if (count == 1 && buffer[0] == '0')
		{
			return;
		}

		if (power < 0)
		{
			int n = 1 - power;

			memmove(buffer + n, buffer, count + 1);

			buffer[0] = '0';
			buffer[1] = '.';

			for (int i = 2; i < n; ++i) {
				buffer[i] = '0';
			}

			count += n;
		}
		else
		{
			int n = power + 1;

			if (n < count)
			{
				memmove(buffer + n + 1, buffer + n, ++count - n);

				buffer[n] = '.';
			}
			else if (n > count)
			{
				for (; count < n; ++count) {
					buffer[count] = '0';
				}

				buffer[count] = 0;
			}
		}
	}

	static void formatExponent(char* buffer, int& count, int power)
	{
		if (count == 0)
		{
			memcpy(buffer, "0", 2);
			count = 1;
			return;
		}
		else if (count == 1 && buffer[0] == '0')
		{
			return;
		}

		if (count > 1)
		{
			memmove(buffer + 2, buffer + 1, count - 1);
			buffer[1] = '.';
			count += 1;
		}

		buffer[count++] = 'e';

		if (power < 0)
		{
			buffer[count++] = '-';
			power = -power;
		}

		size_t p = count;

		while (power)
		{
			int digit = power % 10;

			memmove(buffer + p + 1, buffer + p, count - p);

			buffer[p] = (char)digit + '0';

			power /= 10;
			count += 1;
		}

		buffer[count] = 0;
	}

	static int generateDigits(int requestedDigits, detail::BigInteger& numerator, detail::BigInteger& denominator,
		detail::BigInteger& deltaMinus, detail::BigInteger& deltaPlus, bool isEven, char* buffer)
	{
		int count = 0;

		while (count < requestedDigits)
		{
			uint16_t q = numerator.divideWithRemainder(denominator);

			buffer[count++] = (char)q + '0';

			bool inDeltaRoomMinus;
			bool inDeltaRoomPlus;

			if (isEven)
			{
				inDeltaRoomMinus = numerator.compare(deltaMinus) <= 0;
				inDeltaRoomPlus = numerator.plusCompare(deltaPlus, denominator) >= 0;
			}
			else
			{
				inDeltaRoomMinus = numerator.compare(deltaMinus) < 0;
				inDeltaRoomPlus = numerator.plusCompare(deltaPlus, denominator) > 0;
			}

			if (inDeltaRoomMinus && inDeltaRoomPlus)
			{
				int n = numerator.plusCompare(numerator, denominator);

				if (n > 0)
				{
					++buffer[count - 1];
				}
				else if (n == 0)
				{
					if ((buffer[count - 1] - '0') % 2) {
						++buffer[count - 1];
					}
				}

				break;
			}
			else if (inDeltaRoomMinus)
			{
				break;
			}
			else if (inDeltaRoomPlus)
			{
				++buffer[count - 1];

				break;
			}
			else
			{
				numerator.multiply(10);
				deltaMinus.multiply(10);
				deltaPlus.multiply(10);
			}
		}

		buffer[count] = 0;

		return count;
	}

	static void round(char* buffer, int& count, int& power)
	{
		if (count <= 0) {
			return;
		}

		int n = buffer[count - 1] - '5';

		buffer[--count] = 0;

		int carry = (n >= 0) ? 1 : 0;

		if (count || carry)
		{
			for (int i = count - 1; i >= 0; --i)
			{
				if (carry)
				{
					if (++buffer[i] - '0' == 10) {
						buffer[i] = '0';
					}
					else {
						carry = 0;
					}
				}
				else
				{
					break;
				}
			}

			if (carry)
			{
				memmove(buffer + 1, buffer, count + 1);
				buffer[0] = '1';
				++count;
				++power;
			}
		}
		else
		{
			++power;
			return;
		}

		if (power > 308 || (power == 308 && strncmp(buffer, "17976931348623158", count) > 0))
		{
			memcpy(buffer, "17976931348623158", count);
			power = 308;
		}
	}

	static void trimTrailingZeros(char* buffer, int& count)
	{
		while (count > 1 && buffer[count - 1] == '0') {
			buffer[--count] = 0;
		}
	}

	void doubleToString(double d, char* buffer, int fracDigits)
	{
		int count;

		if (d == 0.0)
		{
			memcpy(buffer, "0", 2);
			count = 1;
		}
		else if (detail::Binary64(d).isInfinity())
		{
			memcpy(buffer, "inf", 4);
			count = 3;
		}
		else if (detail::Binary64(d).isNan())
		{
			memcpy(buffer, "nan", 4);
			count = 3;
		}
		else
		{
			bool isEven = (detail::Binary64(d).significand() & 1) == 0;

			detail::BigInteger numerator;
			detail::BigInteger denominator;
			detail::BigInteger deltaMinus;
			detail::BigInteger deltaPlus;

			int power;

			initValues(detail::Binary64(d).sign() < 0 ? -d : d, numerator, denominator, deltaMinus, deltaPlus, power);

			int requestedDigits;

			if (fracDigits < 0) {
				requestedDigits = 17;
			}
			else if (selectNotation(power)) {
				requestedDigits = power + fracDigits + 1;
			}
			else {
				requestedDigits = fracDigits + 1;
			}

			if (requestedDigits < 0)
			{
				memcpy(buffer, "0", 2);
				count = 1;
			}
			else
			{
				count = generateDigits(requestedDigits + 1, numerator, denominator, deltaMinus, deltaPlus, isEven, buffer);

				if (count > requestedDigits) {
					round(buffer, count, power);
				}

				trimTrailingZeros(buffer, count);

				if (selectNotation(power)) {
					formatDecimal(buffer, count, power);
				}
				else {
					formatExponent(buffer, count, power);
				}
			}
		}

		if (detail::Binary64(d).sign() < 0)
		{
			memmove(buffer + 1, buffer, count + 1);
			buffer[0] = '-';
		}
	}

} // detail
} // eclog
} // vallest

