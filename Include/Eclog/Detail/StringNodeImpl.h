// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_STRINGNODEIMPL_H_
#define ECLOG_CPP_DETAIL_STRINGNODEIMPL_H_

#include <Eclog/StringNode.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/ByteArray.h>
#include <Eclog/Detail/StringDelimiter.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>

namespace eclog {

	namespace detail {

		template<typename Alloc>
		class StringNodeImpl : public StringNode, private NonCopyable {
		public:
			explicit StringNodeImpl(const ValueDesc& desc) :
				value_(desc.string()),
				notation_(desc.stringNotation()),
				delimiter_(desc.stringDelimiter())
			{
			}

			explicit StringNodeImpl(const StringNode& other) :
				value_(other.value()),
				notation_(other.notation()),
				delimiter_(other.delimiter())
			{
			}

		public:
			virtual NodeType nodeType() const ECLOG_OVERRIDE
			{
				return node_type_string;
			}

			virtual cstring value() const ECLOG_OVERRIDE
			{
				return value_.str();
			}

			virtual void setNotation(StringNotation notation) ECLOG_OVERRIDE
			{
				notation_ = notation;
			}

			virtual StringNotation notation() const ECLOG_OVERRIDE
			{
				return notation_;
			}

			virtual void setDelimiter(cstring delimiter) ECLOG_OVERRIDE
			{
				setDelimiter(delimiter, 0);
			}

			virtual void setDelimiter(cstring delimiter, ErrorCode& ec) ECLOG_OVERRIDE
			{
				setDelimiter(delimiter, &ec);
			}

			virtual cstring delimiter() const ECLOG_OVERRIDE
			{
				return delimiter_.str();
			}

			virtual void assign(const StringDesc& desc) ECLOG_OVERRIDE
			{
				ByteArray<Alloc> value(desc.string());
				ByteArray<Alloc> delimiter(desc.stringDelimiter());

				swap(value_, value);
				swap(delimiter_, delimiter);

				notation_ = desc.stringNotation();
			}

			virtual void assign(const StringNode& other) ECLOG_OVERRIDE
			{
				if (&other == this) {
					return;
				}

				ByteArray<Alloc> value(other.value());
				ByteArray<Alloc> delimiter(other.delimiter());

				swap(value_, value);
				swap(delimiter_, delimiter);

				notation_ = other.notation();
			}

		private:
			void setDelimiter(cstring delimiter, ErrorCode* ec)
			{
				if (!StringDelimiter::validate(delimiter))
				{
					ECLOG_ERROR(InvalidArgument);
					return;
				}

				delimiter_ = delimiter;
			}

		private:
			ByteArray<Alloc> value_;

			StringNotation notation_;
			ByteArray<Alloc> delimiter_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_STRINGNODEIMPL_H_

