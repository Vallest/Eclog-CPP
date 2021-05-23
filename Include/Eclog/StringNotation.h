// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STRINGNOTATION_H_
#define ECLOG_CPP_STRINGNOTATION_H_

namespace eclog {

	enum StringNotation {
		string_notation_unquoted = 1 << 0,
		string_notation_quoted = 1 << 1,
		string_notation_raw = 1 << 2,
		string_notation_heredoc = 1 << 3,
	};

} // eclog

#endif // ECLOG_CPP_STRINGNOTATION_H_

