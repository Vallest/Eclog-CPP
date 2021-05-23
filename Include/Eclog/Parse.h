// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_PARSE_H_
#define ECLOG_CPP_PARSE_H_

#include <Eclog/Context.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/Parse.h>
#include <Eclog/Detail/ParseHandlerAdapters.h>

namespace eclog {

	template<typename Handler>
	inline void parse(Context& ctx, Handler& handler)
	{
		detail::ParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, 0);
	}

	template<typename Handler>
	inline void parse(Context& ctx, Handler& handler, ErrorCode& ec)
	{
		detail::ParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, &ec);
	}

	template<typename Handler>
	inline void parseObject(Context& ctx, Handler handler)
	{
		detail::ObjectParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, 0);
	}

	template<typename Handler>
	inline void parseObject(Context& ctx, Handler handler, ErrorCode& ec)
	{
		detail::ObjectParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, &ec);
	}

	template<typename Handler>
	inline void parseArray(Context& ctx, Handler handler)
	{
		detail::ArrayParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseArray((detail::Context&)ctx, adapter, 0);
	}

	template<typename Handler>
	inline void parseArray(Context& ctx, Handler handler, ErrorCode& ec)
	{
		detail::ArrayParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseArray((detail::Context&)ctx, adapter, &ec);
	}

} // eclog

#endif // ECLOG_CPP_PARSE_H_

