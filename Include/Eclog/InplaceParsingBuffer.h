// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_INPLACEPARSINGBUFFER_H_
#define ECLOG_CPP_INPLACEPARSINGBUFFER_H_

#include <Eclog/ParsingBuffer.h>
#include <Eclog/OutputStream.h>
#include <Eclog/UTF8Encoder.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/Assert.h>

#include <string.h> // memcpy

namespace vallest {
namespace eclog {

	class InplaceParsingBuffer : public ParsingBuffer, private detail::NonCopyable {
	private:
		ECLOG_WARNING_PUSH
		ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
		class BytesBuffer : public OutputStream {
		public:
			BytesBuffer() : encoder_(*this), buffer_(0), maxSize_(0), size_(0)
			{
			}

		public:
			virtual bool state() const ECLOG_OVERRIDE
			{
				return true;
			}

			virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
			{
				ECLOG_ASSERT(buffer_ && size_ > 0);

				if (size > maxSize_ - size_) {
					ECLOG_FAULT(BufferOverflow);
				}

				memcpy(buffer_ + size_ - 1, buffer, size);

				buffer_[size_ - 1 + size] = 0;

				size_ += size;
			}

		public:
			void reset(char* buffer, size_t maxSize)
			{
				if (buffer)
				{
					if (maxSize < 1) {
						ECLOG_FAULT(BufferOverflow);
					}

					buffer_ = buffer;
					maxSize_ = maxSize;
					size_ = 1;

					buffer_[0] = 0;
				}
				else
				{
					buffer_ = 0;
					maxSize_ = 0;
					size_ = 0;
				}
			}

			size_t size() const
			{
				return size_;
			}

			char* data()
			{
				return buffer_;
			}

			const char* data() const
			{
				return buffer_;
			}

			cstring str() const
			{
				return buffer_ ? cstring(buffer_, size_ - 1) : "";
			}

			void putChar(int ch)
			{
				encoder_.putChar(ch);
			}

			void shrink(size_t size)
			{
				ECLOG_ASSERT(size_ >= 1 && size <= size_ - 1);
				size_ = size + 1;

				buffer_[size] = 0;
			}

		private:
			UTF8Encoder encoder_;

			char* buffer_;
			size_t maxSize_;
			size_t size_;
		};
		ECLOG_WARNING_POP

	public:
		explicit InplaceParsingBuffer(void* buffer, size_t maxSize) :
			buffer_((char*)buffer), maxSize_(maxSize), size_(0)
		{
			ECLOG_ASSERT(buffer && maxSize > 0);
		}
	
	public:
		virtual void* claim() ECLOG_OVERRIDE
		{
			if (bytesBuffer_.data())
			{
				ECLOG_ASSERT(bytesBuffer_.size() > 0);
				size_ += bytesBuffer_.size();
			}

			bytesBuffer_.reset(buffer_ + size_, maxSize_ - size_);

			return buffer_ + size_;
		}

		virtual void discard(void* ptr) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data() == 0 || ptr == bytesBuffer_.data());
			ECLOG_ASSERT(ptr >= buffer_ && ptr < buffer_ + maxSize_);
			size_ = (char*)ptr - buffer_;

			bytesBuffer_.reset(0, 0);
		}

		virtual size_t length() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			return bytesBuffer_.str().size();
		}

		virtual char* address() ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			return bytesBuffer_.data();
		}

		virtual cstring str() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			return bytesBuffer_.str();
		}

		virtual void putChar(int ch) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			bytesBuffer_.putChar(ch);
		}

		virtual void shrink(size_t length) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			bytesBuffer_.shrink(length);
		}

	private:
		char* buffer_;
		size_t maxSize_;
		size_t size_;

		BytesBuffer bytesBuffer_;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_INPLACEPARSINGBUFFER_H_

