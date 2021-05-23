// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_NUMBERNODEIMPL_H_
#define ECLOG_CPP_DETAIL_NUMBERNODEIMPL_H_

#include <Eclog/NumberNode.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/Assert.h>

namespace eclog {

	namespace detail {

		class NumberNodeImpl : public NumberNode, private NonCopyable {
		public:
			explicit NumberNodeImpl(const ValueDesc& desc) :
				value_(desc.number()),
				fracDigits_(desc.fracDigits())
			{
			}

			explicit NumberNodeImpl(const NumberNode& other)
			{
				assign(other);
			}

		public:
			virtual NodeType nodeType() const ECLOG_OVERRIDE
			{
				return node_type_number;
			}

			virtual Number value() const ECLOG_OVERRIDE
			{
				return value_;
			}

			virtual void setFracDigits(int fracDigits) ECLOG_OVERRIDE
			{
				fracDigits_ = fracDigits;
			}

			virtual int fracDigits() const ECLOG_OVERRIDE
			{
				return fracDigits_;
			}

			virtual void assign(const NumberDesc& desc) ECLOG_OVERRIDE
			{
				value_ = desc.number();
				fracDigits_ = desc.fracDigits();
			}

			virtual void assign(const NumberNode& other) ECLOG_OVERRIDE
			{
				if (&other == this) {
					return;
				}

				value_ = other.value();
				fracDigits_ = other.fracDigits();
			}

		private:
			Number value_;

			int fracDigits_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_NUMBERNODEIMPL_H_

