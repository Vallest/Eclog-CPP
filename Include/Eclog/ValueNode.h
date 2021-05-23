// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_VALUENODE_H_
#define ECLOG_CPP_VALUENODE_H_

#include <Eclog/Node.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/Error.h>

namespace eclog {

	class NullNode;
	class BooleanNode;
	class StringNode;
	class NumberNode;
	class ObjectNode;
	class ArrayNode;

	class ValueNode : public Node {
	protected:
		~ValueNode() {} // prevents calling delete

	public:
		bool isNull() const
		{
			return (nodeType() == node_type_null);
		}

		bool isBoolean() const
		{
			return (nodeType() == node_type_boolean);
		}

		bool isString() const
		{
			return (nodeType() == node_type_string);
		}

		bool isNumber() const
		{
			return (nodeType() == node_type_number);
		}

		bool isObject() const
		{
			return (nodeType() == node_type_object);
		}

		bool isArray() const
		{
			return (nodeType() == node_type_array);
		}

		NullNode& asNull()
		{
			if (!isNull()) {
				ECLOG_FAULT(BadCast);
			}

			return *(NullNode*)this;
		}

		BooleanNode& asBoolean()
		{
			if (!isBoolean()) {
				ECLOG_FAULT(BadCast);
			}

			return *(BooleanNode*)this;
		}

		StringNode& asString()
		{
			if (!isString()) {
				ECLOG_FAULT(BadCast);
			}

			return *(StringNode*)this;
		}

		NumberNode& asNumber()
		{
			if (!isNumber()) {
				ECLOG_FAULT(BadCast);
			}

			return *(NumberNode*)this;
		}

		ObjectNode& asObject()
		{
			if (!isObject()) {
				ECLOG_FAULT(BadCast);
			}

			return *(ObjectNode*)this;
		}

		ArrayNode& asArray()
		{
			if (!isArray()) {
				ECLOG_FAULT(BadCast);
			}

			return *(ArrayNode*)this;
		}

		const NullNode& asNull() const
		{
			if (!isNull()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const NullNode*)this;
		}

		const BooleanNode& asBoolean() const
		{
			if (!isBoolean()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const BooleanNode*)this;
		}

		const StringNode& asString() const
		{
			if (!isString()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const StringNode*)this;
		}

		const NumberNode& asNumber() const
		{
			if (!isNumber()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const NumberNode*)this;
		}

		const ObjectNode& asObject() const
		{
			if (!isObject()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const ObjectNode*)this;
		}

		const ArrayNode& asArray() const
		{
			if (!isArray()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const ArrayNode*)this;
		}
	};

} // eclog

#endif // ECLOG_CPP_VALUENODE_H_

