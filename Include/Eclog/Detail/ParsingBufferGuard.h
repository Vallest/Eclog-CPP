// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_PARSINGBUFFERGUARD_H_
#define ECLOG_CPP_DETAIL_PARSINGBUFFERGUARD_H_

#include <Eclog/ParsingBuffer.h>
#include <Eclog/Detail/InlineStack.h>
#include <Eclog/Detail/NonCopyable.h>

namespace vallest {
namespace eclog {
namespace detail {

	template<size_t MaxSize>
	class ParsingBufferGuard : private NonCopyable {
	public:
		explicit ParsingBufferGuard(ParsingBuffer& parsingBuffer) :
			parsingBuffer_(parsingBuffer)
		{
		}

		~ParsingBufferGuard()
		{
			clear();
		}

		void clear()
		{
			while (ptrs_.size()) {
				pop();
			}
		}

		void push()
		{
			void* ptr = parsingBuffer_.claim();

			ptrs_.push(ptr);
		}

		void pop()
		{
			void* ptr = ptrs_.top();

			parsingBuffer_.discard(ptr);

			ptrs_.pop();
		}

	private:
		ParsingBuffer& parsingBuffer_;

		InlineStack<void*, MaxSize> ptrs_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_PARSINGBUFFERGUARD_H_

