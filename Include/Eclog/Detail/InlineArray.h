// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_INLINEARRAY_H_
#define ECLOG_CPP_DETAIL_INLINEARRAY_H_

#include <Eclog/Detail/Assert.h>

#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		template<typename T, size_t MaxSize>
		class InlineArray {
		public:
			InlineArray() : size_(0)
			{
			}

			void clear()
			{
				size_ = 0;
			}

			size_t maxSize() const
			{
				return MaxSize;
			}

			size_t size() const
			{
				return size_;
			}

			void resize(size_t size)
			{
				ECLOG_ASSERT(size <= MaxSize);
				size_ = size;
			}

			T& operator[](size_t index)
			{
				return array_[index];
			}

			const T& operator[](size_t index) const
			{
				return array_[index];
			}

			void pushBack(const T& value)
			{
				ECLOG_ASSERT(size_ < MaxSize);
				array_[size_++] = value;
			}

			void popBack()
			{
				ECLOG_ASSERT(size_ > 0);
				--size_;
			}

			T* data()
			{
				return array_;
			}

			const T* data() const
			{
				return array_;
			}

		private:
			T array_[MaxSize];

			size_t size_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_INLINEARRAY_H_

