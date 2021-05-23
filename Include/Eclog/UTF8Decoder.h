// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_UTF8DECODER_H_
#define ECLOG_CPP_UTF8DECODER_H_

#include <Eclog/Error.h>
#include <Eclog/Detail/UTF8Decoder.h>

namespace eclog {

	class UTF8Decoder : private detail::UTF8Decoder {
	public:
		explicit UTF8Decoder(InputStream& is) : detail::UTF8Decoder(is)
		{
		}

		int peekChar()
		{
			return detail::UTF8Decoder::peekChar(0);
		}

		int peekChar(ErrorCode& ec)
		{
			return detail::UTF8Decoder::peekChar(&ec);
		}

		int getChar()
		{
			return detail::UTF8Decoder::getChar(0);
		}

		int getChar(ErrorCode& ec)
		{
			return detail::UTF8Decoder::getChar(&ec);
		}

		long long position() const
		{
			return detail::UTF8Decoder::position();
		}
	};

} // eclog

#endif // ECLOG_CPP_UTF8DECODER_H_

