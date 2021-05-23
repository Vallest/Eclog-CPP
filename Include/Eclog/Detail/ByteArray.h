// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_BYTEARRAY_H_
#define ECLOG_CPP_DETAIL_BYTEARRAY_H_

#include <Eclog/cstring.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/PODArray.h>
#include <Eclog/Detail/Assert.h>

namespace eclog {

	namespace detail {

		template<typename Alloc>
		class ByteArray {
		public:
			ByteArray()
			{
			}

			ByteArray(cstring str)
			{
				init(str);
			}

			ByteArray(const ByteArray& other) : v_(other.v_)
			{
			}

			ByteArray& operator=(const ByteArray& other)
			{
				if (this != &other) {
					v_ = other.v_;
				}

				return *this;
			}

			ByteArray& operator=(cstring str)
			{
				ByteArray t(str);

				swap(t);

				return *this;
			}

			void clear()
			{
				v_.clear();
			}

			bool empty() const
			{
				return size() == 0;
			}

			size_t size() const
			{
				return v_.empty() ? 0 : v_.size() - 1;
			}

			size_t maxSize() const
			{
				return v_.maxSize() - 1;
			}

			size_t capacity() const
			{
				return v_.capacity() - 1;
			}

			void reserve(size_t capacity)
			{
				v_.reserve(capacity + 1);
			}

			char& operator[](size_t pos)
			{
				ECLOG_ASSERT(pos < size());
				return v_[pos];
			}

			const char& operator[](size_t pos) const
			{
				ECLOG_ASSERT(pos < size());
				return v_[pos];
			}

			char* data()
			{
				return v_.data();
			}

			const char* data() const
			{
				return v_.data();
			}

			cstring str() const
			{
				return size() ? cstring(data(), size()) : "";
			}

			void insert(size_t pos, char byte)
			{
				if (v_.empty())
				{
					init(cstring(&byte, 1));
				}
				else
				{
					if (pos > size()) {
						pos = size();
					}

					v_.insert(pos, byte);
				}
			}

			void insert(size_t pos, cstring str)
			{
				if (v_.empty())
				{
					init(str);
				}
				else if (str)
				{
					if (pos > size()) {
						pos = size();
					}

					v_.insert(pos, str.data(), str.size());
				}
			}

			void append(char byte)
			{
				insert(size(), byte);
			}

			void append(cstring str)
			{
				insert(size(), str);
			}

			void remove(size_t pos, size_t count = -1)
			{
				if (pos >= size()) {
					return;
				}

				if (count > size() - pos) {
					count = size() - pos;
				}

				v_.remove(pos, count);
			}

			void swap(ByteArray& other)
			{
				v_.swap(other.v_);
			}

		private:
			void init(cstring str)
			{
				if (str)
				{
					v_.reserve(str.size() + 1);
					v_.append(str.data(), str.size());
					v_.append("", 1);
				}
			}

		private:
			PODArray<char, Alloc> v_;
		};

		template<typename Alloc>
		inline void swap(ByteArray<Alloc>& a, ByteArray<Alloc>& b)
		{
			a.swap(b);
		}

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_BYTEARRAY_H_

