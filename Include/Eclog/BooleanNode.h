// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_BOOLEANNODE_H_
#define ECLOG_CPP_BOOLEANNODE_H_

#include <Eclog/ValueNode.h>

namespace eclog {

	class BooleanNode : public ValueNode {
	protected:
		~BooleanNode() {} // prevents calling delete

	public:
		virtual bool value() const = 0;

		virtual void assign(bool value) = 0;
		virtual void assign(const BooleanNode& other) = 0;
	};

} // eclog

#endif // ECLOG_CPP_BOOLEANNODE_H_

