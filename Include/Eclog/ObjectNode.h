// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_OBJECTNODE_H_
#define ECLOG_CPP_OBJECTNODE_H_

#include <Eclog/KeyNode.h>
#include <Eclog/ValueNode.h>
#include <Eclog/KeyDesc.h>
#include <Eclog/ValueDesc.h>
#include <Eclog/NumberDesc.h>
#include <Eclog/StringDesc.h>
#include <Eclog/ObjectDesc.h>
#include <Eclog/ArrayDesc.h>
#include <Eclog/InputStream.h>
#include <Eclog/OutputStream.h>
#include <Eclog/StdStringOutputStream.h>
#include <Eclog/RendererConfig.h>
#include <Eclog/Context.h>
#include <Eclog/Utility.h>
#include <Eclog/cstring.h>
#include <Eclog/Error.h>

#include <stddef.h> // ptrdiff_t, size_t
#include <istream>
#include <ostream>
#include <string>

namespace vallest {
namespace eclog {

	class ObjectNode : public ValueNode {
	protected:
		~ObjectNode() {} // prevents calling delete

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
			virtual KeyNode& key() = 0;
			virtual const KeyNode& key() const = 0;

			virtual ValueNode& value() = 0;
			virtual const ValueNode& value() const = 0;

			virtual void updateValue(const ValueNode& value) = 0;
			virtual void updateValue(const ValueDesc& desc) = 0;

		protected:
			virtual Element* prev() = 0;
			virtual const Element* prev() const = 0;

			virtual Element* next() = 0;
			virtual const Element* next() const = 0;
		};

		class Iterator {
		public:
			Iterator();
			Iterator(Element* p);
			Iterator(const Iterator& other);

			Iterator& operator=(const Iterator& other);

			Iterator& operator++();
			Iterator operator++(int);
			Iterator& operator--();
			Iterator operator--(int);

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;

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

			ConstIterator& operator++();
			ConstIterator operator++(int);
			ConstIterator& operator--();
			ConstIterator operator--(int);

			bool operator==(const ConstIterator& other) const;
			bool operator!=(const ConstIterator& other) const;

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

		virtual bool contains(cstring key) const = 0;

		virtual Iterator find(cstring key) = 0;
		virtual ConstIterator find(cstring key) const = 0;

		Iterator findNull(cstring key);
		Iterator findBoolean(cstring key);
		Iterator findString(cstring key);
		Iterator findNumber(cstring key);
		Iterator findObject(cstring key);
		Iterator findArray(cstring key);

		ConstIterator findNull(cstring key) const;
		ConstIterator findBoolean(cstring key) const;
		ConstIterator findString(cstring key) const;
		ConstIterator findNumber(cstring key) const;
		ConstIterator findObject(cstring key) const;
		ConstIterator findArray(cstring key) const;

		Element& get(cstring key);
		ValueNode& getValue(cstring key);
		NullNode& getNull(cstring key);
		BooleanNode& getBoolean(cstring key);
		StringNode& getString(cstring key);
		NumberNode& getNumber(cstring key);
		ObjectNode& getObject(cstring key);
		ArrayNode& getArray(cstring key);

		const Element& get(cstring key) const;
		const ValueNode& getValue(cstring key) const;
		const NullNode& getNull(cstring key) const;
		const BooleanNode& getBoolean(cstring key) const;
		const StringNode& getString(cstring key) const;
		const NumberNode& getNumber(cstring key) const;
		const ObjectNode& getObject(cstring key) const;
		const ArrayNode& getArray(cstring key) const;

		ValueNode& getOrAddValue(const KeyDesc& key, const ValueDesc& defaultValue = null);
		NullNode& getOrAddNull(const KeyDesc& key, const Null& defaultValue = null);
		BooleanNode& getOrAddBoolean(const KeyDesc& key, bool defaultValue = false);
		StringNode& getOrAddString(const KeyDesc& key, const StringDesc& defaultValue = cstring());
		NumberNode& getOrAddNumber(const KeyDesc& key, const NumberDesc& defaultValue = 0);
		ObjectNode& getOrAddObject(const KeyDesc& key, const ObjectDesc& defaultValue = empty_object);
		ArrayNode& getOrAddArray(const KeyDesc& key, const ArrayDesc& defaultValue = empty_array);

		bool append(const Element& element);
		bool append(const KeyNode& key, const ValueNode& value);
		bool append(const KeyDesc& key, const ValueNode& value);
		bool append(const KeyNode& key, const ValueDesc& value);
		bool append(const KeyDesc& key, const ValueDesc& value);

		virtual Pair<Iterator, bool> insert(Iterator pos, const Element& element) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueNode& value) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueNode& value) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueDesc& value) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueDesc& value) = 0;

		void appendForce(const Element& element);
		void appendForce(const KeyNode& key, const ValueNode& value);
		void appendForce(const KeyDesc& key, const ValueNode& value);
		void appendForce(const KeyNode& key, const ValueDesc& value);
		void appendForce(const KeyDesc& key, const ValueDesc& value);

		virtual Iterator insertForce(Iterator pos, const Element& element) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueNode& value) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueNode& value) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueDesc& value) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueDesc& value) = 0;

		virtual void merge(const ObjectDesc& patch) = 0;
		virtual void merge(const ObjectNode& patch) = 0;

		virtual void remove(Iterator pos) = 0;
		virtual size_t remove(Iterator first, Iterator last) = 0;
		virtual bool remove(cstring key) = 0;

		virtual void parse(Context& ctx) = 0;
		virtual void parse(Context& ctx, ErrorCode& ec) = 0;
		virtual void parse(InputStream& stream) = 0;
		virtual void parse(InputStream& stream, ErrorCode& ec) = 0;
		virtual void parse(cstring str) = 0;
		virtual void parse(cstring str, ErrorCode& ec) = 0;
		virtual void parse(std::istream& stream) = 0;
		virtual void parse(std::istream& stream, ErrorCode& ec) = 0;
		virtual void parse(const std::string& str) = 0;
		virtual void parse(const std::string& str, ErrorCode& ec) = 0;
		virtual void parse(const char* str) = 0;
		virtual void parse(const char* str, ErrorCode& ec) = 0;

		virtual void render(OutputStream& stream) const = 0;
		virtual void render(OutputStream& stream, ErrorCode& ec) const = 0;
		virtual void render(OutputStream& stream, const RendererConfig& rc) const = 0;
		virtual void render(OutputStream& stream, const RendererConfig& rc, ErrorCode& ec) const = 0;
		virtual void render(std::ostream& stream) const = 0;
		virtual void render(std::ostream& stream, ErrorCode& ec) const = 0;
		virtual void render(std::ostream& stream, const RendererConfig& rc) const = 0;
		virtual void render(std::ostream& stream, const RendererConfig& rc, ErrorCode& ec) const = 0;

		std::string toStdString() const;
		std::string toStdString(ErrorCode& ec) const;
		std::string toStdString(const RendererConfig& rc) const;
		std::string toStdString(const RendererConfig& rc, ErrorCode& ec) const;

		virtual void assign(const ObjectDesc& desc) = 0;
		virtual void assign(const ObjectNode& other) = 0;
	};

	inline ObjectNode::Iterator::Iterator() : p_(0)
	{
	}

	inline ObjectNode::Iterator::Iterator(Element* p) : p_(p)
	{
	}

	inline ObjectNode::Iterator::Iterator(const Iterator& other) : p_(other.p_)
	{
	}

	inline ObjectNode::Iterator& ObjectNode::Iterator::operator=(const Iterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ObjectNode::Iterator& ObjectNode::Iterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ObjectNode::Iterator ObjectNode::Iterator::operator++(int)
	{
		Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ObjectNode::Iterator& ObjectNode::Iterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ObjectNode::Iterator ObjectNode::Iterator::operator--(int)
	{
		Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ObjectNode::Iterator::operator==(const Iterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ObjectNode::Iterator::operator!=(const Iterator& other) const
	{
		return p_ != other.p_;
	}

	inline ObjectNode::Element* ObjectNode::Iterator::get() const
	{
		return p_;
	}

	inline ObjectNode::Element* ObjectNode::Iterator::operator->()
	{
		return p_;
	}

	inline ObjectNode::Element& ObjectNode::Iterator::operator*()
	{
		return *p_;
	}

	inline ObjectNode::ConstIterator::ConstIterator() : p_(0)
	{
	}

	inline ObjectNode::ConstIterator::ConstIterator(const Element* p) : p_(p)
	{
	}

	inline ObjectNode::ConstIterator::ConstIterator(Iterator it) : p_(it.get())
	{
	}

	inline ObjectNode::ConstIterator::ConstIterator(const ConstIterator& other) : p_(other.p_)
	{
	}

	inline ObjectNode::ConstIterator& ObjectNode::ConstIterator::operator=(const ConstIterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ObjectNode::ConstIterator& ObjectNode::ConstIterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ObjectNode::ConstIterator ObjectNode::ConstIterator::operator++(int)
	{
		const Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ObjectNode::ConstIterator& ObjectNode::ConstIterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ObjectNode::ConstIterator ObjectNode::ConstIterator::operator--(int)
	{
		const Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ObjectNode::ConstIterator::operator==(const ConstIterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ObjectNode::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return p_ != other.p_;
	}

	inline const ObjectNode::Element* ObjectNode::ConstIterator::get() const
	{
		return p_;
	}

	inline const ObjectNode::Element* ObjectNode::ConstIterator::operator->()
	{
		return p_;
	}

	inline const ObjectNode::Element& ObjectNode::ConstIterator::operator*()
	{
		return *p_;
	}

	inline ObjectNode::Element& ObjectNode::first()
	{
		return *begin();
	}

	inline ObjectNode::Element& ObjectNode::last()
	{
		return *--end();
	}

	inline const ObjectNode::Element& ObjectNode::first() const
	{
		return *begin();
	}

	inline const ObjectNode::Element& ObjectNode::last() const
	{
		return *--end();
	}

	inline ObjectNode::Iterator ObjectNode::findNull(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isNull()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findBoolean(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isBoolean()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findString(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isString()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findNumber(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isNumber()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findObject(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isObject()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findArray(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isArray()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findNull(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isNull()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findBoolean(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isBoolean()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findString(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isString()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findNumber(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isNumber()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findObject(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isObject()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findArray(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isArray()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Element& ObjectNode::get(cstring key)
	{
		Iterator it = find(key);

		if (it == end()) {
			ECLOG_FAULT(OutOfRange);
		}

		return *it;
	}

	inline ValueNode& ObjectNode::getValue(cstring key)
	{
		return get(key).value();
	}

	inline NullNode& ObjectNode::getNull(cstring key)
	{
		return getValue(key).asNull();
	}

	inline BooleanNode& ObjectNode::getBoolean(cstring key)
	{
		return getValue(key).asBoolean();
	}

	inline StringNode& ObjectNode::getString(cstring key)
	{
		return getValue(key).asString();
	}

	inline NumberNode& ObjectNode::getNumber(cstring key)
	{
		return getValue(key).asNumber();
	}

	inline ObjectNode& ObjectNode::getObject(cstring key)
	{
		return getValue(key).asObject();
	}

	inline ArrayNode& ObjectNode::getArray(cstring key)
	{
		return getValue(key).asArray();
	}

	inline const ObjectNode::Element& ObjectNode::get(cstring key) const
	{
		ConstIterator it = find(key);

		if (it == end()) {
			ECLOG_FAULT(OutOfRange);
		}

		return *it;
	}

	inline const ValueNode& ObjectNode::getValue(cstring key) const
	{
		return get(key).value();
	}

	inline const NullNode& ObjectNode::getNull(cstring key) const
	{
		return getValue(key).asNull();
	}

	inline const BooleanNode& ObjectNode::getBoolean(cstring key) const
	{
		return getValue(key).asBoolean();
	}

	inline const StringNode& ObjectNode::getString(cstring key) const
	{
		return getValue(key).asString();
	}

	inline const NumberNode& ObjectNode::getNumber(cstring key) const
	{
		return getValue(key).asNumber();
	}

	inline const ObjectNode& ObjectNode::getObject(cstring key) const
	{
		return getValue(key).asObject();
	}

	inline const ArrayNode& ObjectNode::getArray(cstring key) const
	{
		return getValue(key).asArray();
	}

	inline ValueNode& ObjectNode::getOrAddValue(const KeyDesc& key, const ValueDesc& defaultValue)
	{
		Iterator it = find(key.str());

		if (it != end()) {
			return it->value();
		}

		append(key, defaultValue);

		return last().value();
	}

	inline NullNode& ObjectNode::getOrAddNull(const KeyDesc& key, const Null& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asNull();
	}

	inline BooleanNode& ObjectNode::getOrAddBoolean(const KeyDesc& key, bool defaultValue)
	{
		return getOrAddValue(key, defaultValue).asBoolean();
	}

	inline StringNode& ObjectNode::getOrAddString(const KeyDesc& key, const StringDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asString();
	}

	inline NumberNode& ObjectNode::getOrAddNumber(const KeyDesc& key, const NumberDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asNumber();
	}

	inline ObjectNode& ObjectNode::getOrAddObject(const KeyDesc& key, const ObjectDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asObject();
	}

	inline ArrayNode& ObjectNode::getOrAddArray(const KeyDesc& key, const ArrayDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asArray();
	}

	inline bool ObjectNode::append(const ObjectNode::Element& element)
	{
		return insert(end(), element).second;
	}

	inline bool ObjectNode::append(const KeyNode& key, const ValueNode& value)
	{
		return insert(end(), key, value).second;
	}

	inline bool ObjectNode::append(const KeyDesc& key, const ValueNode& value)
	{
		return insert(end(), key, value).second;
	}

	inline bool ObjectNode::append(const KeyNode& key, const ValueDesc& value)
	{
		return insert(end(), key, value).second;
	}

	inline bool ObjectNode::append(const KeyDesc& key, const ValueDesc& value)
	{
		return insert(end(), key, value).second;
	}

	inline void ObjectNode::appendForce(const ObjectNode::Element& element)
	{
		insertForce(end(), element);
	}

	inline void ObjectNode::appendForce(const KeyNode& key, const ValueNode& value)
	{
		insertForce(end(), key, value);
	}

	inline void ObjectNode::appendForce(const KeyDesc& key, const ValueNode& value)
	{
		insertForce(end(), key, value);
	}

	inline void ObjectNode::appendForce(const KeyNode& key, const ValueDesc& value)
	{
		insertForce(end(), key, value);
	}

	inline void ObjectNode::appendForce(const KeyDesc& key, const ValueDesc& value)
	{
		insertForce(end(), key, value);
	}

	inline std::string ObjectNode::toStdString() const
	{
		StdStringOutputStream stream;

		render(stream);

		std::string str;

		str.swap(stream.str());

		return str;
	}

	inline std::string ObjectNode::toStdString(ErrorCode& ec) const
	{
		StdStringOutputStream stream;

		render(stream, ec);

		std::string str;

		str.swap(stream.str());

		return str;
	}

	inline std::string ObjectNode::toStdString(const RendererConfig& rc) const
	{
		StdStringOutputStream stream;

		render(stream, rc);

		std::string str;

		str.swap(stream.str());

		return str;
	}

	inline std::string ObjectNode::toStdString(const RendererConfig& rc, ErrorCode& ec) const
	{
		StdStringOutputStream stream;

		render(stream, rc, ec);

		std::string str;

		str.swap(stream.str());

		return str;
	}

} // eclog
} // vallest

#endif // ECLOG_CPP_OBJECTNODE_H_

