// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_VALUE_H_
#define ECLOG_CPP_VALUE_H_

#include <Eclog/Null.h>
#include <Eclog/ValueType.h>
#include <Eclog/NumberInfo.h>
#include <Eclog/Number.h>
#include <Eclog/StringNotation.h>
#include <Eclog/cstring.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/IntegerConversion.h>
#include <Eclog/Detail/DoubleConversion.h>
#include <Eclog/Detail/TypeTraits.h>
#include <Eclog/Detail/Limits.h>
#include <Eclog/Detail/Assert.h>

#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable: 4127)
#endif

namespace eclog {

	class Value {
	public:
		explicit Value(ValueType type) : type_(type)
		{
			ECLOG_ASSERT(type == value_type_object || type == value_type_array);
		}

		explicit Value(ValueType type, cstring bytes) :
			type_(type), bytes_(bytes)
		{
			ECLOG_ASSERT(type == value_type_null || type == value_type_boolean);
		}

		explicit Value(ValueType type, cstring bytes, NumberInfo numberInfo) :
			type_(type), bytes_(bytes)
		{
			ECLOG_ASSERT(type == value_type_number);

			numberInfo_ = numberInfo;
		}

		explicit Value(ValueType type, cstring bytes, StringNotation notation, size_t delimiterSize) :
			type_(type), bytes_(bytes.begin() + delimiterSize, bytes.end())
		{
			ECLOG_ASSERT(type == value_type_string);

			str_.notation = notation;
			str_.dbegin = bytes.begin();
			str_.dend = bytes.begin() + delimiterSize;
		}

		ValueType type() const
		{
			return type_;
		}

		bool isNull() const
		{
			return (type_ == value_type_null);
		}

		bool isBoolean() const
		{
			return (type_ == value_type_boolean);
		}

		bool isString() const
		{
			return (type_ == value_type_string);
		}

		bool isNumber() const
		{
			return (type_ == value_type_number);
		}

		bool isObject() const
		{
			return (type_ == value_type_object);
		}

		bool isArray() const
		{
			return (type_ == value_type_array);
		}

		Null asNull() const
		{
			if (type_ != value_type_null) {
				ECLOG_FAULT(BadCast);
			}

			return null;
		}

		bool asBoolean() const
		{
			if (type_ != value_type_boolean) {
				ECLOG_FAULT(BadCast);
			}

			return (bytes_[0] == 't');
		}

		cstring asString() const
		{
			if (type_ != value_type_string) {
				ECLOG_FAULT(BadCast);
			}

			return bytes_;
		}

		Number asNumber() const
		{
			if (type_ != value_type_number) {
				ECLOG_FAULT(BadCast);
			}

			if (numberInfo_ & (number_info_has_frac | number_info_has_exp | number_info_inf | number_info_nan))
			{
				return detail::stringToDouble(bytes_.data());
			}
			else
			{
				int error;

				long long n = detail::stringToSignedInteger<long long>(bytes_.data(), 0, &error);

				if (error == 0)
				{
					if (n >= detail::minValue<int>() && n <= detail::maxValue<int>()) {
						return (int)n;
					}
					else if (n >= detail::minValue<long>() && n <= detail::maxValue<long>()) {
						return (long)n;
					}
					else {
						return n;
					}
				}

				if (numberInfo_ & number_info_has_neg_sign)
				{
					return detail::stringToDouble(bytes_.data());
				}

				unsigned long long m = detail::stringToUnsignedInteger<unsigned long long>(bytes_.data(), 0, &error);

				if (error == 0)
				{
					if (m <= detail::maxValue<unsigned int>()) {
						return (unsigned int)m;
					}
					else if (m <= detail::maxValue<unsigned long>()) {
						return (unsigned long)m;
					}
					else {
						return m;
					}
				}

				return detail::stringToDouble(bytes_.data());
			}
		}

		cstring bytes() const
		{
			return bytes_;
		}

		int numberInfo() const
		{
			return numberInfo_;
		}

		StringNotation stringNotation() const
		{
			return str_.notation;
		}

		cstring stringDelimiter() const
		{
			return cstring(str_.dbegin, str_.dend);
		}

	private:
		ValueType type_;

		cstring bytes_;

		union
		{
			int numberInfo_;

			struct
			{
				const char* dbegin;
				const char* dend;

				StringNotation notation;
			}
			str_;
		};
	};

} // eclog

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

#endif // ECLOG_CPP_VALUE_H_

