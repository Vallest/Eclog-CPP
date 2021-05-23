// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_ARRAYNODE_H_
#define ECLOG_CPP_ARRAYNODE_H_

#include <Eclog/ValueNode.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/ArrayDesc.h>
#include <Eclog/cstring.h>

#include <stddef.h> // ptrdiff_t

namespace eclog {

	class ArrayNode : public ValueNode {
	protected:
		~ArrayNode() {} // prevents calling delete

	public:
		class Iterator;
		class ConstIterator;

		class Element {
		private:
			friend class Iterator;
			friend class ConstIterator;

		protected:
			~Element() {} // prevents calling delete

		public:
			virtual ValueNode& value() = 0;
			virtual const ValueNode& value() const = 0;

			virtual void updateValue(const ValueNode& value) = 0;
			virtual void updateValue(const ValueDesc& desc) = 0;

		protected:
			virtual Element* prev(ptrdiff_t n = 1) = 0;
			virtual const Element* prev(ptrdiff_t n = 1) const = 0;

			virtual Element* next(ptrdiff_t n = 1) = 0;
			virtual const Element* next(ptrdiff_t n = 1) const = 0;

			virtual ptrdiff_t distance(const Element* other) const = 0;
		};

		class Iterator {
		public:
			Iterator();
			Iterator(Element* p);
			Iterator(const Iterator& other);

			Iterator& operator=(const Iterator& other);

			Iterator& operator+=(ptrdiff_t n);
			Iterator& operator-=(ptrdiff_t n);

			Iterator& operator++();
			Iterator operator++(int);
			Iterator& operator--();
			Iterator operator--(int);

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;
			bool operator<(const Iterator& other) const;
			bool operator>(const Iterator& other) const;
			bool operator<=(const Iterator& other) const;
			bool operator>=(const Iterator& other) const;

			Iterator operator+(ptrdiff_t n) const;
			Iterator operator-(ptrdiff_t n) const;
			ptrdiff_t operator-(const Iterator& other) const;

			Element* get() const;
			Element* operator->();
			Element& operator*();

		private:
			Element* p_;
		};

		class ConstIterator {
		public:
			ConstIterator();
			ConstIterator(const Element* p);
			ConstIterator(Iterator it);
			ConstIterator(const ConstIterator& other);

			ConstIterator& operator=(const ConstIterator& other);

			ConstIterator& operator+=(ptrdiff_t n);
			ConstIterator& operator-=(ptrdiff_t n);

			ConstIterator& operator++();
			ConstIterator operator++(int);
			ConstIterator& operator--();
			ConstIterator operator--(int);

			bool operator==(const ConstIterator& other) const;
			bool operator!=(const ConstIterator& other) const;
			bool operator<(const ConstIterator& other) const;
			bool operator>(const ConstIterator& other) const;
			bool operator<=(const ConstIterator& other) const;
			bool operator>=(const ConstIterator& other) const;

			ConstIterator operator+(ptrdiff_t n) const;
			ConstIterator operator-(ptrdiff_t n) const;
			ptrdiff_t operator-(const ConstIterator& other) const;

			const Element* get() const;
			const Element* operator->();
			const Element& operator*();

		private:
			const Element* p_;
		};

	public:
		virtual void clear() = 0;

		virtual bool empty() const = 0;
		virtual size_t size() const = 0;

		virtual Iterator begin() = 0;
		virtual Iterator end() = 0;

		virtual ConstIterator begin() const = 0;
		virtual ConstIterator end() const = 0;

		Element& first();
		Element& last();

		const Element& first() const;
		const Element& last() const;

		virtual size_t indexOf(const Element& element) const = 0;

		virtual Element& at(size_t index) = 0;
		virtual const Element& at(size_t index) const = 0;

		ValueNode& getValue(size_t index);
		NullNode& getNull(size_t index);
		BooleanNode& getBoolean(size_t index);
		StringNode& getString(size_t index);
		NumberNode& getNumber(size_t index);
		ObjectNode& getObject(size_t index);
		ArrayNode& getArray(size_t index);

		const ValueNode& getValue(size_t index) const;
		const NullNode& getNull(size_t index) const;
		const BooleanNode& getBoolean(size_t index) const;
		const StringNode& getString(size_t index) const;
		const NumberNode& getNumber(size_t index) const;
		const ObjectNode& getObject(size_t index) const;
		const ArrayNode& getArray(size_t index) const;

		void append(const Element& element);
		void append(const ValueNode& value);
		void append(const ValueDesc& value);

		virtual Iterator insert(Iterator pos, const Element& element) = 0;
		virtual Iterator insert(Iterator pos, const ValueNode& value) = 0;
		virtual Iterator insert(Iterator pos, const ValueDesc& value) = 0;

		virtual void remove(Iterator pos) = 0;
		virtual void remove(Iterator first, Iterator last) = 0;
		virtual void remove(size_t index) = 0;
		virtual void remove(size_t index, size_t count) = 0;

		virtual void assign(const ArrayDesc& desc) = 0;
		virtual void assign(const ArrayNode& other) = 0;
	};

	inline ArrayNode::Iterator::Iterator() : p_(0)
	{
	}

	inline ArrayNode::Iterator::Iterator(Element* p) : p_(p)
	{
	}

	inline ArrayNode::Iterator::Iterator(const Iterator& other) : p_(other.p_)
	{
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator=(const Iterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator+=(ptrdiff_t n)
	{
		p_ = p_->next(n);

		return *this;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator-=(ptrdiff_t n)
	{
		p_ = p_->prev(n);

		return *this;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator++(int)
	{
		Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator--(int)
	{
		Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ArrayNode::Iterator::operator==(const Iterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ArrayNode::Iterator::operator!=(const Iterator& other) const
	{
		return !(*this == other);
	}

	inline bool ArrayNode::Iterator::operator<(const Iterator& other) const
	{
		return p_->distance(other.p_) > 0;
	}

	inline bool ArrayNode::Iterator::operator>(const Iterator& other) const
	{
		return other < *this;
	}

	inline bool ArrayNode::Iterator::operator<=(const Iterator& other) const
	{
		return !(*this > other);
	}

	inline bool ArrayNode::Iterator::operator>=(const Iterator& other) const
	{
		return !(*this < other);
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator+(ptrdiff_t n) const
	{
		return p_->next(n);
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator-(ptrdiff_t n) const
	{
		return p_->prev(n);
	}

	inline ptrdiff_t ArrayNode::Iterator::operator-(const Iterator& other) const
	{
		return other.p_->distance(p_);
	}

	inline ArrayNode::Element* ArrayNode::Iterator::get() const
	{
		return p_;
	}

	inline ArrayNode::Element* ArrayNode::Iterator::operator->()
	{
		return p_;
	}

	inline ArrayNode::Element& ArrayNode::Iterator::operator*()
	{
		return *p_;
	}

	inline ArrayNode::Iterator operator+(ptrdiff_t n, ArrayNode::Iterator it)
	{
		return it + n;
	}

	inline ArrayNode::ConstIterator::ConstIterator() : p_(0)
	{
	}

	inline ArrayNode::ConstIterator::ConstIterator(const ArrayNode::Element* p) : p_(p)
	{
	}

	inline ArrayNode::ConstIterator::ConstIterator(Iterator it) : p_(it.get())
	{
	}

	inline ArrayNode::ConstIterator::ConstIterator(const ConstIterator& other) : p_(other.p_)
	{
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator=(const ConstIterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator+=(ptrdiff_t n)
	{
		p_ = p_->next(n);

		return *this;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator-=(ptrdiff_t n)
	{
		p_ = p_->prev(n);

		return *this;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator++(int)
	{
		const ArrayNode::Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator--(int)
	{
		const ArrayNode::Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ArrayNode::ConstIterator::operator==(const ConstIterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ArrayNode::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !(*this == other);
	}

	inline bool ArrayNode::ConstIterator::operator<(const ConstIterator& other) const
	{
		return p_->distance(other.p_) > 0;
	}

	inline bool ArrayNode::ConstIterator::operator>(const ConstIterator& other) const
	{
		return other < *this;
	}

	inline bool ArrayNode::ConstIterator::operator<=(const ConstIterator& other) const
	{
		return !(*this > other);
	}

	inline bool ArrayNode::ConstIterator::operator>=(const ConstIterator& other) const
	{
		return !(*this < other);
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator+(ptrdiff_t n) const
	{
		return p_->next(n);
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator-(ptrdiff_t n) const
	{
		return p_->prev(n);
	}

	inline ptrdiff_t ArrayNode::ConstIterator::operator-(const ConstIterator& other) const
	{
		return other.p_->distance(p_);
	}

	inline const ArrayNode::Element* ArrayNode::ConstIterator::get() const
	{
		return p_;
	}

	inline const ArrayNode::Element* ArrayNode::ConstIterator::operator->()
	{
		return p_;
	}

	inline const ArrayNode::Element& ArrayNode::ConstIterator::operator*()
	{
		return *p_;
	}

	inline ArrayNode::ConstIterator operator+(ptrdiff_t n, ArrayNode::ConstIterator it)
	{
		return it + n;
	}

	inline ArrayNode::Element& ArrayNode::first()
	{
		return *begin();
	}

	inline ArrayNode::Element& ArrayNode::last()
	{
		return *--end();
	}

	inline const ArrayNode::Element& ArrayNode::first() const
	{
		return *begin();
	}

	inline const ArrayNode::Element& ArrayNode::last() const
	{
		return *--end();
	}

	inline ValueNode& ArrayNode::getValue(size_t index)
	{
		return at(index).value();
	}

	inline NullNode& ArrayNode::getNull(size_t index)
	{
		return getValue(index).asNull();
	}

	inline BooleanNode& ArrayNode::getBoolean(size_t index)
	{
		return getValue(index).asBoolean();
	}

	inline StringNode& ArrayNode::getString(size_t index)
	{
		return getValue(index).asString();
	}

	inline NumberNode& ArrayNode::getNumber(size_t index)
	{
		return getValue(index).asNumber();
	}

	inline ObjectNode& ArrayNode::getObject(size_t index)
	{
		return getValue(index).asObject();
	}

	inline ArrayNode& ArrayNode::getArray(size_t index)
	{
		return getValue(index).asArray();
	}

	inline const ValueNode& ArrayNode::getValue(size_t index) const
	{
		return at(index).value();
	}

	inline const NullNode& ArrayNode::getNull(size_t index) const
	{
		return getValue(index).asNull();
	}

	inline const BooleanNode& ArrayNode::getBoolean(size_t index) const
	{
		return getValue(index).asBoolean();
	}

	inline const StringNode& ArrayNode::getString(size_t index) const
	{
		return getValue(index).asString();
	}

	inline const NumberNode& ArrayNode::getNumber(size_t index) const
	{
		return getValue(index).asNumber();
	}

	inline const ObjectNode& ArrayNode::getObject(size_t index) const
	{
		return getValue(index).asObject();
	}

	inline const ArrayNode& ArrayNode::getArray(size_t index) const
	{
		return getValue(index).asArray();
	}

	inline void ArrayNode::append(const ArrayNode::Element& element)
	{
		insert(end(), element);
	}

	inline void ArrayNode::append(const ValueNode& value)
	{
		insert(end(), value);
	}

	inline void ArrayNode::append(const ValueDesc& value)
	{
		insert(end(), value);
	}

} // eclog

#endif // ECLOG_CPP_ARRAYNODE_H_

