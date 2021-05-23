// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_PARSEHANDLER_H_
#define ECLOG_CPP_DETAIL_PARSEHANDLER_H_

#include <Eclog/Key.h>
#include <Eclog/Value.h>
#include <Eclog/Error.h>

namespace eclog {

	namespace detail {

		class ParseHandler {
		public:
			virtual void onObjectBegin(ErrorCode*)
			{
			}

			virtual void onObjectEnd(ErrorCode*)
			{
			}

			virtual void onArrayBegin(ErrorCode*)
			{
			}

			virtual void onArrayEnd(ErrorCode*)
			{
			}

			virtual void onKey(const Key&, ErrorCode*)
			{
			}

			virtual void onValue(const Value&, ErrorCode*)
			{
			}
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_PARSEHANDLER_H_

