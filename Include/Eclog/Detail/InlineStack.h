// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_INLINESTACK_H_
#define ECLOG_CPP_DETAIL_INLINESTACK_H_

#include <Eclog/Detail/Assert.h>

#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		template<typename T, size_t MaxSize>
		class InlineStack {
		public:
			InlineStack() : size_(0)
			{
			}

			size_t maxSize() const
			{
				return MaxSize;
			}

			size_t size() const
			{
				return size_;
			}

			T& top()
			{
				ECLOG_ASSERT(size_ > 0 && size_ <= MaxSize);
				return stack_[size_ - 1];
			}

			const T& top() const
			{
				ECLOG_ASSERT(size_ > 0 && size_ <= MaxSize);
				return stack_[size_ - 1];
			}

			void push(const T& value)
			{
				ECLOG_ASSERT(size_ < MaxSize);
				stack_[size_++] = value;
			}

			void pop()
			{
				ECLOG_ASSERT(size_ > 0);
				--size_;
			}

		private:
			T stack_[MaxSize];

			size_t size_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_INLINESTACK_H_

