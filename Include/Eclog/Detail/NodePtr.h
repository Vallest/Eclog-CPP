// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_NODEPTR_H_
#define ECLOG_CPP_DETAIL_NODEPTR_H_

#include <Eclog/Detail/NonCopyable.h>

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T, typename Factory>
	class NodePtr : private NonCopyable {
	public:
		explicit NodePtr(T* ptr = 0) : ptr_(ptr)
		{
		}

		~NodePtr()
		{
			if (ptr_) {
				Factory::destroy(ptr_);
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
				Factory::destroy(ptr_);
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

#endif // ECLOG_CPP_DETAIL_NODEPTR_H_

