// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_KEYNODEIMPL_H_
#define ECLOG_CPP_DETAIL_KEYNODEIMPL_H_

#include <Eclog/KeyNode.h>
#include <Eclog/KeyDesc.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/ByteArray.h>
#include <Eclog/Detail/StringDelimiter.h>
#include <Eclog/Detail/CompilerSpecific.h>

namespace eclog {

	namespace detail {

		template<typename Alloc>
		class KeyNodeImpl : public KeyNode {
		public:
			explicit KeyNodeImpl(const eclog::KeyDesc& desc) :
				str_(((const KeyDesc&)desc).str()),
				notation_(((const KeyDesc&)desc).notation()),
				delimiter_(((const KeyDesc&)desc).delimiter())
			{
			}

			explicit KeyNodeImpl(const KeyNode& other) :
				str_(other.str()),
				notation_(other.notation()),
				delimiter_(other.delimiter())
			{
			}

		public:
			virtual NodeType nodeType() const ECLOG_OVERRIDE
			{
				return node_type_key;
			}

			virtual cstring str() const ECLOG_OVERRIDE
			{
				return str_.str();
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
			ByteArray<Alloc> str_;

			StringNotation notation_;
			ByteArray<Alloc> delimiter_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_KEYNODEIMPL_H_

