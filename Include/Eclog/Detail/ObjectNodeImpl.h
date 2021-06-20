// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_OBJECTNODEIMPL_H_
#define ECLOG_CPP_DETAIL_OBJECTNODEIMPL_H_

#include <Eclog/ObjectNode.h>
#include <Eclog/Parse.h>
#include <Eclog/StdStreamInputStream.h>
#include <Eclog/MemoryInputStream.h>
#include <Eclog/StdStreamOutputStream.h>
#include <Eclog/DynamicParsingBuffer.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/DocumentParseHandler.h>
#include <Eclog/Detail/DocumentRenderer.h>
#include <Eclog/Detail/NodePtr.h>
#include <Eclog/Detail/RbTree.h>
#include <Eclog/Detail/LinkedList.h>
#include <Eclog/Detail/Memory.h>
#include <Eclog/Detail/Renderer.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/Assert.h>

#include <stddef.h> // ptrdiff_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Factory>
	class ObjectNodeImpl : public ObjectNode, private NonCopyable {
	private:
		struct RbTreeNode
		{
			int color;
			RbTreeNode* parent;
			RbTreeNode* left;
			RbTreeNode* right;
		};

		class LinkedListNode : public ObjectNode::Element {
		public:
			virtual KeyNode& key() ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual const KeyNode& key() const ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual ValueNode& value() ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual const ValueNode& value() const ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual void updateValue(const ValueNode&) ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual void updateValue(const ValueDesc&) ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual LinkedListNode* prev() ECLOG_OVERRIDE
			{
				return prev_;
			}

			virtual const LinkedListNode* prev() const ECLOG_OVERRIDE
			{
				return prev_;
			}

			virtual LinkedListNode* next() ECLOG_OVERRIDE
			{
				return next_;
			}

			virtual const LinkedListNode* next() const ECLOG_OVERRIDE
			{
				return next_;
			}

		public:
			void setPrev(LinkedListNode* prev)
			{
				prev_ = prev;
			}

			void setNext(LinkedListNode* next)
			{
				next_ = next;
			}

		private:
			LinkedListNode* prev_;
			LinkedListNode* next_;
		};

		class Element : public LinkedListNode {
		public:
			virtual KeyNode& key() ECLOG_OVERRIDE
			{
				return *key_;
			}

			virtual const KeyNode& key() const ECLOG_OVERRIDE
			{
				return *key_;
			}

			virtual ValueNode& value() ECLOG_OVERRIDE
			{
				return *value_;
			}

			virtual const ValueNode& value() const ECLOG_OVERRIDE
			{
				return *value_;
			}

			virtual void updateValue(const ValueNode& value) ECLOG_OVERRIDE
			{
				ValueNode* p = Factory::create(value);

				Factory::destroy(value_);

				value_ = p;
			}

			virtual void updateValue(const ValueDesc& desc) ECLOG_OVERRIDE
			{
				ValueNode* p = Factory::create(desc);

				Factory::destroy(value_);

				value_ = p;
			}

		public:
			void setKey(KeyNode* key)
			{
				key_ = key;
			}

			void setValue(ValueNode* value)
			{
				value_ = value;
			}

			RbTreeNode* rbTreeNode()
			{
				return &rbTreeNode_;
			}

		public:
			static Element* getBaseAddress(RbTreeNode* p)
			{
				return (Element*)((char*)p - Element().offsetOfRbTreeNode());
			}

			static const Element* getBaseAddress(const RbTreeNode* p)
			{
				return (const Element*)((const char*)p - Element().offsetOfRbTreeNode());
			}

		private:
			ptrdiff_t offsetOfRbTreeNode() const
			{
				return (const char*)&rbTreeNode_ - (const char*)this;
			}

		private:
			KeyNode* key_;
			ValueNode* value_;
			RbTreeNode rbTreeNode_;
		};

		struct RbTreeNodeTraits
		{
			typedef int ColorType;

			static RbTreeNode* getParent(const RbTreeNode* node)
			{
				return node->parent;
			}

			static void setParent(RbTreeNode* node, RbTreeNode* parent)
			{
				node->parent = parent;
			}

			static RbTreeNode* getLeft(const RbTreeNode* node)
			{
				return node->left;
			}

			static void setLeft(RbTreeNode* node, RbTreeNode* left)
			{
				node->left = left;
			}

			static RbTreeNode* getRight(const RbTreeNode* node)
			{
				return node->right;
			}

			static void setRight(RbTreeNode* node, RbTreeNode* right)
			{
				node->right = right;
			}

			static ColorType getColor(const RbTreeNode* node)
			{
				return node->color;
			}

			static void setColor(RbTreeNode* node, ColorType color)
			{
				node->color = color;
			}

			static ColorType red()
			{
				return 0;
			}

			static ColorType black()
			{
				return 1;
			}
		};

		struct RbTreeNodeCompare
		{
			bool operator()(const cstring& a, const RbTreeNode& b) const
			{
				return a < Element::getBaseAddress(&b)->key().str();
			}

			bool operator()(const RbTreeNode& a, const cstring& b) const
			{
				return Element::getBaseAddress(&a)->key().str() < b;
			}

			bool operator()(const RbTreeNode& a, const RbTreeNode& b) const
			{
				return Element::getBaseAddress(&a)->key().str() < Element::getBaseAddress(&b)->key().str();
			}
		};

		struct LinkedListNodeTraits
		{
			static LinkedListNode* getPrev(const LinkedListNode* p)
			{
				return (LinkedListNode*)p->prev();
			}

			static void setPrev(LinkedListNode* p, LinkedListNode* prev)
			{
				p->setPrev(prev);
			}

			static LinkedListNode* getNext(const LinkedListNode* p)
			{
				return (LinkedListNode*)p->next();
			}

			static void setNext(LinkedListNode* p, LinkedListNode* next)
			{
				p->setNext(next);
			}
		};

		typedef RbTree<RbTreeNode, RbTreeNodeTraits, RbTreeNodeCompare> Tree;
		typedef LinkedList<LinkedListNode, LinkedListNodeTraits> List;

		typedef typename Factory::AllocType Alloc;

	public:
		ObjectNodeImpl()
		{
		}

		explicit ObjectNodeImpl(const ValueDesc& desc)
		{
			assign((const ObjectDesc&)desc);
		}

		explicit ObjectNodeImpl(const ObjectNode& other)
		{
			assign(other);
		}

		~ObjectNodeImpl()
		{
			remove(begin(), end());
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_object;
		}

		virtual void clear() ECLOG_OVERRIDE
		{
			remove(begin(), end());
		}

		virtual bool empty() const ECLOG_OVERRIDE
		{
			return list_.empty();
		}

		virtual size_t size() const ECLOG_OVERRIDE
		{
			return list_.size();
		}

		virtual Iterator begin() ECLOG_OVERRIDE
		{
			return list_.begin();
		}

		virtual Iterator end() ECLOG_OVERRIDE
		{
			return list_.end();
		}

		virtual ConstIterator begin() const ECLOG_OVERRIDE
		{
			return list_.begin();
		}

		virtual ConstIterator end() const ECLOG_OVERRIDE
		{
			return list_.end();
		}

		virtual bool contains(cstring key) const ECLOG_OVERRIDE
		{
			return tree_.find(key) != tree_.end();
		}

		virtual Iterator find(cstring key) ECLOG_OVERRIDE
		{
			RbTreeNode* p = tree_.find(key);

			if (p == tree_.end()) {
				return list_.end();
			}

			return Element::getBaseAddress(p);
		}

		virtual ConstIterator find(cstring key) const ECLOG_OVERRIDE
		{
			const RbTreeNode* p = tree_.find(key);

			if (p == tree_.end()) {
				return list_.end();
			}

			return Element::getBaseAddress(p);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const ObjectNode::Element& element) ECLOG_OVERRIDE
		{
			return insert(pos.get(), element.key(), element.value());
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const ObjectNode::Element& element) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), element.key(), element.value());
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual void merge(const ObjectDesc& patch) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t(patch);

			merge(t);
		}

		virtual void merge(const ObjectNode& patch) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t(patch);

			merge(t);
		}

		virtual void remove(Iterator pos) ECLOG_OVERRIDE
		{
			tree_.erase(((Element*)pos.get())->rbTreeNode());
			list_.erase((LinkedListNode*)pos.get());

			Factory::destroy(&pos->key());
			Factory::destroy(&pos->value());

			destroy<Element, Alloc>((Element*)pos.get());
		}

		virtual size_t remove(Iterator first, Iterator last) ECLOG_OVERRIDE
		{
			size_t count = 0;

			while (first != last)
			{
				remove(first++);

				++count;
			}

			return count;
		}

		virtual bool remove(cstring key) ECLOG_OVERRIDE
		{
			ObjectNode::Iterator it = find(key);

			if (it != end())
			{
				remove(it);
				return true;
			}

			return false;
		}

		virtual void parse(eclog::Context& ctx) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t;

			DocumentParseHandler<typename Factory::AllocType> handler(t);

			eclog::parse(ctx, handler);

			swap(t);
		}

		virtual void parse(eclog::Context& ctx, ErrorCode& ec) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t;

			DocumentParseHandler<typename Factory::AllocType> handler(t);

			eclog::parse(ctx, handler, ec);

			if (ec) {
				return;
			}

			swap(t);
		}

		virtual void parse(InputStream& stream) ECLOG_OVERRIDE
		{
			BasicDynamicParsingBuffer<typename Factory::AllocType> buffer;
			eclog::Context ctx(stream, buffer);

			parse(ctx);
		}

		virtual void parse(InputStream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			BasicDynamicParsingBuffer<typename Factory::AllocType> buffer;
			eclog::Context ctx(stream, buffer);

			parse(ctx, ec);
		}

		virtual void parse(cstring str) ECLOG_OVERRIDE
		{
			MemoryInputStream stream(str.data(), str.size());

			parse(stream);
		}

		virtual void parse(cstring str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			MemoryInputStream stream(str.data(), str.size());

			parse(stream, ec);
		}
		
		virtual void parse(std::istream& stream) ECLOG_OVERRIDE
		{
			StdStreamInputStream is(stream);

			parse(is);
		}

		virtual void parse(std::istream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			StdStreamInputStream is(stream);

			parse(is, ec);
		}

		virtual void parse(const std::string& str) ECLOG_OVERRIDE
		{
			parse(cstring(str.data(), str.size()));
		}

		virtual void parse(const std::string& str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			parse(cstring(str.data(), str.size()), ec);
		}

		virtual void parse(const char* str) ECLOG_OVERRIDE
		{
			parse(cstring(str));
		}

		virtual void parse(const char* str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			parse(cstring(str), ec);
		}

		virtual void render(OutputStream& stream) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream);

			renderer.render(*this, 0);
		}

		virtual void render(OutputStream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream);

			renderer.render(*this, &ec);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream, rc);

			renderer.render(*this, 0);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream, rc);

			renderer.render(*this, &ec);
		}

		virtual void render(std::ostream& stream) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os);
		}

		virtual void render(std::ostream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os, ec);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os, rc);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os, rc, ec);
		}

		virtual void assign(const ObjectDesc& desc) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t;

			for (size_t i = 0; i < desc.objectSize(); ++i)
			{
				t.appendForce(desc.object()[i].first, desc.object()[i].second);
			}

			swap(t);
		}

		virtual void assign(const ObjectNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			ObjectNodeImpl t;

			for (ObjectNode::ConstIterator it = other.begin(); it != other.end(); ++it)
			{
				t.append(it->key(), it->value());
			}

			swap(t);
		}

	public:
		void swap(ObjectNodeImpl& other)
		{
			detail::swap(tree_, other.tree_);
			detail::swap(list_, other.list_);
		}

	private:
		template<typename K, typename V>
		Pair<Element*, bool> insert(ObjectNode::Element* pos, const K& keyArg, const V& valueArg)
		{
			NodePtr<KeyNode, Factory> key(Factory::create(keyArg));

			UniquePtr<Element, Alloc> p(create<Element, Alloc>());

			p->setKey(key.get());

			Pair<RbTreeNode*, bool> result = tree_.insertUnique(p->rbTreeNode());

			if (result.second)
			{
				NodePtr<ValueNode, Factory> value;

				ECLOG_TRY
				{
					value.reset(Factory::create(valueArg));
				}
					ECLOG_CATCH_ALL
				{
					tree_.erase(p->rbTreeNode());
					ECLOG_RETHROW;
				}

				list_.insertBefore(p.get(), (LinkedListNode*)pos);

				key.release();
				p->setValue(value.release());

				return Pair<Element*, bool>(p.release(), true);
			}
			else
			{
				return Pair<Element*, bool>(Element::getBaseAddress(result.first), false);
			}
		}

		template<typename K, typename V>
		Element* insertForce(ObjectNode::Element* pos, const K& keyArg, const V& valueArg)
		{
			NodePtr<KeyNode, Factory> key(Factory::create(keyArg));
			NodePtr<ValueNode, Factory> value(Factory::create(valueArg));

			UniquePtr<Element, Alloc> p(create<Element, Alloc>());

			p->setKey(key.get());
			p->setValue(value.get());

			list_.insertBefore(p.get(), (LinkedListNode*)pos);

			Pair<RbTreeNode*, bool> result = tree_.insertUnique(p->rbTreeNode());

			if (result.second)
			{
				key.release();
				value.release();

				return p.release();
			}
			else
			{
				Element* p2 = Element::getBaseAddress(result.first);

				list_.erase(p2);
				list_.replace(p2, p.get());

				Factory::destroy(&p2->key());
				Factory::destroy(&p2->value());

				p2->setKey(key.release());
				p2->setValue(value.release());

				return p2;
			}
		}

		void merge(ObjectNodeImpl& patch)
		{
			LinkedListNode* p = patch.list_.begin();

			while (p != patch.list_.end())
			{
				Element* patchElement = (Element*)p;
				p = p->next();

				RbTreeNode* rbTreeNode = tree_.find(patchElement->key().str());

				if (rbTreeNode == tree_.end())
				{
					if (!patchElement->value().isNull())
					{
						if (patchElement->value().isObject()) {
							removeNullNodes((ObjectNodeImpl&)patchElement->value());
						}

						patch.tree_.erase(patchElement->rbTreeNode());
						patch.list_.erase(patchElement);

						tree_.insertUnique(patchElement->rbTreeNode());
						list_.insertBefore(patchElement, list_.end());
					}

					continue;
				}

				Element* targetElement = Element::getBaseAddress(rbTreeNode);

				if (patchElement->value().isNull())
				{
					Factory::destroy(&targetElement->key());
					Factory::destroy(&targetElement->value());

					tree_.erase(targetElement->rbTreeNode());
					list_.erase(targetElement);

					destroy<Element, Alloc>(targetElement);
				}
				else if (patchElement->value().isObject() && targetElement->value().isObject())
				{
					((ObjectNodeImpl&)targetElement->value()).merge((ObjectNodeImpl&)patchElement->value());
				}
				else
				{
					if (patchElement->value().isObject()) {
						removeNullNodes((ObjectNodeImpl&)patchElement->value());
					}

					Factory::destroy(&targetElement->key());
					Factory::destroy(&targetElement->value());

					targetElement->setKey(&patchElement->key());
					targetElement->setValue(&patchElement->value());

					patch.tree_.erase(patchElement->rbTreeNode());
					patch.list_.erase(patchElement);

					destroy<Element, Alloc>(patchElement);
				}
			}
		}

		void removeNullNodes(ObjectNodeImpl& obj)
		{
			LinkedListNode* p = obj.list_.begin();

			while (p != obj.list_.end())
			{
				Element* element = (Element*)p;
				p = p->next();

				if (element->value().isNull())
				{
					obj.tree_.erase(element->rbTreeNode());
					obj.list_.erase(element);

					Factory::destroy(&element->key());
					Factory::destroy(&element->value());

					destroy<Element, Alloc>(element);
				}
				else if (element->value().isObject())
				{
					removeNullNodes((ObjectNodeImpl&)element->value());
				}
			}
		}

	private:
		Tree tree_;
		List list_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_OBJECTNODEIMPL_H_

