// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_MEMORYOUTPUTSTREAM_H_
#define ECLOG_CPP_MEMORYOUTPUTSTREAM_H_

#include <Eclog/OutputStream.h>
#include <Eclog/Allocator.h>
#include <Eclog/Detail/ByteArray.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>

namespace vallest {
namespace eclog {

	template<typename Alloc>
	class BasicMemoryOutputStream : public OutputStream, private detail::NonCopyable {
	public:
		BasicMemoryOutputStream()
		{
		}

	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return true;
		}

		virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
		{
			bytes_.append(cstring(buffer, size));
		}

	public:
		size_t size() const
		{
			return bytes_.size();
		}

		char* data()
		{
			return bytes_.data();
		}

		const char* data() const
		{
			return bytes_.data();
		}

	private:
		detail::ByteArray<Alloc> bytes_;
	};

	typedef BasicMemoryOutputStream<ECLOG_DEFAULT_ALLOCATOR> MemoryOutputStream;

} // eclog
} // vallest

#endif // ECLOG_CPP_MEMORYOUTPUTSTREAM_H_

