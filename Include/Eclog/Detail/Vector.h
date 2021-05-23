// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_VECTOR_H_
#define ECLOG_CPP_DETAIL_VECTOR_H_

#include <Eclog/Error.h>
#include <Eclog/Detail/Memory.h>
#include <Eclog/Detail/Algorithm.h>
#include <Eclog/Detail/Utility.h>
#include <Eclog/Detail/Limits.h>
#include <Eclog/Detail/Assert.h>

#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		template<typename T, typename Alloc>
		class Vector {
		public:
			Vector() : size_(0), capacity_(0), v_(0)
			{
			}

			Vector(const Vector& other) : size_(0), capacity_(0), v_(0)
			{
				assign(other);
			}

			~Vector()
			{
				reset(0, 0, 0);
			}

			Vector& operator=(const Vector& other)
			{
				if (this != &other) {
					assign(other);
				}

				return *this;
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

			size_t indexOf(const T& value) const
			{
				return &value - v_;
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

			void clear()
			{
				destructRange(v_, v_ + size_);

				size_ = 0;
			}

			void insert(size_t index, const T& value)
			{
				pushBack(value);

				if (index < size_) {
					rotate(v_ + index, v_ + (size_ - 1), v_ + size_);
				}
			}

			void pushBack(const T& value)
			{
				if (size_ == maxSize()) {
					ECLOG_FAULT(LengthError);
				}

				if (size_ < capacity_)
				{
					construct<T>(v_ + size_, value);

					size_ += 1;
				}
				else
				{
					size_t capacity = growTo(size_ + 1);

					T* v = makeCopy(capacity);

					ECLOG_TRY
					{
						construct<T>(v + size_, value);
					}
					ECLOG_CATCH_ALL
					{
						reset(v, size_, capacity);
						ECLOG_RETHROW;
					}

					reset(v, size_ + 1, capacity);
				}
			}

			void popBack()
			{
				ECLOG_ASSERT(size_ > 0);

				destruct<T>(v_ + (size_ - 1));

				size_ -= 1;
			}

			void remove(size_t index, size_t count = 1)
			{
				if (index < size_ && count > 0)
				{
					if (count > size_ - index) {
						count = size_ - index;
					}

					copy(v_ + index + count, v_ + size_, v_ + index);

					destructRange(v_ + size_ - count, v_ + size_);

					size_ -= count;
				}
			}

			void swap(Vector& other)
			{
				detail::swap(size_, other.size_);
				detail::swap(capacity_, other.capacity_);
				detail::swap(v_, other.v_);
			}

		private:
			void destroyAll()
			{
				destructRange(v_, v_ + size_);

				Alloc::deallocate(v_);
			}

			void reset(T* v, size_t size, size_t capacity)
			{
				destroyAll();

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

				if (v_)
				{
					ECLOG_TRY
					{
						constructN<T>(v, min(size_, size), v_);
					}
					ECLOG_CATCH_ALL
					{
						Alloc::deallocate(v);
						ECLOG_RETHROW;
					}
				}

				return v;
			}

			size_t growTo(size_t size) const
			{
				size_t capacity = maxSize() - capacity_ / 2 < capacity_ ?
					0 : capacity_ + capacity_ / 2;

				return max(capacity, size);
			}

			void assign(const Vector& other)
			{
				if (other.size_ == 0)
				{
					clear();
				}
				else if (capacity_ >= other.size_)
				{
					copy(other.v_, other.v_ + min(size_, other.size_), v_);

					if (other.size_ > size_) {
						constructN<T>(v_ + size_, other.size_ - size_, other.v_ + size_);
					}
					else if (other.size_ < size_) {
						destructRange(v_ + other.size_, v_ + size_);
					}

					size_ = other.size_;
				}
				else
				{
					reset(other.makeCopy(other.size_), other.size_, other.size_);
				}
			}

		private:
			size_t size_;
			size_t capacity_;
			T* v_;
		};

		template<typename T, typename Alloc>
		inline void swap(Vector<T, Alloc>& a, Vector<T, Alloc>& b)
		{
			a.swap(b);
		}

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_VECTOR_H_

