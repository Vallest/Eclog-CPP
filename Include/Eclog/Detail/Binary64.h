// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_BINARY64_H_
#define ECLOG_CPP_DETAIL_BINARY64_H_

#include <Eclog/IntTypes.h>

#include <string.h> // memcpy

namespace vallest {
namespace eclog {
namespace detail {

	class Binary64 {
	public:
		static const uint64_t sign_mask = ECLOG_MAKE64(0x80000000, 0x00000000);
		static const uint64_t exponent_mask = ECLOG_MAKE64(0x7ff00000, 0x00000000);
		static const uint64_t significand_mask = ECLOG_MAKE64(0x000fffff, 0xffffffff);
		static const uint64_t hidden_bit = ECLOG_MAKE64(0x00100000, 0x00000000);
		static const int physical_significand_size = 52;
		static const int significand_size = 53;

	private:
		static const int exponent_bias = 0x3ff + physical_significand_size;
		static const int subnormal_exponent = -exponent_bias + 1;
		static const int max_exponent = 0x7ff - exponent_bias;
		static const uint64_t infinity_value = ECLOG_MAKE64(0x7ff00000, 0x00000000);
		static const uint64_t nan_value = ECLOG_MAKE64(0x7ff00000, 0x00000001);

	public:
		Binary64(double d)
		{
			assign(d);
		}

		Binary64(uint64_t d64) : d64_(d64)
		{
		}

		void assign(double d)
		{
			memcpy(&d64_, &d, sizeof(uint64_t));
		}

		double value() const
		{
			double val;
			memcpy(&val, &d64_, sizeof(uint64_t));

			return val;
		}

		double previousValue() const
		{
			if (d64_ == (infinity_value | sign_mask)) {
				return value();
			}

			if (sign() < 0) {
				return Binary64(d64_ + 1).value();
			}
			else if (significand() == 0) {
				return -0.0;
			}
			else {
				return Binary64(d64_ - 1).value();
			}
		}

		double nextValue() const
		{
			if (d64_ == infinity_value) {
				return value();
			}

			if (sign() < 0 && significand() == 0) {
				return 0.0;
			}

			if (sign() < 0) {
				return Binary64(d64_ - 1).value();
			}
			else {
				return Binary64(d64_ + 1).value();
			}
		}

		int sign() const
		{
			return ((d64_ & sign_mask) == 0 ? 1 : -1);
		}

		bool isSubnormal() const
		{
			return ((d64_ & exponent_mask) == 0);
		}

		bool isInfinity() const
		{
			return ((d64_ & exponent_mask) == exponent_mask) && ((d64_ & significand_mask) == 0);
		}

		bool isNan() const
		{
			return ((d64_ & exponent_mask) == exponent_mask) && ((d64_ & significand_mask) != 0);
		}

		bool lowerBoundaryIsCloser() const
		{
			return ((d64_ & significand_mask) == 0 && exponent() != subnormal_exponent);
		}

		int exponent() const
		{
			if (isSubnormal()) {
				return subnormal_exponent;
			}
			else {
				return (int)((d64_ & exponent_mask) >> physical_significand_size) - exponent_bias;
			}
		}

		uint64_t significand() const
		{
			if (isSubnormal()) {
				return (d64_ & significand_mask);
			}
			else {
				return ((d64_ & significand_mask) | hidden_bit);
			}
		}

		static double infinity()
		{
			return Binary64(infinity_value).value();
		}

		static double negInfinity()
		{
			return Binary64(sign_mask | infinity_value).value();
		}

		static double nan()
		{
			return Binary64(nan_value).value();
		}

		static double negNan()
		{
			return Binary64(sign_mask | nan_value).value();
		}

	private:
		uint64_t d64_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_BINARY64_H_

