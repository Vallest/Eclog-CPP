// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DYNAMICPARSINGBUFFER_H_
#define ECLOG_CPP_DYNAMICPARSINGBUFFER_H_

#include <Eclog/ParsingBuffer.h>
#include <Eclog/OutputStream.h>
#include <Eclog/UTF8Encoder.h>
#include <Eclog/Allocator.h>
#include <Eclog/Detail/ByteArray.h>
#include <Eclog/Detail/Memory.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/Assert.h>

namespace eclog {

	template<typename Alloc>
	class BasicDynamicParsingBuffer : public ParsingBuffer, private detail::NonCopyable {
	private:
		class BytesBuffer : public OutputStream {
		public:
			BytesBuffer() :
			ECLOG_WARNING_PUSH
			ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
			encoder_(*this)
			ECLOG_WARNING_POP
			{
			}

		public:
			virtual bool state() const ECLOG_OVERRIDE
			{
				return true;
			}

			virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
			{
				bytes_.append(cstring(buffer, size));
			}

		public:
			size_t size() const
			{
				return bytes_.size();
			}

			char* data()
			{
				return bytes_.data();
			}

			cstring str() const
			{
				return bytes_.str();
			}

			void putChar(int ch)
			{
				encoder_.putChar(ch);
			}

			void shrink(size_t size)
			{
				bytes_.remove(size);
			}

		private:
			UTF8Encoder encoder_;

			detail::ByteArray<Alloc> bytes_;
		};

	public:
		BasicDynamicParsingBuffer() : bytesBuffer_(0)
		{
		}

	public:
		virtual void* claim() ECLOG_OVERRIDE
		{
			bytesBuffer_ = detail::create<BytesBuffer, Alloc>();

			return bytesBuffer_;
		}

		virtual void discard(void* ptr) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ == 0 || ptr == bytesBuffer_);
			detail::destroy<BytesBuffer, Alloc>((BytesBuffer*)ptr);

			bytesBuffer_ = 0;
		}

		virtual size_t length() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			return bytesBuffer_->size();
		}

		virtual char* address() ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			return bytesBuffer_->data();
		}

		virtual cstring str() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			return bytesBuffer_->str();
		}

		virtual void putChar(int ch) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			bytesBuffer_->putChar(ch);
		}

		virtual void shrink(size_t length) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			bytesBuffer_->shrink(length);
		}

	private:
		BytesBuffer* bytesBuffer_;
	};

	typedef BasicDynamicParsingBuffer<ECLOG_DEFAULT_ALLOCATOR> DynamicParsingBuffer;

} // eclog

#endif // ECLOG_CPP_DYNAMICPARSINGBUFFER_H_

