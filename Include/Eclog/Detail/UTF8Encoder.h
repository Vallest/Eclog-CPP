// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_UTF8ENCODER_H_
#define ECLOG_CPP_DETAIL_UTF8ENCODER_H_

#include <Eclog/OutputStream.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/NonCopyable.h>

namespace vallest {
namespace eclog {
namespace detail {

	class UTF8Encoder : private NonCopyable {
	public:
		explicit UTF8Encoder(OutputStream& os) : os_(os)
		{
		}

		void putChar(int ch, ErrorCode* ec)
		{
			encode(ch, ec);
		}

	private:
		void encode(int ch, ErrorCode* ec);

	private:
		OutputStream& os_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_UTF8ENCODER_H_

