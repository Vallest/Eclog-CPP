// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STRINGDESC_H_
#define ECLOG_CPP_STRINGDESC_H_

#include <Eclog/ValueDesc.h>

namespace eclog {

	class StringDesc : public ValueDesc {
	public:
		StringDesc(const char* value) : ValueDesc(value)
		{
		}

		StringDesc(cstring value, StringNotation notation = string_notation_quoted, cstring delimiter = cstring())
			: ValueDesc(value, notation, delimiter)
		{
		}
	};

} // eclog

#endif // ECLOG_CPP_STRINGDESC_H_

