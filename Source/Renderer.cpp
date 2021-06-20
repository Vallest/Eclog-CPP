// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include <Eclog/MemoryInputStream.h>
#include <Eclog/Detail/IntegerConversion.h>
#include <Eclog/Detail/DoubleConversion.h>
#include <Eclog/Detail/Renderer.h>
#include <Eclog/Detail/UTF8Decoder.h>
#include <Eclog/Detail/CharType.h>
#include <Eclog/Detail/Assert.h>

#define ECLOG_NUMBER_BUFFER_SIZE 32

namespace vallest {
namespace eclog {
namespace detail {

	Renderer::Renderer(OutputStream& stream, const RendererConfig& rendererConfig) :
		encoder_(stream), rc_(rendererConfig)
	{
		nestingLevel_ = 0;
		indent_ = 0;
		beginOfLine_ = true;
		separator_ = 0;
		inline_ = 0;
		error_ = 0;
	}

	void Renderer::beginObject(const KeyDesc& key, ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		beginItem(ec);
		ECLOG_ON_ERROR(setError(); return);

		renderString(key.str(), key.notation(), key.delimiter(), ec);
		ECLOG_ON_ERROR(setError(); return);

		renderColon(ec);
		ECLOG_ON_ERROR(setError(); return);

		if (rc_.formatting == RendererConfig::formatting_regular)
		{
			if (!rc_.placeOpenBracketOnNewLineForObjects || inline_)
			{
				renderSpace(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
			else if (rc_.placeOpenBracketOnNewLineForObjects)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderIndent(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
		}

		renderLeftCurlyBracket(ec);
		ECLOG_ON_ERROR(setError(); return);

		beginStruct(ec);
		ECLOG_ON_ERROR(setError(); return);

		increaseNestingLevel();
	}

	void Renderer::beginObject(ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		if (nestingLevel() > 0 || rc_.encloseRootObjectWithCurlyBrackets)
		{
			beginItem(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderLeftCurlyBracket(ec);
			ECLOG_ON_ERROR(setError(); return);

			beginStruct(ec);
			ECLOG_ON_ERROR(setError(); return);
		}

		increaseNestingLevel();
	}

	void Renderer::endObject(ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		decreaseNestingLevel();

		if (nestingLevel() > 0 || rc_.encloseRootObjectWithCurlyBrackets)
		{
			endStruct(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderRightCurlyBracket(ec);
			ECLOG_ON_ERROR(setError(); return);

			endItem();
		}
	}

	void Renderer::beginArray(const KeyDesc& key, ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		beginItem(ec);
		ECLOG_ON_ERROR(setError(); return);

		renderString(key.str(), key.notation(), key.delimiter(), ec);
		ECLOG_ON_ERROR(setError(); return);

		renderColon(ec);
		ECLOG_ON_ERROR(setError(); return);

		if (rc_.formatting == RendererConfig::formatting_regular)
		{
			if (!rc_.placeOpenBracketOnNewLineForArrays || inline_)
			{
				renderSpace(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
			else if (rc_.placeOpenBracketOnNewLineForArrays)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderIndent(ec);
				ECLOG_ON_ERROR(setError(); return);
			}
		}

		renderLeftSquareBracket(ec);
		ECLOG_ON_ERROR(setError(); return);

		beginStruct(ec);
		ECLOG_ON_ERROR(setError(); return);

		increaseNestingLevel();
	}

	void Renderer::beginArray(ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		beginItem(ec);
		ECLOG_ON_ERROR(setError(); return);

		renderLeftSquareBracket(ec);
		ECLOG_ON_ERROR(setError(); return);

		beginStruct(ec);
		ECLOG_ON_ERROR(setError(); return);

		increaseNestingLevel();
	}

	void Renderer::endArray(ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		decreaseNestingLevel();

		endStruct(ec);
		ECLOG_ON_ERROR(setError(); return);

		renderRightSquareBracket(ec);
		ECLOG_ON_ERROR(setError(); return);

		endItem();
	}

	void Renderer::renderMember(const KeyDesc& key, const ValueDesc& value, ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		if (value.type() == value_type_object)
		{
			beginObject(key, ec);
			ECLOG_ON_ERROR(setError(); return);

			for (size_t i = 0; i < value.objectSize(); ++i)
			{
				renderMember(value.object()[i].first, value.object()[i].second, ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			endObject(ec);
			ECLOG_ON_ERROR(setError(); return);
		}
		else if (value.type() == value_type_array)
		{
			beginArray(key, ec);
			ECLOG_ON_ERROR(setError(); return);

			for (size_t i = 0; i < value.arraySize(); ++i)
			{
				renderMember(value.array()[i], ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			endArray(ec);
			ECLOG_ON_ERROR(setError(); return);
		}
		else
		{
			beginItem(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderString(key.str(), key.notation(), key.delimiter(), ec);
			ECLOG_ON_ERROR(setError(); return);

			renderColon(ec);
			ECLOG_ON_ERROR(setError(); return);

			if (rc_.formatting == RendererConfig::formatting_regular && rc_.insertSpaceAfterColon)
			{
				renderSpace(ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			renderValueInternal(value, ec);
			ECLOG_ON_ERROR(setError(); return);

			endItem();
		}
	}

	void Renderer::renderMember(const ValueDesc& value, ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		if (value.type() == value_type_object)
		{
			beginObject(ec);
			ECLOG_ON_ERROR(setError(); return);

			for (size_t i = 0; i < value.objectSize(); ++i)
			{
				renderMember(value.object()[i].first, value.object()[i].second, ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			endObject(ec);
			ECLOG_ON_ERROR(setError(); return);
		}
		else if (value.type() == value_type_array)
		{
			beginArray(ec);
			ECLOG_ON_ERROR(setError(); return);

			for (size_t i = 0; i < value.arraySize(); ++i)
			{
				renderMember(value.array()[i], ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			endArray(ec);
			ECLOG_ON_ERROR(setError(); return);
		}
		else
		{
			beginItem(ec);
			ECLOG_ON_ERROR(setError(); return);

			renderValueInternal(value, ec);
			ECLOG_ON_ERROR(setError(); return);

			endItem();
		}
	}

	void Renderer::renderEmptyLines(int count, ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		if (rc_.formatting == RendererConfig::formatting_compact || inline_) {
			return;
		}

		ECLOG_ASSERT(!separator_ || separator_ == separator_linebreak);
		renderSeparator(ec);
		ECLOG_ON_ERROR(setError(); return);

		for (int i = 0; i < count; ++i)
		{
			renderLinebreak(ec);
			ECLOG_ON_ERROR(setError(); return);
		}
	}

	void Renderer::renderComment(cstring comment, ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		if (rc_.formatting == RendererConfig::formatting_compact || inline_ || !rc_.enableComments) {
			return;
		}

		ECLOG_ASSERT(!separator_ || separator_ == separator_linebreak);
		renderSeparator(ec);
		ECLOG_ON_ERROR(setError(); return);

		MemoryInputStream stream(comment.data(), comment.size());
		UTF8Decoder decoder(stream);

		bool linebreak = false;
		bool beginOfLine = true;

		renderIndent(ec);
		ECLOG_ON_ERROR(setError(); return);

		renderChar('#', ec);
		ECLOG_ON_ERROR(setError(); return);

		for (;;)
		{
			int ch = decoder.getChar(ec);
			ECLOG_ON_ERROR(setError(); return);

			if (ch < 0) {
				break;
			}

			if (ch == '\r')
			{
				ch = decoder.peekChar(ec);
				ECLOG_ON_ERROR(setError(); return);

				if (ch == '\n') {
					decoder.getChar(0);
				}

				linebreak = true;
			}
			else if (ch == '\n')
			{
				linebreak = true;
			}

			if (linebreak)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderIndent(ec);
				ECLOG_ON_ERROR(setError(); return);

				renderChar('#', ec);
				ECLOG_ON_ERROR(setError(); return);

				linebreak = false;
				beginOfLine = true;

				continue;
			}

			if (beginOfLine)
			{
				renderSpace(ec);
				ECLOG_ON_ERROR(setError(); return);

				beginOfLine = false;
			}

			renderChar(ch, ec);
			ECLOG_ON_ERROR(setError(); return);
		}

		renderLinebreak(ec);
		ECLOG_ON_ERROR(setError(); return);
	}

	int Renderer::beginInline()
	{
		return ++inline_;
	}

	int Renderer::endInline()
	{
		if (--inline_ == 0)
		{
			if (separator_ == separator_comma)
			{
				if (rc_.formatting == RendererConfig::formatting_regular)
				{
					separator_ = separator_linebreak;
				}
			}
		}

		return inline_;
	}

	void Renderer::close(ErrorCode* ec)
	{
		if (error()) {
			ECLOG_ERROR(IOError);
		}

		if (separator_)
		{
			if (separator_ == separator_linebreak)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(setError(); return);
			}

			separator_ = 0;
		}
	}

	const RendererConfig& Renderer::rendererConfig() const
	{
		return rc_;
	}

	void Renderer::beginItem(ErrorCode* ec)
	{
		renderSeparator(ec);
		ECLOG_ON_ERROR(return);

		if (beginOfLine_)
		{
			renderIndent(ec);
			ECLOG_ON_ERROR(return);
		}
	}

	void Renderer::endItem()
	{
		if (rc_.formatting == RendererConfig::formatting_regular && !inline_)
		{
			if (!beginOfLine_)
			{
				separator_ = separator_linebreak;
			}
		}
		else
		{
			separator_ = separator_comma;
		}
	}

	void Renderer::beginStruct(ErrorCode* ec)
	{
		if (rc_.formatting == RendererConfig::formatting_regular && !inline_)
		{
			renderLinebreak(ec);
			ECLOG_ON_ERROR(return);
		}

		increaseIndent();
	}

	void Renderer::endStruct(ErrorCode* ec)
	{
		decreaseIndent();

		if (rc_.formatting == RendererConfig::formatting_regular && !inline_)
		{
			if (!beginOfLine_)
			{
				renderLinebreak(ec);
				ECLOG_ON_ERROR(return);
			}

			if (beginOfLine_)
			{
				renderIndent(ec);
				ECLOG_ON_ERROR(return);
			}
		}
	}

	void Renderer::renderValueInternal(const ValueDesc& value, ErrorCode* ec)
	{
		switch (value.type())
		{
		case value_type_null:
			renderSequence("null", ec);
			return;

		case value_type_boolean:
			if (value.boolean()) {
				renderSequence("true", ec);
			}
			else {
				renderSequence("false", ec);
			}
			return;

		case value_type_string:
			renderString(value.string(), value.stringNotation(), value.stringDelimiter(), ec);
			return;

		case value_type_number:
			renderNumber(value.number(), value.fracDigits(), ec);
			return;

		default:
			ECLOG_ASSERT(false);
			return;
		}
	}

	void Renderer::renderString(cstring str, StringNotation notation, cstring delimiter, ErrorCode* ec)
	{
		if (notation == string_notation_quoted || rc_.useQuotedStringsOnly)
		{
			renderQuotedString(str, ec);
			return;
		}
		else if (notation == string_notation_unquoted)
		{
			if (str == "null" || str == "true" || str == "false" || str == "inf" || str == "nan")
			{
				renderQuotedString(str, ec);
				return;
			}

			size_t count = 0;

			for (const char* s = str.begin(); s != str.end(); ++s)
			{
				if (isAlpha(*s) || *s == '_' || (count && (*s == '-' || *s == '.' || isDigit(*s)))) {
					++count;
				}
				else {
					break;
				}
			}

			if (!str.empty() && count == str.size())
			{
				renderUnquotedString(str, ec);
				return;
			}
		}
		else if (notation == string_notation_raw)
		{
			bool good = true;

			for (const char* s = str.begin(); s != str.end(); ++s)
			{
				if (*s >= 0 && *s < 0x20 && *s != '\t')
				{
					good = false;
					break;
				}
				else if (*s == '\"')
				{
					if (delimiter.empty() || cstring(s + 1, str.end()).startsWith(delimiter))
					{
						good = false;
						break;
					}
				}
			}

			if (good)
			{
				renderRawString(str, delimiter, ec);
				return;
			}
		}
		else if (notation == string_notation_heredoc)
		{
			if (rc_.formatting == RendererConfig::formatting_compact || inline_ || delimiter.empty())
			{
				renderQuotedString(str, ec);
				return;
			}

			bool good = true;

			bool beginOfLine = true;

			const char* s = str.begin();

			while (s != str.end())
			{
				if (beginOfLine && (*s == ' ' || *s == '\t'))
				{
					++s;
				}
				else if (beginOfLine && cstring(s, str.end()).startsWith(delimiter))
				{
					s += delimiter.size();

					if (s == str.end() || *s == '\r' || *s == '\n')
					{
						good = false;
						break;
					}
				}
				else if (*s == '\r')
				{
					++s;

					if (s != str.end() && *s == '\n') {
						++s;
					}

					beginOfLine = true;
				}
				else if (*s == '\n')
				{
					++s;
					beginOfLine = true;
				}
				else if (*s >= 0 && *s < 0x20 && *s != '\t')
				{
					good = false;
					break;
				}
				else
				{
					++s;
					beginOfLine = false;
				}
			}

			if (good)
			{
				renderHeredoc(str, delimiter, ec);
				return;
			}
		}

		renderQuotedString(str, ec);
	}

	void Renderer::renderQuotedString(cstring str, ErrorCode* ec)
	{
		MemoryInputStream stream(str.data(), str.size());
		UTF8Decoder decoder(stream);

		renderChar('"', ec);
		ECLOG_ON_ERROR(return);

		for (;;)
		{
			int ch = decoder.getChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch < 0) {
				break;
			}

			switch (ch)
			{
			case '"':
				renderSequence("\\\"", ec);
				ECLOG_ON_ERROR(return);
				break;

			case '\\':
				renderSequence("\\\\", ec);
				ECLOG_ON_ERROR(return);
				break;

			case '\b':
				renderSequence("\\b", ec);
				ECLOG_ON_ERROR(return);
				break;

			case '\f':
				renderSequence("\\f", ec);
				ECLOG_ON_ERROR(return);
				break;

			case '\n':
				renderSequence("\\n", ec);
				ECLOG_ON_ERROR(return);
				break;

			case '\r':
				renderSequence("\\r", ec);
				ECLOG_ON_ERROR(return);
				break;

			case '\t':
				renderSequence("\\t", ec);
				ECLOG_ON_ERROR(return);
				break;

			default:
				if (ch < 0x20)
				{
					const char table[] = { '0', '1', '2', '3', '4', '5',
						'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

					char buffer[6];

					buffer[0] = '\\';
					buffer[1] = 'u';
					buffer[2] = '0';
					buffer[3] = '0';
					buffer[4] = table[(ch >> 4) & 0xf];
					buffer[5] = table[ch & 0xf];

					renderSequence(cstring(buffer, sizeof(buffer)), ec);
					ECLOG_ON_ERROR(return);
				}
				else
				{
					renderChar(ch, ec);
					ECLOG_ON_ERROR(return);
				}
			}
		}

		renderChar('"', ec);
		ECLOG_ON_ERROR(return);
	}

	void Renderer::renderUnquotedString(cstring str, ErrorCode* ec)
	{
		renderSequence(str, ec);
		ECLOG_ON_ERROR(return);
	}

	void Renderer::renderRawString(cstring str, cstring delimiter, ErrorCode* ec)
	{
		MemoryInputStream stream(str.data(), str.size());
		UTF8Decoder decoder(stream);

		renderChar('@', ec);
		ECLOG_ON_ERROR(return);

		for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
		{
			renderChar(*d, ec);
			ECLOG_ON_ERROR(return);
		}

		renderChar('"', ec);
		ECLOG_ON_ERROR(return);

		for (;;)
		{
			int ch = decoder.getChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch < 0) {
				break;
			}

			renderChar(ch, ec);
			ECLOG_ON_ERROR(return);
		}

		renderChar('"', ec);
		ECLOG_ON_ERROR(return);

		for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
		{
			renderChar(*d, ec);
			ECLOG_ON_ERROR(return);
		}
	}

	void Renderer::renderHeredoc(cstring str, cstring delimiter, ErrorCode* ec)
	{
		MemoryInputStream stream(str.data(), str.size());
		UTF8Decoder decoder(stream);

		renderChar('|', ec);
		ECLOG_ON_ERROR(return);

		for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
		{
			renderChar(*d, ec);
			ECLOG_ON_ERROR(return);
		}

		renderLinebreak(ec);
		ECLOG_ON_ERROR(return);

		bool linebreak = true;

		increaseIndent();

		for (;;)
		{
			int ch = decoder.peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch < 0) {
				break;
			}

			if (ch == '\r')
			{
				decoder.getChar(0);

				ch = decoder.peekChar(ec);
				ECLOG_ON_ERROR(return);

				if (ch == '\n') {
					decoder.getChar(0);
				}

				renderLinebreak(ec);
				ECLOG_ON_ERROR(return);

				linebreak = true;
			}
			else if (ch == '\n')
			{
				decoder.getChar(0);

				renderLinebreak(ec);
				ECLOG_ON_ERROR(return);

				linebreak = true;
			}
			else
			{
				decoder.getChar(0);

				if (beginOfLine_)
				{
					renderIndent(ec);
					ECLOG_ON_ERROR(return);
				}

				renderChar(ch, ec);
				ECLOG_ON_ERROR(return);

				linebreak = false;
			}
		}

		if (!linebreak)
		{
			renderLinebreak(ec);
			ECLOG_ON_ERROR(return);
		}

		renderIndent(ec);
		ECLOG_ON_ERROR(return);

		for (const char* d = delimiter.begin(); d != delimiter.end(); ++d)
		{
			renderChar(*d, ec);
			ECLOG_ON_ERROR(return);
		}

		renderLinebreak(ec);
		ECLOG_ON_ERROR(return);

		decreaseIndent();
	}

	void Renderer::renderNumber(const Number& number, int fracDigits, ErrorCode* ec)
	{
		char buffer[ECLOG_NUMBER_BUFFER_SIZE];

		switch (number.underlyingType())
		{
		case Number::underlying_type_double:
			doubleToString(number.load<double>(), buffer, fracDigits);
			break;

		case Number::underlying_type_int:
			integerToString(number.load<int>(), buffer);
			break;

		case Number::underlying_type_uint:
			integerToString(number.load<unsigned int>(), buffer);
			break;

		case Number::underlying_type_long:
			integerToString(number.load<long>(), buffer);
			break;

		case Number::underlying_type_ulong:
			integerToString(number.load<unsigned long>(), buffer);
			break;

		case Number::underlying_type_llong:
			integerToString(number.load<long long>(), buffer);
			break;

		case Number::underlying_type_ullong:
			integerToString(number.load<unsigned long long>(), buffer);
			break;

		default:
			ECLOG_ASSERT(false);
			break;
		}

		cstring s = buffer;

		if (number.underlyingType() == Number::underlying_type_double &&
			rc_.useStringsToRepresentInfinitiesAndNaNs &&
			(s.endsWith("inf") || s.endsWith("nan")))
		{
			renderString(s, string_notation_quoted, "", ec);
		}
		else
		{
			renderSequence(s, ec);
		}
	}

	void Renderer::renderLinebreak(ErrorCode* ec)
	{
		switch (rc_.linebreak)
		{
		case CR:
			encoder_.putChar('\r', ec);
			ECLOG_ON_ERROR(return);
			break;

		case LF:
			encoder_.putChar('\n', ec);
			ECLOG_ON_ERROR(return);
			break;

		case CRLF:
			encoder_.putChar('\r', ec);
			ECLOG_ON_ERROR(return);

			encoder_.putChar('\n', ec);
			ECLOG_ON_ERROR(return);
			break;
		}

		beginOfLine_ = true;
	}

	void Renderer::renderIndent(ErrorCode* ec)
	{
		char ch = rc_.indentCharacter == RendererConfig::indent_character_tab ? '\t' : ' ';

		for (int i = 0; i < indent(); ++i)
		{
			for (int j = 0; j < rc_.indentSize; ++j)
			{
				renderChar(ch, ec);
				ECLOG_ON_ERROR(return);
			}
		}
	}

	void Renderer::renderSeparator(ErrorCode* ec)
	{
		if (separator_ == separator_linebreak)
		{
			if (rc_.useCommasToSeparateItems)
			{
				renderComma(ec);
				ECLOG_ON_ERROR(return);
			}

			renderLinebreak(ec);
			ECLOG_ON_ERROR(return);

			separator_ = 0;
		}
		else if (separator_ == separator_comma)
		{
			renderComma(ec);
			ECLOG_ON_ERROR(return);

			if (rc_.formatting == RendererConfig::formatting_regular)
			{
				renderSpace(ec);
				ECLOG_ON_ERROR(return);
			}

			separator_ = 0;
		}
	}

	void Renderer::renderSpace(ErrorCode* ec)
	{
		renderChar(' ', ec);
	}

	void Renderer::renderLeftCurlyBracket(ErrorCode* ec)
	{
		renderChar('{', ec);
	}

	void Renderer::renderRightCurlyBracket(ErrorCode* ec)
	{
		renderChar('}', ec);
	}

	void Renderer::renderLeftSquareBracket(ErrorCode* ec)
	{
		renderChar('[', ec);
	}

	void Renderer::renderRightSquareBracket(ErrorCode* ec)
	{
		renderChar(']', ec);
	}

	void Renderer::renderColon(ErrorCode* ec)
	{
		renderChar(':', ec);
	}

	void Renderer::renderComma(ErrorCode* ec)
	{
		renderChar(',', ec);
	}

	void Renderer::renderSequence(cstring s, ErrorCode* ec)
	{
		for (const char* p = s.begin(); p != s.end(); ++p)
		{
			renderChar(*p, ec);
			ECLOG_ON_ERROR(return);
		}
	}

	void Renderer::renderChar(int ch, ErrorCode* ec)
	{
		encoder_.putChar(ch, ec);
		ECLOG_ON_ERROR(return);

		beginOfLine_ = false;
	}

	void Renderer::increaseNestingLevel()
	{
		++nestingLevel_;
	}

	void Renderer::decreaseNestingLevel()
	{
		--nestingLevel_;
	}

	int Renderer::nestingLevel() const
	{
		return nestingLevel_;
	}

	void Renderer::increaseIndent()
	{
		++indent_;
	}

	void Renderer::decreaseIndent()
	{
		--indent_;
	}

	int Renderer::indent() const
	{
		return indent_;
	}

	void Renderer::setError(int error)
	{
		error_ = error;
	}

	int Renderer::error() const
	{
		return error_;
	}

} // detail
} // eclog
} // vallest

