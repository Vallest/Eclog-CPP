// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_PODARRAY_H_
#define ECLOG_CPP_DETAIL_PODARRAY_H_

#include <Eclog/Error.h>
#include <Eclog/Detail/Algorithm.h>
#include <Eclog/Detail/Utility.h>
#include <Eclog/Detail/Limits.h>
#include <Eclog/Detail/Assert.h>

#include <string.h> // memcpy, memmove
#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		template<typename T, typename Alloc>
		class PODArray {
		public:
			PODArray() : size_(0), capacity_(0), v_(0)
			{
			}

			PODArray(const T* data, size_t size) : size_(0), capacity_(0), v_(0)
			{
				append(data, size);
			}

			PODArray(const PODArray& other) : size_(0), capacity_(0), v_(0)
			{
				assign(other);
			}

			~PODArray()
			{
				reset(0, 0, 0);
			}

			PODArray& operator=(const PODArray& other)
			{
				if (this != &other) {
					assign(other);
				}

				return *this;
			}

			void clear()
			{
				size_ = 0;
			}

			bool empty() const
			{
				return size_ == 0;
			}

			size_t size() const
			{
				return size_;
			}

			size_t maxSize() const
			{
				return maxValue<size_t>() / sizeof(T);
			}

			size_t capacity() const
			{
				return capacity_;
			}

			void reserve(size_t capacity)
			{
				if (capacity > maxSize()) {
					ECLOG_FAULT(LengthError);
				}

				if (capacity > capacity_) {
					reset(makeCopy(capacity), size_, capacity);
				}
			}

			T& operator[](size_t index)
			{
				ECLOG_ASSERT(index < size_);
				return v_[index];
			}

			const T& operator[](size_t index) const
			{
				ECLOG_ASSERT(index < size_);
				return v_[index];
			}

			T& front()
			{
				ECLOG_ASSERT(size_ > 0);
				return v_[0];
			}

			const T& front() const
			{
				ECLOG_ASSERT(size_ > 0);
				return v_[0];
			}

			T& back()
			{
				ECLOG_ASSERT(size_ > 0);
				return v_[size_ - 1];
			}

			const T& back() const
			{
				ECLOG_ASSERT(size_ > 0);
				return v_[size_ - 1];
			}

			T* data()
			{
				return v_;
			}

			const T* data() const
			{
				return v_;
			}

			size_t insert(size_t index, const T& value)
			{
				return insert(index, &value, 1);
			}

			size_t insert(size_t index, const T* ptr, size_t count)
			{
				ECLOG_ASSERT(ptr != 0);

				if (count > maxSize() - size_) {
					ECLOG_FAULT(LengthError);
				}

				if (index >= size_)
				{
					append(ptr, count);
				}
				else if (count <= capacity_ - size_)
				{
					memmove(v_ + index + count, v_ + index, sizeof(T) * (size_ - index));

					memcpy(v_ + index, ptr, sizeof(T) *count);

					size_ += count;
				}
				else
				{
					size_t capacity = growTo(size_ + count);

					T* v = (T*)Alloc::allocate(sizeof(T) * capacity);

					memcpy(v + index, ptr, sizeof(T) * count);

					if (v_)
					{
						memcpy(v, v_, sizeof(T) * index);
						memcpy(v + index + count, v_ + index, sizeof(T) * (size_ - index));
					}

					reset(v, size_ + count, capacity);
				}

				return index;
			}

			void pushBack(const T& value)
			{
				append(&value, 1);
			}

			void popBack()
			{
				ECLOG_ASSERT(size_ > 0);
				size_ -= 1;
			}

			void append(const T* ptr, size_t count)
			{
				ECLOG_ASSERT(ptr != 0);

				if (count > maxSize() - size_) {
					ECLOG_FAULT(LengthError);
				}

				if (count <= capacity_ - size_)
				{
					memcpy(v_ + size_, ptr, sizeof(T) * count);

					size_ += count;
				}
				else
				{
					size_t capacity = growTo(size_ + count);

					T* v = makeCopy(capacity);

					memcpy(v + size_, ptr, sizeof(T) * count);

					reset(v, size_ + count, capacity);
				}
			}

			void remove(size_t index, size_t count = 1)
			{
				if (index < size_)
				{
					if (count > size_ - index) {
						count = size_ - index;
					}

					memmove(v_ + index, v_ + index + count, sizeof(T) * (size_ - index - count));

					size_ -= count;
				}
			}

			void swap(PODArray& other)
			{
				detail::swap(size_, other.size_);
				detail::swap(capacity_, other.capacity_);
				detail::swap(v_, other.v_);
			}

		private:
			void reset(T* v, size_t size, size_t capacity)
			{
				if (v_) {
					Alloc::deallocate(v_);
				}

				size_ = size;
				capacity_ = capacity;
				v_ = v;
			}

			T* makeCopy(size_t size) const
			{
				if (size > maxSize()) {
					ECLOG_FAULT(LengthError);
				}

				T* v = (T*)Alloc::allocate(sizeof(T) * size);

				if (v_) {
					memcpy(v, v_, sizeof(T) * min(size_, size));
				}

				return v;
			}

			size_t growTo(size_t size) const
			{
				size_t capacity = maxSize() - capacity_ / 2 < capacity_ ?
					0 : capacity_ + capacity_ / 2;

				return max(capacity, size);
			}

			void assign(const PODArray& other)
			{
				if (other.size_ == 0)
				{
					clear();
				}
				else if (capacity_ >= other.size_)
				{
					memcpy(v_, other.v_, sizeof(T) * other.size_);

					size_ = other.size_;
				}
				else
				{
					PODArray t(other.v_, other.size_);

					swap(t);
				}
			}

		private:
			size_t size_;
			size_t capacity_;
			T* v_;
		};

		template<typename T, typename Alloc>
		inline void swap(PODArray<T, Alloc>& a, PODArray<T, Alloc>& b)
		{
			a.swap(b);
		}

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_PODARRAY_H_

