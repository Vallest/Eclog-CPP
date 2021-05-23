// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_NULLNODEIMPL_H_
#define ECLOG_CPP_DETAIL_NULLNODEIMPL_H_

#include <Eclog/NullNode.h>
#include <Eclog/Detail/NonCopyable.h>

namespace eclog {

	namespace detail {

		class NullNodeImpl : public NullNode, private NonCopyable {
		public:
			virtual NodeType nodeType() const ECLOG_OVERRIDE
			{
				return node_type_null;
			}

			virtual Null value() const ECLOG_OVERRIDE
			{
				return null;
			}

			virtual void assign(const Null&) ECLOG_OVERRIDE
			{
			}

			virtual void assign(const NullNode&) ECLOG_OVERRIDE
			{
			}
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_NULLNODEIMPL_H_

