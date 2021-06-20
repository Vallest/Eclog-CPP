// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NUMBER_H_
#define ECLOG_CPP_NUMBER_H_

#include <Eclog/Detail/Binary64.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/Assert.h>

#include <ostream>

namespace vallest {
namespace eclog {

	class Number {
	public:
		enum UnderlyingType {
			underlying_type_double,
			underlying_type_int,
			underlying_type_uint,
			underlying_type_long,
			underlying_type_ulong,
			underlying_type_llong,
			underlying_type_ullong,
		};

	public:
		Number() : underlyingType_(underlying_type_double), double_(0)
		{
		}

		Number(double value) : underlyingType_(underlying_type_double), double_(value)
		{
		}

		Number(int value) : underlyingType_(underlying_type_int), int_(value)
		{
		}

		Number(long value) : underlyingType_(underlying_type_long), long_(value)
		{
		}

		Number(long long value) : underlyingType_(underlying_type_llong), llong_(value)
		{
		}

		Number(unsigned int value) : underlyingType_(underlying_type_uint), uint_(value)
		{
		}

		Number(unsigned long value) : underlyingType_(underlying_type_ulong), ulong_(value)
		{
		}

		Number(unsigned long long value) : underlyingType_(underlying_type_ullong), ullong_(value)
		{
		}

		UnderlyingType underlyingType() const
		{
			return underlyingType_;
		}

		int sign() const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return detail::Binary64(double_).sign();

			case underlying_type_int:
				return int_ < 0 ? -1 : 1;

			case underlying_type_long:
				return long_ < 0 ? -1 : 1;

			case underlying_type_llong:
				return llong_ < 0 ? -1 : 1;

			default:
				return 1;
			}
		}

		bool isSubnormal() const
		{
			return (underlyingType_ == underlying_type_double && detail::Binary64(double_).isSubnormal());
		}

		bool isInfinity() const
		{
			return (underlyingType_ == underlying_type_double && detail::Binary64(double_).isInfinity());
		}

		bool isNan() const
		{
			return (underlyingType_ == underlying_type_double && detail::Binary64(double_).isNan());
		}

		Number& operator=(double value)
		{
			store(value);
			return *this;
		}

		Number& operator=(int value)
		{
			store(value);
			return *this;
		}

		Number& operator=(long value)
		{
			store(value);
			return *this;
		}

		Number& operator=(long long value)
		{
			store(value);
			return *this;
		}

		Number& operator=(unsigned int value)
		{
			store(value);
			return *this;
		}

		Number& operator=(unsigned long value)
		{
			store(value);
			return *this;
		}

		Number& operator=(unsigned long long value)
		{
			store(value);
			return *this;
		}

		template<typename T>
		T load() const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return (T)double_;

			case underlying_type_int:
				return (T)int_;

			case underlying_type_uint:
				return (T)uint_;

			case underlying_type_long:
				return (T)long_;

			case underlying_type_ulong:
				return (T)ulong_;

			case underlying_type_llong:
				return (T)llong_;

			case underlying_type_ullong:
				return (T)ullong_;

			default:
				ECLOG_ASSERT(false);
				return 0;
			}
		}

		void store(double value)
		{
			underlyingType_ = underlying_type_double;
			double_ = value;
		}

		void store(int value)
		{
			underlyingType_ = underlying_type_int;
			int_ = value;
		}

		void store(long value)
		{
			underlyingType_ = underlying_type_long;
			long_ = value;
		}

		void store(long long value)
		{
			underlyingType_ = underlying_type_llong;
			llong_ = value;
		}

		void store(unsigned int value)
		{
			underlyingType_ = underlying_type_uint;
			uint_ = value;
		}

		void store(unsigned long value)
		{
			underlyingType_ = underlying_type_ulong;
			ulong_ = value;
		}

		void store(unsigned long long value)
		{
			underlyingType_ = underlying_type_ullong;
			ullong_ = value;
		}

		bool operator==(const Number& other) const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return other.equalTo(double_);

			case underlying_type_int:
				return other.equalTo(int_);

			case underlying_type_uint:
				return other.equalTo(uint_);

			case underlying_type_long:
				return other.equalTo(long_);

			case underlying_type_ulong:
				return other.equalTo(ulong_);

			case underlying_type_llong:
				return other.equalTo(llong_);

			case underlying_type_ullong:
				return other.equalTo(ullong_);

			default:
				ECLOG_ASSERT(false);
				return false;
			}
		}

		bool operator!=(const Number& other) const
		{
			return !(*this == other);
		}

		bool operator<(const Number& other) const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return other.greaterThan(double_);

			case underlying_type_int:
				return other.greaterThan(int_);

			case underlying_type_uint:
				return other.greaterThan(uint_);

			case underlying_type_long:
				return other.greaterThan(long_);

			case underlying_type_ulong:
				return other.greaterThan(ulong_);

			case underlying_type_llong:
				return other.greaterThan(llong_);

			case underlying_type_ullong:
				return other.greaterThan(ullong_);

			default:
				ECLOG_ASSERT(false);
				return false;
			}
		}

		bool operator>(const Number& other) const
		{
			return other < *this;
		}

		bool operator<=(const Number& other) const
		{
			return !(*this > other);
		}

		bool operator>=(const Number& other) const
		{
			return !(*this < other);
		}

		int compare(const Number& other) const
		{
			if (*this < other) {
				return -1;
			}
			else if (*this > other) {
				return 1;
			}
			else {
				return 0;
			}
		}

	public:
		static Number infinity()
		{
			return detail::Binary64::infinity();
		}

		static Number negInfinity()
		{
			return detail::Binary64::negInfinity();
		}

		static Number nan()
		{
			return detail::Binary64::nan();
		}

		static Number negNan()
		{
			return detail::Binary64::negNan();
		}

	private:
		template<typename T>
		bool equalTo(T value) const
		{
			ECLOG_WARNING_PUSH
			ECLOG_WARNING_IGNORE_SIGN_COMPARE

			switch (underlyingType_)
			{
			case underlying_type_double:
				return double_ == value;

			case underlying_type_int:
				return int_ == value;

			case underlying_type_uint:
				return uint_ == value;

			case underlying_type_long:
				return long_ == value;

			case underlying_type_ulong:
				return ulong_ == value;

			case underlying_type_llong:
				return llong_ == value;

			case underlying_type_ullong:
				return ullong_ == value;

			default:
				ECLOG_ASSERT(false);
				return false;
			}

			ECLOG_WARNING_POP
		}

		template<typename T>
		bool greaterThan(T value) const
		{
			ECLOG_WARNING_PUSH
			ECLOG_WARNING_IGNORE_SIGN_COMPARE

			switch (underlyingType_)
			{
			case underlying_type_double:
				return double_ > value;

			case underlying_type_int:
				return int_ > value;

			case underlying_type_uint:
				return uint_ > value;

			case underlying_type_long:
				return long_ > value;

			case underlying_type_ulong:
				return ulong_ > value;

			case underlying_type_llong:
				return llong_ > value;

			case underlying_type_ullong:
				return ullong_ > value;

			default:
				ECLOG_ASSERT(false);
				return false;
			}

			ECLOG_WARNING_POP
		}

	private:
		UnderlyingType underlyingType_;

		union {
			double double_;
			int int_;
			long long_;
			long long llong_;
			unsigned int uint_;
			unsigned long ulong_;
			unsigned long long ullong_;
		};
	};

#define ECLOG_DEFINE_NUMBER_OPERATORS(Type)					\
	inline bool operator==(Type a, const Number& b)			\
	{														\
		return b == a;										\
	}														\
	inline bool operator!=(Type a, const Number& b)			\
	{														\
		return !(a == b);									\
	}														\
	inline bool operator<(Type a, const Number& b)			\
	{														\
		return b > a;										\
	}														\
	inline bool operator>(Type a, const Number& b)			\
	{														\
		return b < a;										\
	}														\
	inline bool operator<=(Type a, const Number& b)			\
	{														\
		return !(a > b);									\
	}														\
	inline bool operator>=(Type a, const Number& b)			\
	{														\
		return !(a < b);									\
	}

	ECLOG_DEFINE_NUMBER_OPERATORS(double)
	ECLOG_DEFINE_NUMBER_OPERATORS(int)
	ECLOG_DEFINE_NUMBER_OPERATORS(unsigned int)
	ECLOG_DEFINE_NUMBER_OPERATORS(long)
	ECLOG_DEFINE_NUMBER_OPERATORS(unsigned long)
	ECLOG_DEFINE_NUMBER_OPERATORS(long long)
	ECLOG_DEFINE_NUMBER_OPERATORS(unsigned long long)

#undef ECLOG_DEFINE_NUMBER_OPERATORS

	inline std::ostream& operator<<(std::ostream& stream, const Number& n)
	{
		switch (n.underlyingType())
		{
		case Number::underlying_type_double:
			stream << n.load<double>();
			break;

		case Number::underlying_type_int:
			stream << n.load<int>();
			break;

		case Number::underlying_type_uint:
			stream << n.load<unsigned int>();
			break;

		case Number::underlying_type_long:
			stream << n.load<long>();
			break;

		case Number::underlying_type_ulong:
			stream << n.load<unsigned long>();
			break;

		case Number::underlying_type_llong:
			stream << n.load<long long>();
			break;

		case Number::underlying_type_ullong:
			stream << n.load<unsigned long long>();
			break;

		default:
			ECLOG_ASSERT(false);
		}

		return stream;
	}

} // eclog
} // vallest

#endif // ECLOG_CPP_NUMBER_H_

