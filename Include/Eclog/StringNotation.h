// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STRINGNOTATION_H_
#define ECLOG_CPP_STRINGNOTATION_H_

namespace eclog {

	enum StringNotation {
		string_notation_unquoted = 1,
		string_notation_quoted,
		string_notation_raw,
		string_notation_heredoc,
	};

} // eclog

#endif // ECLOG_CPP_STRINGNOTATION_H_

