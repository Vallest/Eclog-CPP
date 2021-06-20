// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_VALUEDESC_H_
#define ECLOG_CPP_VALUEDESC_H_

#include <Eclog/KeyDesc.h>
#include <Eclog/ValueType.h>
#include <Eclog/Null.h>
#include <Eclog/Number.h>
#include <Eclog/EmptyObjectTag.h>
#include <Eclog/EmptyArrayTag.h>
#include <Eclog/Error.h>
#include <Eclog/Utility.h>
#include <Eclog/Detail/StringDelimiter.h>
#include <Eclog/Detail/Assert.h>

namespace vallest {
namespace eclog {

	class ValueDesc {
	public:
		ValueDesc(Null) : type_(value_type_null)
		{
		}

		ValueDesc(bool value) : type_(value_type_boolean), bool_(value)
		{
		}

		ValueDesc(const char* value) : type_(value_type_string)
		{
			cstring string(value);

			str_.begin = string.begin();
			str_.end = string.end();
			str_.dbegin = 0;
			str_.dend = 0;
			str_.notation = string_notation_unquoted;
		}

		ValueDesc(cstring value, StringNotation notation = string_notation_unquoted, cstring delimiter = cstring()) : type_(value_type_string)
		{
			if (!detail::StringDelimiter::validate(delimiter)) {
				ECLOG_FAULT(InvalidArgument);
			}

			str_.begin = value.begin();
			str_.end = value.end();
			str_.dbegin = delimiter.begin();
			str_.dend = delimiter.end();
			str_.notation = notation;
		}

		ValueDesc(const Number& value, int fracDigits = -1) : type_(value_type_number)
		{
			number_.underlyingType = value.underlyingType();

			switch (value.underlyingType())
			{
			case Number::underlying_type_double:
				number_.d = value.load<double>();
				break;

			case Number::underlying_type_int:
				number_.i = value.load<int>();
				break;

			case Number::underlying_type_uint:
				number_.ui = value.load<unsigned int>();
				break;

			case Number::underlying_type_long:
				number_.l = value.load<long>();
				break;

			case Number::underlying_type_ulong:
				number_.ul = value.load<unsigned long>();
				break;

			case Number::underlying_type_llong:
				number_.ll = value.load<long long>();
				break;

			case Number::underlying_type_ullong:
				number_.ull = value.load<unsigned long long>();
				break;

			default:
				ECLOG_ASSERT(false);
			}

			number_.fracDigits = fracDigits;
		}

		ValueDesc(double value, int fracDigits = -1) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_double;
			number_.d = value;
			number_.fracDigits = fracDigits;
		}

		ValueDesc(int value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_int;
			number_.i = value;
			number_.fracDigits = -1;
		}

		ValueDesc(long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_long;
			number_.l = value;
			number_.fracDigits = -1;
		}

		ValueDesc(long long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_llong;
			number_.ll = value;
			number_.fracDigits = -1;
		}

		ValueDesc(unsigned int value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_uint;
			number_.ui = value;
			number_.fracDigits = -1;
		}

		ValueDesc(unsigned long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_ulong;
			number_.ul = value;
			number_.fracDigits = -1;
		}

		ValueDesc(unsigned long long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_ullong;
			number_.ull = value;
			number_.fracDigits = -1;
		}

		ValueDesc(EmptyObjectTag) : type_(value_type_object)
		{
			object_.p = 0;
			object_.size = 0;
		}

		ValueDesc(const Pair<KeyDesc, ValueDesc>* p, size_t size) : type_(value_type_object)
		{
			object_.p = p;
			object_.size = size;
		}

		template<size_t N>
		ValueDesc(const Pair<KeyDesc, ValueDesc>(&v)[N]) : type_(value_type_object)
		{
			object_.p = v;
			object_.size = N;
		}

		ValueDesc(EmptyArrayTag) : type_(value_type_array)
		{
			array_.p = 0;
			array_.size = 0;
		}

		ValueDesc(const ValueDesc* p, size_t size) : type_(value_type_array)
		{
			array_.p = p;
			array_.size = size;
		}

		template<size_t N>
		ValueDesc(const ValueDesc(&v)[N]) : type_(value_type_array)
		{
			array_.p = v;
			array_.size = N;
		}

	public:
		ValueType type() const
		{
			return type_;
		}

		bool boolean() const
		{
			ECLOG_ASSERT(type_ == value_type_boolean);
			return bool_;
		}

		cstring string() const
		{
			ECLOG_ASSERT(type_ == value_type_string);
			return str_.begin ? cstring(str_.begin, str_.end) : cstring();
		}

		StringNotation stringNotation() const
		{
			ECLOG_ASSERT(type_ == value_type_string);
			return str_.notation;
		}

		cstring stringDelimiter() const
		{
			ECLOG_ASSERT(type_ == value_type_string);
			return str_.dbegin ? cstring(str_.dbegin, str_.dend) : cstring();
		}

		Number number() const
		{
			ECLOG_ASSERT(type_ == value_type_number);

			switch (number_.underlyingType)
			{
			case Number::underlying_type_double:
				return number_.d;

			case Number::underlying_type_int:
				return number_.i;

			case Number::underlying_type_uint:
				return number_.ui;

			case Number::underlying_type_long:
				return number_.l;

			case Number::underlying_type_ulong:
				return number_.ul;

			case Number::underlying_type_llong:
				return number_.ll;

			case Number::underlying_type_ullong:
				return number_.ull;

			default:
				ECLOG_ASSERT(false);
				return 0;
			}
		}

		int fracDigits() const
		{
			ECLOG_ASSERT(type_ == value_type_number);
			return number_.fracDigits;
		}

		const Pair<KeyDesc, ValueDesc>* object() const
		{
			return object_.p;
		}

		size_t objectSize() const
		{
			return object_.size;
		}

		const ValueDesc* array() const
		{
			return array_.p;
		}

		size_t arraySize() const
		{
			return array_.size;
		}

	private:
		ValueType type_;

		union
		{
			bool bool_;

			struct
			{
				const char* begin;
				const char* end;
				const char* dbegin;
				const char* dend;

				StringNotation notation;
			}
			str_;

			struct
			{
				Number::UnderlyingType underlyingType;

				union {
					double d;
					int i;
					long l;
					long long ll;
					unsigned int ui;
					unsigned long ul;
					unsigned long long ull;
				};

				int fracDigits;
			}
			number_;

			struct
			{
				const Pair<KeyDesc, ValueDesc>* p;
				size_t size;
			}
			object_;

			struct
			{
				const ValueDesc* p;
				size_t size;
			}
			array_;
		};
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_VALUEDESC_H_

