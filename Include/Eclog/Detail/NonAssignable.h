// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_NONASSIGNABLE_H_
#define ECLOG_CPP_DETAIL_NONASSIGNABLE_H_

namespace vallest {
namespace eclog {
namespace detail {

	class NonAssignable {
	protected:
		NonAssignable() {}
		~NonAssignable() {}

	private:
		NonAssignable& operator=(const NonAssignable&);
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_NONASSIGNABLE_H_

