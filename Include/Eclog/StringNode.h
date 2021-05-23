// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_STRINGNODE_H_
#define ECLOG_CPP_STRINGNODE_H_

#include <Eclog/ValueNode.h>
#include <Eclog/StringDesc.h>
#include <Eclog/cstring.h>
#include <Eclog/StringNotation.h>

namespace eclog {

	class StringNode : public ValueNode {
	protected:
		~StringNode() {} // prevents calling delete

	public:
		virtual cstring value() const = 0;

		virtual void setNotation(StringNotation notation) = 0;
		virtual StringNotation notation() const = 0;

		virtual void setDelimiter(cstring delimiter) = 0;
		virtual void setDelimiter(cstring delimiter, ErrorCode& ec) = 0;
		virtual cstring delimiter() const = 0;

		virtual void assign(const StringDesc& desc) = 0;
		virtual void assign(const StringNode& other) = 0;
	};

} // eclog

#endif // ECLOG_CPP_STRINGNODE_H_

