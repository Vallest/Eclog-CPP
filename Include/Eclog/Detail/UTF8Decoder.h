// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_UTF8DECODER_H_
#define ECLOG_CPP_DETAIL_UTF8DECODER_H_

#include <Eclog/InputStream.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/NonCopyable.h>

#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		class UTF8Decoder : private NonCopyable {
		public:
			explicit UTF8Decoder(InputStream& is) :
				is_(is), p_(buffer_), avail_(0), hasChar_(false), position_(0)
			{
			}

			int peekChar(ErrorCode* ec)
			{
				if (hasChar_) {
					return char_;
				}

				char_ = decode(ec);
				hasChar_ = (char_ >= 0);

				return char_;
			}

			int getChar(ErrorCode* ec)
			{
				if (hasChar_)
				{
					hasChar_ = false;
					++position_;
					return char_;
				}

				int ch = decode(ec);

				position_ += (ch >= 0);

				return ch;
			}

			long long position() const
			{
				return position_;
			}

		private:
			int decode(ErrorCode* ec);

		private:
			InputStream& is_;

			unsigned char buffer_[128];
			unsigned char* p_;
			size_t avail_;

			bool hasChar_;
			int char_;

			long long position_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_UTF8DECODER_H_

