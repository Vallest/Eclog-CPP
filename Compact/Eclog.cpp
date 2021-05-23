// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Licensed under the MIT License.
//
// This file is auto-generated, do not edit.

#include <Eclog.h>

#define ECLOG_DEFINE_ERROR_ID(Class, Id) \
	const ErrorId& Class::id() \
	{ \
		static ErrorId errid(Id); \
		return errid; \
	}

namespace eclog {

	ECLOG_DEFINE_ERROR_ID(Error, "Error")
	ECLOG_DEFINE_ERROR_ID(RuntimeError, "RuntimeError")
	ECLOG_DEFINE_ERROR_ID(BufferOverflow, "BufferOverflow")
	ECLOG_DEFINE_ERROR_ID(LogicError, "LogicError")
	ECLOG_DEFINE_ERROR_ID(OutOfRange, "OutOfRange")
	ECLOG_DEFINE_ERROR_ID(LengthError, "LengthError")
	ECLOG_DEFINE_ERROR_ID(InvalidArgument, "InvalidArgument")
	ECLOG_DEFINE_ERROR_ID(InvalidOperation, "InvalidOperation")
	ECLOG_DEFINE_ERROR_ID(IOError, "IOError")
	ECLOG_DEFINE_ERROR_ID(UnicodeError, "UnicodeError")
	ECLOG_DEFINE_ERROR_ID(DecodeError, "DecodeError")
	ECLOG_DEFINE_ERROR_ID(EncodeError, "EncodeError")
	ECLOG_DEFINE_ERROR_ID(OutOfMemory, "OutOfMemory")
	ECLOG_DEFINE_ERROR_ID(ParseError, "ParseError")
	ECLOG_DEFINE_ERROR_ID(BadCast, "BadCast")

	const char* getErrorMessage(Success)
	{
		return "success";
	}

	const char* getErrorMessage(ErrorCodeEnum e)
	{
		switch (e)
		{
		case ec_runtime_error:
			return "runtime error";

		case ec_buffer_overflow:
			return "buffer overflow";

		case ec_logic_error:
			return "logic error";

		case ec_out_of_range:
			return "out of range";

		case ec_length_error:
			return "length error";

		case ec_invalid_argument:
			return "invalid argument";

		case ec_invalid_operation:
			return "invalid operation";

		case ec_io_error:
			return "io error";

		case ec_unicode_error:
			return "unicode error";

		case ec_decode_error:
			return "decode error";

		case ec_encode_error:
			return "encode error";

		case ec_out_of_memory:
			return "out of memory";

		case ec_parse_error:
			return "parse error";

		case ec_bad_cast:
			return "bad cast";

		default:
			ECLOG_ASSERT(false);
			return "";
		}
	}

	const char* getErrorMessage(ParseErrorEnum e)
	{
		switch (e)
		{
		case pe_unexpected_end_of_file:
			return "unexpected end of file";

		case pe_unexpected_character:
			return "unexpected character";

		case pe_unrecognized_escape:
			return "unrecognized escape";

		case pe_invalid_unicode_escape:
			return "invalid unicode escape";

        case pe_invalid_utf16_surrogate:
            return "invalid UTF-16 surrogate";

		case pe_unescaped_control_character:
			return "unescaped control character";

		case pe_string_delimiter_too_long:
			return "string delimiter too long";

		case pe_invalid_string_delimiter:
			return "invalid string delimiter";

		case pe_empty_string_delimiter:
			return "empty string delimiter";

		case pe_empty_key:
			return "empty key";

		case pe_invalid_key:
			return "invalid key";

		case pe_user_asked_for_termination:
			return "user asked for termination";

		default:
			ECLOG_ASSERT(false);
			return "";
		}
	}

	const ErrorId& getErrorId(ErrorCodeEnum e)
	{
		switch (e)
		{
		case ec_runtime_error:
			return RuntimeError::id();

		case ec_buffer_overflow:
			return BufferOverflow::id();

		case ec_logic_error:
			return LogicError::id();

		case ec_out_of_range:
			return OutOfRange::id();

		case ec_length_error:
			return LengthError::id();

		case ec_invalid_argument:
			return InvalidArgument::id();

		case ec_invalid_operation:
			return InvalidOperation::id();

		case ec_io_error:
			return IOError::id();

		case ec_unicode_error:
			return UnicodeError::id();

		case ec_decode_error:
			return DecodeError::id();

		case ec_encode_error:
			return EncodeError::id();

		case ec_out_of_memory:
			return OutOfMemory::id();

		case ec_parse_error:
			return ParseError::id();

		case ec_bad_cast:
			return BadCast::id();

		default:
			ECLOG_ASSERT(false);
			return Error::id();
		}
	}

	template<typename T>
	const T* getDefaultError(typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type*)
	{
		static T err;
		return &err;
	}

	template const RuntimeError* getDefaultError(void*);
	template const BufferOverflow* getDefaultError(void*);
	template const LogicError* getDefaultError(void*);
	template const OutOfRange* getDefaultError(void*);
	template const LengthError* getDefaultError(void*);
	template const InvalidArgument* getDefaultError(void*);
	template const InvalidOperation* getDefaultError(void*);
	template const IOError* getDefaultError(void*);
	template const UnicodeError* getDefaultError(void*);
	template const DecodeError* getDefaultError(void*);
	template const EncodeError* getDefaultError(void*);
	template const OutOfMemory* getDefaultError(void*);
	template const BadCast* getDefaultError(void*);

} // eclog

#if defined(_MSC_VER) && (_MSC_VER >= 1500) && defined(_M_X64)
	#define ECLOG_HAS_UMUL128
	#include <intrin.h>
#endif

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

#include <string.h> // strlen, memset, memcmp, memmove

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

#include <string.h> // memcpy, memmove, strncmp
#include <math.h> // ceil

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

#include <string.h> // memmove, memset

namespace eclog {

	namespace detail {

		int UTF8Decoder::decode(ErrorCode* ec)
		{
			static const char length[32] = {
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0,
			};

			static const char mask[5] = { 0, 0x7f, 0x1f, 0x0f, 0x07 };
			static const char shift[5] = { 0, 18, 12, 6, 0 };
			static const int min[5] = { 2097152, 0, 128, 2048, 65536 };
			static const char shifte[5] = { 0, 6, 4, 2, 0 };

			if (avail_ < 4)
			{
				memmove(buffer_, p_, avail_);
				p_ = buffer_;

				if (is_.eof())
				{
					if (avail_ == 0) {
						return -1;
					}

					memset(buffer_ + avail_, 0, 4 - avail_);
				}
				else
				{
					while (avail_ < 4)
					{
						size_t free = detail::arraySize(buffer_) - avail_;

						size_t read = is_.read((char*)buffer_ + avail_, free);

						avail_ += read;

						if (!is_.state())
						{
							if (is_.eof())
							{
								if (avail_ == 0) {
									return -1;
								}

								if (avail_ < 4)
								{
									memset(buffer_ + avail_, 0, 4 - avail_);
								}

								break;
							}
							else
							{
								ECLOG_ERROR(IOError);
								return -2;
							}
						}
					}
				}
			}

			int n = length[p_[0] >> 3];

			int code = (p_[0] & mask[n]) << 18;
			code |= (p_[1] & 0x3f) << 12;
			code |= (p_[2] & 0x3f) << 6;
			code |= (p_[3] & 0x3f) << 0;
			code >>= shift[n];

			int error = (code < min[n]) << 7;
			error |= ((code >> 11) == 0x1b) << 6; // surrogate character (U+D800-U+DFFF) ?
			error |= (p_[1] & 0xc0) >> 2;
			error |= (p_[2] & 0xc0) >> 4;
			error |= (p_[3]) >> 6;
			error ^= 0x2a;
			error >>= shifte[n];

			if (error)
			{
				ECLOG_ERROR(DecodeError);
				return -2;
			}

			p_ += n;
			avail_ -= n;

			return code;
		}

	} // detail

} // eclog

namespace eclog {

	namespace detail {

		void UTF8Encoder::encode(int ch, ErrorCode* ec)
		{
			char bytes[4];
			int n = 0;

			if (ch < 128)
			{
				n = 1;
				bytes[0] = (char)ch;
			}
			else if (ch < 2048)
			{
				n = 2;
				bytes[0] = (char)(0xc0 | (ch >> 6));
				bytes[1] = (char)(0x80 | (ch & 0x3f));
			}
			else if (ch < 65536)
			{
				n = 3;
				bytes[0] = (char)(0xe0 | (ch >> 12));
				bytes[1] = (char)(0x80 | ((ch >> 6) & 0x3f));
				bytes[2] = (char)(0x80 | (ch & 0x3f));
			}
			else if (ch < 2097152)
			{
				n = 4;
				bytes[0] = (char)(0xf0 | (ch >> 18));
				bytes[1] = (char)(0x80 | ((ch >> 12) & 0x3f));
				bytes[2] = (char)(0x80 | ((ch >> 6) & 0x3f));
				bytes[3] = (char)(0x80 | (ch & 0x3f));
			}

			int error = (n == 0) << 1;
			error |= ((ch >> 11) == 0x1b) << 0; // surrogate character (U+D800-U+DFFF) ?

			if (error)
			{
				ECLOG_ERROR(EncodeError);
				return;
			}

			os_.write(bytes, n);

			if (!os_.state())
			{
				ECLOG_ERROR(IOError);
				return;
			}
		}

	} // detail

} // eclog

namespace eclog {

	Null null;

} // eclog

#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		template<typename T, size_t MaxSize>
		class InlineStack {
		public:
			InlineStack() : size_(0)
			{
			}

			size_t maxSize() const
			{
				return MaxSize;
			}

			size_t size() const
			{
				return size_;
			}

			T& top()
			{
				ECLOG_ASSERT(size_ > 0 && size_ <= MaxSize);
				return stack_[size_ - 1];
			}

			const T& top() const
			{
				ECLOG_ASSERT(size_ > 0 && size_ <= MaxSize);
				return stack_[size_ - 1];
			}

			void push(const T& value)
			{
				ECLOG_ASSERT(size_ < MaxSize);
				stack_[size_++] = value;
			}

			void pop()
			{
				ECLOG_ASSERT(size_ > 0);
				--size_;
			}

		private:
			T stack_[MaxSize];

			size_t size_;
		};

	} // detail

} // eclog

namespace eclog {

	namespace detail {

		template<size_t MaxSize>
		class ParsingBufferGuard : private NonCopyable {
		public:
			explicit ParsingBufferGuard(ParsingBuffer& parsingBuffer) :
				parsingBuffer_(parsingBuffer)
			{
			}

			~ParsingBufferGuard()
			{
				clear();
			}

			void clear()
			{
				while (ptrs_.size()) {
					pop();
				}
			}

			void push()
			{
				void* ptr = parsingBuffer_.claim();

				ptrs_.push(ptr);
			}

			void pop()
			{
				void* ptr = ptrs_.top();

				parsingBuffer_.discard(ptr);

				ptrs_.pop();
			}

		private:
			ParsingBuffer& parsingBuffer_;

			InlineStack<void*, MaxSize> ptrs_;
		};

	} // detail

} // eclog

#include <stddef.h> // size_t
#include <limits.h>

namespace eclog {

	namespace detail {

		static void onUnexpectedChar(int line, int column, int ch, ErrorCode* ec)
		{
			if (ch < 0) {
				ECLOG_ERROR(ParseError, line, column, pe_unexpected_end_of_file);
			}
			else {
				ECLOG_ERROR(ParseError, line, column, pe_unexpected_character);
			}
		}

		static int peekNonEof(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return -1);

			if (ch < 0)
			{
				ECLOG_ERROR(ParseError, ctx.line(), ctx.column(), pe_unexpected_end_of_file);
				return -2;
			}

			return ch;
		}

		static void transferChar(Context& ctx)
		{
			int ch = ctx.decoder().getChar(0);
			ctx.buffer().putChar(ch);
		}

		static void transferChar(Context& ctx, int ch)
		{
			ctx.decoder().getChar(0);
			ctx.buffer().putChar(ch);
		}

		static void transferSequence(Context& ctx, const char* s, ErrorCode* ec)
		{
			while (*s)
			{
				int ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (ch != *s)
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}

				transferChar(ctx);

				++s;
			}
		}

        static bool skipSequence(Context& ctx, const char* s, ErrorCode* ec)
        {
            while (*s)
            {
                int ch = peekNonEof(ctx, ec);
                ECLOG_ON_ERROR(return false);

                if (ch != *s) {
                    return false;
                }

                ctx.decoder().getChar(0);

                ++s;
            }

            return true;
        }

		static bool skipSpacesAndTabs(Context& ctx, ErrorCode* ec)
		{
			int count = 0;

			for (;;)
			{
				int ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return false);

				if (ch == ' ')
				{
					ctx.decoder().getChar(0);
					++count;
				}
				else if (ch == '\t')
				{
					ctx.decoder().getChar(0);
					++count;
				}
				else
				{
					break;
				}
			}

			return count > 0;
		}

		static int skipLinebreak(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return 0);

			int linebreak = 0;

			if (ch == '\r')
			{
				ctx.decoder().getChar(0);

				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return 0);

				if (ch == '\n')
				{
					ctx.decoder().getChar(0);
					linebreak = CRLF;
				}
				else
				{
					linebreak = CR;
				}
			}
			else if (ch == '\n')
			{
				ctx.decoder().getChar(0);
				linebreak = LF;
			}

			if (linebreak) {
				ctx.addLine();
			}

			return linebreak;
		}

		static bool skipComment(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return false);

			if (ch == '#')
			{
				ctx.decoder().getChar(0);

				for (;;)
				{
					ch = ctx.decoder().peekChar(ec);
					ECLOG_ON_ERROR(return false);

					if (ch == '\r' || ch == '\n')
					{
						skipLinebreak(ctx, ec);
						ECLOG_ON_ERROR(return false);

						return true;
					}
					else if (ch < 0)
					{
						return true;
					}
					else if (ch < 0x20 && ch != '\t')
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return false;
					}

					ctx.decoder().getChar(0);
				}
			}

			return false;
		}

		static void skipWhitespaceAndComments(Context& ctx, ErrorCode* ec)
		{
			for (;;)
			{
				bool spaces = skipSpacesAndTabs(ctx, ec);
				ECLOG_ON_ERROR(return);

				int linebreak = skipLinebreak(ctx, ec);
				ECLOG_ON_ERROR(return);

				bool comment = skipComment(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (!spaces && !comment && !linebreak) {
					return;
				}
			}
		}

		static void writeLinebreak(Context& ctx, int linebreak)
		{
			switch (linebreak)
			{
			case CR:
				ctx.buffer().putChar('\r');
				break;

			case LF:
				ctx.buffer().putChar('\n');
				break;

			case CRLF:
				ctx.buffer().putChar('\r');
				ctx.buffer().putChar('\n');
				break;
			}
		}

		static int parseUnicodeHexDigits(Context& ctx, ErrorCode* ec)
		{
            int ch = peekNonEof(ctx, ec);
            ECLOG_ON_ERROR(return 0);

            bool variableLength = false;

            if (ch == '{')
            {
                ctx.decoder().getChar(0);

                variableLength = true;
            }

            int code = 0;

			size_t i = 0;
            const size_t length = variableLength ? 6 : 4;

			for (; i < length; ++i)
			{
                ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return false);

				if (isBetween(ch, '0', '9'))
				{
					ctx.decoder().getChar(0);
                    code = (code << 4) + (ch - '0');
				}
				else if (isBetween(ch, 'a', 'f'))
				{
					ctx.decoder().getChar(0);
                    code = (code << 4) + 10 + (ch - 'a');
				}
				else if (isBetween(ch, 'A', 'F'))
				{
					ctx.decoder().getChar(0);
                    code = (code << 4) + 10 + (ch - 'A');
				}
				else
				{
                    break;
				}
			}

            if (code > 0x10ffff)
            {
                return -1;
            }
            else if (!variableLength && i == 4)
            {
                return code;
            }
            else if (variableLength && i > 0)
            {
                ch = peekNonEof(ctx, ec);
                ECLOG_ON_ERROR(return false);

                if (ch == '}')
                {
                    ctx.decoder().getChar(0);

                    return code;
                }
                else
                {
                    return -2;
                }
            }
            else
            {
                return -3;
            }
		}

		static int parseUnicodeEscapeSequence(Context& ctx, ErrorCode* ec)
		{
			int ch = peekNonEof(ctx, ec);
			ECLOG_ON_ERROR(return 0);

			ECLOG_ASSERT(ch == 'u');

			ctx.decoder().getChar(0);

            const int escapeCharColumn = ctx.column() - 2;

            int code = parseUnicodeHexDigits(ctx, ec);
            ECLOG_ON_ERROR(return 0);

            if (code < 0)
            {
                ECLOG_ERROR(ParseError, ctx.line(), escapeCharColumn, pe_invalid_unicode_escape);
                return 0;
            }

			// surrogate character (U+D800-U+DFFF) ?
			if ((code >> 11) == 0x1b)
			{
				if ((code >> 10) == 0x36)
				{
                    const int high = code;

                    const bool hasNext = skipSequence(ctx, "\\u", ec);
                    ECLOG_ON_ERROR(return 0);

                    if (hasNext)
                    {
                        const int low = parseUnicodeHexDigits(ctx, ec);
                        ECLOG_ON_ERROR(return 0);

                        if ((low >> 10) == 0x37)
                        {
                            code = (((high & 0x3ff) << 10) | (low & 0x3ff)) + 0x10000;

                            return code;
                        }
                    }
				}

                ECLOG_ERROR(ParseError, ctx.line(), escapeCharColumn, pe_invalid_utf16_surrogate);
                return 0;
			}
			else
			{
                return code;
			}
		}

		static void transferDecimalDigits(Context& ctx, ErrorCode* ec)
		{
			int ch = peekNonEof(ctx, ec);
			ECLOG_ON_ERROR(return);

			transferChar(ctx);

			for (;;)
			{
				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				if (isDigit(ch)) {
					transferChar(ctx);
				}
				else {
					return;
				}
			}
		}

		static void transferUnquotedString(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(isAlpha(ch) || ch == '_');

			transferChar(ctx);

			for (;;)
			{
				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				if (isAlpha(ch) || isDigit(ch) || ch == '_' || ch == '-' || ch == '.')
				{
					transferChar(ctx);
				}
				else
				{
					return;
				}
			}
		}

		static void transferQuotedString(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '"');

			ctx.decoder().getChar(0);

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (ch == '\\')
				{
					ctx.decoder().getChar(0);

					ch = peekNonEof(ctx, ec);
					ECLOG_ON_ERROR(return);

					switch (ch)
					{
					case '\"':
					case '\\':
					case '/':
						transferChar(ctx);
						break;

					case 'b':
						transferChar(ctx, '\b');
						break;

					case 'f':
						transferChar(ctx, '\f');
						break;

					case 'n':
						transferChar(ctx, '\n');
						break;

					case 'r':
						transferChar(ctx, '\r');
						break;

					case 't':
						transferChar(ctx, '\t');
						break;

					case 'u':
						ch = parseUnicodeEscapeSequence(ctx, ec);
						ECLOG_ON_ERROR(return);

                        ctx.buffer().putChar(ch);
						break;

					default:
						ECLOG_ERROR(ParseError, ctx.line(), ctx.column() - 1, pe_unrecognized_escape);
						return;
					}
				}
				else if (ch < 0x20 && ch != '\t')
				{
					ECLOG_ERROR(ParseError, ctx.line(), ctx.column(), pe_unescaped_control_character);
					return;
				}
				else if (ch == '"')
				{
					ctx.decoder().getChar(0);
					return;
				}
				else
				{
					transferChar(ctx);
				}
			}
		}

		static void transferRawString(Context& ctx, bool embedDelimiter, size_t& delimiterSize, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '@');

			ctx.decoder().getChar(0);

			const int delimiterColumn = ctx.column();

			InlineArray<char, 16> delimiter;

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (isAlphanum(ch) || ch == '_')
				{
					if (delimiter.size() < 16)
					{
						ctx.decoder().getChar(0);
						delimiter.pushBack((char)ch);
					}
					else
					{
						ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_string_delimiter_too_long);
						return;
					}
				}
				else
				{
					break;
				}
			}

			if (ch == '"')
			{
				ctx.decoder().getChar(0);
			}
			else
			{
				ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_invalid_string_delimiter);
				return;
			}

			if (embedDelimiter)
			{
				for (size_t i = 0; i < delimiter.size(); ++i)
				{
					ctx.buffer().putChar(delimiter[i]);
				}

				delimiterSize = delimiter.size();
			}
			else
			{
				delimiterSize = 0;
			}

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (ch == '"')
				{
					ctx.decoder().getChar(0);

					size_t m = 0;

					while (m < delimiter.size())
					{
						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == delimiter[m])
						{
							ctx.decoder().getChar(0);
							++m;
						}
						else {
							break;
						}
					}

					if (m == delimiter.size()) {
						return;
					}

					ctx.buffer().putChar('"');

					for (size_t i = 0; i < m; ++i)
					{
						ctx.buffer().putChar(delimiter[i]);
					}
				}
				else if (ch < 0x20 && ch != '\t')
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}
				else
				{
					transferChar(ctx);
				}
			}
		}

        static size_t unindent(char* str, size_t length, int indent)
        {
            const char* first = str;
            const char* last = first + length;

            char* p = str;

            bool beginOfLine = true;
            int n = 0;

            while (first != last)
            {
                if (beginOfLine && (*first == ' ' || *first == '\t') && n < indent)
                {
                    first++;
                    n++;
                }
                else if (*first == '\r' || *first == '\n')
                {
                    if (*first == '\r')
                    {
                        *p++ = *first++;

                        if (first != last && *first == '\n')
                        {
                            *p++ = *first++;
                        }
                    }
                    else if (*first == '\n')
                    {
                        *p++ = *first++;
                    }

                    beginOfLine = true;
                    n = 0;
                }
                else
                {
                    *p++ = *first++;

                    beginOfLine = false;
                }
            }

            return p - str;
        }

		static void transferHeredocString(Context& ctx, bool embedDelimiter, size_t& delimiterSize, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '|');

			ctx.decoder().getChar(0);

			const int delimiterColumn = ctx.column();

			InlineArray<char, 16> delimiter;

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (isAlphanum(ch) || ch == '_')
				{
					if (delimiter.size() < 16)
					{
						ctx.decoder().getChar(0);
						delimiter.pushBack((char)ch);
					}
					else
					{
						ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_string_delimiter_too_long);
						return;
					}
				}
				else
				{
					break;
				}
			}

			ch = peekNonEof(ctx, ec);
			ECLOG_ON_ERROR(return);

			if (ch == '\r' || ch == '\n')
			{
				if (delimiter.size() == 0)
				{
					ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_empty_string_delimiter);
					return;
				}

				skipLinebreak(ctx, ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_invalid_string_delimiter);
				return;
			}

			if (embedDelimiter)
			{
				for (size_t i = 0; i < delimiter.size(); ++i)
				{
					ctx.buffer().putChar(delimiter[i]);
				}

				delimiterSize = delimiter.size();
			}
			else
			{
				delimiterSize = 0;
			}

			const size_t docBeginPos = ctx.buffer().length();

			size_t lineBeginPos = docBeginPos;

			bool beginOfLine = true;
			int indent = 0;
			int charCount = 0;

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (beginOfLine && (ch == ' ' || ch == '\t'))
				{
					transferChar(ctx);

					++indent;
				}
				else if (beginOfLine && ch == delimiter[0])
				{
					ctx.decoder().getChar(0);

					size_t m = 1;

					while (m < delimiter.size())
					{
						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == delimiter[m])
						{
							ctx.decoder().getChar(0);
							++m;
						}
						else {
							break;
						}
					}

					if (m == delimiter.size())
					{
						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == '\r' || ch == '\n')
						{
							if (indent > 0) {
								ctx.buffer().shrink(lineBeginPos);
							}

							break;
						}
					}

					for (size_t i = 0; i < m; ++i)
					{
						ctx.buffer().putChar(delimiter[i]);
					}
				}
				else if (ch == '\r' || ch == '\n')
				{
					int linebreak = skipLinebreak(ctx, ec);
					ECLOG_ON_ERROR(return);

					writeLinebreak(ctx, linebreak);

					lineBeginPos = ctx.buffer().length();
					beginOfLine = true;
					indent = 0;
					charCount = 0;
				}
				else if (ch < 0x20 && ch != '\t')
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}
				else
				{
					transferChar(ctx);

					beginOfLine = false;
					++charCount;
				}
			}

			if (indent > 0)
			{
				size_t length = unindent(ctx.buffer().address() + docBeginPos,
					ctx.buffer().length() - docBeginPos, indent);

				ctx.buffer().shrink(docBeginPos + length);
			}
		}

		static void transferString(Context& ctx, int& stringNotation, bool embedDelimiter, size_t& delimiterSize, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (isAlpha(ch) || ch == '_')
			{
				transferUnquotedString(ctx, ec);
				ECLOG_ON_ERROR(return);

				stringNotation |= string_notation_unquoted;
				delimiterSize = 0;
			}
			else if (ch == '"')
			{
				transferQuotedString(ctx, ec);
				ECLOG_ON_ERROR(return);

				stringNotation |= string_notation_quoted;
				delimiterSize = 0;
			}
			else if (ch == '@')
			{
				transferRawString(ctx, embedDelimiter, delimiterSize, ec);
				ECLOG_ON_ERROR(return);

				stringNotation |= string_notation_raw;
			}
			else if (ch == '|')
			{
				transferHeredocString(ctx, embedDelimiter, delimiterSize, ec);
				ECLOG_ON_ERROR(return);

				stringNotation |= string_notation_heredoc;
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
			}
		}

		static void transferNumber(Context& ctx, int& outNumberInfo, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '+' || ch == '-' || isDigit(ch));

			enum {
				state_sign,
				state_int,
				state_frac,
				state_exp,
				state_end,
			};

			int state = state_sign;

			for (;;)
			{
				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				switch (state)
				{
				case state_sign:
					if (ch == '+' || ch == '-')
					{
						outNumberInfo |= number_info_has_sign;

						if (ch == '-') {
							outNumberInfo |= number_info_has_neg_sign;
						}

						transferChar(ctx);

						state = state_int;
						break;
					}
					ECLOG_FALLTHROUGH

				case state_int:
					if (ch == '0')
					{
						transferChar(ctx);
						state = state_frac;
					}
					else if (isBetween(ch, '1', '9'))
					{
						transferDecimalDigits(ctx, ec);
						ECLOG_ON_ERROR(return);

						state = state_frac;
					}
					else if (ch == 'i')
					{
						outNumberInfo |= number_info_inf;

						transferSequence(ctx, "inf", ec);
						ECLOG_ON_ERROR(return);

						state = state_end;
						break;
					}
					else if (ch == 'n')
					{
						outNumberInfo |= number_info_nan;

						transferSequence(ctx, "nan", ec);
						ECLOG_ON_ERROR(return);

						state = state_end;
						break;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;

				case state_frac:
					if (ch == '.')
					{
						outNumberInfo |= number_info_has_frac;

						transferChar(ctx);

						transferDecimalDigits(ctx, ec);
						ECLOG_ON_ERROR(return);

						state = state_exp;
						break;
					}
					ECLOG_FALLTHROUGH

				case state_exp:
					if (ch == 'e' || ch == 'E')
					{
						outNumberInfo |= number_info_has_exp;

						transferChar(ctx);

						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == '+' || ch == '-')
						{
							transferChar(ctx);

							ch = peekNonEof(ctx, ec);
							ECLOG_ON_ERROR(return);
						}

						if (ch == '0')
						{
							transferChar(ctx);
						}
						else if (isBetween(ch, '1', '9'))
						{
							transferDecimalDigits(ctx, ec);
							ECLOG_ON_ERROR(return);
						}
						else
						{
							onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
							return;
						}

						state = state_end;
						break;
					}

				case state_end:
					return;
				}
			}
		}

		static void parseKeyValuePairList(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			enum {
				state_key,
				state_key2,
				state_key_separator,
				state_value,
				state_value2,
				state_next,
				state_keyword_or_string,
				state_keyword_or_string2,
				state_keyword_or_string3,
			};

			enum {
				keyword_true = 1,
				keyword_false,
				keyword_inf,
				keyword_nan,
				keyword_null
			};

			ParsingBufferGuard<2> parsingBufferGuard(ctx.buffer());

			InlineStack<int, 2> state;

			int line = 0;
			int column = 0;

			int keyword = 0;

			int stringNotation = 0;
			size_t delimiterSize = 0;

			int lineOfLastValue = 0;

			state.push(state_key);

			for (;;)
			{
				skipWhitespaceAndComments(ctx, ec);
				ECLOG_ON_ERROR(return);

				int ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				switch (state.top())
				{
				case state_key:
					if (isAlpha(ch) || ch == '_' || ch == '"' || ch == '@' || ch == '|')
					{
						parsingBufferGuard.push();

						line = ctx.line();
						column = ctx.column();

						state.top() = state_key2;
						state.push(state_keyword_or_string);
					}
					else
					{
						return;
					}
					break;

				case state_key2:
					if (!keyword)
					{
						if (ctx.buffer().str().empty())
						{
							ECLOG_ERROR(ParseError, line, column, pe_empty_key);
							return;
						}

						handler.onKey(Key(ctx.buffer().str(), (StringNotation)stringNotation, delimiterSize), ec);
						ECLOG_ON_ERROR(return);

						state.top() = state_key_separator;;
					}
					else
					{
						ECLOG_ERROR(ParseError, line, column, pe_invalid_key);
						return;
					}
					break;

				case state_key_separator:
					if (ch == ':')
					{
						ctx.decoder().getChar(0);

						state.top() = state_value;;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;

				case state_value:
					if (isAlpha(ch) || ch == '_' || ch == '"' || ch == '@' || ch == '|')
					{
						parsingBufferGuard.push();

						state.top() = state_value2;
						state.push(state_keyword_or_string);
					}
					else if (ch == '+' || ch == '-' || isDigit(ch))
					{
						parsingBufferGuard.push();

						int numberInfo = 0;

						transferNumber(ctx, numberInfo, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						handler.onValue(Value(value_type_number, ctx.buffer().str(), (NumberInfo)numberInfo), ec);
						ECLOG_ON_ERROR(return);

						state.top() = state_next;
					}
					else if (ch == '{')
					{
						handler.onValue(Value(value_type_object), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else if (ch == '[')
					{
						handler.onValue(Value(value_type_array), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;

				case state_value2:
					switch (keyword)
					{
					case keyword_true:
					case keyword_false:
						handler.onValue(Value(value_type_boolean, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_inf:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_inf), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_nan:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_nan), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_null:
						handler.onValue(Value(value_type_null, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					default:
						handler.onValue(Value(value_type_string, ctx.buffer().str(), (StringNotation)stringNotation, delimiterSize), ec);
						ECLOG_ON_ERROR(return);
						break;
					}

					state.top() = state_next;
					break;

				case state_next:
					if (ch == ',')
					{
						ctx.decoder().getChar(0);

						parsingBufferGuard.clear();

						state.top() = state_key;
					}
					else if (ctx.line() > lineOfLastValue)
					{
						parsingBufferGuard.clear();

						state.top() = state_key;
					}
					else
					{
						return;
					}
					break;

				case state_keyword_or_string:
					keyword = 0;
					stringNotation = 0;

					transferString(ctx, stringNotation, true, delimiterSize, ec);
					ECLOG_ON_ERROR(return);

					lineOfLastValue = ctx.line();

					if (stringNotation == string_notation_unquoted)
					{
						if (ctx.buffer().str() == "true") {
							keyword = keyword_true;
						}
						else if (ctx.buffer().str() == "false") {
							keyword = keyword_false;
						}
						else if (ctx.buffer().str() == "inf") {
							keyword = keyword_inf;
						}
						else if (ctx.buffer().str() == "nan") {
							keyword = keyword_nan;
						}
						else if (ctx.buffer().str() == "null") {
							keyword = keyword_null;
						}

						state.pop();
					}
					else
					{
						state.top() = state_keyword_or_string2;
					}
					break;

				case state_keyword_or_string2:
					if (ch == '+')
					{
						ctx.decoder().getChar(0);

						state.top() = state_keyword_or_string3;
					}
					else
					{
						state.pop();
					}
					break;

				case state_keyword_or_string3:
					if (ch == '"' || ch == '@' || ch == '|')
					{
						transferString(ctx, stringNotation, false, delimiterSize, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_keyword_or_string2;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;
				};
			}
		}

		static void parseValueList(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			enum {
				state_value,
				state_value2,
				state_next,
				state_keyword_or_string,
				state_keyword_or_string2,
				state_keyword_or_string3,
			};

			enum {
				keyword_true = 1,
				keyword_false,
				keyword_inf,
				keyword_nan,
				keyword_null
			};

			ParsingBufferGuard<2> parsingBufferGuard(ctx.buffer());

			InlineStack<int, 2> state;

			int keyword = 0;

			int stringNotation = 0;
			size_t delimiterSize = 0;

			int lineOfLastValue = 0;

			state.push(state_value);

			for (;;)
			{
				skipWhitespaceAndComments(ctx, ec);
				ECLOG_ON_ERROR(return);

				int ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				switch (state.top())
				{
				case state_value:
					if (isAlpha(ch) || ch == '_' || ch == '"' || ch == '@' || ch == '|')
					{
						parsingBufferGuard.push();

						state.top() = state_value2;
						state.push(state_keyword_or_string);
					}
					else if (ch == '+' || ch == '-' || isDigit(ch))
					{
						parsingBufferGuard.push();

						int numberInfo = 0;

						transferNumber(ctx, numberInfo, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						handler.onValue(Value(value_type_number, ctx.buffer().str(), (NumberInfo)numberInfo), ec);
						ECLOG_ON_ERROR(return);

						state.top() = state_next;
					}
					else if (ch == '{')
					{
						handler.onValue(Value(value_type_object), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else if (ch == '[')
					{
						handler.onValue(Value(value_type_array), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else
					{
						return;
					}
					break;

				case state_value2:
					switch (keyword)
					{
					case keyword_true:
					case keyword_false:
						handler.onValue(Value(value_type_boolean, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_inf:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_inf), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_nan:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_nan), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_null:
						handler.onValue(Value(value_type_null, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					default:
						handler.onValue(Value(value_type_string, ctx.buffer().str(), (StringNotation)stringNotation, delimiterSize), ec);
						ECLOG_ON_ERROR(return);
						break;
					}

					state.top() = state_next;
					break;

				case state_next:
					if (ch == ',')
					{
						ctx.decoder().getChar(0);

						parsingBufferGuard.clear();

						state.top() = state_value;
					}
					else if (ctx.line() > lineOfLastValue)
					{
						parsingBufferGuard.clear();

						state.top() = state_value;
					}
					else
					{
						return;
					}
					break;

				case state_keyword_or_string:
					keyword = 0;
					stringNotation = 0;

					transferString(ctx, stringNotation, true, delimiterSize, ec);
					ECLOG_ON_ERROR(return);

					lineOfLastValue = ctx.line();

					if (stringNotation == string_notation_unquoted)
					{
						if (ctx.buffer().str() == "true") {
							keyword = keyword_true;
						}
						else if (ctx.buffer().str() == "false") {
							keyword = keyword_false;
						}
						else if (ctx.buffer().str() == "inf") {
							keyword = keyword_inf;
						}
						else if (ctx.buffer().str() == "nan") {
							keyword = keyword_nan;
						}
						else if (ctx.buffer().str() == "null") {
							keyword = keyword_null;
						}

						state.pop();
					}
					else
					{
						state.top() = state_keyword_or_string2;
					}
					break;

				case state_keyword_or_string2:
					if (ch == '+')
					{
						ctx.decoder().getChar(0);

						state.top() = state_keyword_or_string3;
					}
					else
					{
						state.pop();
					}
					break;

				case state_keyword_or_string3:
					if (ch == '"' || ch == '@' || ch == '|')
					{
						transferString(ctx, stringNotation, false, delimiterSize, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_keyword_or_string2;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;
				};
			}
		}

		void parseObject(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			enum {
				flag_none = 0,
				flag_root_object = 1 << 0,
				flag_curly_bracket = 1 << 1,
			};

			int flag = flag_none;

			if (ctx.decoder().position() == 0) {
				flag |= flag_root_object;
			}

			if (flag & flag_root_object)
			{
				skipWhitespaceAndComments(ctx, ec);
				ECLOG_ON_ERROR(return);
			}

			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch == '{')
			{
				ctx.decoder().getChar(0);

				flag |= flag_curly_bracket;

				handler.onObjectBegin(ec);
				ECLOG_ON_ERROR(return);

				if (!(flag & flag_root_object)) {
					ctx.beginNested();
				}
			}
			else if (flag & flag_root_object)
			{
				handler.onObjectBegin(ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}

			parseKeyValuePairList(ctx, handler, ec);
			ECLOG_ON_ERROR(return);

			skipWhitespaceAndComments(ctx, ec);
			ECLOG_ON_ERROR(return);

			ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (flag & flag_root_object)
			{
				if (flag & flag_curly_bracket)
				{
					if (ch == '}')
					{
						ctx.decoder().getChar(0);

						handler.onObjectEnd(ec);
						ECLOG_ON_ERROR(return);

						skipWhitespaceAndComments(ctx, ec);
						ECLOG_ON_ERROR(return);

						ch = ctx.decoder().peekChar(ec);
						ECLOG_ON_ERROR(return);

						if (ch >= 0)
						{
							onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
							return;
						}
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
				}
				else if (ch < 0)
				{
					handler.onObjectEnd(ec);
					ECLOG_ON_ERROR(return);
				}
				else
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}
			}
			else if (ch == '}')
			{
				ctx.decoder().getChar(0);

				handler.onObjectEnd(ec);
				ECLOG_ON_ERROR(return);

				ctx.endNested();
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}
		}

		void parseArray(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch == '[')
			{
				ctx.decoder().getChar(0);

				handler.onArrayBegin(ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}

			ctx.beginNested();

			parseValueList(ctx, handler, ec);
			ECLOG_ON_ERROR(return);

			skipWhitespaceAndComments(ctx, ec);
			ECLOG_ON_ERROR(return);

			ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch == ']')
			{
				ctx.decoder().getChar(0);

				handler.onArrayEnd(ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}

			ctx.endNested();
		}

	} // detail

} // eclog

#define ECLOG_NUMBER_BUFFER_SIZE 32

namespace eclog {

	namespace detail {

		Renderer::Renderer(OutputStream& stream, const RendererConfig& rendererConfig) :
			encoder_(stream), rc_(rendererConfig)
		{
			nestingLevel_ = 0;
			indent_ = 0;
			beginOfLine_ = true;
			separator_ = 0;
			inline_ = 0;
			error_ = 0;
		}

		void Renderer::beginObject(const KeyDesc& key, ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			beginItem(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderString(key.str(), key.notation(), key.delimiter(), ec);
			ECLOG_ON_ERROR(setError(); return);

			renderColon(ec);
			ECLOG_ON_ERROR(setError(); return);

			if (rc_.formatting == RendererConfig::formatting_regular)
			{
				if (!rc_.placeOpenBracketOnNewLineForObjects || inline_)
				{
					renderSpace(ec);
					ECLOG_ON_ERROR(setError(); return);
				}
				else if (rc_.placeOpenBracketOnNewLineForObjects)
				{
					renderLinebreak(ec);
					ECLOG_ON_ERROR(setError(); return);

					renderIndent(ec);
					ECLOG_ON_ERROR(setError(); return);
				}
			}

			renderLeftCurlyBracket(ec);
			ECLOG_ON_ERROR(setError(); return);

			beginStruct(ec);
			ECLOG_ON_ERROR(setError(); return);

			increaseNestingLevel();
		}

		void Renderer::beginObject(ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			if (nestingLevel() > 0 || rc_.encloseRootObjectWithCurlyBrackets)
			{
				beginItem(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderLeftCurlyBracket(ec);
				ECLOG_ON_ERROR(setError(); return);

				beginStruct(ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			increaseNestingLevel();
		}

		void Renderer::endObject(ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			decreaseNestingLevel();

			if (nestingLevel() > 0 || rc_.encloseRootObjectWithCurlyBrackets)
			{
				endStruct(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderRightCurlyBracket(ec);
				ECLOG_ON_ERROR(setError(); return);

				endItem();
			}
		}

		void Renderer::beginArray(const KeyDesc& key, ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			beginItem(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderString(key.str(), key.notation(), key.delimiter(), ec);
			ECLOG_ON_ERROR(setError(); return);

			renderColon(ec);
			ECLOG_ON_ERROR(setError(); return);

			if (rc_.formatting == RendererConfig::formatting_regular)
			{
				if (!rc_.placeOpenBracketOnNewLineForArrays || inline_)
				{
					renderSpace(ec);
					ECLOG_ON_ERROR(setError(); return);
				}
				else if (rc_.placeOpenBracketOnNewLineForArrays)
				{
					renderLinebreak(ec);
					ECLOG_ON_ERROR(setError(); return);

					renderIndent(ec);
					ECLOG_ON_ERROR(setError(); return);
				}
			}

			renderLeftSquareBracket(ec);
			ECLOG_ON_ERROR(setError(); return);

			beginStruct(ec);
			ECLOG_ON_ERROR(setError(); return);

			increaseNestingLevel();
		}

		void Renderer::beginArray(ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			beginItem(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderLeftSquareBracket(ec);
			ECLOG_ON_ERROR(setError(); return);

			beginStruct(ec);
			ECLOG_ON_ERROR(setError(); return);

			increaseNestingLevel();
		}

		void Renderer::endArray(ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			decreaseNestingLevel();

			endStruct(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderRightSquareBracket(ec);
			ECLOG_ON_ERROR(setError(); return);

			endItem();
		}

		void Renderer::renderMember(const KeyDesc& key, const ValueDesc& value, ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			if (value.type() == value_type_object)
			{
				beginObject(key, ec);
				ECLOG_ON_ERROR(setError(); return);

				for (size_t i = 0; i < value.objectSize(); ++i)
				{
					renderMember(value.object()[i].first, value.object()[i].second, ec);
					ECLOG_ON_ERROR(setError(); return);
				}

				endObject(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
			else if (value.type() == value_type_array)
			{
				beginArray(key, ec);
				ECLOG_ON_ERROR(setError(); return);

				for (size_t i = 0; i < value.arraySize(); ++i)
				{
					renderMember(value.array()[i], ec);
					ECLOG_ON_ERROR(setError(); return);
				}

				endArray(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
			else
			{
				beginItem(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderString(key.str(), key.notation(), key.delimiter(), ec);
				ECLOG_ON_ERROR(setError(); return);

				renderColon(ec);
				ECLOG_ON_ERROR(setError(); return);

				if (rc_.formatting == RendererConfig::formatting_regular && rc_.insertSpaceAfterColon)
				{
					renderSpace(ec);
					ECLOG_ON_ERROR(setError(); return);
				}

				renderValueInternal(value, ec);
				ECLOG_ON_ERROR(setError(); return);

				endItem();
			}
		}

		void Renderer::renderMember(const ValueDesc& value, ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			if (value.type() == value_type_object)
			{
				beginObject(ec);
				ECLOG_ON_ERROR(setError(); return);

				for (size_t i = 0; i < value.objectSize(); ++i)
				{
					renderMember(value.object()[i].first, value.object()[i].second, ec);
					ECLOG_ON_ERROR(setError(); return);
				}

				endObject(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
			else if (value.type() == value_type_array)
			{
				beginArray(ec);
				ECLOG_ON_ERROR(setError(); return);

				for (size_t i = 0; i < value.arraySize(); ++i)
				{
					renderMember(value.array()[i], ec);
					ECLOG_ON_ERROR(setError(); return);
				}

				endArray(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
			else
			{
				beginItem(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderValueInternal(value, ec);
				ECLOG_ON_ERROR(setError(); return);

				endItem();
			}
		}

		void Renderer::renderEmptyLines(int count, ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			if (rc_.formatting == RendererConfig::formatting_compact || inline_) {
				return;
			}

			ECLOG_ASSERT(!separator_ || separator_ == separator_linebreak);
			renderSeparator(ec);
			ECLOG_ON_ERROR(setError(); return);

			for (int i = 0; i < count; ++i)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
		}

		void Renderer::renderComment(cstring comment, ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			if (rc_.formatting == RendererConfig::formatting_compact || inline_ || !rc_.enableComments) {
				return;
			}

			ECLOG_ASSERT(!separator_ || separator_ == separator_linebreak);
			renderSeparator(ec);
			ECLOG_ON_ERROR(setError(); return);

			MemoryInputStream stream(comment.data(), comment.size());
			UTF8Decoder decoder(stream);

			bool linebreak = false;
			bool beginOfLine = true;

			renderIndent(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderChar('#', ec);
			ECLOG_ON_ERROR(setError(); return);

			for (;;)
			{
				int ch = decoder.getChar(ec);
				ECLOG_ON_ERROR(setError(); return);

				if (ch < 0) {
					break;
				}

				if (ch == '\r')
				{
					ch = decoder.peekChar(ec);
					ECLOG_ON_ERROR(setError(); return);

					if (ch == '\n') {
						decoder.getChar(0);
					}

					linebreak = true;
				}
				else if (ch == '\n')
				{
					linebreak = true;
				}

				if (linebreak)
				{
					renderLinebreak(ec);
					ECLOG_ON_ERROR(setError(); return);

					renderIndent(ec);
					ECLOG_ON_ERROR(setError(); return);

					renderChar('#', ec);
					ECLOG_ON_ERROR(setError(); return);

					linebreak = false;
					beginOfLine = true;

					continue;
				}

				if (beginOfLine)
				{
					renderSpace(ec);
					ECLOG_ON_ERROR(setError(); return);

					beginOfLine = false;
				}

				renderChar(ch, ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			renderLinebreak(ec);
			ECLOG_ON_ERROR(setError(); return);
		}

		int Renderer::beginInline()
		{
			return ++inline_;
		}

		int Renderer::endInline()
		{
			if (--inline_ == 0)
			{
				if (separator_ == separator_comma)
				{
					if (rc_.formatting == RendererConfig::formatting_regular)
					{
						separator_ = separator_linebreak;
					}
				}
			}

			return inline_;
		}

		void Renderer::close(ErrorCode* ec)
		{
			if (error()) {
				ECLOG_ERROR(IOError);
			}

			if (separator_)
			{
				if (separator_ == separator_linebreak)
				{
					renderLinebreak(ec);
					ECLOG_ON_ERROR(setError(); return);
				}

				separator_ = 0;
			}
		}

		const RendererConfig& Renderer::rendererConfig() const
		{
			return rc_;
		}

		void Renderer::beginItem(ErrorCode* ec)
		{
			renderSeparator(ec);
			ECLOG_ON_ERROR(return);

			if (beginOfLine_)
			{
				renderIndent(ec);
				ECLOG_ON_ERROR(return);
			}
		}

		void Renderer::endItem()
		{
			if (rc_.formatting == RendererConfig::formatting_regular && !inline_)
			{
				if (!beginOfLine_)
				{
					separator_ = separator_linebreak;
				}
			}
			else
			{
				separator_ = separator_comma;
			}
		}

		void Renderer::beginStruct(ErrorCode* ec)
		{
			if (rc_.formatting == RendererConfig::formatting_regular && !inline_)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(return);
			}

			increaseIndent();
		}

		void Renderer::endStruct(ErrorCode* ec)
		{
			decreaseIndent();

			if (rc_.formatting == RendererConfig::formatting_regular && !inline_)
			{
				if (!beginOfLine_)
				{
					renderLinebreak(ec);
					ECLOG_ON_ERROR(return);
				}

				if (beginOfLine_)
				{
					renderIndent(ec);
					ECLOG_ON_ERROR(return);
				}
			}
		}

		void Renderer::renderValueInternal(const ValueDesc& value, ErrorCode* ec)
		{
			switch (value.type())
			{
			case value_type_null:
				renderSequence("null", ec);
				return;

			case value_type_boolean:
				if (value.boolean()) {
					renderSequence("true", ec);
				}
				else {
					renderSequence("false", ec);
				}
				return;

			case value_type_string:
				renderString(value.string(), value.stringNotation(), value.stringDelimiter(), ec);
				return;

			case value_type_number:
				renderNumber(value.number(), value.fracDigits(), ec);
				return;

			default:
				ECLOG_ASSERT(false);
				return;
			}
		}

		void Renderer::renderString(cstring str, StringNotation notation, cstring delimiter, ErrorCode* ec)
		{
			if (notation == string_notation_quoted || rc_.useQuotedStringsOnly)
			{
				renderQuotedString(str, ec);
				return;
			}
			else if (notation == string_notation_unquoted)
			{
				if (str == "null" || str == "true" || str == "false" || str == "inf" || str == "nan")
				{
					renderQuotedString(str, ec);
					return;
				}

				size_t count = 0;

				for (const char* s = str.begin(); s != str.end(); ++s)
				{
					if (isAlpha(*s) || *s == '_' || (count && (*s == '-' || *s == '.' || isDigit(*s)))) {
						++count;
					}
					else {
						break;
					}
				}

				if (!str.empty() && count == str.size())
				{
					renderUnquotedString(str, ec);
					return;
				}
			}
			else if (notation == string_notation_raw)
			{
				bool good = true;

				for (const char* s = str.begin(); s != str.end(); ++s)
				{
					if (*s >= 0 && *s < 0x20 && *s != '\t')
					{
						good = false;
						break;
					}
					else if (*s == '\"')
					{
						if (delimiter.empty() || cstring(s + 1, str.end()).startsWith(delimiter))
						{
							good = false;
							break;
						}
					}
				}

				if (good)
				{
					renderRawString(str, delimiter, ec);
					return;
				}
			}
			else if (notation == string_notation_heredoc)
			{
				if (rc_.formatting == RendererConfig::formatting_compact || inline_ || delimiter.empty())
				{
					renderQuotedString(str, ec);
					return;
				}

				bool good = true;

				bool beginOfLine = true;

				const char* s = str.begin();

				while (s != str.end())
				{
					if (beginOfLine && (*s == ' ' || *s == '\t'))
					{
						++s;
					}
					else if (beginOfLine && cstring(s, str.end()).startsWith(delimiter))
					{
						s += delimiter.size();

						if (s == str.end() || *s == '\r' || *s == '\n')
						{
							good = false;
							break;
						}
					}
					else if (*s == '\r')
					{
						++s;

						if (s != str.end() && *s == '\n') {
							++s;
						}

						beginOfLine = true;
					}
					else if (*s == '\n')
					{
						++s;
						beginOfLine = true;
					}
					else if (*s >= 0 && *s < 0x20 && *s != '\t')
					{
						good = false;
						break;
					}
					else
					{
						++s;
						beginOfLine = false;
					}
				}

				if (good)
				{
					renderHeredoc(str, delimiter, ec);
					return;
				}
			}

			renderQuotedString(str, ec);
		}

		void Renderer::renderQuotedString(cstring str, ErrorCode* ec)
		{
			MemoryInputStream stream(str.data(), str.size());
			UTF8Decoder decoder(stream);

			renderChar('"', ec);
			ECLOG_ON_ERROR(return);

			for (;;)
			{
				int ch = decoder.getChar(ec);
				ECLOG_ON_ERROR(return);

				if (ch < 0) {
					break;
				}

				switch (ch)
				{
				case '"':
					renderSequence("\\\"", ec);
					ECLOG_ON_ERROR(return);
					break;

				case '\\':
					renderSequence("\\\\", ec);
					ECLOG_ON_ERROR(return);
					break;

				case '\b':
					renderSequence("\\b", ec);
					ECLOG_ON_ERROR(return);
					break;

				case '\f':
					renderSequence("\\f", ec);
					ECLOG_ON_ERROR(return);
					break;

				case '\n':
					renderSequence("\\n", ec);
					ECLOG_ON_ERROR(return);
					break;

				case '\r':
					renderSequence("\\r", ec);
					ECLOG_ON_ERROR(return);
					break;

				case '\t':
					renderSequence("\\t", ec);
					ECLOG_ON_ERROR(return);
					break;

				default:
					if (ch < 0x20)
					{
						const char table[] = { '0', '1', '2', '3', '4', '5',
							'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

						char buffer[6];

						buffer[0] = '\\';
						buffer[1] = 'u';
						buffer[2] = '0';
						buffer[3] = '0';
						buffer[4] = table[(ch >> 4) & 0xf];
						buffer[5] = table[ch & 0xf];

						renderSequence(cstring(buffer, sizeof(buffer)), ec);
						ECLOG_ON_ERROR(return);
					}
					else
					{
						renderChar(ch, ec);
						ECLOG_ON_ERROR(return);
					}
				}
			}

			renderChar('"', ec);
			ECLOG_ON_ERROR(return);
		}

		void Renderer::renderUnquotedString(cstring str, ErrorCode* ec)
		{
			renderSequence(str, ec);
			ECLOG_ON_ERROR(return);
		}

		void Renderer::renderRawString(cstring str, cstring delimiter, ErrorCode* ec)
		{
			MemoryInputStream stream(str.data(), str.size());
			UTF8Decoder decoder(stream);

			renderChar('@', ec);
			ECLOG_ON_ERROR(return);

			for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
			{
				renderChar(*d, ec);
				ECLOG_ON_ERROR(return);
			}

			renderChar('"', ec);
			ECLOG_ON_ERROR(return);

			for (;;)
			{
				int ch = decoder.getChar(ec);
				ECLOG_ON_ERROR(return);

				if (ch < 0) {
					break;
				}

				renderChar(ch, ec);
				ECLOG_ON_ERROR(return);
			}

			renderChar('"', ec);
			ECLOG_ON_ERROR(return);

			for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
			{
				renderChar(*d, ec);
				ECLOG_ON_ERROR(return);
			}
		}

		void Renderer::renderHeredoc(cstring str, cstring delimiter, ErrorCode* ec)
		{
			MemoryInputStream stream(str.data(), str.size());
			UTF8Decoder decoder(stream);

			renderChar('|', ec);
			ECLOG_ON_ERROR(return);

			for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
			{
				renderChar(*d, ec);
				ECLOG_ON_ERROR(return);
			}

			renderLinebreak(ec);
			ECLOG_ON_ERROR(return);

			bool linebreak = true;

			increaseIndent();

			for (;;)
			{
				int ch = decoder.peekChar(ec);
				ECLOG_ON_ERROR(return);

				if (ch < 0) {
					break;
				}

				if (ch == '\r')
				{
					decoder.getChar(0);

					ch = decoder.peekChar(ec);
					ECLOG_ON_ERROR(return);

					if (ch == '\n') {
						decoder.getChar(0);
					}

					renderLinebreak(ec);
					ECLOG_ON_ERROR(return);

					linebreak = true;
				}
				else if (ch == '\n')
				{
					decoder.getChar(0);

					renderLinebreak(ec);
					ECLOG_ON_ERROR(return);

					linebreak = true;
				}
				else
				{
					decoder.getChar(0);

					if (beginOfLine_)
					{
						renderIndent(ec);
						ECLOG_ON_ERROR(return);
					}

					renderChar(ch, ec);
					ECLOG_ON_ERROR(return);

					linebreak = false;
				}
			}

			if (!linebreak)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(return);
			}

			renderIndent(ec);
			ECLOG_ON_ERROR(return);

			for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
			{
				renderChar(*d, ec);
				ECLOG_ON_ERROR(return);
			}

			renderLinebreak(ec);
			ECLOG_ON_ERROR(return);

			decreaseIndent();
		}

		void Renderer::renderNumber(const Number& number, int fracDigits, ErrorCode* ec)
		{
			char buffer[ECLOG_NUMBER_BUFFER_SIZE];

			switch (number.underlyingType())
			{
			case Number::underlying_type_double:
				doubleToString(number.load<double>(), buffer, fracDigits);
				break;

			case Number::underlying_type_int:
				integerToString(number.load<int>(), buffer);
				break;

			case Number::underlying_type_uint:
				integerToString(number.load<unsigned int>(), buffer);
				break;

			case Number::underlying_type_long:
				integerToString(number.load<long>(), buffer);
				break;

			case Number::underlying_type_ulong:
				integerToString(number.load<unsigned long>(), buffer);
				break;

			case Number::underlying_type_llong:
				integerToString(number.load<long long>(), buffer);
				break;

			case Number::underlying_type_ullong:
				integerToString(number.load<unsigned long long>(), buffer);
				break;

			default:
				ECLOG_ASSERT(false);
				break;
			}

			cstring s = buffer;

			if (number.underlyingType() == Number::underlying_type_double &&
				rc_.useStringsToRepresentInfinitiesAndNaNs &&
				(s.endsWith("inf") || s.endsWith("nan")))
			{
				renderString(s, string_notation_quoted, "", ec);
			}
			else
			{
				renderSequence(s, ec);
			}
		}

		void Renderer::renderLinebreak(ErrorCode* ec)
		{
			switch (rc_.linebreak)
			{
			case CR:
				encoder_.putChar('\r', ec);
				ECLOG_ON_ERROR(return);
				break;

			case LF:
				encoder_.putChar('\n', ec);
				ECLOG_ON_ERROR(return);
				break;

			case CRLF:
				encoder_.putChar('\r', ec);
				ECLOG_ON_ERROR(return);

				encoder_.putChar('\n', ec);
				ECLOG_ON_ERROR(return);
				break;
			}

			beginOfLine_ = true;
		}

		void Renderer::renderIndent(ErrorCode* ec)
		{
			char ch = rc_.indentCharacter == RendererConfig::indent_character_tab ? '\t' : ' ';

			for (int i = 0; i < indent(); ++i)
			{
				for (int j = 0; j < rc_.indentSize; ++j)
				{
					renderChar(ch, ec);
					ECLOG_ON_ERROR(return);
				}
			}
		}

		void Renderer::renderSeparator(ErrorCode* ec)
		{
			if (separator_ == separator_linebreak)
			{
				if (rc_.useCommasToSeparateItems)
				{
					renderComma(ec);
					ECLOG_ON_ERROR(return);
				}

				renderLinebreak(ec);
				ECLOG_ON_ERROR(return);

				separator_ = 0;
			}
			else if (separator_ == separator_comma)
			{
				renderComma(ec);
				ECLOG_ON_ERROR(return);

				if (rc_.formatting == RendererConfig::formatting_regular)
				{
					renderSpace(ec);
					ECLOG_ON_ERROR(return);
				}

				separator_ = 0;
			}
		}

		void Renderer::renderSpace(ErrorCode* ec)
		{
			renderChar(' ', ec);
		}

		void Renderer::renderLeftCurlyBracket(ErrorCode* ec)
		{
			renderChar('{', ec);
		}

		void Renderer::renderRightCurlyBracket(ErrorCode* ec)
		{
			renderChar('}', ec);
		}

		void Renderer::renderLeftSquareBracket(ErrorCode* ec)
		{
			renderChar('[', ec);
		}

		void Renderer::renderRightSquareBracket(ErrorCode* ec)
		{
			renderChar(']', ec);
		}

		void Renderer::renderColon(ErrorCode* ec)
		{
			renderChar(':', ec);
		}

		void Renderer::renderComma(ErrorCode* ec)
		{
			renderChar(',', ec);
		}

		void Renderer::renderSequence(cstring s, ErrorCode* ec)
		{
			for (const char* p = s.begin(); p != s.end(); ++p)
			{
				renderChar(*p, ec);
				ECLOG_ON_ERROR(return);
			}
		}

		void Renderer::renderChar(int ch, ErrorCode* ec)
		{
			encoder_.putChar(ch, ec);
			ECLOG_ON_ERROR(return);

			beginOfLine_ = false;
		}

		void Renderer::increaseNestingLevel()
		{
			++nestingLevel_;
		}

		void Renderer::decreaseNestingLevel()
		{
			--nestingLevel_;
		}

		int Renderer::nestingLevel() const
		{
			return nestingLevel_;
		}

		void Renderer::increaseIndent()
		{
			++indent_;
		}

		void Renderer::decreaseIndent()
		{
			--indent_;
		}

		int Renderer::indent() const
		{
			return indent_;
		}

		void Renderer::setError(int error)
		{
			error_ = error;
		}

		int Renderer::error() const
		{
			return error_;
		}

	} // detail

} // eclog


