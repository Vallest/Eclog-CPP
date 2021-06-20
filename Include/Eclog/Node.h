// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NODE_H_
#define ECLOG_CPP_NODE_H_

#include <Eclog/NodeType.h>

namespace vallest {
namespace eclog {

	class Node {
	protected:
		~Node() {} // prevents calling delete

	public:
		virtual NodeType nodeType() const = 0;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_NODE_H_

