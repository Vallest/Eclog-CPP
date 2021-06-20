// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_PARSINGBUFFER_H_
#define ECLOG_CPP_PARSINGBUFFER_H_

#include <Eclog/cstring.h>

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {

	class ParsingBuffer {
	public:
		virtual void* claim() = 0;

		virtual void discard(void*) = 0;

		virtual size_t length() const = 0;

		virtual char* address() = 0;

		virtual cstring str() const = 0;

		virtual void putChar(int ch) = 0;

		virtual void shrink(size_t length) = 0;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_PARSINGBUFFER_H_

