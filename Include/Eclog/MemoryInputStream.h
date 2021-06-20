// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_MEMORYINPUTSTREAM_H_
#define ECLOG_CPP_MEMORYINPUTSTREAM_H_

#include <Eclog/InputStream.h>
#include <Eclog/Detail/Algorithm.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>

#include <string.h> // memcpy

namespace vallest {
namespace eclog {

	class MemoryInputStream : public InputStream, private detail::NonCopyable {
	public:
		explicit MemoryInputStream(const void* data, size_t size) :
			first_((const char*)data), last_((const char*)data + size)
		{
		}

	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return !eof();
		}

		virtual bool eof() const ECLOG_OVERRIDE
		{
			return first_ == last_;
		}

		virtual size_t read(char* buffer, size_t size) ECLOG_OVERRIDE
		{
			size_t n = detail::min<size_t>(last_ - first_, size);

			memcpy(buffer, first_, n);

			first_ += n;

			return n;
		}

	private:
		const char* first_;
		const char* last_;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_MEMORYINPUTSTREAM_H_

