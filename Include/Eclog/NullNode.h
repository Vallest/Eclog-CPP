// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NULLNODE_H_
#define ECLOG_CPP_NULLNODE_H_

#include <Eclog/ValueNode.h>
#include <Eclog/Null.h>

namespace vallest {
namespace eclog {

	class NullNode : public ValueNode {
	protected:
		~NullNode() {} // prevents calling delete

	public:
		virtual Null value() const = 0;

		virtual void assign(const Null&) = 0;
		virtual void assign(const NullNode&) = 0;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_NULLNODE_H_

