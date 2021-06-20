// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_ARRAYNODEIMPL_H_
#define ECLOG_CPP_DETAIL_ARRAYNODEIMPL_H_

#include <Eclog/ArrayNode.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/NodePtr.h>
#include <Eclog/Detail/Vector.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/Assert.h>

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Factory>
	class ArrayNodeImpl : public ArrayNode, private NonCopyable {
	private:
		class Element : public ArrayNode::Element {
		public:
			Element() : value_(0)
			{
			}

			explicit Element(ValueNode* value) : value_(value)
			{
			}

		public:
			virtual ValueNode& value() ECLOG_OVERRIDE
			{
				if (!value_) {
					ECLOG_FAULT(OutOfRange);
				}

				return *value_;
			}

			virtual const ValueNode& value() const ECLOG_OVERRIDE
			{
				if (!value_) {
					ECLOG_FAULT(OutOfRange);
				}

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

			virtual Element* prev(ptrdiff_t n = 1) ECLOG_OVERRIDE
			{
				return this - n;
			}

			virtual const Element* prev(ptrdiff_t n = 1) const ECLOG_OVERRIDE
			{
				return this - n;
			}

			virtual Element* next(ptrdiff_t n = 1) ECLOG_OVERRIDE
			{
				return this + n;
			}

			virtual const Element* next(ptrdiff_t n = 1) const ECLOG_OVERRIDE
			{
				return this + n;
			}

			virtual ptrdiff_t distance(const ArrayNode::Element* other) const ECLOG_OVERRIDE
			{
				return (Element*)other - this;
			}

		private:
			ValueNode* value_;
		};

		typedef typename Factory::AllocType Alloc;

	public:
		ArrayNodeImpl()
		{
			v_.pushBack(Element());
		}

		explicit ArrayNodeImpl(const ValueDesc& desc)
		{
			v_.pushBack(Element());

			assign((const ArrayDesc&)desc);
		}

		explicit ArrayNodeImpl(const ArrayNode& other)
		{
			v_.pushBack(Element());

			assign(other);
		}

		~ArrayNodeImpl()
		{
			remove(0, size());
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_array;
		}

		virtual void clear() ECLOG_OVERRIDE
		{
			remove(0, size());
		}

		virtual bool empty() const ECLOG_OVERRIDE
		{
			return size() == 0;
		}

		virtual size_t size() const ECLOG_OVERRIDE
		{
			return v_.size() - 1;
		}

		virtual Iterator begin() ECLOG_OVERRIDE
		{
			return v_.data();
		}

		virtual Iterator end() ECLOG_OVERRIDE
		{
			return v_.data() + size();
		}

		virtual ConstIterator begin() const ECLOG_OVERRIDE
		{
			return v_.data();
		}

		virtual ConstIterator end() const ECLOG_OVERRIDE
		{
			return v_.data() + size();
		}

		virtual size_t indexOf(const ArrayNode::Element& element) const ECLOG_OVERRIDE
		{
			return v_.indexOf((const Element&)element);
		}

		virtual ArrayNode::Element& at(size_t index) ECLOG_OVERRIDE
		{
			if (index >= size()) {
				ECLOG_FAULT(OutOfRange);
			}

			return v_[index];
		}

		virtual const ArrayNode::Element& at(size_t index) const ECLOG_OVERRIDE
		{
			if (index >= size()) {
				ECLOG_FAULT(OutOfRange);
			}

			return v_[index];
		}

		virtual Iterator insert(Iterator pos, const ArrayNode::Element& element) ECLOG_OVERRIDE
		{
			return insert(pos.get(), element.value());
		}

		virtual Iterator insert(Iterator pos, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), value);
		}

		virtual Iterator insert(Iterator pos, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), value);
		}

		virtual void remove(Iterator pos) ECLOG_OVERRIDE
		{
			remove(indexOf(*pos), 1);
		}

		virtual void remove(Iterator first, Iterator last) ECLOG_OVERRIDE
		{
			size_t firstIndex = indexOf(*first);
			size_t lastIndex = indexOf(*last);
			size_t count = lastIndex - firstIndex;

			remove(firstIndex, count);
		}

		virtual void remove(size_t index) ECLOG_OVERRIDE
		{
			remove(index, 1);
		}

		virtual void remove(size_t index, size_t count) ECLOG_OVERRIDE
		{
			if (index < size() && count > 0)
			{
				if (count > size() - index) {
					count = size() - index;
				}

				for (size_t i = index; i < index + count; ++i) {
					Factory::destroy(&v_[i].value());
				}

				v_.remove(index, count);
			}
		}

		virtual void assign(const ArrayDesc& desc) ECLOG_OVERRIDE
		{
			ArrayNodeImpl t;

			for (size_t i = 0; i < desc.arraySize(); ++i)
			{
				t.insert(t.end(), desc.array()[i]);
			}

			detail::swap(v_, t.v_);
		}

		virtual void assign(const ArrayNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			ArrayNodeImpl t;

			for (ArrayNode::ConstIterator it = other.begin(); it != other.end(); ++it)
			{
				t.insert(t.end(), it->value());
			}

			detail::swap(v_, t.v_);
		}

	private:
		template<typename V>
		ArrayNode::Element* insert(ArrayNode::Element* pos, const V& valueArg)
		{
			NodePtr<ValueNode, Factory> value(Factory::create(valueArg));

			size_t index = indexOf(*pos);

			v_.insert(index, Element(value.get()));

			value.release();

			return v_.data() + index;
		}

	private:
		Vector<Element, Alloc> v_;
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_ARRAYNODEIMPL_H_

