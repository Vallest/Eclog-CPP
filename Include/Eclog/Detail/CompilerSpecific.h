// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_COMPILERSPECIFIC_H_
#define ECLOG_CPP_DETAIL_COMPILERSPECIFIC_H_

#if __cplusplus >= 201703L
	#define ECLOG_FALLTHROUGH [[fallthrough]];
#elif defined(__clang__)
	#if defined(__has_cpp_attribute)
		#if __has_cpp_attribute(clang::fallthrough)
			#define ECLOG_FALLTHROUGH [[clang::fallthrough]];
		#endif
	#endif
#elif defined(__GNUC__)
	#if defined(__has_cpp_attribute)
		#if __has_cpp_attribute(fallthrough)
			#define ECLOG_FALLTHROUGH __attribute__((fallthrough));
		#endif
	#endif
#endif

#ifndef ECLOG_FALLTHROUGH
	#define ECLOG_FALLTHROUGH
#endif

#if (defined(__cpp_rvalue_references) && __cpp_rvalue_references >= 200610) || (defined(_MSC_VER) && _MSC_VER >= 1600)
	#define ECLOG_RVALUE_REFERENCES
#endif

#if defined(_MSC_VER)
	#define ECLOG_WARNING_PUSH __pragma(warning(push))
	#define ECLOG_WARNING_POP __pragma(warning(pop))
	#define ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR
	#define ECLOG_WARNING_IGNORE_SIGN_COMPARE __pragma(warning(disable:4018 4389))
	#define ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST __pragma(warning(disable:4355))
#elif defined(__GNUC__)
	#define ECLOG_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define ECLOG_WARNING_POP _Pragma("GCC diagnostic pop")
	#define ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR _Pragma("GCC diagnostic ignored \"-Wdelete-non-virtual-dtor\"")
	#define ECLOG_WARNING_IGNORE_SIGN_COMPARE _Pragma("GCC diagnostic ignored \"-Wsign-compare\"")
	#define ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
#else
	#define ECLOG_WARNING_PUSH
	#define ECLOG_WARNING_POP
	#define ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR
	#define ECLOG_WARNING_IGNORE_SIGN_COMPARE
	#define ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
#endif

#if __cplusplus >= 201103L
	#define ECLOG_OVERRIDE override
#elif defined(_MSC_VER) && _MSC_VER > 1600
	#define ECLOG_OVERRIDE override
#endif

#ifndef ECLOG_OVERRIDE
	#define ECLOG_OVERRIDE
#endif

#endif // ECLOG_CPP_DETAIL_COMPILERSPECIFIC_H_

