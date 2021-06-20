// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include <Eclog/Detail/UTF8Encoder.h>

namespace vallest {
namespace eclog {
namespace detail {

	void UTF8Encoder::encode(int ch, ErrorCode* ec)
	{
		char bytes[4];
		int n = 0;

		if (ch < 128)
		{
			n = 1;
			bytes[0] = (char)ch;
		}
		else if (ch < 2048)
		{
			n = 2;
			bytes[0] = (char)(0xc0 | (ch >> 6));
			bytes[1] = (char)(0x80 | (ch & 0x3f));
		}
		else if (ch < 65536)
		{
			n = 3;
			bytes[0] = (char)(0xe0 | (ch >> 12));
			bytes[1] = (char)(0x80 | ((ch >> 6) & 0x3f));
			bytes[2] = (char)(0x80 | (ch & 0x3f));
		}
		else if (ch < 2097152)
		{
			n = 4;
			bytes[0] = (char)(0xf0 | (ch >> 18));
			bytes[1] = (char)(0x80 | ((ch >> 12) & 0x3f));
			bytes[2] = (char)(0x80 | ((ch >> 6) & 0x3f));
			bytes[3] = (char)(0x80 | (ch & 0x3f));
		}

		int error = (n == 0) << 1;
		error |= ((ch >> 11) == 0x1b) << 0; // surrogate character (U+D800-U+DFFF) ?

		if (error)
		{
			ECLOG_ERROR(EncodeError);
			return;
		}

		os_.write(bytes, n);

		if (!os_.state())
		{
			ECLOG_ERROR(IOError);
			return;
		}
	}

} // detail
} // eclog
} // vallest

