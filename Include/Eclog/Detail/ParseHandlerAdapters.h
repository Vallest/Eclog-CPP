// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_PARSEHANDLERADAPTERS_H_
#define ECLOG_CPP_DETAIL_PARSEHANDLERADAPTERS_H_

#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/Context.h>
#include <Eclog/Detail/Parse.h>
#include <Eclog/Detail/ParseHandler.h>

namespace vallest {
namespace eclog {
namespace detail {

	inline bool checkTerminated(Context& ctx, ErrorCode* ec)
	{
		if (ctx.terminated())
		{
			ECLOG_ERROR(ParseError, ctx.line(), ctx.column(), pe_user_asked_for_termination);
			return true;
		}

		return false;
	}

	template<typename Handler>
	class ParseHandlerAdapter : public ParseHandler, private NonCopyable {
	public:
		explicit ParseHandlerAdapter(Context& ctx, Handler& handler) :
			ctx_(ctx), handler_(handler)
		{
		}

		virtual void onObjectBegin(ErrorCode* ec) ECLOG_OVERRIDE
		{
			handler_.onObjectBegin();
			checkTerminated(ctx_, ec);
		}

		virtual void onObjectEnd(ErrorCode* ec) ECLOG_OVERRIDE
		{
            handler_.onObjectEnd();
            checkTerminated(ctx_, ec);
		}

		virtual void onArrayBegin(ErrorCode* ec) ECLOG_OVERRIDE
		{
			handler_.onArrayBegin();
			checkTerminated(ctx_, ec);
		}

		virtual void onArrayEnd(ErrorCode* ec) ECLOG_OVERRIDE
		{
            handler_.onArrayEnd();
            checkTerminated(ctx_, ec);
		}

		virtual void onKey(const Key& key, ErrorCode* ec) ECLOG_OVERRIDE
		{
			handler_.onKey(key);
			checkTerminated(ctx_, ec);
		}

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject())
			{
				parseObject(ctx_, *this, ec);
			}
			else if (value.isArray())
			{
				parseArray(ctx_, *this, ec);
			}
			else
			{
				handler_.onValue(value);
				checkTerminated(ctx_, ec);
			}
		}

	private:
		Context& ctx_;
		Handler& handler_;
	};

	class IgnoreParseHandler : public ParseHandler, private NonCopyable {
    public:
        IgnoreParseHandler(Context& ctx) : ctx_(ctx)
        {
        }

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject())
			{
				parseObject(ctx_, *this, ec);
			}
			else if (value.isArray())
			{
				parseArray(ctx_, *this, ec);
			}
		}

    private:
        Context& ctx_;
    };

	inline void ignore(Context& ctx, Value value, ErrorCode* ec)
	{
		if (value.isObject())
		{
			IgnoreParseHandler handler(ctx);
			parseObject(ctx, handler, ec);
		}
		else if (value.isArray())
		{
			IgnoreParseHandler handler(ctx);
			parseArray(ctx, handler, ec);
		}
	}

	template<typename Handler>
	class ObjectParseHandlerAdapter : public ParseHandler, private NonCopyable {
	public:
		explicit ObjectParseHandlerAdapter(Context& ctx, Handler handler) :
			ctx_(ctx), handler_(handler)
		{
		}

		virtual void onKey(const Key& key, ErrorCode*) ECLOG_OVERRIDE
		{
			key_ = key;
		}

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject() || value.isArray())
			{
				const long long oldPos = ctx_.decoder().position();

				handler_(key_, value);

				if (checkTerminated(ctx_, ec)) {
					return;
				}

				if (ctx_.decoder().position() == oldPos) {
					ignore(ctx_, value, ec);
				}
			}
			else
			{
				handler_(key_, value);
				checkTerminated(ctx_, ec);
			}
		}

	private:
		Context& ctx_;
		Handler handler_;
		Key key_;
	};

	template<typename Handler>
	class ArrayParseHandlerAdapter : public ParseHandler, private NonCopyable {
	public:
		explicit ArrayParseHandlerAdapter(Context& ctx, Handler handler) :
			ctx_(ctx), handler_(handler)
		{
		}

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject() || value.isArray())
			{
				const long long oldPos = ctx_.decoder().position();

				handler_(value);

				if (checkTerminated(ctx_, ec)) {
					return;
				}

				if (ctx_.decoder().position() == oldPos) {
					ignore(ctx_, value, ec);
				}
			}
			else
			{
				handler_(value);
				checkTerminated(ctx_, ec);
			}
		}

	private:
		Context& ctx_;
		Handler handler_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_PARSEHANDLERADAPTERS_H_

