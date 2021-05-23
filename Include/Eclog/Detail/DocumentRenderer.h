// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_DOCUMENTRENDERER_H_
#define ECLOG_CPP_DETAIL_DOCUMENTRENDERER_H_

#include <Eclog/KeyNode.h>
#include <Eclog/ValueNode.h>
#include <Eclog/NullNode.h>
#include <Eclog/BooleanNode.h>
#include <Eclog/StringNode.h>
#include <Eclog/NumberNode.h>
#include <Eclog/ObjectNode.h>
#include <Eclog/ArrayNode.h>
#include <Eclog/StringDesc.h>
#include <Eclog/NumberDesc.h>
#include <Eclog/RendererConfig.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/Renderer.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/Assert.h>

namespace eclog {

	namespace detail {

		class DocumentRenderer : private NonCopyable {
		public:
			explicit DocumentRenderer(OutputStream& stream, const RendererConfig& rc = RendererConfig()) : renderer_(stream, rc)
			{
			}

			void render(const ObjectNode& root, ErrorCode* ec)
			{
				renderer_.beginObject(ec);
				ECLOG_ON_ERROR(return);

				renderObject(root, ec);
				ECLOG_ON_ERROR(return);

				renderer_.endObject(ec);
				ECLOG_ON_ERROR(return);

				renderer_.close(ec);
				ECLOG_ON_ERROR(return);
			}

		private:
			void renderObject(const ObjectNode& node, ErrorCode* ec)
			{
				for (ObjectNode::ConstIterator it = node.begin(); it != node.end(); ++it)
				{
					const KeyNode& keyNode = it->key();
					const ValueNode& valueNode = it->value();

					if (valueNode.isObject())
					{
						renderer_.beginObject(makeDesc(keyNode), ec);
						ECLOG_ON_ERROR(return);

						renderObject((const ObjectNode&)valueNode, ec);
						ECLOG_ON_ERROR(return);

						renderer_.endObject(ec);
						ECLOG_ON_ERROR(return);
					}
					else if (valueNode.isArray())
					{
						renderer_.beginArray(makeDesc(keyNode), ec);
						ECLOG_ON_ERROR(return);

						renderArray((const ArrayNode&)valueNode, ec);
						ECLOG_ON_ERROR(return);

						renderer_.endArray(ec);
						ECLOG_ON_ERROR(return);
					}
					else
					{
						renderer_.renderMember(makeDesc(keyNode), makeDesc(valueNode), ec);
						ECLOG_ON_ERROR(return);
					}
				}
			}

			void renderArray(const ArrayNode& node, ErrorCode* ec)
			{
				for (ArrayNode::ConstIterator it = node.begin(); it != node.end(); ++it)
				{
					const ValueNode& valueNode = it->value();

					if (valueNode.isObject())
					{
						renderer_.beginObject(ec);
						ECLOG_ON_ERROR(return);

						renderObject((const ObjectNode&)valueNode, ec);
						ECLOG_ON_ERROR(return);

						renderer_.endObject(ec);
						ECLOG_ON_ERROR(return);
					}
					else if (valueNode.isArray())
					{
						renderer_.beginArray(ec);
						ECLOG_ON_ERROR(return);

						renderArray((const ArrayNode&)valueNode, ec);
						ECLOG_ON_ERROR(return);

						renderer_.endArray(ec);
						ECLOG_ON_ERROR(return);
					}
					else
					{
						renderer_.renderMember(makeDesc(valueNode), ec);
						ECLOG_ON_ERROR(return);
					}
				}
			}

			static KeyDesc makeDesc(const KeyNode& keyNode)
			{
				return KeyDesc(keyNode.str(), keyNode.notation(), keyNode.delimiter());
			}

			static ValueDesc makeDesc(const ValueNode& valueNode)
			{
				switch (valueNode.nodeType())
				{
				case node_type_null:
					return ValueDesc(null);

				case node_type_boolean:
					return ValueDesc(((const BooleanNode&)valueNode).value());

				case node_type_string:
					return ValueDesc(((const StringNode&)valueNode).value(), ((const StringNode&)valueNode).notation(), ((const StringNode&)valueNode).delimiter());

				case node_type_number:
					return ValueDesc(((const NumberNode&)valueNode).value(), ((const NumberNode&)valueNode).fracDigits());

				default:
					ECLOG_ASSERT(false);
					return ValueDesc(null);
				}
			}

		private:
			Renderer renderer_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_DOCUMENTRENDERER_H_

