// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_NONCOPYABLE_H_
#define ECLOG_CPP_DETAIL_NONCOPYABLE_H_

namespace vallest {
namespace eclog {
namespace detail {

	class NonCopyable {
	protected:
		NonCopyable() {}
		~NonCopyable() {}

	private:
		NonCopyable(const NonCopyable&);
		NonCopyable& operator=(const NonCopyable&);
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_NONCOPYABLE_H_

