// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NODETYPE_H_
#define ECLOG_CPP_NODETYPE_H_

namespace vallest {
namespace eclog {

	enum NodeType {
		node_type_key,
		node_type_null,
		node_type_boolean,
		node_type_string,
		node_type_number,
		node_type_object,
		node_type_array,
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_NODETYPE_H_

