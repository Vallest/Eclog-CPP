// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_KEYDESC_H_
#define ECLOG_CPP_KEYDESC_H_

#include <Eclog/cstring.h>
#include <Eclog/StringNotation.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/StringDelimiter.h>

namespace eclog {

	class KeyDesc {
	public:
		KeyDesc(const char* str) : str_(str), notation_(string_notation_unquoted)
		{
			if (str_.empty()) {
				ECLOG_FAULT(InvalidArgument);
			}
		}

		KeyDesc(cstring str, StringNotation notation = string_notation_unquoted, cstring delimiter = cstring()) :
			str_(str), notation_(notation), delimiter_(delimiter)
		{
			if (str_.empty() || !detail::StringDelimiter::validate(delimiter_)) {
				ECLOG_FAULT(InvalidArgument);
			}
		}

		cstring str() const
		{
			return str_;
		}

		StringNotation notation() const
		{
			return notation_;
		}

		cstring delimiter() const
		{
			return delimiter_;
		}

	private:
		cstring str_;

		StringNotation notation_;
		cstring delimiter_;
	};

} // eclog

#endif // ECLOG_CPP_KEYDESC_H_

