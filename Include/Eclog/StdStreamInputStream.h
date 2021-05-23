// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STDSTREAMINPUTSTREAM_H_
#define ECLOG_CPP_STDSTREAMINPUTSTREAM_H_

#include <Eclog/InputStream.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>

#include <istream>

namespace eclog {

	class StdStreamInputStream : public InputStream, private detail::NonCopyable {
	public:
		explicit StdStreamInputStream(std::istream& stream) :
			stream_(stream)
		{
		}

	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return !stream_.fail();
		}

		virtual bool eof() const ECLOG_OVERRIDE
		{
			return stream_.eof();
		}

		virtual size_t read(char* buffer, size_t size) ECLOG_OVERRIDE
		{
			stream_.read(buffer, size);

			return (size_t)stream_.gcount();
		}

	private:
		std::istream& stream_;
	};

} // eclog

#endif // ECLOG_CPP_STDSTREAMINPUTSTREAM_H_

