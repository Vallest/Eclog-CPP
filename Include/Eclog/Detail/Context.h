// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_CONTEXT_H_
#define ECLOG_CPP_DETAIL_CONTEXT_H_

#include <Eclog/ParsingBuffer.h>
#include <Eclog/Detail/UTF8Decoder.h>
#include <Eclog/Detail/NonCopyable.h>

namespace vallest {
namespace eclog {
namespace detail {

	class Context : private NonCopyable {
	public:
		explicit Context(InputStream& stream, ParsingBuffer& buffer) :
			decoder_(stream), buffer_(buffer),
			line_(1), lineBeginPos_(0), nestingLevel_(0),
			terminated_(false)
		{
		}

		UTF8Decoder& decoder()
		{
			return decoder_;
		}

		ParsingBuffer& buffer()
		{
			return buffer_;
		}

		void addLine()
		{
			lineBeginPos_ = decoder_.position();
			++line_;
		}

		int line() const
		{
			return line_;
		}

		int column() const
		{
			return (int)(decoder_.position() - lineBeginPos_) + 1;
		}

		void beginNested()
		{
			++nestingLevel_;
		}

		void endNested()
		{
			--nestingLevel_;
		}

		int nestingLevel() const
		{
			return nestingLevel_;
		}

		void terminate()
		{
			terminated_ = true;
		}

		bool terminated() const
		{
			return terminated_;
		}

	private:
		UTF8Decoder decoder_;
		ParsingBuffer& buffer_;

		int line_;
		long long lineBeginPos_;

		int nestingLevel_;

		bool terminated_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_CONTEXT_H_

