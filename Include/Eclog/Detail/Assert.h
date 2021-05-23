// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_ASSERT_H_
#define ECLOG_CPP_DETAIL_ASSERT_H_

#include <assert.h>

#ifdef NDEBUG
	#define ECLOG_ASSERT(x) (void)(x)
#else
	#define ECLOG_ASSERT(x) assert(x)
#endif

#endif // ECLOG_CPP_DETAIL_ASSERT_H_

