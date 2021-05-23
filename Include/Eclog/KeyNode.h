// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_KEYNODE_H_
#define ECLOG_CPP_KEYNODE_H_

#include <Eclog/Node.h>
#include <Eclog/KeyDesc.h>
#include <Eclog/cstring.h>
#include <Eclog/StringNotation.h>
#include <Eclog/Error.h>

namespace eclog {

	class KeyNode : public Node {
	protected:
		~KeyNode() {} // prevents calling delete

	public:
		virtual cstring str() const = 0;

		virtual void setNotation(StringNotation notation) = 0;
		virtual StringNotation notation() const = 0;

		virtual void setDelimiter(cstring delimiter) = 0;
		virtual void setDelimiter(cstring delimiter, ErrorCode& ec) = 0;
		virtual cstring delimiter() const = 0;
	};

} // eclog

#endif // ECLOG_CPP_KEYNODE_H_

