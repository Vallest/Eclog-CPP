// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"
#include "Random.h"

#include <Eclog/Document.h>

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

#include <stdlib.h> // atoi

namespace {

	std::string generateRandKey(Random& rand, int maxValue)
	{
		std::ostringstream os;

		int n = (maxValue > 0 ? rand.next() % maxValue + 1 : 0);

		if (n == 1) {
			os << "";
		}
		else {
			os << "_" << n;
		}

		return os.str();
	}

	std::string generateRandString(Random& rand, int maxLength)
	{
		std::ostringstream os;

		int length = maxLength > 0 ? (maxLength / 2 + rand.next() % (maxLength / 2) + 1) : 0;

		for (int i = 0; i < length; ++i)
		{
			int ch = rand.next() % 36;

			if (ch < 10) {
				ch = ' ';
			}
			else {
				ch = ch - 10 + 'a';
			}

			os << (char)ch;
		}

		return os.str();
	}

	struct ValueDesc
	{
		eclog::NodeType type;
		std::string desc;
	};

	inline bool operator==(const ValueDesc& a, const ValueDesc& b)
	{
		return a.type == b.type && a.desc == b.desc;
	}

	ValueDesc generateRandValueDesc(Random& rand)
	{
		ValueDesc vd;

		vd.type = (eclog::NodeType)(rand.next() % 6 + 1);

		if (vd.type == eclog::node_type_boolean)
		{
			if ((rand.next() & 1) != 0) {
				vd.desc = "t";
			}
		}
		else if (vd.type == eclog::node_type_string)
		{
			vd.desc = generateRandString(rand, 64);
		}
		else if (vd.type == eclog::node_type_number)
		{
			std::ostringstream os;
			os << rand.next() % 4096;
			vd.desc = os.str();
		}

		return vd;
	}

	ValueDesc getValueDesc(const eclog::ValueNode& value)
	{
		ValueDesc vd;

		vd.type = value.nodeType();

		if (value.nodeType() == eclog::node_type_boolean)
		{
			if (value.asBoolean().value()) {
				vd.desc = "t";
			}
		}
		else if (value.nodeType() == eclog::node_type_string)
		{
			eclog::cstring str = value.asString().value();
			vd.desc.assign(str.begin(), str.end());
		}
		else if (value.nodeType() == eclog::node_type_number)
		{
			std::ostringstream os;
			os << value.asNumber().valueInt();
			vd.desc = os.str();
		}

		return vd;
	}

	typedef std::pair<std::string, ValueDesc> KeyValueDescPair;

	class KeyEq {
	public:
		explicit KeyEq(const std::string& key) : key_(key)
		{
		}

		bool operator()(const KeyValueDescPair& p) const
		{
			return p.first == key_;
		}

	private:
		std::string key_;
	};

	void add(std::vector<KeyValueDescPair>& v, const std::string& key, const ValueDesc& vd)
	{
		std::vector<KeyValueDescPair>::iterator it = std::find_if(v.begin(), v.end(), KeyEq(key));

		if (it != v.end()) {
			v.erase(it);
		}

		v.push_back(std::make_pair(key, vd));
	}

	void insert(std::vector<KeyValueDescPair>& v, size_t index, const std::string& key, const ValueDesc& vd)
	{
		std::vector<KeyValueDescPair>::iterator it = v.insert(v.begin() + index, std::make_pair(key, vd));

		std::vector<KeyValueDescPair>::iterator it2 = std::find_if(v.begin(), it, KeyEq(key));

		if (it2 != it)
		{
			v.erase(it2);
		}
		else
		{
			it2 = std::find_if(it + 1, v.end(), KeyEq(key));

			if (it2 != v.end()) {
				v.erase(it2);
			}
		}
	}

	void equal(const eclog::ObjectNode& node, const std::vector<KeyValueDescPair>& v)
	{
		CHECK((v.size() > 0 ? !node.empty() : node.empty()));
		CHECK(node.size() == v.size());

		size_t idx = 0;

		for (eclog::ObjectNode::ConstIterator it = node.begin(); it != node.end(); ++it)
		{
			CHECK((it->key().str() == v[idx].first.c_str()));
			CHECK(getValueDesc(it->value()) == v[idx].second);
			++idx;
		}
	}

	void equal(const eclog::ArrayNode& node, const std::vector<ValueDesc>& v)
	{
		CHECK((v.size() > 0 ? !node.empty() : node.empty()));
		CHECK(node.size() == v.size());

		size_t idx = 0;

		for (eclog::ArrayNode::ConstIterator it = node.begin(); it != node.end(); ++it)
		{
			CHECK(getValueDesc(it->value()) == v[idx]);
			++idx;
		}
	}

	void addRandValues(eclog::ObjectNode& node, Random& rand, int level = 0, int count = 0, bool force = true);
	void addRandValues(eclog::ArrayNode& node, Random& rand, int level = 0, int count = 0, bool force = true);

	void addRandValues(eclog::ObjectNode& node, Random& rand, int level, int count, bool force)
	{
		CHECK(node.empty());
		CHECK(node.size() == 0);

		std::vector<KeyValueDescPair> v;

		if (count == 0) {
			count = rand.next() % 20;
		}

		for (int i = 0; i < count; ++i)
		{
			std::string key = generateRandKey(rand, count);
			ValueDesc vd = generateRandValueDesc(rand);

			switch (vd.type)
			{
			case eclog::node_type_null:
				if (force)
				{
					node.appendForce(key.c_str(), eclog::null);
					add(v, key, vd);
				}
				else if (node.append(key.c_str(), eclog::null))
				{
					add(v, key, vd);
				}
				break;

			case eclog::node_type_boolean:
				if (force)
				{
					node.appendForce(key.c_str(), vd.desc == "t");
					add(v, key, vd);
				}
				else if (node.append(key.c_str(), vd.desc == "t"))
				{
					add(v, key, vd);
				}
				break;

			case eclog::node_type_string:
				if (force)
				{
					node.appendForce(key.c_str(), vd.desc.c_str());
					add(v, key, vd);
				}
				else if (node.append(key.c_str(), vd.desc.c_str()))
				{
					add(v, key, vd);
				}
				break;

			case eclog::node_type_number:
				if (force)
				{
					node.appendForce(key.c_str(), atoi(vd.desc.c_str()));
					add(v, key, vd);
				}
				else if (node.append(key.c_str(), atoi(vd.desc.c_str())))
				{
					add(v, key, vd);
				}
				break;

			case eclog::node_type_object:
				if (level < 3)
				{
					if (force)
					{
						node.appendForce(key.c_str(), eclog::empty_object);
						addRandValues(node.last().value().asObject(), rand, level + 1, 0, force);
						add(v, key, vd);
					}
					else if (node.append(key.c_str(), eclog::empty_object))
					{
						eclog::ObjectNode::Iterator it = --node.end();
						addRandValues(it->value().asObject(), rand, level + 1, 0, force);
						add(v, key, vd);
					}
				}
				break;

			case eclog::node_type_array:
				if (level < 3)
				{
					if (force)
					{
						node.appendForce(key.c_str(), eclog::empty_array);
						addRandValues(node.last().value().asArray(), rand, level + 1, 0, force);
						add(v, key, vd);
					}
					else if (node.append(key.c_str(), eclog::empty_array))
					{
						eclog::ObjectNode::Iterator it = --node.end();
						addRandValues(it->value().asArray(), rand, level + 1, 0, force);
						add(v, key, vd);
					}
				}
				break;

			default:
				FAIL("bad node type");
			}
		}

		equal(node, v);

		CHECK(node.find("a_key_that_does_not_exist") == node.end());
		CHECK(node.findNull("a_key_that_does_not_exist") == node.end());
		CHECK(node.findBoolean("a_key_that_does_not_exist") == node.end());
		CHECK(node.findString("a_key_that_does_not_exist") == node.end());
		CHECK(node.findNumber("a_key_that_does_not_exist") == node.end());
		CHECK(node.findObject("a_key_that_does_not_exist") == node.end());
		CHECK(node.findArray("a_key_that_does_not_exist") == node.end());
	}

	void addRandValues(eclog::ArrayNode& node, Random& rand, int level, int count, bool force)
	{
		CHECK(node.empty());
		CHECK(node.size() == 0);

		std::vector<ValueDesc> v;

		if (count == 0) {
			count = rand.next() % 20;
		}

		for (int i = 0; i < count; ++i)
		{
			ValueDesc vd = generateRandValueDesc(rand);

			switch (vd.type)
			{
			case eclog::node_type_null:
				node.append(eclog::null);
				v.push_back(vd);
				break;

			case eclog::node_type_boolean:
				node.append(vd.desc == "t");
				v.push_back(vd);
				break;

			case eclog::node_type_string:
				node.append(vd.desc.c_str());
				v.push_back(vd);
				break;

			case eclog::node_type_number:
				node.append(atoi(vd.desc.c_str()));
				v.push_back(vd);
				break;

			case eclog::node_type_object:
				if (level <= 3)
				{
					node.append(eclog::empty_object);
					addRandValues(node.last().value().asObject(), rand, level + 1, 0, force);
					v.push_back(vd);
				}
				break;

			case eclog::node_type_array:
				if (level <= 3)
				{
					node.append(eclog::empty_array);
					addRandValues(node.last().value().asArray(), rand, level + 1, 0, force);
					v.push_back(vd);
				}
				break;

			default:
				FAIL("bad node type");
			}
		}

		equal(node, v);
	}

	void insertRandValues(eclog::ObjectNode& node, Random& rand, int level = 0, bool force = true);
	void insertRandValues(eclog::ArrayNode& node, Random& rand, int level = 0, bool force = true);

	void insertRandValues(eclog::ObjectNode& node, Random& rand, int level, bool force)
	{
		CHECK(node.empty());
		CHECK(node.size() == 0);

		std::vector<KeyValueDescPair> v;

		int count = rand.next() % 20;

		for (int i = 0; i < count; ++i)
		{
			int index = (int)(node.size() > 0 ? rand.next() % node.size() : 0);

			eclog::ObjectNode::Iterator pos = node.begin();

			for (int j = 0; j < index; ++j) {
				++pos;
			}

			if (node.size() > 0) {
				CHECK(pos->key().str() == v[index].first.c_str());
			}

			std::string key = generateRandKey(rand, count);
			ValueDesc vd = generateRandValueDesc(rand);

			switch (vd.type)
			{
			case eclog::node_type_null:
				if (force)
				{
					node.insertForce(pos, key.c_str(), eclog::null);
					insert(v, index, key, vd);
				}
				else if (node.insert(pos, key.c_str(), eclog::null).second)
				{
					insert(v, index, key, vd);
				}
				break;

			case eclog::node_type_boolean:
				if (force)
				{
					node.insertForce(pos, key.c_str(), vd.desc == "t");
					insert(v, index, key, vd);
				}
				else if (node.insert(pos, key.c_str(), vd.desc == "t").second)
				{
					insert(v, index, key, vd);
				}
				break;

			case eclog::node_type_string:
				if (force)
				{
					node.insertForce(pos, key.c_str(), vd.desc.c_str());
					insert(v, index, key, vd);
				}
				else if (node.insert(pos, key.c_str(), vd.desc.c_str()).second)
				{
					insert(v, index, key, vd);
				}
				break;

			case eclog::node_type_number:
				if (force)
				{
					node.insertForce(pos, key.c_str(), atoi(vd.desc.c_str()));
					insert(v, index, key, vd);
				}
				else if (node.insert(pos, key.c_str(), atoi(vd.desc.c_str())).second)
				{
					insert(v, index, key, vd);
				}
				break;

			case eclog::node_type_object:
				if (level < 3)
				{
					if (force)
					{
						insertRandValues(node.insertForce(pos, key.c_str(), eclog::empty_object)->value().asObject(), rand, level + 1, force);
						insert(v, index, key, vd);
					}
					else
					{
						eclog::Pair<eclog::ObjectNode::Iterator, bool> result = node.insert(pos, key.c_str(), eclog::empty_object);

						if (result.second)
						{
							insertRandValues(result.first->value().asObject(), rand, level + 1, force);
							insert(v, index, key, vd);
						}
					}
				}
				break;

			case eclog::node_type_array:
				if (level < 3)
				{
					if (force)
					{
						insertRandValues(node.insertForce(pos, key.c_str(), eclog::empty_array)->value().asArray(), rand, level + 1, force);
						insert(v, index, key, vd);
					}
					else
					{
						eclog::Pair<eclog::ObjectNode::Iterator, bool> result = node.insert(pos, key.c_str(), eclog::empty_array);

						if (result.second)
						{
							insertRandValues(result.first->value().asArray(), rand, level + 1, force);
							insert(v, index, key, vd);
						}
					}
				}
				break;

			default:
				FAIL("bad node type");
			}
		}

		equal(node, v);
	}

	void insertRandValues(eclog::ArrayNode& node, Random& rand, int level, bool force)
	{
		CHECK(node.empty());
		CHECK(node.size() == 0);

		std::vector<ValueDesc> v;

		int count = rand.next() % 20;

		for (int i = 0; i < count; ++i)
		{
			int index = (int)(node.size() > 0 ? rand.next() % node.size() : 0);
			eclog::ArrayNode::Iterator pos = node.begin() + index;

			ValueDesc vd = generateRandValueDesc(rand);

			switch (vd.type)
			{
			case eclog::node_type_null:
				node.insert(pos, eclog::null);
				v.insert(v.begin() + index, vd);
				break;

			case eclog::node_type_boolean:
				node.insert(pos, vd.desc == "t");
				v.insert(v.begin() + index, vd);
				break;

			case eclog::node_type_string:
				node.insert(pos, vd.desc.c_str());
				v.insert(v.begin() + index, vd);
				break;

			case eclog::node_type_number:
				node.insert(pos, atoi(vd.desc.c_str()));
				v.insert(v.begin() + index, vd);
				break;

			case eclog::node_type_object:
				if (level <= 3)
				{
					eclog::ArrayNode::Iterator it = node.insert(pos, eclog::empty_object);
					insertRandValues(it->value().asObject(), rand, level + 1, force);
					v.insert(v.begin() + index, vd);
				}
				break;

			case eclog::node_type_array:
				if (level <= 3)
				{
					eclog::ArrayNode::Iterator it = node.insert(pos, eclog::empty_array);
					insertRandValues(it->value().asArray(), rand, level + 1, force);
					v.insert(v.begin() + index, vd);
				}
				break;

			default:
				FAIL("bad node type");
			}
		}

		equal(node, v);
	}

	void access(const eclog::ObjectNode& node);
	void access(const eclog::ArrayNode& node);
	void access(const eclog::ValueNode& node);

	void access(const eclog::ObjectNode& node)
	{
		CHECK((node.empty() ? node.size() == 0 : node.size() > 0));

		size_t count = 0;

		for (eclog::ObjectNode::ConstIterator it = node.begin(); it != node.end(); ++it)
		{
			if (count == 0)
			{
				CHECK(it == node.begin());
				CHECK(it != node.end());
				CHECK(it.get() == node.begin().get());
			}
			else if (count == node.size() - 1)
			{
				CHECK(it != node.end());
				CHECK(it == --node.end());
			}
			else
			{
				CHECK(it != node.begin());
				CHECK(it != node.end());
			}

			CHECK(node.contains(it->key().str()));
			CHECK(node.find(it->key().str()) == it);

			switch (it->value().nodeType())
			{
			case eclog::node_type_null:
				CHECK(node.findNull(it->key().str()) != node.end());
				CHECK(node.getNull(it->key().str()).isNull());
				break;

			case eclog::node_type_boolean:
				CHECK(node.findBoolean(it->key().str()) != node.end());
				CHECK(node.getBoolean(it->key().str()).isBoolean());
				break;

			case eclog::node_type_string:
				CHECK(node.findString(it->key().str()) != node.end());
				CHECK(node.getString(it->key().str()).isString());
				break;

			case eclog::node_type_number:
				CHECK(node.findNumber(it->key().str()) != node.end());
				CHECK(node.getNumber(it->key().str()).isNumber());
				break;

			case eclog::node_type_object:
				CHECK(node.findObject(it->key().str()) != node.end());
				CHECK(node.getObject(it->key().str()).isObject());
				break;

			case eclog::node_type_array:
				CHECK(node.findArray(it->key().str()) != node.end());
				CHECK(node.getArray(it->key().str()).isArray());
				break;

			default:
				FAIL("bad node type");
			}

			access(it->value());

			++count;
		}

		CHECK(count == node.size());
	}

	void access(const eclog::ArrayNode& node)
	{
		CHECK((node.empty() ? node.size() == 0 : node.size() > 0));
		CHECK(node.end() - node.begin() == (int)node.size());
		CHECK(node.end() - node.size() == node.begin());
		CHECK(node.begin() + node.size() == node.end());
		CHECK(node.size() + node.begin() == node.end());

		size_t count = 0;

		for (eclog::ArrayNode::ConstIterator it = node.begin(); it != node.end(); ++it)
		{
			if (count == 0)
			{
				CHECK(it == node.begin());
				CHECK(it != node.end());
				CHECK(it < node.end());
				CHECK(it <= node.end());
				CHECK(node.end() > it);
				CHECK(node.end() >= it);
				CHECK(it.get() == node.begin().get());
			}
			else if (count == node.size() - 1)
			{
				CHECK(it > node.begin());
				CHECK(it >= node.begin());
				CHECK(it != node.end());
				CHECK(it < node.end());
				CHECK(it <= node.end());
				CHECK(it == --node.end());
			}
			else
			{
				CHECK(it != node.begin());
				CHECK(it != node.end());
				CHECK(it > node.begin());
				CHECK(it >= node.begin());
				CHECK(it < node.end());
				CHECK(it <= node.end());
			}

			CHECK(node.begin() + count == it);
			CHECK(count + node.begin() == it);
			CHECK(it - node.begin() == (int)count);
			CHECK(node.indexOf(*it) == count);

			CHECK(node.begin() + count == it);
			CHECK(&node.getValue(count) == &it->value());
			CHECK(it - node.begin() == (int)count);

			switch (it->value().nodeType())
			{
			case eclog::node_type_null:
				CHECK(node.getNull(count).isNull());
				break;

			case eclog::node_type_boolean:
				CHECK(node.getBoolean(count).isBoolean());
				break;

			case eclog::node_type_string:
				CHECK(node.getString(count).isString());
				break;

			case eclog::node_type_number:
				CHECK(node.getNumber(count).isNumber());
				break;

			case eclog::node_type_object:
				CHECK(node.getObject(count).isObject());
				break;

			case eclog::node_type_array:
				CHECK(node.getArray(count).isArray());
				break;

			default:
				FAIL("bad node type");
			}

			access(it->value());

			++count;
		}

		CHECK(count == node.size());
	}

	void access(const eclog::ValueNode& node)
	{
		switch (node.nodeType())
		{
		case eclog::node_type_null:
			CHECK(node.isNull());
			break;

		case eclog::node_type_boolean:
			CHECK(node.isBoolean());
			node.asBoolean().value();
			break;

		case eclog::node_type_string:
			CHECK(node.isString());
			node.asString().value();
			break;

		case eclog::node_type_number:
			CHECK(node.isNumber());
			node.asNumber().value();
			node.asNumber().valueDouble();
			node.asNumber().valueInt();
			node.asNumber().valueUInt();
			node.asNumber().valueLong();
			node.asNumber().valueULong();
			node.asNumber().valueLLong();
			node.asNumber().valueULLong();
			break;

		case eclog::node_type_object:
			CHECK(node.isObject());
			access(node.asObject());
			break;

		case eclog::node_type_array:
			CHECK(node.isArray());
			access(node.asArray());
			break;

		default:
			FAIL("bad node type");
		}
	}

	void equal(const eclog::ValueNode& a, const eclog::ValueNode& b)
	{
		CHECK(a.nodeType() == b.nodeType());

		if (a.nodeType() != b.nodeType()) {
			return;
		}

		switch (a.nodeType())
		{
		case eclog::node_type_boolean:
			CHECK(a.asBoolean().value() == b.asBoolean().value());
			break;

		case eclog::node_type_string:
			CHECK(a.asString().value() == b.asString().value());
			break;

		case eclog::node_type_number:
			CHECK(a.asNumber().value() == b.asNumber().value());
			break;

		case eclog::node_type_object:
			CHECK(a.asObject().size() == b.asObject().size());

			if (a.asObject().size() == b.asObject().size())
			{
				eclog::ObjectNode::ConstIterator it = a.asObject().begin();
				eclog::ObjectNode::ConstIterator it2 = b.asObject().begin();

				for (; it != a.asObject().end(); ++it, ++it2)
				{
					CHECK(it->key().str() == it2->key().str());

					equal(it->value(), it2->value());
				}
			}
			break;

		case eclog::node_type_array:
			CHECK(a.asArray().size() == b.asArray().size());

			if (a.asArray().size() == b.asArray().size())
			{
				for (size_t i = 0; i < a.asArray().size(); ++i)
				{
					equal(a.asArray().at(i).value(), b.asArray().at(i).value());
				}
			}
			break;

		default:
			break;
		}
	}

	void removeValues(Random& rand, eclog::ObjectNode& node);
	void removeValues(Random& rand, eclog::ArrayNode& node);

	void removeValues(Random& rand, eclog::ObjectNode& node)
	{
		std::vector<KeyValueDescPair> v;

		for (eclog::ObjectNode::Iterator it = node.begin(); it != node.end(); ++it)
		{
			eclog::cstring key = it->key().str();

			add(v, std::string(key.begin(), key.end()), getValueDesc(it->value()));
		}

		equal(node, v);

		while (!node.empty())
		{
			int index1 = (int)(node.size() > 0 ? rand.next() % node.size() : 0);
			int index2 = (int)(node.size() > 0 ? rand.next() % node.size() : 0);

			if (index1 > index2) {
				std::swap(index1, index2);
			}

			if (rand.next() % 100 > 10)
			{
				eclog::ObjectNode::Iterator it = node.begin();

				for (int i = 0; i < index1; ++i) {
					++it;
				}

				if (it->value().nodeType() == eclog::node_type_object && rand.next() % 100 > 20)
				{
					removeValues(rand, it->value().asObject());
				}
				else if (it->value().nodeType() == eclog::node_type_array && rand.next() % 100 > 20)
				{
					removeValues(rand, it->value().asArray());
				}

				if (rand.next() % 100 > 50)
				{
					node.remove(it->key().str());

					v.erase(v.begin() + index1);

					equal(node, v);
				}
				else
				{
					node.remove(it);

					v.erase(v.begin() + index1);

					equal(node, v);
				}
			}
			else
			{
				eclog::ObjectNode::Iterator it1 = node.begin();

				for (int i = 0; i < index1; ++i) {
					++it1;
				}

				eclog::ObjectNode::Iterator it2 = node.begin();

				for (int i = 0; i < index2 + 1; ++i) {
					++it2;
				}

				node.remove(it1, it2);

				v.erase(v.begin() + index1, v.begin() + index2 + 1);

				equal(node, v);
			}
		}
	}

	void removeValues(Random& rand, eclog::ArrayNode& node)
	{
		std::vector<ValueDesc> v;

		for (eclog::ArrayNode::Iterator it = node.begin(); it != node.end(); ++it)
		{
			v.push_back(getValueDesc(it->value()));
		}

		equal(node, v);

		while (!node.empty())
		{
			int index1 = (int)(node.size() > 0 ? rand.next() % node.size() : 0);
			int index2 = (int)(node.size() > 0 ? rand.next() % node.size() : 0);

			if (index1 > index2) {
				std::swap(index1, index2);
			}

			if (rand.next() % 100 > 10)
			{
				eclog::ArrayNode::Iterator it = node.begin() + index1;

				if (it->value().nodeType() == eclog::node_type_object && rand.next() % 100 > 20)
				{
					removeValues(rand, it->value().asObject());
				}
				else if (it->value().nodeType() == eclog::node_type_array && rand.next() % 100 > 20)
				{
					removeValues(rand, it->value().asArray());
				}

				if (rand.next() % 100 > 50)
				{
					node.remove(it);

					v.erase(v.begin() + index1);

					equal(node, v);
				}
				else
				{
					node.remove(index1);

					v.erase(v.begin() + index1);

					equal(node, v);
				}
			}
			else
			{
				if (rand.next() % 100 > 50)
				{
					eclog::ArrayNode::Iterator it1 = node.begin() + index1;
					eclog::ArrayNode::Iterator it2 = node.begin() + index2 + 1;

					node.remove(it1, it2);

					v.erase(v.begin() + index1, v.begin() + index2 + 1);

					equal(node, v);
				}
				else
				{
					node.remove(index1, index2 - index1 + 1);

					v.erase(v.begin() + index1, v.begin() + index2 + 1);

					equal(node, v);
				}
			}
		}
	}
}

TEST_CASE("Document")
{
	SUBCASE("Construct #1")
	{
		eclog::BasicDocument<DebugAllocator> doc;

		CHECK(doc.empty());
	}

	SUBCASE("Construct #2")
	{
		typedef eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> PD;

		PD pd[] =
		{
			PD("a", eclog::null),
			PD("b", true),
			PD("c", 1.0),
			PD("d", "Hello World"),
		};

		eclog::BasicDocument<DebugAllocator> doc(pd);

		CHECK(doc.size() == 4);
		CHECK(doc.getValue("a").isNull());
		CHECK(doc.getValue("b").asBoolean().value() == true);
		CHECK(doc.getValue("c").asNumber().value() == 1.0);
		CHECK(doc.getValue("d").asString().value() == "Hello World");
	}

	SUBCASE("Add")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(78949);

		addRandValues(doc, rand);
	}

	SUBCASE("Add #2")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(78949);

		addRandValues(doc, rand, 0, 0, false);
	}

	SUBCASE("Insert")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(29471);

		insertRandValues(doc, rand);

		access(doc);
	}

	SUBCASE("Insert #2")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(29471);

		insertRandValues(doc, rand, 0, false);

		access(doc);
	}

	SUBCASE("Access #1")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		doc.append("empty_obj", eclog::empty_object);
		doc.append("empty_array", eclog::empty_array);

		access(doc);
	}

	SUBCASE("Access #2")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(41398);

		addRandValues(doc, rand);

		access(doc);
	}

	SUBCASE("Copy Construct #1")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(7894);

		addRandValues(doc, rand);

		eclog::BasicDocument<DebugAllocator> doc2(doc);

		equal(doc, doc2);
	}

	SUBCASE("Copy Construct #2")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(9810);

		addRandValues(doc, rand);

		eclog::BasicDocument<DebugAllocator> doc2(doc);

		equal(doc, doc2);
	}

	SUBCASE("Copy Construct #3")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(39187);

		addRandValues(doc, rand);

		eclog::BasicDocument<DebugAllocator> doc2(doc);

		equal(doc, doc2);
	}

	SUBCASE("Assign #1")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(31605);

		addRandValues(doc, rand);

		eclog::BasicDocument<DebugAllocator> doc2;

		doc2 = doc;

		equal(doc, doc2);
	}

	SUBCASE("Assign #2")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;
		eclog::BasicDocument<DebugAllocator> doc2;

		Random rand(31605);

		addRandValues(doc, rand);
		addRandValues(doc2, rand);

		doc2 = doc;

		equal(doc, doc2);
	}

	SUBCASE("Assign #3")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(31605);

		addRandValues(doc, rand);

		eclog::BasicDocument<DebugAllocator> doc2;

		doc2 = doc;

		equal(doc, doc2);
	}

	SUBCASE("Assign #4")
	{
		typedef eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> PD;

		PD pd[] =
		{
			PD("a", eclog::null),
			PD("b", true),
			PD("c", 1.0),
			PD("d", "Hello World"),
		};

		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(31605);

		addRandValues(doc, rand);

		doc = pd;

		CHECK(doc.getValue("a").isNull());
		CHECK(doc.getValue("b").asBoolean().value() == true);
		CHECK(doc.getValue("c").asNumber().value() == 1.0);
		CHECK(doc.getValue("d").asString().value() == "Hello World");
	}

	SUBCASE("Merge")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;
		eclog::BasicDocument<DebugAllocator> patch;
		eclog::BasicDocument<DebugAllocator> check;

		doc.parse("a: b");
		patch.parse("a: c");
		doc.merge(patch);
		check.parse("a: c");

		equal(doc, check);

		doc.parse("a: b");
		patch.parse("b: c");
		doc.merge(patch);
		check.parse("a: b, b: c");

		equal(doc, check);

		doc.parse("a: b");
		patch.parse("a: null");
		doc.merge(patch);
		check.parse("");

		equal(doc, check);

		doc.parse("a: b, b: c");
		patch.parse("a: null");
		doc.merge(patch);
		check.parse("b: c");

		equal(doc, check);

		doc.parse("a: [b]");
		patch.parse("a: c");
		doc.merge(patch);
		check.parse("a: c");

		equal(doc, check);

		doc.parse("a: c");
		patch.parse("a: [b]");
		doc.merge(patch);
		check.parse("a: [b]");

		equal(doc, check);

		doc.parse("a: {b: c}");
		patch.parse("a: {b: d, c: null}");
		doc.merge(patch);
		check.parse("a: {b: d}");

		equal(doc, check);

		doc.parse("a: [{b: c}]");
		patch.parse("a: [1]");
		doc.merge(patch);
		check.parse("a: [1]");

		equal(doc, check);

		doc.parse("e: null");
		patch.parse("a: 1");
		doc.merge(patch);
		check.parse("e: null, a: 1");

		equal(doc, check);

		doc.parse("");
		patch.parse("a: {bb: {ccc: null}}");
		doc.merge(patch);
		check.parse("a: {bb: {}}");

		equal(doc, check);

		doc.parse("a: {b: {c: true}}");
		patch.parse("a: {b: {c: {d: null}}}");
		doc.merge(patch);
		check.parse("a: {b: {c: {}}}");

		equal(doc, check);
	}

	SUBCASE("Clear")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(9381);

		addRandValues(doc, rand);

		CHECK(!doc.empty());
		CHECK(doc.size() > 0);

		doc.clear();

		CHECK(doc.empty());
		CHECK(doc.size() == 0);
	}

	SUBCASE("Remove")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(82613);

		addRandValues(doc, rand, 0, 100);

		removeValues(rand, doc);
	}

	SUBCASE("Parse")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(74322);

		addRandValues(doc, rand);

		doc.parse("empty_obj: {}");

		CHECK(doc.size() == 1);
		CHECK(doc.findObject("empty_obj") != doc.end());
	}

	SUBCASE("Parse #2")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(98320);

		addRandValues(doc, rand);

		std::string text;

		if (!loadTextFile("Person.ecl", text))
		{
			getOutStream() << "Failed to load Person.ecl\n";
			return;
		}

		doc.parse(text);

		eclog::ObjectNode::Iterator it;

		it = doc.findObject("address");
		CHECK(it != doc.end());

		it = it->value().asObject().findString("state");
		CHECK(it != doc.end());

		CHECK(it->key().notation() == eclog::string_notation_unquoted);
		CHECK(it->value().asString().notation() == eclog::string_notation_unquoted);
	}

	SUBCASE("Object IO")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(892342);

		addRandValues(doc.getOrAddObject("obj"), rand);
		addRandValues(doc.getOrAddObject("obj2"), rand);

		std::ostringstream oss;

		doc.getObject("obj").render(oss);

		std::string text = oss.str();

		std::istringstream iss(text);

		doc.getObject("obj2").parse(iss);

		equal(doc.getObject("obj"), doc.getObject("obj2"));
	}

	SUBCASE("Object IO #2")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		Random rand(892342);

		addRandValues(doc.getOrAddObject("obj"), rand);
		addRandValues(doc.getOrAddObject("obj2"), rand);

		std::string text = doc.getObject("obj").toStdString();

		doc.getObject("obj2").parse(text);

		equal(doc.getObject("obj"), doc.getObject("obj2"));
	}

	SUBCASE("Object IO String")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		doc.parse("str: \"Hello \" + @dd\"World\"dd");

		std::string text = doc.toStdString();

		CHECK(text == "str: \"Hello World\"\n");
	}

	SUBCASE("GetOrAdd")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		doc.getOrAddObject("obj").getOrAddNull("null");
		doc.getOrAddObject("obj").getOrAddBoolean("boolean", true);
		doc.getOrAddObject("obj").getOrAddString("str", "Hello");
		doc.getOrAddObject("obj").getOrAddBoolean("boolean", false);
		doc.getOrAddObject("obj").getOrAddString("str", eclog::StringDesc("Hello", eclog::string_notation_raw));
		doc.getOrAddObject("obj").getOrAddNumber("number", 0.0);
		doc.getOrAddObject("obj").getOrAddNumber("number", eclog::NumberDesc(1, -1));
		doc.getOrAddObject("obj").getOrAddNumber("number", eclog::Number(1.0));
		doc.getOrAddObject("obj").getOrAddObject("object");
		doc.getOrAddObject("obj").getOrAddObject("object").getOrAddNull("null");
		doc.getOrAddObject("obj").getOrAddArray("array").append(eclog::null);
		doc.getOrAddObject("obj").getOrAddArray("array").append(true);

		CHECK(doc.getOrAddObject("obj").size() == 6);
		CHECK(doc.getOrAddObject("obj").findNull("null") != doc.getOrAddObject("obj").end());
		CHECK(doc.getOrAddObject("obj").getBoolean("boolean").value() == true);
		CHECK(doc.getOrAddObject("obj").getString("str").value() == "Hello");
		CHECK(doc.getOrAddObject("obj").getNumber("number").value().underlyingType() == eclog::Number::underlying_type_double);
		CHECK(doc.getOrAddObject("obj").getNumber("number").valueDouble() == 0.0);
		CHECK(doc.getOrAddObject("obj").getObject("object").contains("null"));
		CHECK(doc.getOrAddObject("obj").getArray("array").size() == 2);
	}

	SUBCASE("UpdateValue")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		eclog::ObjectNode& objectNode = doc.getOrAddObject("obj");

		objectNode.append("1", eclog::null);
		objectNode.append("2", true);
		objectNode.append("3", "Hello World");
		objectNode.append("4", 1.0 / 7.0);
		objectNode.append("5", eclog::empty_object);
		objectNode.append("6", eclog::empty_array);

		doc.append("obj2", objectNode);

		eclog::ArrayNode& arrayNode = doc.getOrAddArray("array");

		arrayNode.append(eclog::null);
		arrayNode.append(true);
		arrayNode.append("Hello World");
		arrayNode.append(1.0 / 7.0);
		arrayNode.append(eclog::empty_object);
		arrayNode.append(eclog::empty_array);
		arrayNode.append(doc.getValue("obj2"));

		doc.append("array2", arrayNode);

		objectNode.get("1").updateValue(objectNode.getValue("6"));
		CHECK(objectNode.getValue("1").isArray());

		objectNode.get("1").updateValue(objectNode.getValue("5"));
		CHECK(objectNode.getValue("1").isObject());

		objectNode.get("1").updateValue(objectNode.getValue("4"));
		CHECK(objectNode.getNumber("1").valueDouble() == 1.0 / 7.0);

		objectNode.get("1").updateValue(objectNode.getValue("3"));
		CHECK(objectNode.getString("1").value() == "Hello World");

		objectNode.get("1").updateValue(objectNode.getValue("2"));
		CHECK(objectNode.getBoolean("1").value() == true);

		objectNode.get("1").updateValue(eclog::null);
		CHECK(objectNode.getValue("1").isNull());

		objectNode.get("6").updateValue(false);
		CHECK(objectNode.getBoolean("6").value() == false);

		objectNode.get("5").updateValue("FooBar");
		CHECK(objectNode.getString("5").value() == "FooBar");

		objectNode.get("3").updateValue(0.0);
		CHECK(objectNode.getNumber("3").valueInt() == 0);

		objectNode.get("1").updateValue(eclog::empty_object);
		CHECK(objectNode.getValue("1").isObject());

		objectNode.get("2").updateValue(eclog::empty_array);
		CHECK(objectNode.getValue("2").isArray());

		objectNode.get("1").updateValue(doc);
		CHECK(objectNode.getObject("1").getObject("obj2").getValue("1").isNull());
		CHECK(objectNode.getObject("1").getObject("obj2").getNumber("4").valueDouble() == 1.0 / 7.0);

		objectNode.get("1").updateValue(arrayNode);
		CHECK(objectNode.getArray("1").size() == 7);
		CHECK(objectNode.getArray("1").getString(2).value() == "Hello World");

		arrayNode.at(0).updateValue(arrayNode.getValue(5));
		CHECK(arrayNode.getValue(0).isArray());

		arrayNode.at(0).updateValue(arrayNode.getValue(4));
		CHECK(arrayNode.getValue(0).isObject());

		arrayNode.at(0).updateValue(arrayNode.getValue(3));
		CHECK(arrayNode.getNumber(0).valueDouble() == 1.0 / 7.0);

		arrayNode.at(0).updateValue(arrayNode.getValue(2));
		CHECK(arrayNode.getString(0).value() == "Hello World");

		arrayNode.at(0).updateValue(arrayNode.getValue(1));
		CHECK(arrayNode.getBoolean(0).value() == true);

		arrayNode.at(0).updateValue(eclog::null);
		CHECK(arrayNode.getValue(0).isNull());

		arrayNode.at(5).updateValue(false);
		CHECK(arrayNode.getBoolean(5).value() == false);

		arrayNode.at(4).updateValue("FooBar");
		CHECK(arrayNode.getString(4).value() == "FooBar");

		arrayNode.at(2).updateValue(0.0);
		CHECK(arrayNode.getNumber(2).valueInt() == 0);

		arrayNode.at(0).updateValue(eclog::empty_object);
		CHECK(arrayNode.getValue(0).isObject());

		arrayNode.at(1).updateValue(eclog::empty_array);
		CHECK(arrayNode.getValue(1).isArray());

		arrayNode.at(0).updateValue(doc);
		CHECK(arrayNode.getObject(0).getObject("obj2").getValue("1").isNull());
		CHECK(arrayNode.getObject(0).getObject("obj2").getNumber("4").valueDouble() == 1.0 / 7.0);

		arrayNode.at(0).updateValue(doc.getValue("array2"));
		CHECK(arrayNode.getArray(0).size() == 7);
		CHECK(arrayNode.getArray(0).getString(2).value() == "Hello World");
		CHECK(arrayNode.getArray(0).getObject(6).size() == 6);
		CHECK(arrayNode.getArray(0).getObject(6).getString("3").value() == "Hello World");
		CHECK(arrayNode.getArray(0).getObject(6).getNumber("4").valueDouble() == 1.0 / 7.0);
	}

	SUBCASE("Iterator Copy")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		eclog::ObjectNode& objectNode = doc.getOrAddObject("obj");
		eclog::ArrayNode& arrayNode = doc.getOrAddArray("array");

		Random rand(65095);

		addRandValues(objectNode, rand);
		addRandValues(arrayNode, rand);

		eclog::BasicDocument<DebugAllocator> doc2;

		eclog::ObjectNode& objectNode2 = doc2.getOrAddObject("obj");
		eclog::ArrayNode& arrayNode2 = doc2.getOrAddArray("array");

		for (eclog::ObjectNode::ConstIterator it = objectNode.begin(); it != objectNode.end(); ++it)
		{
			objectNode2.append(*it);
		}

		for (eclog::ArrayNode::ConstIterator it = arrayNode.begin(); it != arrayNode.end(); ++it)
		{
			arrayNode2.append(*it);
		}

		equal(doc, doc2);
	}

	SUBCASE("Nested Desc")
	{
		typedef eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> PD;
		typedef eclog::ValueDesc VD;

		PD pd3[] =
		{
			PD( "a", eclog::null ),
			PD( "b", true ),
			PD( "c", 1.0 ),
			PD( "d", "Hello World" ),
		};

		VD vd[] =
		{
			VD( eclog::null ),
			VD( true ),
			VD( 1.0 ),
			VD( "Hello World" ),
			VD( pd3 ),
		};

		PD pd2[] =
		{
			PD( "a", eclog::null ),
			PD( "b", true ),
			PD( "c", 1.0 ),
			PD( "d", "Hello World" ),
			PD( "e", vd ),
		};

		PD pd[] =
		{
			PD( "1", eclog::null ),
			PD( "2", true ),
			PD( "3", 1.0 ),
			PD( "4", "Hello World" ),
			PD( "5", pd2 ),
		};

		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		doc.assign(pd);

		CHECK(doc.getValue("1").isNull());
		CHECK(doc.getValue("2").asBoolean().value() == true);
		CHECK(doc.getValue("3").asNumber().value() == 1.0);
		CHECK(doc.getValue("4").asString().value() == "Hello World");
		CHECK(doc.getObject("5").getValue("a").isNull());
		CHECK(doc.getObject("5").getValue("b").asBoolean().value() == true);
		CHECK(doc.getObject("5").getValue("c").asNumber().value() == 1.0);
		CHECK(doc.getObject("5").getValue("d").asString().value() == "Hello World");
		CHECK(doc.getObject("5").getArray("e").getNull(0).isNull());
		CHECK(doc.getObject("5").getArray("e").getBoolean(1).value() == true);
		CHECK(doc.getObject("5").getArray("e").getNumber(2).value() == 1.0);
		CHECK(doc.getObject("5").getArray("e").getString(3).value() == "Hello World");
		CHECK(doc.getObject("5").getArray("e").getObject(4).getValue("a").isNull());
		CHECK(doc.getObject("5").getArray("e").getObject(4).getValue("b").asBoolean().value() == true);
		CHECK(doc.getObject("5").getArray("e").getObject(4).getValue("c").asNumber().value() == 1.0);
		CHECK(doc.getObject("5").getArray("e").getObject(4).getValue("d").asString().value() == "Hello World");
	}

	SUBCASE("Render")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		doc.append("empty_obj", eclog::empty_object);

		std::ostringstream os;

		eclog::RendererConfig rc;

		rc.formatting = eclog::RendererConfig::formatting_compact;

		doc.render(os, rc);

		CHECK(os.str() == "empty_obj:{}");
	}

	SUBCASE("String Delimiter")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		std::string text = "@\"str\": @ddd\"Hello World\"ddd\n@qqq\"str2\"qqq: |EOF\n\theredoc\n\tEOF\nstr3: @sss\"\"sss\n";

		doc.parse(text);

		std::ostringstream os;

		doc.render(os);

		CHECK(os.str() == text);
	}

	SUBCASE("String")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		doc.append("str", eclog::ValueDesc("Hello World", eclog::string_notation_raw));

		std::ostringstream os;

		doc.render(os);

		CHECK(os.str() == "str: @\"Hello World\"\n");
	}

	SUBCASE("Number")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		doc.append("a", 1);
		doc.append("b", 2ul);
		doc.append("n", 1.0 / 7.0);
		doc.append("m", eclog::ValueDesc(1.0 / 7.0, 2));

		CHECK(doc.getNumber("a").value().underlyingType() == eclog::Number::underlying_type_int);
		CHECK(doc.getNumber("b").value().underlyingType() == eclog::Number::underlying_type_ulong);
		CHECK(doc.getNumber("n").value().underlyingType() == eclog::Number::underlying_type_double);
		CHECK(doc.getNumber("m").value().underlyingType() == eclog::Number::underlying_type_double);
	}

	SUBCASE("Swap")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;
		eclog::BasicDocument<DebugAllocator> doc2;

		Random rand(201925);

		addRandValues(doc, rand);
		addRandValues(doc2, rand);

		eclog::BasicDocument<DebugAllocator> doc3(doc);
		eclog::BasicDocument<DebugAllocator> doc4(doc2);

		eclog::swap(doc3, doc4);

		equal(doc, doc4);
		equal(doc2, doc3);
	}
}

#if defined(ECLOG_TEST_CPP11)
TEST_CASE("Document #CPP11")
{
	SUBCASE("Initializer List")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;

		eclog::ValueDesc vd[]
		{
			eclog::null,
			true,
			1.0,
			"Hello World"
		};

		eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> pd2[]
		{
			{ "a", eclog::null },
			{ "b", true },
			{ "c", 1.0 },
			{ "d", "Hello World" },
			{ "e", vd },
		};

		eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> pd[]
		{
			{ "1", eclog::null },
			{ "2", true },
			{ "3", 1.0 },
			{ "4", "Hello World" },
			{ "5", pd2 },
		};

		doc.assign(pd);

		CHECK(doc.getValue("1").isNull());
		CHECK(doc.getValue("2").asBoolean().value() == true);
		CHECK(doc.getValue("3").asNumber().value() == 1.0);
		CHECK(doc.getValue("4").asString().value() == "Hello World");
		CHECK(doc.getObject("5").getValue("a").isNull());
		CHECK(doc.getObject("5").getValue("b").asBoolean().value() == true);
		CHECK(doc.getObject("5").getValue("c").asNumber().value() == 1.0);
		CHECK(doc.getObject("5").getValue("d").asString().value() == "Hello World");
		CHECK(doc.getObject("5").getArray("e").getValue(0).isNull());
		CHECK(doc.getObject("5").getArray("e").getBoolean(1).value() == true);
		CHECK(doc.getObject("5").getArray("e").getNumber(2).value() == 1.0);
		CHECK(doc.getObject("5").getArray("e").getString(3).value() == "Hello World");
	}

	SUBCASE("Range-Based For Loop #Object")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;
		eclog::BasicDocument<DebugAllocator> doc2;

		Random rand(201925);

		addRandValues(doc, rand);

		for (const auto& element : doc)
		{
			doc2.append(element);
		}

		equal(doc, doc2);

		for (auto& element : doc)
		{
			element.updateValue(1.0);
			CHECK(element.value().isNumber());
		}
	}

	SUBCASE("Range-Based For Loop #Array")
	{
		MemoryLeakDetector mld;

		eclog::BasicDocument<DebugAllocator> doc;
		eclog::BasicDocument<DebugAllocator> doc2;

		eclog::ArrayNode& array = doc.getOrAddArray("array", eclog::empty_array);
		eclog::ArrayNode& array2 = doc2.getOrAddArray("array", eclog::empty_array);

		Random rand(7354);

		addRandValues(array, rand);

		for (const auto& element : array)
		{
			array2.append(element);
		}

		equal(array, array2);

		for (auto& element : array)
		{
			element.updateValue(1.0);
			CHECK(element.value().isNumber());
		}
	}

	SUBCASE("Merge")
	{
		MemoryLeakDetector mld;

		eclog::ValueDesc vd[]
		{
			eclog::null,
			true,
			1.0,
			"Hello World"
		};

		eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> pd[]
		{
			{ "a", eclog::null },
			{ "b", true },
			{ "c", 1.0 },
			{ "d", "Hello World" },
			{ "e", vd },
		};

		eclog::Pair<eclog::KeyDesc, eclog::ValueDesc> pd2[]
		{
			{ "a", vd },
			{ "b", false },
			{ "c", 2.0 },
			{ "e", eclog::null },
			{ "f", "FooBar" },
			{ "g", 12 },
		};

		eclog::BasicDocument<DebugAllocator> doc(pd);
		eclog::BasicDocument<DebugAllocator> check;

		check.parse("a: null, b: true, c: 1, d: \"Hello World\", e: [null, true, 1.0, \"Hello World\"]");

		equal(doc, check);

		doc.merge(pd2);

		check.parse("a: [null, true, 1, \"Hello World\"], b: false, c: 2, d: \"Hello World\", f: \"FooBar\", g: 12.0");

		equal(doc, check);
	}
}
#endif

