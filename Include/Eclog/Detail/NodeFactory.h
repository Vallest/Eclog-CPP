// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_NODEFACTORY_H_
#define ECLOG_CPP_DETAIL_NODEFACTORY_H_

#include <Eclog/KeyNode.h>
#include <Eclog/ValueNode.h>
#include <Eclog/KeyDesc.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/Detail/KeyNodeImpl.h>
#include <Eclog/Detail/NullNodeImpl.h>
#include <Eclog/Detail/BooleanNodeImpl.h>
#include <Eclog/Detail/StringNodeImpl.h>
#include <Eclog/Detail/NumberNodeImpl.h>
#include <Eclog/Detail/ObjectNodeImpl.h>
#include <Eclog/Detail/ArrayNodeImpl.h>
#include <Eclog/Detail/Memory.h>
#include <Eclog/Detail/Assert.h>

namespace eclog {

	namespace detail {

		template<typename Alloc>
		class NodeFactory {
		public:
			typedef Alloc AllocType;

		private:
			typedef KeyNodeImpl<Alloc> KeyNodeType;
			typedef NullNodeImpl NullNodeType;
			typedef BooleanNodeImpl BooleanNodeType;
			typedef StringNodeImpl<Alloc> StringNodeType;
			typedef NumberNodeImpl NumberNodeType;
			typedef ObjectNodeImpl<NodeFactory> ObjectNodeType;
			typedef ArrayNodeImpl<NodeFactory> ArrayNodeType;

		public:
			static KeyNode* create(const KeyNode& key)
			{
				return detail::create<KeyNodeType, Alloc>(key);
			}

			static KeyNode* create(const eclog::KeyDesc& key)
			{
				return detail::create<KeyNodeType, Alloc>(key);
			}

			static ValueNode* create(const ValueNode& value)
			{
				switch (value.nodeType())
				{
				case node_type_null:
					return detail::create<NullNodeType, Alloc>();

				case node_type_boolean:
					return detail::create<BooleanNodeType, Alloc>((const BooleanNode&)value);

				case node_type_string:
					return detail::create<StringNodeType, Alloc>((const StringNode&)value);

				case node_type_number:
					return detail::create<NumberNodeType, Alloc>((const NumberNode&)value);

				case node_type_object:
					return detail::create<ObjectNodeType, Alloc>((const ObjectNode&)value);

				case node_type_array:
					return detail::create<ArrayNodeType, Alloc>((const ArrayNode&)value);

				default:
					ECLOG_ASSERT(false);
					return 0;
				}
			}

			static ValueNode* create(const ValueDesc& desc)
			{
				switch (desc.type())
				{
				case value_type_null:
					return detail::create<NullNodeType, Alloc>();

				case value_type_boolean:
					return detail::create<BooleanNodeType, Alloc>(desc);

				case value_type_string:
					return detail::create<StringNodeType, Alloc>(desc);

				case value_type_number:
					return detail::create<NumberNodeType, Alloc>(desc);

				case value_type_object:
					return detail::create<ObjectNodeType, Alloc>(desc);

				case value_type_array:
					return detail::create<ArrayNodeType, Alloc>(desc);

				default:
					ECLOG_ASSERT(false);
					return 0;
				}
			}

			static void destroy(Node* ptr)
			{
				switch (ptr->nodeType())
				{
				case node_type_key:
					detail::destroy<KeyNodeType, Alloc>((KeyNodeType*)ptr);
					break;

				case node_type_null:
					detail::destroy<NullNodeType, Alloc>((NullNodeType*)ptr);
					break;

				case node_type_boolean:
					detail::destroy<BooleanNodeType, Alloc>((BooleanNodeType*)ptr);
					break;

				case node_type_string:
					detail::destroy<StringNodeType, Alloc>((StringNodeType*)ptr);
					break;

				case node_type_number:
					detail::destroy<NumberNodeType, Alloc>((NumberNodeType*)ptr);
					break;

				case node_type_object:
					detail::destroy<ObjectNodeType, Alloc>((ObjectNodeType*)ptr);
					break;

				case node_type_array:
					detail::destroy<ArrayNodeType, Alloc>((ArrayNodeType*)ptr);
					break;

				default:
					ECLOG_ASSERT(false);
					break;
				}
			}
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_NODEFACTORY_H_

