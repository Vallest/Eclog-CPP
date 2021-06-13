// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include <Eclog/Value.h>
#include <Eclog/NumberInfo.h>
#include <Eclog/StringNotation.h>
#include <Eclog/Linebreak.h>
#include <Eclog/cstring.h>
#include <Eclog/Detail/Parse.h>
#include <Eclog/Detail/ParsingBufferGuard.h>
#include <Eclog/Detail/InlineStack.h>
#include <Eclog/Detail/InlineArray.h>
#include <Eclog/Detail/CharType.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/Assert.h>

#include <stddef.h> // size_t
#include <limits.h>

namespace eclog {

	namespace detail {

		static void onUnexpectedChar(int line, int column, int ch, ErrorCode* ec)
		{
			if (ch < 0) {
				ECLOG_ERROR(ParseError, line, column, pe_unexpected_end_of_file);
			}
			else {
				ECLOG_ERROR(ParseError, line, column, pe_unexpected_character);
			}
		}

		static int peekNonEof(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return -1);

			if (ch < 0)
			{
				ECLOG_ERROR(ParseError, ctx.line(), ctx.column(), pe_unexpected_end_of_file);
				return -2;
			}

			return ch;
		}

		static void transferChar(Context& ctx)
		{
			int ch = ctx.decoder().getChar(0);
			ctx.buffer().putChar(ch);
		}

		static void transferChar(Context& ctx, int ch)
		{
			ctx.decoder().getChar(0);
			ctx.buffer().putChar(ch);
		}

		static void transferSequence(Context& ctx, const char* s, ErrorCode* ec)
		{
			while (*s)
			{
				int ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (ch != *s)
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}

				transferChar(ctx);

				++s;
			}
		}

        static bool skipSequence(Context& ctx, const char* s, ErrorCode* ec)
        {
            while (*s)
            {
                int ch = peekNonEof(ctx, ec);
                ECLOG_ON_ERROR(return false);

                if (ch != *s) {
                    return false;
                }

                ctx.decoder().getChar(0);

                ++s;
            }

            return true;
        }

		static bool skipSpacesAndTabs(Context& ctx, ErrorCode* ec)
		{
			int count = 0;

			for (;;)
			{
				int ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return false);

				if (ch == ' ')
				{
					ctx.decoder().getChar(0);
					++count;
				}
				else if (ch == '\t')
				{
					ctx.decoder().getChar(0);
					++count;
				}
				else
				{
					break;
				}
			}

			return count > 0;
		}

		static int skipLinebreak(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return 0);

			int linebreak = 0;

			if (ch == '\r')
			{
				ctx.decoder().getChar(0);

				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return 0);

				if (ch == '\n')
				{
					ctx.decoder().getChar(0);
					linebreak = CRLF;
				}
				else
				{
					linebreak = CR;
				}
			}
			else if (ch == '\n')
			{
				ctx.decoder().getChar(0);
				linebreak = LF;
			}

			if (linebreak) {
				ctx.addLine();
			}

			return linebreak;
		}

		static bool skipComment(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return false);

			if (ch == '#')
			{
				ctx.decoder().getChar(0);

				for (;;)
				{
					ch = ctx.decoder().peekChar(ec);
					ECLOG_ON_ERROR(return false);

					if (ch == '\r' || ch == '\n')
					{
						skipLinebreak(ctx, ec);
						ECLOG_ON_ERROR(return false);

						return true;
					}
					else if (ch < 0)
					{
						return true;
					}
					else if (ch < 0x20 && ch != '\t')
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return false;
					}

					ctx.decoder().getChar(0);
				}
			}

			return false;
		}

		static void skipWhitespaceAndComments(Context& ctx, ErrorCode* ec)
		{
			for (;;)
			{
				bool spaces = skipSpacesAndTabs(ctx, ec);
				ECLOG_ON_ERROR(return);

				int linebreak = skipLinebreak(ctx, ec);
				ECLOG_ON_ERROR(return);

				bool comment = skipComment(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (!spaces && !comment && !linebreak) {
					return;
				}
			}
		}

		static void writeLinebreak(Context& ctx, int linebreak)
		{
			switch (linebreak)
			{
			case CR:
				ctx.buffer().putChar('\r');
				break;

			case LF:
				ctx.buffer().putChar('\n');
				break;

			case CRLF:
				ctx.buffer().putChar('\r');
				ctx.buffer().putChar('\n');
				break;
			}
		}

		static int parseUnicodeHexDigits(Context& ctx, ErrorCode* ec)
		{
            int ch = peekNonEof(ctx, ec);
            ECLOG_ON_ERROR(return 0);

            bool variableLength = false;

            if (ch == '{')
            {
                ctx.decoder().getChar(0);

                variableLength = true;
            }

            int code = 0;

			size_t i = 0;
            const size_t length = variableLength ? 6 : 4;

			for (; i < length; ++i)
			{
                ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return false);

				if (isBetween(ch, '0', '9'))
				{
					ctx.decoder().getChar(0);
                    code = (code << 4) + (ch - '0');
				}
				else if (isBetween(ch, 'a', 'f'))
				{
					ctx.decoder().getChar(0);
                    code = (code << 4) + 10 + (ch - 'a');
				}
				else if (isBetween(ch, 'A', 'F'))
				{
					ctx.decoder().getChar(0);
                    code = (code << 4) + 10 + (ch - 'A');
				}
				else
				{
                    break;
				}
			}

            if (code > 0x10ffff)
            {
                return -1;
            }
            else if (!variableLength && i == 4)
            {
                return code;
            }
            else if (variableLength && i > 0)
            {
                ch = peekNonEof(ctx, ec);
                ECLOG_ON_ERROR(return false);

                if (ch == '}')
                {
                    ctx.decoder().getChar(0);

                    return code;
                }
                else
                {
                    return -2;
                }
            }
            else
            {
                return -3;
            }
		}

		static int parseUnicodeEscapeSequence(Context& ctx, ErrorCode* ec)
		{
			int ch = peekNonEof(ctx, ec);
			ECLOG_ON_ERROR(return 0);

			ECLOG_ASSERT(ch == 'u');

			ctx.decoder().getChar(0);

            const int escapeCharColumn = ctx.column() - 2;

            int code = parseUnicodeHexDigits(ctx, ec);
            ECLOG_ON_ERROR(return 0);

            if (code < 0)
            {
                ECLOG_ERROR(ParseError, ctx.line(), escapeCharColumn, pe_invalid_unicode_escape);
                return 0;
            }

			// surrogate character (U+D800-U+DFFF) ?
			if ((code >> 11) == 0x1b)
			{
				if ((code >> 10) == 0x36)
				{
                    const int high = code;

                    const bool hasNext = skipSequence(ctx, "\\u", ec);
                    ECLOG_ON_ERROR(return 0);

                    if (hasNext)
                    {
                        const int low = parseUnicodeHexDigits(ctx, ec);
                        ECLOG_ON_ERROR(return 0);

                        if ((low >> 10) == 0x37)
                        {
                            code = (((high & 0x3ff) << 10) | (low & 0x3ff)) + 0x10000;

                            return code;
                        }
                    }
				}

                ECLOG_ERROR(ParseError, ctx.line(), escapeCharColumn, pe_invalid_utf16_surrogate);
                return 0;
			}
			else
			{
                return code;
			}
		}

		static void transferDecimalDigits(Context& ctx, ErrorCode* ec)
		{
			int ch = peekNonEof(ctx, ec);
			ECLOG_ON_ERROR(return);

			transferChar(ctx);

			for (;;)
			{
				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				if (isDigit(ch)) {
					transferChar(ctx);
				}
				else {
					return;
				}
			}
		}

		static void transferUnquotedString(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(isAlpha(ch) || ch == '_');

			transferChar(ctx);

			for (;;)
			{
				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				if (isAlpha(ch) || isDigit(ch) || ch == '_' || ch == '-' || ch == '.')
				{
					transferChar(ctx);
				}
				else
				{
					return;
				}
			}
		}

		static void transferQuotedString(Context& ctx, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '"');

			ctx.decoder().getChar(0);

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (ch == '\\')
				{
					ctx.decoder().getChar(0);

					ch = peekNonEof(ctx, ec);
					ECLOG_ON_ERROR(return);

					switch (ch)
					{
					case '\"':
					case '\\':
					case '/':
						transferChar(ctx);
						break;

					case 'b':
						transferChar(ctx, '\b');
						break;

					case 'f':
						transferChar(ctx, '\f');
						break;

					case 'n':
						transferChar(ctx, '\n');
						break;

					case 'r':
						transferChar(ctx, '\r');
						break;

					case 't':
						transferChar(ctx, '\t');
						break;

					case 'u':
						ch = parseUnicodeEscapeSequence(ctx, ec);
						ECLOG_ON_ERROR(return);

                        ctx.buffer().putChar(ch);
						break;

					default:
						ECLOG_ERROR(ParseError, ctx.line(), ctx.column() - 1, pe_unrecognized_escape);
						return;
					}
				}
				else if (ch < 0x20 && ch != '\t')
				{
					ECLOG_ERROR(ParseError, ctx.line(), ctx.column(), pe_unescaped_control_character);
					return;
				}
				else if (ch == '"')
				{
					ctx.decoder().getChar(0);
					return;
				}
				else
				{
					transferChar(ctx);
				}
			}
		}

		static void transferRawString(Context& ctx, bool embedDelimiter, size_t& delimiterSize, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '@');

			ctx.decoder().getChar(0);

			const int delimiterColumn = ctx.column();

			InlineArray<char, 16> delimiter;

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (isAlphanum(ch) || ch == '_')
				{
					if (delimiter.size() < 16)
					{
						ctx.decoder().getChar(0);
						delimiter.pushBack((char)ch);
					}
					else
					{
						ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_string_delimiter_too_long);
						return;
					}
				}
				else
				{
					break;
				}
			}

			if (ch == '"')
			{
				ctx.decoder().getChar(0);
			}
			else
			{
				ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_invalid_string_delimiter);
				return;
			}

			if (embedDelimiter)
			{
				for (size_t i = 0; i < delimiter.size(); ++i)
				{
					ctx.buffer().putChar(delimiter[i]);
				}

				delimiterSize = delimiter.size();
			}
			else
			{
				delimiterSize = 0;
			}

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (ch == '"')
				{
					ctx.decoder().getChar(0);

					size_t m = 0;

					while (m < delimiter.size())
					{
						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == delimiter[m])
						{
							ctx.decoder().getChar(0);
							++m;
						}
						else {
							break;
						}
					}

					if (m == delimiter.size()) {
						return;
					}

					ctx.buffer().putChar('"');

					for (size_t i = 0; i < m; ++i)
					{
						ctx.buffer().putChar(delimiter[i]);
					}
				}
				else if (ch < 0x20 && ch != '\t')
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}
				else
				{
					transferChar(ctx);
				}
			}
		}

        static size_t unindent(char* str, size_t length, int indent)
        {
            const char* first = str;
            const char* last = first + length;

            char* p = str;

            bool beginOfLine = true;
            int n = 0;

            while (first != last)
            {
                if (beginOfLine && (*first == ' ' || *first == '\t') && n < indent)
                {
                    first++;
                    n++;
                }
                else if (*first == '\r' || *first == '\n')
                {
                    if (*first == '\r')
                    {
                        *p++ = *first++;

                        if (first != last && *first == '\n')
                        {
                            *p++ = *first++;
                        }
                    }
                    else if (*first == '\n')
                    {
                        *p++ = *first++;
                    }

                    beginOfLine = true;
                    n = 0;
                }
                else
                {
                    *p++ = *first++;

                    beginOfLine = false;
                }
            }

            return p - str;
        }

		static void transferHeredocString(Context& ctx, bool embedDelimiter, size_t& delimiterSize, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '|');

			ctx.decoder().getChar(0);

			const int delimiterColumn = ctx.column();

			InlineArray<char, 16> delimiter;

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (isAlphanum(ch) || ch == '_')
				{
					if (delimiter.size() < 16)
					{
						ctx.decoder().getChar(0);
						delimiter.pushBack((char)ch);
					}
					else
					{
						ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_string_delimiter_too_long);
						return;
					}
				}
				else
				{
					break;
				}
			}

			ch = peekNonEof(ctx, ec);
			ECLOG_ON_ERROR(return);

			if (ch == '\r' || ch == '\n')
			{
				if (delimiter.size() == 0)
				{
					ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_empty_string_delimiter);
					return;
				}

				skipLinebreak(ctx, ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				ECLOG_ERROR(ParseError, ctx.line(), delimiterColumn, pe_invalid_string_delimiter);
				return;
			}

			if (embedDelimiter)
			{
				for (size_t i = 0; i < delimiter.size(); ++i)
				{
					ctx.buffer().putChar(delimiter[i]);
				}

				delimiterSize = delimiter.size();
			}
			else
			{
				delimiterSize = 0;
			}

			const size_t docBeginPos = ctx.buffer().length();

			size_t lineBeginPos = docBeginPos;

			bool beginOfLine = true;
			int indent = 0;
			int charCount = 0;

			for (;;)
			{
				ch = peekNonEof(ctx, ec);
				ECLOG_ON_ERROR(return);

				if (beginOfLine && (ch == ' ' || ch == '\t'))
				{
					transferChar(ctx);

					++indent;
				}
				else if (beginOfLine && ch == delimiter[0])
				{
					ctx.decoder().getChar(0);

					size_t m = 1;

					while (m < delimiter.size())
					{
						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == delimiter[m])
						{
							ctx.decoder().getChar(0);
							++m;
						}
						else {
							break;
						}
					}

					if (m == delimiter.size())
					{
						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == '\r' || ch == '\n')
						{
							if (indent > 0) {
								ctx.buffer().shrink(lineBeginPos);
							}

							break;
						}
					}

					for (size_t i = 0; i < m; ++i)
					{
						ctx.buffer().putChar(delimiter[i]);
					}
				}
				else if (ch == '\r' || ch == '\n')
				{
					int linebreak = skipLinebreak(ctx, ec);
					ECLOG_ON_ERROR(return);

					writeLinebreak(ctx, linebreak);

					lineBeginPos = ctx.buffer().length();
					beginOfLine = true;
					indent = 0;
					charCount = 0;
				}
				else if (ch < 0x20 && ch != '\t')
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}
				else
				{
					transferChar(ctx);

					beginOfLine = false;
					++charCount;
				}
			}

			if (indent > 0)
			{
				size_t length = unindent(ctx.buffer().address() + docBeginPos,
					ctx.buffer().length() - docBeginPos, indent);

				ctx.buffer().shrink(docBeginPos + length);
			}
		}

		static void transferString(Context& ctx, int& stringNotation, bool embedDelimiter, size_t& delimiterSize, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (isAlpha(ch) || ch == '_')
			{
				transferUnquotedString(ctx, ec);
				ECLOG_ON_ERROR(return);

				stringNotation = string_notation_unquoted;
				delimiterSize = 0;
			}
			else if (ch == '"')
			{
				transferQuotedString(ctx, ec);
				ECLOG_ON_ERROR(return);

				stringNotation = string_notation_quoted;
				delimiterSize = 0;
			}
			else if (ch == '@')
			{
				transferRawString(ctx, embedDelimiter, delimiterSize, ec);
				ECLOG_ON_ERROR(return);

				stringNotation = string_notation_raw;
			}
			else if (ch == '|')
			{
				transferHeredocString(ctx, embedDelimiter, delimiterSize, ec);
				ECLOG_ON_ERROR(return);

				stringNotation = string_notation_heredoc;
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
			}
		}

		static void transferNumber(Context& ctx, int& outNumberInfo, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			ECLOG_ASSERT(ch == '+' || ch == '-' || isDigit(ch));

			enum {
				state_sign,
				state_int,
				state_frac,
				state_exp,
				state_end,
			};

			int state = state_sign;

			for (;;)
			{
				ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				switch (state)
				{
				case state_sign:
					if (ch == '+' || ch == '-')
					{
						outNumberInfo |= number_info_has_sign;

						if (ch == '-') {
							outNumberInfo |= number_info_has_neg_sign;
						}

						transferChar(ctx);

						state = state_int;
						break;
					}
					ECLOG_FALLTHROUGH

				case state_int:
					if (ch == '0')
					{
						transferChar(ctx);
						state = state_frac;
					}
					else if (isBetween(ch, '1', '9'))
					{
						transferDecimalDigits(ctx, ec);
						ECLOG_ON_ERROR(return);

						state = state_frac;
					}
					else if (ch == 'i')
					{
						outNumberInfo |= number_info_inf;

						transferSequence(ctx, "inf", ec);
						ECLOG_ON_ERROR(return);

						state = state_end;
						break;
					}
					else if (ch == 'n')
					{
						outNumberInfo |= number_info_nan;

						transferSequence(ctx, "nan", ec);
						ECLOG_ON_ERROR(return);

						state = state_end;
						break;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;

				case state_frac:
					if (ch == '.')
					{
						outNumberInfo |= number_info_has_frac;

						transferChar(ctx);

						transferDecimalDigits(ctx, ec);
						ECLOG_ON_ERROR(return);

						state = state_exp;
						break;
					}
					ECLOG_FALLTHROUGH

				case state_exp:
					if (ch == 'e' || ch == 'E')
					{
						outNumberInfo |= number_info_has_exp;

						transferChar(ctx);

						ch = peekNonEof(ctx, ec);
						ECLOG_ON_ERROR(return);

						if (ch == '+' || ch == '-')
						{
							transferChar(ctx);

							ch = peekNonEof(ctx, ec);
							ECLOG_ON_ERROR(return);
						}

						if (ch == '0')
						{
							transferChar(ctx);
						}
						else if (isBetween(ch, '1', '9'))
						{
							transferDecimalDigits(ctx, ec);
							ECLOG_ON_ERROR(return);
						}
						else
						{
							onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
							return;
						}

						state = state_end;
						break;
					}

				case state_end:
					return;
				}
			}
		}

		static void parseKeyValuePairList(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			enum {
				state_key,
				state_key2,
				state_key_separator,
				state_value,
				state_value2,
				state_next,
				state_keyword_or_string,
				state_keyword_or_string2,
				state_keyword_or_string3,
			};

			enum {
				keyword_true = 1,
				keyword_false,
				keyword_inf,
				keyword_nan,
				keyword_null
			};

			ParsingBufferGuard<2> parsingBufferGuard(ctx.buffer());

			InlineStack<int, 2> state;

			int line = 0;
			int column = 0;

			int keyword = 0;

			int stringNotation = 0;
			size_t delimiterSize = 0;

			int lineOfLastValue = 0;

			state.push(state_key);

			for (;;)
			{
				skipWhitespaceAndComments(ctx, ec);
				ECLOG_ON_ERROR(return);

				int ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				switch (state.top())
				{
				case state_key:
					if (isAlpha(ch) || ch == '_' || ch == '"' || ch == '@' || ch == '|')
					{
						parsingBufferGuard.push();

						line = ctx.line();
						column = ctx.column();

						state.top() = state_key2;
						state.push(state_keyword_or_string);
					}
					else
					{
						return;
					}
					break;

				case state_key2:
					if (!keyword)
					{
						handler.onKey(Key(ctx.buffer().str(), (StringNotation)stringNotation, delimiterSize), ec);
						ECLOG_ON_ERROR(return);

						state.top() = state_key_separator;;
					}
					else
					{
						ECLOG_ERROR(ParseError, line, column, pe_invalid_key);
						return;
					}
					break;

				case state_key_separator:
					if (ch == ':')
					{
						ctx.decoder().getChar(0);

						state.top() = state_value;;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;

				case state_value:
					if (isAlpha(ch) || ch == '_' || ch == '"' || ch == '@' || ch == '|')
					{
						parsingBufferGuard.push();

						state.top() = state_value2;
						state.push(state_keyword_or_string);
					}
					else if (ch == '+' || ch == '-' || isDigit(ch))
					{
						parsingBufferGuard.push();

						int numberInfo = 0;

						transferNumber(ctx, numberInfo, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						handler.onValue(Value(value_type_number, ctx.buffer().str(), (NumberInfo)numberInfo), ec);
						ECLOG_ON_ERROR(return);

						state.top() = state_next;
					}
					else if (ch == '{')
					{
						handler.onValue(Value(value_type_object), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else if (ch == '[')
					{
						handler.onValue(Value(value_type_array), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;

				case state_value2:
					switch (keyword)
					{
					case keyword_true:
					case keyword_false:
						handler.onValue(Value(value_type_boolean, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_inf:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_inf), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_nan:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_nan), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_null:
						handler.onValue(Value(value_type_null, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					default:
						handler.onValue(Value(value_type_string, ctx.buffer().str(), (StringNotation)stringNotation, delimiterSize), ec);
						ECLOG_ON_ERROR(return);
						break;
					}

					state.top() = state_next;
					break;

				case state_next:
					if (ch == ',')
					{
						ctx.decoder().getChar(0);

						parsingBufferGuard.clear();

						state.top() = state_key;
					}
					else if (ctx.line() > lineOfLastValue)
					{
						parsingBufferGuard.clear();

						state.top() = state_key;
					}
					else
					{
						return;
					}
					break;

				case state_keyword_or_string:
					keyword = 0;

					transferString(ctx, stringNotation, true, delimiterSize, ec);
					ECLOG_ON_ERROR(return);

					lineOfLastValue = ctx.line();

					if (stringNotation == string_notation_unquoted)
					{
						if (ctx.buffer().str() == "true") {
							keyword = keyword_true;
						}
						else if (ctx.buffer().str() == "false") {
							keyword = keyword_false;
						}
						else if (ctx.buffer().str() == "inf") {
							keyword = keyword_inf;
						}
						else if (ctx.buffer().str() == "nan") {
							keyword = keyword_nan;
						}
						else if (ctx.buffer().str() == "null") {
							keyword = keyword_null;
						}

						state.pop();
					}
					else
					{
						state.top() = state_keyword_or_string2;
					}
					break;

				case state_keyword_or_string2:
					if (ch == '+')
					{
						ctx.decoder().getChar(0);

						state.top() = state_keyword_or_string3;
					}
					else
					{
						state.pop();
					}
					break;

				case state_keyword_or_string3:
					if (ch == '"' || ch == '@' || ch == '|')
					{
						int n;
						size_t d;

						transferString(ctx, n, false, d, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_keyword_or_string2;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;
				};
			}
		}

		static void parseValueList(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			enum {
				state_value,
				state_value2,
				state_next,
				state_keyword_or_string,
				state_keyword_or_string2,
				state_keyword_or_string3,
			};

			enum {
				keyword_true = 1,
				keyword_false,
				keyword_inf,
				keyword_nan,
				keyword_null
			};

			ParsingBufferGuard<2> parsingBufferGuard(ctx.buffer());

			InlineStack<int, 2> state;

			int keyword = 0;

			int stringNotation = 0;
			size_t delimiterSize = 0;

			int lineOfLastValue = 0;

			state.push(state_value);

			for (;;)
			{
				skipWhitespaceAndComments(ctx, ec);
				ECLOG_ON_ERROR(return);

				int ch = ctx.decoder().peekChar(ec);
				ECLOG_ON_ERROR(return);

				switch (state.top())
				{
				case state_value:
					if (isAlpha(ch) || ch == '_' || ch == '"' || ch == '@' || ch == '|')
					{
						parsingBufferGuard.push();

						state.top() = state_value2;
						state.push(state_keyword_or_string);
					}
					else if (ch == '+' || ch == '-' || isDigit(ch))
					{
						parsingBufferGuard.push();

						int numberInfo = 0;

						transferNumber(ctx, numberInfo, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						handler.onValue(Value(value_type_number, ctx.buffer().str(), (NumberInfo)numberInfo), ec);
						ECLOG_ON_ERROR(return);

						state.top() = state_next;
					}
					else if (ch == '{')
					{
						handler.onValue(Value(value_type_object), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else if (ch == '[')
					{
						handler.onValue(Value(value_type_array), ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_next;
					}
					else
					{
						return;
					}
					break;

				case state_value2:
					switch (keyword)
					{
					case keyword_true:
					case keyword_false:
						handler.onValue(Value(value_type_boolean, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_inf:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_inf), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_nan:
						handler.onValue(Value(value_type_number, ctx.buffer().str(), number_info_nan), ec);
						ECLOG_ON_ERROR(return);
						break;

					case keyword_null:
						handler.onValue(Value(value_type_null, ctx.buffer().str()), ec);
						ECLOG_ON_ERROR(return);
						break;

					default:
						handler.onValue(Value(value_type_string, ctx.buffer().str(), (StringNotation)stringNotation, delimiterSize), ec);
						ECLOG_ON_ERROR(return);
						break;
					}

					state.top() = state_next;
					break;

				case state_next:
					if (ch == ',')
					{
						ctx.decoder().getChar(0);

						parsingBufferGuard.clear();

						state.top() = state_value;
					}
					else if (ctx.line() > lineOfLastValue)
					{
						parsingBufferGuard.clear();

						state.top() = state_value;
					}
					else
					{
						return;
					}
					break;

				case state_keyword_or_string:
					keyword = 0;

					transferString(ctx, stringNotation, true, delimiterSize, ec);
					ECLOG_ON_ERROR(return);

					lineOfLastValue = ctx.line();

					if (stringNotation == string_notation_unquoted)
					{
						if (ctx.buffer().str() == "true") {
							keyword = keyword_true;
						}
						else if (ctx.buffer().str() == "false") {
							keyword = keyword_false;
						}
						else if (ctx.buffer().str() == "inf") {
							keyword = keyword_inf;
						}
						else if (ctx.buffer().str() == "nan") {
							keyword = keyword_nan;
						}
						else if (ctx.buffer().str() == "null") {
							keyword = keyword_null;
						}

						state.pop();
					}
					else
					{
						state.top() = state_keyword_or_string2;
					}
					break;

				case state_keyword_or_string2:
					if (ch == '+')
					{
						ctx.decoder().getChar(0);

						state.top() = state_keyword_or_string3;
					}
					else
					{
						state.pop();
					}
					break;

				case state_keyword_or_string3:
					if (ch == '"' || ch == '@' || ch == '|')
					{
						int n;
						size_t d;

						transferString(ctx, n, false, d, ec);
						ECLOG_ON_ERROR(return);

						lineOfLastValue = ctx.line();

						state.top() = state_keyword_or_string2;
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
					break;
				};
			}
		}

		void parseObject(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			enum {
				flag_none = 0,
				flag_root_object = 1 << 0,
				flag_curly_bracket = 1 << 1,
			};

			int flag = flag_none;

			if (ctx.decoder().position() == 0) {
				flag |= flag_root_object;
			}

			if (flag & flag_root_object)
			{
				skipWhitespaceAndComments(ctx, ec);
				ECLOG_ON_ERROR(return);
			}

			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch == '{')
			{
				ctx.decoder().getChar(0);

				flag |= flag_curly_bracket;

				handler.onObjectBegin(ec);
				ECLOG_ON_ERROR(return);

				if (!(flag & flag_root_object)) {
					ctx.beginNested();
				}
			}
			else if (flag & flag_root_object)
			{
				handler.onObjectBegin(ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}

			parseKeyValuePairList(ctx, handler, ec);
			ECLOG_ON_ERROR(return);

			skipWhitespaceAndComments(ctx, ec);
			ECLOG_ON_ERROR(return);

			ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (flag & flag_root_object)
			{
				if (flag & flag_curly_bracket)
				{
					if (ch == '}')
					{
						ctx.decoder().getChar(0);

						handler.onObjectEnd(ec);
						ECLOG_ON_ERROR(return);

						skipWhitespaceAndComments(ctx, ec);
						ECLOG_ON_ERROR(return);

						ch = ctx.decoder().peekChar(ec);
						ECLOG_ON_ERROR(return);

						if (ch >= 0)
						{
							onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
							return;
						}
					}
					else
					{
						onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
						return;
					}
				}
				else if (ch < 0)
				{
					handler.onObjectEnd(ec);
					ECLOG_ON_ERROR(return);
				}
				else
				{
					onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
					return;
				}
			}
			else if (ch == '}')
			{
				ctx.decoder().getChar(0);

				handler.onObjectEnd(ec);
				ECLOG_ON_ERROR(return);

				ctx.endNested();
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}
		}

		void parseArray(Context& ctx, ParseHandler& handler, ErrorCode* ec)
		{
			int ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch == '[')
			{
				ctx.decoder().getChar(0);

				handler.onArrayBegin(ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}

			ctx.beginNested();

			parseValueList(ctx, handler, ec);
			ECLOG_ON_ERROR(return);

			skipWhitespaceAndComments(ctx, ec);
			ECLOG_ON_ERROR(return);

			ch = ctx.decoder().peekChar(ec);
			ECLOG_ON_ERROR(return);

			if (ch == ']')
			{
				ctx.decoder().getChar(0);

				handler.onArrayEnd(ec);
				ECLOG_ON_ERROR(return);
			}
			else
			{
				onUnexpectedChar(ctx.line(), ctx.column(), ch, ec);
				return;
			}

			ctx.endNested();
		}

	} // detail

} // eclog

