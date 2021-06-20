// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"
#include "DebugObject.h"
#include "Random.h"

#include <Eclog/Detail/Vector.h>

#include <algorithm>
#include <vector>

using namespace vallest;

TEST_CASE("Vector")
{
	SUBCASE("Push Back")
	{
		MemoryLeakDetector mld;
		ObjectLeakDetector old;
		Random rand;

		eclog::detail::Vector<DebugObject, DebugAllocator> v;

		int sum = 0;

		for (int i = 0; i < 10; ++i)
		{
			sum += i;

			v.pushBack(i);
		}

		for (int i = 0; i < 90; ++i)
		{
			size_t index = (size_t)rand.next() % v.size();

			sum += v[index].value();

			v.pushBack(v[index]);
		}

		int sum2 = 0;

		for (size_t i = 0; i < v.size(); ++i)
		{
			sum2 += v[i].value();
		}

		CHECK(sum == sum2);
	}

	SUBCASE("Insert")
	{
		MemoryLeakDetector mld;
		ObjectLeakDetector old;
		Random rand;

		eclog::detail::Vector<DebugObject, DebugAllocator> v;

		int sum = 0;

		for (int i = 0; i < 10; ++i)
		{
			sum += i;

			v.insert(0, i);
		}

		for (int i = 0; i < 90; ++i)
		{
			size_t index = (size_t)rand.next() % v.size();

			sum += v[index].value();

			v.insert(rand.next() % 100, v[index]);
		}

		int sum2 = 0;

		for (size_t i = 0; i < v.size(); ++i)
		{
			sum2 += v[i].value();
		}

		CHECK(sum == sum2);
	}

	SUBCASE("Reserve")
	{
		MemoryLeakDetector mld;
		ObjectLeakDetector old;
		Random rand;

		eclog::detail::Vector<DebugObject, DebugAllocator> v;

		v.reserve(10);

		CHECK(v.empty());
		CHECK(v.size() == 0);
		CHECK(v.capacity() == 10);
		CHECK(DebugObject::count() == 0);

		for (int i = 0; i < 50; ++i)
		{
			v.insert(rand.next() % 100, i);
		}

		CHECK(!v.empty());
		CHECK(v.size() == 50);
		CHECK(v.capacity() >= 50);
		CHECK(DebugObject::count() == 50);

		v.reserve(100);

		CHECK(v.size() == 50);
		CHECK(v.capacity() == 100);
		CHECK(DebugObject::count() == 50);

		for (int i = 0; i < 50; ++i)
		{
			v.insert(rand.next() % 100, i);
		}

		CHECK(v.size() == 100);
		CHECK(v.capacity() >= 100);
		CHECK(DebugObject::count() == 100);
	}

	SUBCASE("Clear")
	{
		MemoryLeakDetector mld;
		ObjectLeakDetector old;
		Random rand;

		eclog::detail::Vector<DebugObject, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.insert(rand.next() % 100, i);
		}

		v.clear();

		CHECK(v.empty());
		CHECK(v.size() == 0);
		CHECK(DebugObject::count() == 0);
	}

	SUBCASE("Copy")
	{
		MemoryLeakDetector mld;
		ObjectLeakDetector old;

		eclog::detail::Vector<DebugObject, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.pushBack(i);
		}

		eclog::detail::Vector<DebugObject, DebugAllocator> v2(v);

		CHECK(!v2.empty());
		CHECK(v2.size() == 100);
		CHECK(v2.capacity() == 100);
		CHECK(DebugObject::count() == 200);

		for (size_t i = 0; i < v2.size(); ++i)
		{
			CHECK(v2[i].value() == (int)i);
		}
	}

	SUBCASE("Copy Assignment")
	{
		MemoryLeakDetector mld;
		ObjectLeakDetector old;
		Random rand;

		eclog::detail::Vector<DebugObject, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.pushBack(i);
		}

		eclog::detail::Vector<DebugObject, DebugAllocator> v2;

		for (int i = 0; i < 50; ++i)
		{
			v2.insert(rand.next() % 100, i * 2 + 1);
		}

		v2 = v;

		CHECK(!v2.empty());
		CHECK(v2.size() == 100);
		CHECK(DebugObject::count() == 200);

		for (size_t i = 0; i < v2.size(); ++i)
		{
			CHECK(v2[i].value() == (int)i);
		}

		eclog::detail::Vector<DebugObject, DebugAllocator> v3;

		v3.reserve(50);

		for (int i = 0; i < 50; ++i)
		{
			v3.insert(rand.next() % 100, i * 2 + 1);
		}

		v3.reserve(200);

		v3 = v;

		CHECK(!v3.empty());
		CHECK(v3.size() == 100);
		CHECK(v3.capacity() == 200);
		CHECK(DebugObject::count() == 300);

		for (size_t i = 0; i < v3.size(); ++i)
		{
			CHECK(v3[i].value() == (int)i);
		}

		eclog::detail::Vector<DebugObject, DebugAllocator> v4;

		for (int i = 0; i < 200; ++i)
		{
			v4.insert(rand.next() % 100, i * 2 + 1);
		}

		v4 = v;

		CHECK(!v4.empty());
		CHECK(v4.size() == 100);
		CHECK(DebugObject::count() == 400);

		for (size_t i = 0; i < v4.size(); ++i)
		{
			CHECK(v4[i].value() == (int)i);
		}

		v.clear();
		v4 = v;

		CHECK(v4.empty());
		CHECK(v4.size() == 0);
		CHECK(DebugObject::count() == 200);
	}

	SUBCASE("Remove")
	{
		MemoryLeakDetector mld;
		ObjectLeakDetector old;

		eclog::detail::Vector<DebugObject, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.pushBack(i);
		}

		v.remove(0, 10);

		CHECK(v.size() == 90);
		CHECK(v.capacity() >= 100);
		CHECK(DebugObject::count() == 90);

		for (size_t i = 0; i < v.size(); ++i)
		{
			CHECK(v[i].value() == (int)i + 10);
		}

		v.remove(10, 10);

		CHECK(v.size() == 80);
		CHECK(v.capacity() >= 100);
		CHECK(DebugObject::count() == 80);

		for (size_t i = 10; i < v.size(); ++i)
		{
			CHECK(v[i].value() == (int)i + 20);
		}

		v.remove(10, (size_t)-1);

		CHECK(v.size() == 10);
		CHECK(v.capacity() >= 100);
		CHECK(DebugObject::count() == 10);

		for (size_t i = 0; i < v.size(); ++i)
		{
			CHECK(v[i].value() == (int)i + 10);
		}
	}
}

