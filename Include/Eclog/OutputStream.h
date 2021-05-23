// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_OUTPUTSTREAM_H_
#define ECLOG_CPP_OUTPUTSTREAM_H_

#include <stddef.h> // size_t

namespace eclog {

	class OutputStream {
	public:
		virtual bool state() const = 0;

		virtual void write(const char* buffer, size_t size) = 0;
	};

} // eclog

#endif // ECLOG_CPP_OUTPUTSTREAM_H_

