// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_DOCUMENTPARSEHANDLER_H_
#define ECLOG_CPP_DETAIL_DOCUMENTPARSEHANDLER_H_

#include <Eclog/ObjectNode.h>
#include <Eclog/ArrayNode.h>
#include <Eclog/Key.h>
#include <Eclog/Value.h>
#include <Eclog/KeyDesc.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/Detail/PODArray.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/Assert.h>

#include <limits.h>

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Alloc>
	class DocumentParseHandler : private NonCopyable {
	public:
		explicit DocumentParseHandler(ObjectNode& root) : root_(root), hasKey_(false)
		{
		}

	public:
		void onObjectBegin()
		{
			if (hasKey_)
			{
				currentObject().appendForce(makeDesc(key_), empty_object);

				push(currentObject().last().value());

				hasKey_ = false;
			}
			else if (!stack_.empty())
			{
				currentArray().append(empty_object);

				push(currentArray().last().value());
			}
			else
			{
				push(root_);
			}
		}

		void onObjectEnd()
		{
			pop();
		}

		void onArrayBegin()
		{
			if (hasKey_)
			{
				currentObject().appendForce(makeDesc(key_), empty_array);

				push(currentObject().last().value());

				hasKey_ = false;
			}
			else
			{
				currentArray().append(empty_array);

				push(currentArray().last().value());
			}
		}

		void onArrayEnd()
		{
			pop();
		}

		void onKey(const Key& key)
		{
			key_ = key;

			hasKey_ = true;
		}

		void onValue(const Value& value)
		{
			if (hasKey_)
			{
				currentObject().appendForce(makeDesc(key_), makeDesc(value));

				hasKey_ = false;
			}
			else
			{
				currentArray().append(makeDesc(value));
			}
		}

	private:
		void push(ValueNode& node)
		{
			stack_.pushBack(&node);
		}

		void pop()
		{
			stack_.popBack();
		}

		ObjectNode& currentObject()
		{
			return *(ObjectNode*)stack_.back();
		}

		ArrayNode& currentArray()
		{
			return *(ArrayNode*)stack_.back();
		}

	private:
		static KeyDesc makeDesc(const Key& key)
		{
			return KeyDesc(key, key.notation(), key.delimiter());
		}

		static ValueDesc makeDesc(const Value& value)
		{
			switch (value.type())
			{
			case value_type_null:
				return ValueDesc(null);

			case value_type_boolean:
				return ValueDesc(value.asBoolean());

			case value_type_string:
				return ValueDesc(value.asString(), value.stringNotation(), value.stringDelimiter());

			case value_type_number:
				return ValueDesc(value.asNumber());

			default:
				ECLOG_ASSERT(false);
				return ValueDesc(null);
			}
		}

	private:
		ObjectNode& root_;

		bool hasKey_;
		Key key_;

		PODArray<void*, Alloc> stack_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_DOCUMENTPARSEHANDLER_H_

