// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_MEMORY_H_
#define ECLOG_CPP_DETAIL_MEMORY_H_

#include <Eclog/Error.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/CompilerSpecific.h>

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T>
	inline T* construct(void* ptr)
	{
		return new(ptr) T();
	}

	template<typename T, typename A1>
	inline T* construct(void* ptr, const A1& arg1)
	{
		return new(ptr) T(arg1);
	}

	template<typename T, typename A1, typename A2>
	inline T* construct(void* ptr, const A1& arg1, const A2& arg2)
	{
		return new(ptr) T(arg1, arg2);
	}

	template<typename T, typename A1, typename A2, typename A3>
	inline T* construct(void* ptr, const A1& arg1, const A2& arg2, const A3& arg3)
	{
		return new(ptr) T(arg1, arg2, arg3);
	}

	template<typename T>
	inline void destruct(T* ptr)
	{
		(void)ptr;

		ECLOG_WARNING_PUSH
		ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR
		ptr->~T();
		ECLOG_WARNING_POP
	}

	template<typename T>
	inline void destructRange(T* first, T* last)
	{
		for (; first != last; ++first) {
			destruct(first);
		}
	}

	template<typename T, typename InputIterator>
	inline void constructN(void* ptr, size_t n, InputIterator it)
	{
		T* last = (T*)ptr;

		ECLOG_TRY
		{
			for (size_t i = 0; i < n; ++i)
			{
				construct<T>(last, *it);
				++last;
				++it;
			}
		}
		ECLOG_CATCH_ALL
		{
			destructRange((T*)ptr, last);
			ECLOG_RETHROW;
		}
	}

	template<typename T, typename Alloc>
	inline T* create()
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr);
		}
		ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
			ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc, typename A1>
	inline T* create(const A1& arg1)
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr, arg1);
		}
		ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
			ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc, typename A1, typename A2>
	inline T* create(const A1& arg1, const A2& arg2)
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr, arg1, arg2);
		}
			ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
		ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc, typename A1, typename A2, typename A3>
	inline T* create(const A1& arg1, const A2& arg2, const A3& arg3)
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr, arg1, arg2, arg3);
		}
			ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
		ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc>
	inline void destroy(T* ptr)
	{
		destruct<T>(ptr);
		Alloc::deallocate(ptr);
	}

	template<typename T, typename Alloc>
	class UniquePtr : private NonCopyable {
	public:
		explicit UniquePtr(T* ptr) : ptr_(ptr)
		{
		}

		~UniquePtr()
		{
			if (ptr_) {
				destroy<T, Alloc>(ptr_);
			}
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}

		T* get() const
		{
			return ptr_;
		}

		void reset(T* ptr = 0)
		{
			if (ptr_) {
				destroy<T, Alloc>(ptr_);
			}

			ptr_ = ptr;
		}

		T* release()
		{
			T* ptr = ptr_;
			ptr_ = 0;
			return ptr;
		}

	private:
		T* ptr_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_MEMORY_H_

