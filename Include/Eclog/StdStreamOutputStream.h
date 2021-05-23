// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STDSTREAMOUTPUTSTREAM_H_
#define ECLOG_CPP_STDSTREAMOUTPUTSTREAM_H_

#include <Eclog/OutputStream.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>

#include <ostream>

namespace eclog {

	class StdStreamOutputStream : public OutputStream, private detail::NonCopyable {
	public:
		explicit StdStreamOutputStream(std::ostream& stream) :
			stream_(stream)
		{
		}

		virtual bool state() const ECLOG_OVERRIDE
		{
			return stream_ ? true : false;
		}

		virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
		{
			stream_.write(buffer, size);
		}

	private:
		std::ostream& stream_;
	};

} // eclog

#endif // ECLOG_CPP_STDSTREAMOUTPUTSTREAM_H_

