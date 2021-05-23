// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NUMBERNODE_H_
#define ECLOG_CPP_NUMBERNODE_H_

#include <Eclog/ValueNode.h>
#include <Eclog/NumberDesc.h>
#include <Eclog/Number.h>

namespace eclog {

	class NumberNode : public ValueNode {
	protected:
		~NumberNode() {} // prevents calling delete

	public:
		virtual Number value() const = 0;

		double valueDouble() const;
		int valueInt() const;
		unsigned int valueUInt() const;
		long valueLong() const;
		unsigned long valueULong() const;
		long long valueLLong() const;
		unsigned long long valueULLong() const;

		virtual void setFracDigits(int fracDigits) = 0;
		virtual int fracDigits() const = 0;

		virtual void assign(const NumberDesc& desc) = 0;
		virtual void assign(const NumberNode& other) = 0;
	};

	inline double NumberNode::valueDouble() const
	{
		return value().load<double>();
	}

	inline int NumberNode::valueInt() const
	{
		return value().load<int>();
	}

	inline unsigned int NumberNode::valueUInt() const
	{
		return value().load<unsigned int>();
	}

	inline long NumberNode::valueLong() const
	{
		return value().load<long>();
	}

	inline unsigned long NumberNode::valueULong() const
	{
		return value().load<unsigned long>();
	}

	inline long long NumberNode::valueLLong() const
	{
		return value().load<long long>();
	}

	inline unsigned long long NumberNode::valueULLong() const
	{
		return value().load<unsigned long long>();
	}

} // eclog

#endif // ECLOG_CPP_NUMBERNODE_H_

