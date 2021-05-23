// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_UTF8ENCODER_H_
#define ECLOG_CPP_UTF8ENCODER_H_

#include <Eclog/Error.h>
#include <Eclog/Detail/UTF8Encoder.h>

namespace eclog {

	class UTF8Encoder : private detail::UTF8Encoder {
	public:
		explicit UTF8Encoder(OutputStream& os) : detail::UTF8Encoder(os)
		{
		}

		void putChar(int ch)
		{
			detail::UTF8Encoder::putChar(ch, 0);
		}

		void putChar(int ch, ErrorCode& ec)
		{
			detail::UTF8Encoder::putChar(ch, &ec);
		}
	};

} // eclog

#endif // ECLOG_CPP_UTF8ENCODER_H_

