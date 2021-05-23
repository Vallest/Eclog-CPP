// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_RENDERER_H_
#define ECLOG_CPP_DETAIL_RENDERER_H_

#include <Eclog/RendererConfig.h>
#include <Eclog/KeyDesc.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/NumberDesc.h>
#include <Eclog/StringDesc.h>
#include <Eclog/Error.h>
#include <Eclog/OutputStream.h>
#include <Eclog/Detail/UTF8Encoder.h>
#include <Eclog/Detail/NonCopyable.h>

namespace eclog {

	namespace detail {

		class Renderer : private NonCopyable {
		private:
			enum {
				separator_linebreak = 1,
				separator_comma,
			};

		public:
			explicit Renderer(OutputStream& stream, const RendererConfig& rendererConfig);

			void beginObject(const KeyDesc& key, ErrorCode* ec);
			void beginObject(ErrorCode* ec);
			void endObject(ErrorCode* ec);

			void beginArray(const KeyDesc& key, ErrorCode* ec);
			void beginArray(ErrorCode* ec);
			void endArray(ErrorCode* ec);

			void renderMember(const KeyDesc& key, const ValueDesc& value, ErrorCode* ec);
			void renderMember(const ValueDesc& value, ErrorCode* ec);

			void renderEmptyLines(int count, ErrorCode* ec);

			void renderComment(cstring comment, ErrorCode* ec);

			int beginInline();
			int endInline();

			void close(ErrorCode* ec);

			const RendererConfig& rendererConfig() const;

		private:
			void beginItem(ErrorCode* ec);
			void endItem();

			void beginStruct(ErrorCode* ec);
			void endStruct(ErrorCode* ec);

			void renderValueInternal(const ValueDesc& value, ErrorCode* ec);

			void renderString(cstring str, StringNotation notation, cstring delimiter, ErrorCode* ec);

			void renderQuotedString(cstring str, ErrorCode* ec);
			void renderUnquotedString(cstring str, ErrorCode* ec);
			void renderRawString(cstring str, cstring delimiter, ErrorCode* ec);
			void renderHeredoc(cstring str, cstring delimiter, ErrorCode* ec);

			void renderNumber(const Number& number, int fracDigits, ErrorCode* ec);

			void renderLinebreak(ErrorCode* ec);
			void renderIndent(ErrorCode* ec);
			void renderSeparator(ErrorCode* ec);
			void renderSpace(ErrorCode* ec);
			void renderLeftCurlyBracket(ErrorCode* ec);
			void renderRightCurlyBracket(ErrorCode* ec);
			void renderLeftSquareBracket(ErrorCode* ec);
			void renderRightSquareBracket(ErrorCode* ec);
			void renderColon(ErrorCode* ec);
			void renderComma(ErrorCode* ec);
			void renderSequence(cstring s, ErrorCode* ec);
			void renderChar(int ch, ErrorCode* ec);

			void increaseNestingLevel();
			void decreaseNestingLevel();
			int nestingLevel() const;

			void increaseIndent();
			void decreaseIndent();
			int indent() const;

			void setError(int error = 1);
			int error() const;

		private:
			UTF8Encoder encoder_;
			RendererConfig rc_;

			int nestingLevel_;
			int indent_;
			bool beginOfLine_;
			int separator_;
			int inline_;

			int error_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_RENDERER_H_

