// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_PARSE_H_
#define ECLOG_CPP_DETAIL_PARSE_H_

#include <Eclog/Error.h>
#include <Eclog/Detail/Context.h>
#include <Eclog/Detail/ParseHandler.h>

namespace vallest {
namespace eclog {
namespace detail {

	void parseObject(Context& ctx, ParseHandler& handler, ErrorCode* ec);
	void parseArray(Context& ctx, ParseHandler& handler, ErrorCode* ec);

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_PARSE_H_

