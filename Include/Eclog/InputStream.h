// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_INPUTSTREAM_H_
#define ECLOG_CPP_INPUTSTREAM_H_

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {

	class InputStream {
	public:
		virtual bool state() const = 0;
		virtual bool eof() const = 0;

		virtual size_t read(char* buffer, size_t size) = 0;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_INPUTSTREAM_H_

