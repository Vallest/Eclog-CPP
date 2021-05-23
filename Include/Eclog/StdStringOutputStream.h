// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STRINGOUTPUTSTREAM_H_
#define ECLOG_CPP_STRINGOUTPUTSTREAM_H_

#include <Eclog/OutputStream.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>

#include <string>

namespace eclog {

	class StdStringOutputStream : public OutputStream, private detail::NonCopyable {
	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return true;
		}

		virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
		{
			str_.append(buffer, size);
		}

	public:
		std::string& str()
		{
			return str_;
		}

		const std::string& str() const
		{
			return str_;
		}

	private:
		std::string str_;
	};

} // eclog

#endif // ECLOG_CPP_STRINGOUTPUTSTREAM_H_

