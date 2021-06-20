// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include <Eclog/Detail/UTF8Decoder.h>
#include <Eclog/Detail/Utility.h>

#include <string.h> // memmove, memset

namespace vallest {
namespace eclog {
namespace detail {

	int UTF8Decoder::decode(ErrorCode* ec)
	{
		static const char length[32] = {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0,
		};

		static const char mask[5] = { 0, 0x7f, 0x1f, 0x0f, 0x07 };
		static const char shift[5] = { 0, 18, 12, 6, 0 };
		static const int min[5] = { 2097152, 0, 128, 2048, 65536 };
		static const char shifte[5] = { 0, 6, 4, 2, 0 };

		if (avail_ < 4)
		{
			memmove(buffer_, p_, avail_);
			p_ = buffer_;

			if (is_.eof())
			{
				if (avail_ == 0) {
					return -1;
				}

				memset(buffer_ + avail_, 0, 4 - avail_);
			}
			else
			{
				while (avail_ < 4)
				{
					size_t free = detail::arraySize(buffer_) - avail_;

					size_t read = is_.read((char*)buffer_ + avail_, free);

					avail_ += read;

					if (!is_.state())
					{
						if (is_.eof())
						{
							if (avail_ == 0) {
								return -1;
							}

							if (avail_ < 4)
							{
								memset(buffer_ + avail_, 0, 4 - avail_);
							}

							break;
						}
						else
						{
							ECLOG_ERROR(IOError);
							return -2;
						}
					}
				}
			}
		}

		int n = length[p_[0] >> 3];

		int code = (p_[0] & mask[n]) << 18;
		code |= (p_[1] & 0x3f) << 12;
		code |= (p_[2] & 0x3f) << 6;
		code |= (p_[3] & 0x3f) << 0;
		code >>= shift[n];

		int error = (code < min[n]) << 7;
		error |= ((code >> 11) == 0x1b) << 6; // surrogate character (U+D800-U+DFFF) ?
		error |= (p_[1] & 0xc0) >> 2;
		error |= (p_[2] & 0xc0) >> 4;
		error |= (p_[3]) >> 6;
		error ^= 0x2a;
		error >>= shifte[n];

		if (error)
		{
			ECLOG_ERROR(DecodeError);
			return -2;
		}

		p_ += n;
		avail_ -= n;

		return code;
	}

} // detail
} // eclog
} // vallest

