// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_BOOLEANNODEIMPL_H_
#define ECLOG_CPP_DETAIL_BOOLEANNODEIMPL_H_

#include <Eclog/BooleanNode.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>

namespace eclog {

	namespace detail {

		class BooleanNodeImpl : public BooleanNode, private NonCopyable {
		public:
			explicit BooleanNodeImpl(const ValueDesc& desc) :
				value_(desc.boolean())
			{
			}

			explicit BooleanNodeImpl(const BooleanNode& other) :
				value_(other.value())
			{
			}

		public:
			virtual NodeType nodeType() const ECLOG_OVERRIDE
			{
				return node_type_boolean;
			}

			virtual bool value() const ECLOG_OVERRIDE
			{
				return value_;
			}

			virtual void assign(bool value) ECLOG_OVERRIDE
			{
				value_ = value;
			}

			virtual void assign(const BooleanNode& other) ECLOG_OVERRIDE
			{
				if (&other == this) {
					return;
				}

				value_ = other.value();
			}

		private:
			bool value_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_BOOLEANNODEIMPL_H_

