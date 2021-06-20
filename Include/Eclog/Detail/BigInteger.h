// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_BIGINTEGER_H_
#define ECLOG_CPP_DETAIL_BIGINTEGER_H_

#include <Eclog/IntTypes.h>
#include <Eclog/Detail/Algorithm.h>
#include <Eclog/Detail/CharType.h>
#include <Eclog/Detail/Math128.h>

#include <string.h> // strlen, memset, memcmp, memmove

namespace vallest {
namespace eclog {
namespace detail {

	class BigInteger {
	private:
		enum {
			max_bit = 3328,
			max_chunk = max_bit / 64,
			highest_index = max_chunk - 1,
		};

	public:
		BigInteger()
		{
			zero();
		}

		BigInteger(uint64_t n)
		{
			assign(n);
		}

		BigInteger(const char* str, size_t length)
		{
			zero();
			appendDecimal(str, length);
		}

		BigInteger(const BigInteger& other)
		{
			assign(other);
		}

		bool isZero() const
		{
			return (count_ == 1 && chunks_[0] == 0);
		}

		uint64_t at(size_t index) const
		{
			return (index < count_ ? chunks_[index] : 0);
		}

		bool equals(uint64_t n) const
		{
			return (count_ == 1 && chunks_[0] == n);
		}

		bool equals(const BigInteger& other) const
		{
			if (count_ == other.count_) {
				return (memcmp(chunks_, other.chunks_, sizeof(uint64_t) * count_) == 0);
			}

			return false;
		}

		int compare(const BigInteger& other) const
		{
			if (count_ != other.count_) {
				return (count_ < other.count_ ? -1 : 1);
			}

			for (size_t i = count_; i > 0; --i)
			{
				if (chunks_[i - 1] != other.chunks_[i - 1]) {
					return (chunks_[i - 1] < other.chunks_[i - 1] ? -1 : 1);
				}
			}

			return 0;
		}

		int plusCompare(const BigInteger& delta, const BigInteger& other) const
		{
			if (count_ < delta.count_) {
				return delta.plusCompare(*this, other);
			}

			if (count_ + 1 < other.count_) {
				return -1;
			}

			if (count_ > other.count_) {
				return 1;
			}

#ifdef ECLOG_HAS_INT128
			uint128_t borrow = 0;

			for (size_t i = other.count_ - 1; i != ((size_t)0 - 1); --i)
			{
				uint128_t sum = (uint128_t)at(i) + (uint128_t)delta.at(i);
				uint128_t n = (uint128_t)other.chunks_[i] + borrow;

				if (sum > n)
				{
					return 1;
				}
				else
				{
					if ((borrow = n - sum) > 1) {
						return -1;
					}

					borrow = borrow << 64;
				}
			}

			if (borrow) {
				return -1;
			}
#else
			uint64_t borrowHigh = 0;
			uint64_t borrowLow = 0;

			for (size_t i = other.count_ - 1; i != ((size_t)0 - 1); --i)
			{
				uint64_t sumHigh;
				uint64_t sumLow = add64to128(at(i), delta.at(i), &sumHigh);

				uint64_t high;
				uint64_t low = add128(other.chunks_[i], 0, borrowLow, borrowHigh, &high);

				if (sumHigh > high || (sumHigh == high && sumLow > low))
				{
					return 1;
				}
				else
				{
					borrowLow = subtract128(low, high, sumLow, sumHigh, &borrowHigh);

					if (borrowHigh || borrowLow > 1) {
						return -1;
					}

					borrowHigh = borrowLow;
					borrowLow = 0;
				}
			}

			if (borrowHigh || borrowLow) {
				return -1;
			}
#endif
			return 0;
		}

		void zero()
		{
			chunks_[0] = 0;
			count_ = 1;
		}

		void assign(uint64_t n)
		{
			chunks_[0] = n;
			count_ = 1;
		}

		void assign(const BigInteger& other)
		{
			if (this == &other) {
				return;
			}

			count_ = other.count_;
			memcpy(chunks_, other.chunks_, sizeof(uint64_t) * count_);
		}

		void assign(const char* str, size_t length)
		{
			zero();
			appendDecimal(str, length);
		}

		void add(uint64_t n)
		{
			uint64_t m = chunks_[0];

			chunks_[0] += n;

			for (size_t i = 0; i < count_ - 1; ++i)
			{
				if (chunks_[i] < m)
				{
					m = chunks_[i + 1];
					chunks_[i + 1] += 1;
				}
				else
				{
					return;
				}
			}

			if (chunks_[count_ - 1] < m) {
				append(1);
			}
		}

		void subtract(const BigInteger& other)
		{
			subtract(this, &other, this);
		}

		void subtractTimes(const BigInteger& other, uint64_t factor)
		{
			if (factor == 0) {
				return;
			}

			if (factor == 1)
			{
				subtract(other);
				return;
			}

			uint64_t borrow = 0;
			uint64_t carry = 0;

			size_t index = 0;

			for (; index < other.count_; ++index)
			{
				uint64_t high;
				uint64_t low = mulAdd64to128(other.chunks_[index], factor, carry, &high);

				uint64_t m = at(index);
				uint64_t n = m - borrow - low;

				chunks_[index] = n;

				borrow = ((n > m) || (n == m && borrow)) ? 1 : 0;
				carry = high;
			}

			for (; index < count_ || ((borrow || carry) && index < max_chunk); ++index)
			{
				uint64_t m = chunks_[index];
				uint64_t n = m - borrow - carry;

				chunks_[index] = n;

				borrow = ((n > m) || (n == m && borrow)) ? 1 : 0;
				carry = 0;
			}

			clamp(index);
		}

		void multiply(uint64_t n)
		{
			if (n == 0) {
				zero();
				return;
			}

			if (n == 1) {
				return;
			}

			if (isZero()) {
				return;
			}

			uint64_t carry = 0;

			for (size_t i = 0; i < count_; ++i)
			{
				uint64_t high;
				uint64_t low = mulAdd64to128(chunks_[i], n, carry, &high);

				chunks_[i] = low;
				carry = high;
			}

			if (carry) {
				append(carry);
			}
		}

		void multiplyPow10(size_t n)
		{
			multiplyPow5(n);
			multiplyPow2(n);
		}

		void multiplyPow5(size_t n)
		{
			static const uint32_t cachedPow5[] = {
				1,
				5,
				5 * 5,
				5 * 5 * 5,
				5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
				5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
			};

			while (n >= 27)
			{
				multiply(ECLOG_MAKE64(0x6765c793, 0xfa10079d));
				n -= 27;
			}

			while (n > 13)
			{
				multiply(cachedPow5[13]);
				n -= 13;
			}

			multiply(cachedPow5[n]);
		}

		void multiplyPow2(size_t n)
		{
			shiftLeft(n);
		}

		void shiftLeft(size_t n)
		{
			if (isZero()) {
				return;
			}

			if (n == 0) {
				return;
			}

			size_t chunkShift = n / 64;
			size_t bitShift = n % 64;

			if (chunkShift > max_chunk - 1)
			{
				zero();
				return;
			}

			size_t count;

			if (bitShift)
			{
				count = chunkShift + count_;
				size_t index = count - 1;
				size_t m = 0;

				uint64_t newChunk = chunks_[count_ - 1] >> (64 - bitShift);

				if (newChunk && index + 1 <= highest_index)
				{
					chunks_[index + 1] = newChunk;
					++count;
				}

				if (index > highest_index)
				{
					m = index - highest_index;
					index = highest_index;
					count = max_chunk;
				}

				for (size_t i = count_ - 1 - m; i > 0; --i) {
					chunks_[index--] = (chunks_[i] << bitShift) | chunks_[i - 1] >> (64 - bitShift);
				}

				chunks_[index] = chunks_[0] << bitShift;
			}
			else
			{
				size_t m = chunkShift + count_ > max_chunk ? max_chunk - chunkShift : count_;
				count = chunkShift + m;

				memmove(&chunks_[chunkShift], &chunks_[0], sizeof(uint64_t) * m);
			}

			memset(chunks_, 0, chunkShift * sizeof(uint64_t));
			clamp(count);
		}

		void shiftRight(size_t n)
		{
			if (isZero()) {
				return;
			}

			if (n == 0) {
				return;
			}

			size_t chunkShift = n / 64;
			size_t bitShift = n % 64;

			if (chunkShift >= count_)
			{
				zero();
				return;
			}

			if (bitShift)
			{
				size_t index = 0;

				for (size_t i = chunkShift; i < count_ - 1; ++i) {
					chunks_[index++] = (chunks_[i] >> bitShift) | chunks_[i + 1] << (64 - bitShift);
				}

				chunks_[index] = chunks_[count_ - 1] >> bitShift;

				count_ -= chunkShift;
				count_ -= (chunks_[index] == 0 && count_ > 1) ? 1 : 0;
			}
			else
			{
				memmove(&chunks_[0], &chunks_[chunkShift], sizeof(uint64_t) * (count_ - chunkShift));
				count_ -= chunkShift;
			}
		}

		uint16_t divideWithRemainder(const BigInteger& other)
		{
			if (other.isZero()) {
				return (uint16_t)(-1);
			}

			if (count_ < other.count_) {
				return 0;
			}

			uint64_t result = 0;

			while (count_ > other.count_)
			{
				uint64_t n = chunks_[count_ - 1];

				subtractTimes(other, n);

				result += n;
			}

			uint64_t a = chunks_[count_ - 1];
			uint64_t b = other.chunks_[other.count_ - 1];

			if (a > b && b + 1 > b)
			{
				uint64_t n = a / (b + 1);

				subtractTimes(other, n);

				result += n;
			}

			while (compare(other) >= 0)
			{
				subtract(other);

				result += 1;
			}

			return (uint16_t)result;
		}

		int difference(const BigInteger& other)
		{
			int cmp = compare(other);

			if (cmp == 0)
			{
				zero();
				return 0;
			}

			const BigInteger* a;
			const BigInteger* b;

			if (cmp < 0)
			{
				a = &other;
				b = this;
			}
			else
			{
				a = this;
				b = &other;
			}

			subtract(a, b, this);

			return cmp;
		}

		void appendDecimal(const char* str, size_t length)
		{
			if (length == (size_t)(-1)) {
				length = strlen(str);
			}

			while (length >= 19)
			{
				appendDecimal64(str, 19);

				str += 19;
				length -= 19;
			}

			if (length) {
				appendDecimal64(str, length);
			}
		}

	private:
		static void subtract(const BigInteger* a, const BigInteger* b, BigInteger* outResult)
		{
			size_t count = max(a->count_, b->count_);
			uint64_t borrow = 0;

			for (size_t i = 0; i < count; ++i)
			{
				uint64_t m = a->at(i);
				uint64_t n = m - borrow - b->at(i);

				outResult->chunks_[i] = n;

				borrow = ((n > m) || (n == m && borrow)) ? 1 : 0;
			}

			if (borrow)
			{
				memset(&outResult->chunks_[count], 0xff, (max_chunk - count) * sizeof(uint64_t));

				outResult->count_ = max_chunk;
			}
			else
			{
				outResult->clamp(count);
			}
		}

		void appendDecimal64(const char* str, size_t length)
		{
			uint64_t n = 0;
			size_t exp = 0;

			for (size_t i = 0; i < length; ++i)
			{
				if (isDigit(*str))
				{
					n = n * 10 + (*str - '0');
					++exp;
				}

				++str;
			}

			if (isZero())
			{
				assign(n);
				return;
			}

			multiplyPow10(exp);
			add(n);
		}

		void append(uint64_t n)
		{
			if (count_ < max_chunk) {
				chunks_[count_++] = n;
			}
		}

		void clamp(size_t count)
		{
			for (count_ = count; count_ > 1; --count_)
			{
				if (chunks_[count_ - 1]) {
					break;
				}
			}
		}

	private:
		uint64_t chunks_[max_chunk];
		size_t count_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_BIGINTEGER_H_

