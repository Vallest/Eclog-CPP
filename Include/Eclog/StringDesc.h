// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STRINGDESC_H_
#define ECLOG_CPP_STRINGDESC_H_

#include <Eclog/ValueDesc.h>

namespace vallest {
namespace eclog {

	class StringDesc : public ValueDesc {
	public:
		StringDesc(const char* value) : ValueDesc(value)
		{
		}

		StringDesc(cstring value, StringNotation notation = string_notation_unquoted, cstring delimiter = cstring())
			: ValueDesc(value, notation, delimiter)
		{
		}
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_STRINGDESC_H_

