// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_TEST_DEBUGHANDLERS_H_
#define ECLOG_TEST_DEBUGHANDLERS_H_

#include <Eclog/Context.h>
#include <Eclog/Parse.h>
#include <Eclog/Key.h>
#include <Eclog/Value.h>
#include <Eclog/Detail/NonAssignable.h>

#include <vector>
#include <sstream>
#include <string>

class DebugParseHandler {
public:
	DebugParseHandler()
	{
	}

	DebugParseHandler(const DebugParseHandler& other) : os_(other.os_.str())
	{
	}

	std::string result() const
	{
		return os_.str();
	}

public:
	void onObjectBegin()
	{
		os_ << "object\n";
	}

	void onObjectEnd()
	{
		os_ << "object_end" << "\n";
	}

	void onArrayBegin()
	{
		os_ << "array\n";
	}

	void onArrayEnd()
	{
		os_ << "array_end" << "\n";
	}

	void onKey(eclog::Key key)
	{
		os_ << "key " << escapeString(key) << "\n";
	}

	void onValue(eclog::Value value)
	{
		write(value);
		os_ << "\n";
	}

private:
	void write(eclog::Value value)
	{
		os_ << "value ";

		if (value.type() == eclog::value_type_string) {
			os_ << escapeString(value.asString());
		}
		else {
			os_ << value.bytes();
		}

		os_ << " type " << toString(value.type());

		if (value.type() == eclog::value_type_number) {
			os_ << " info " << toString((eclog::NumberInfo)value.numberInfo());
		}
	}

	static std::string toString(eclog::NumberInfo info)
	{
		if ((int)info == 0) {
			return "none";
		}

		std::vector<std::string> v;

		if (info & eclog::number_info_has_sign) {
			v.push_back("sign");
		}

		if (info & eclog::number_info_has_neg_sign) {
			v.push_back("neg");
		}

		if (info & eclog::number_info_has_frac) {
			v.push_back("frac");
		}

		if (info & eclog::number_info_has_exp) {
			v.push_back("exp");
		}

		if (info & eclog::number_info_inf) {
			v.push_back("inf");
		}

		if (info & eclog::number_info_nan) {
			v.push_back("nan");
		}

		std::string result;

		for (size_t i = 0; i < v.size(); ++i)
		{
			if (i > 0) {
				result += "|";
			}

			result += v[i];
		}

		return result;
	}

	static std::string toString(eclog::ValueType type)
	{
		switch (type)
		{
		case eclog::value_type_null:
			return "null";

		case eclog::value_type_boolean:
			return "boolean";

		case eclog::value_type_string:
			return "string";

		case eclog::value_type_number:
			return "number";

		case eclog::value_type_object:
			return "object";

		case eclog::value_type_array:
			return "array";
		}

		return "unknown";
	}

	static std::string escapeString(eclog::cstring str)
	{
		std::ostringstream os;

		os << "\"";

		for (const char* p = str.begin(); p != str.end(); ++p)
		{
			switch (*p)
			{
			case '"':
				os << "\\\"";
				break;

			case '\\':
				os << "\\\\";
				break;

			case '\0':
				os << "\\0";
				break;

			case '\b':
				os << "\\b";
				break;

			case '\f':
				os << "\\f";
				break;

			case '\n':
				os << "\\n";
				break;

			case '\r':
				os << "\\r";
				break;

			case '\t':
				os << "\\t";
				break;

			default:
				os << *p;
				break;
			}
		}

		os << "\"";

		return os.str();
	}

private:
	std::ostringstream os_;
};

class DebugObjectParseHandler : public eclog::detail::NonAssignable {
public:
	explicit DebugObjectParseHandler(eclog::Context& ctx, DebugParseHandler& handler, eclog::ErrorCode& ec) :
		ctx_(ctx), handler_(handler), ec_(ec)
	{
	}

	void operator()(eclog::Key, eclog::Value);

private:
	eclog::Context& ctx_;

	DebugParseHandler& handler_;

	eclog::ErrorCode& ec_;
};

class DebugArrayParseHandler : public eclog::detail::NonAssignable {
public:
	explicit DebugArrayParseHandler(eclog::Context& ctx, DebugParseHandler& handler, eclog::ErrorCode& ec) :
		ctx_(ctx), handler_(handler), ec_(ec)
	{
	}

	void operator()(eclog::Value);

private:
	eclog::Context& ctx_;

	DebugParseHandler& handler_;

	eclog::ErrorCode& ec_;
};

void DebugObjectParseHandler::operator()(eclog::Key key, eclog::Value value)
{
	if (value.isObject())
	{
		DebugObjectParseHandler handler(ctx_, handler_, ec_);

		handler_.onKey(key);

		handler_.onObjectBegin();

		eclog::parseObject(ctx_, handler, ec_);

		handler_.onObjectEnd();
	}
	else if (value.isArray())
	{
		DebugArrayParseHandler handler(ctx_, handler_, ec_);

		handler_.onKey(key);

		handler_.onArrayBegin();

		eclog::parseArray(ctx_, handler, ec_);

		handler_.onArrayEnd();
	}
	else
	{
		handler_.onKey(key);

		handler_.onValue(value);
	}
}

void DebugArrayParseHandler::operator()(eclog::Value value)
{
	if (value.isObject())
	{
		DebugObjectParseHandler handler(ctx_, handler_, ec_);

		handler_.onObjectBegin();

		eclog::parseObject(ctx_, handler, ec_);

		handler_.onObjectEnd();
	}
	else if (value.isArray())
	{
		DebugArrayParseHandler handler(ctx_, handler_, ec_);

		handler_.onArrayBegin();

		eclog::parseArray(ctx_, handler, ec_);

		handler_.onArrayEnd();
	}
	else
	{
		handler_.onValue(value);
	}
}

#endif // ECLOG_TEST_DEBUGHANDLERS_H_

