// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"
#include "Random.h"

#include <Eclog/Detail/PODArray.h>

#include <algorithm>
#include <vector>

using namespace vallest;

TEST_CASE("PODArray")
{
	SUBCASE("Push Back")
	{
		MemoryLeakDetector mld;
		Random rand;

		eclog::detail::PODArray<int, DebugAllocator> v;

		int sum = 0;

		for (int i = 0; i < 10; ++i)
		{
			sum += i;

			v.pushBack(i);
		}

		for (int i = 0; i < 90; ++i)
		{
			size_t index = (size_t)rand.next() % v.size();

			sum += v[index];

			v.pushBack(v[index]);
		}

		int sum2 = 0;

		for (size_t i = 0; i < v.size(); ++i)
		{
			sum2 += v[i];
		}

		CHECK(sum == sum2);
	}

	SUBCASE("Append")
	{
		MemoryLeakDetector mld;
		Random rand;

		eclog::detail::PODArray<char, DebugAllocator> v;

		size_t sum = 0;

		for (size_t i = 0; i < 10; ++i)
		{
			sum += i;

			v.append((const char*)&i, sizeof(size_t));
		}

		for (size_t i = 0; i < 90; ++i)
		{
			size_t index = (size_t)rand.next() % (v.size() / sizeof(size_t));

			sum += *(size_t*)(v.data() + index * sizeof(size_t));

			v.append(v.data() + (index * sizeof(size_t)), sizeof(size_t));
		}

		size_t sum2 = 0;

		for (size_t i = 0; i < 100; ++i)
		{
			sum2 += *(size_t*)(v.data() + i * sizeof(size_t));
		}

		CHECK(sum == sum2);
	}

	SUBCASE("Insert")
	{
		MemoryLeakDetector mld;
		Random rand;

		eclog::detail::PODArray<char, DebugAllocator> v;

		size_t sum = 0;

		for (size_t i = 0; i < 10; ++i)
		{
			sum += i;

			v.insert(0, (const char*)&i, sizeof(size_t));
		}

		for (size_t i = 0; i < 90; ++i)
		{
			size_t index = (size_t)rand.next() % (v.size() / sizeof(size_t));

			sum += *(size_t*)(v.data() + index * sizeof(size_t));

			v.insert(index * sizeof(size_t), v.data() + (index * sizeof(size_t)), sizeof(size_t));
		}

		size_t sum2 = 0;

		for (size_t i = 0; i < 100; ++i)
		{
			sum2 += *(size_t*)(v.data() + i * sizeof(size_t));
		}

		CHECK(sum == sum2);
	}

	SUBCASE("Reserve")
	{
		MemoryLeakDetector mld;
		Random rand;

		eclog::detail::PODArray<int, DebugAllocator> v;

		v.reserve(10);

		CHECK(v.empty());
		CHECK(v.size() == 0);
		CHECK(v.capacity() == 10);

		for (int i = 0; i < 50; ++i)
		{
			v.insert(rand.next() % 100, i);
		}

		CHECK(!v.empty());
		CHECK(v.size() == 50);
		CHECK(v.capacity() >= 50);

		v.reserve(100);

		CHECK(v.size() == 50);
		CHECK(v.capacity() == 100);

		for (int i = 0; i < 50; ++i)
		{
			v.insert(rand.next() % 100, i);
		}

		CHECK(v.size() == 100);
		CHECK(v.capacity() >= 100);
	}

	SUBCASE("Clear")
	{
		MemoryLeakDetector mld;
		Random rand;

		eclog::detail::PODArray<int, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.insert(rand.next() % 100, i);
		}

		v.clear();

		CHECK(v.empty());
		CHECK(v.size() == 0);
	}

	SUBCASE("Copy")
	{
		MemoryLeakDetector mld;

		eclog::detail::PODArray<int, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.pushBack(i);
		}

		eclog::detail::PODArray<int, DebugAllocator> v2(v);

		CHECK(!v2.empty());
		CHECK(v2.size() == 100);
		CHECK(v2.capacity() == 100);

		for (size_t i = 0; i < v2.size(); ++i)
		{
			CHECK(v2[i] == (int)i);
		}
	}

	SUBCASE("Copy Assignment")
	{
		MemoryLeakDetector mld;
		Random rand;

		eclog::detail::PODArray<int, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.pushBack(i);
		}

		eclog::detail::PODArray<int, DebugAllocator> v2;

		for (int i = 0; i < 50; ++i)
		{
			v2.insert(rand.next() % 100, i * 2 + 1);
		}

		v2 = v;

		CHECK(!v2.empty());
		CHECK(v2.size() == 100);

		for (size_t i = 0; i < v2.size(); ++i)
		{
			CHECK(v2[i] == (int)i);
		}

		eclog::detail::PODArray<int, DebugAllocator> v3;

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

		for (size_t i = 0; i < v3.size(); ++i)
		{
			CHECK(v3[i] == (int)i);
		}

		eclog::detail::PODArray<int, DebugAllocator> v4;

		for (int i = 0; i < 200; ++i)
		{
			v4.insert(rand.next() % 100, i * 2 + 1);
		}

		v4 = v;

		CHECK(!v4.empty());
		CHECK(v4.size() == 100);

		for (size_t i = 0; i < v4.size(); ++i)
		{
			CHECK(v4[i] == (int)i);
		}

		v.clear();
		v4 = v;

		CHECK(v4.empty());
		CHECK(v4.size() == 0);
	}

	SUBCASE("Remove")
	{
		MemoryLeakDetector mld;
		Random rand;

		eclog::detail::PODArray<int, DebugAllocator> v;

		for (int i = 0; i < 100; ++i)
		{
			v.pushBack(i);
		}

		v.remove(0, 10);

		CHECK(v.size() == 90);
		CHECK(v.capacity() >= 100);

		for (size_t i = 0; i < v.size(); ++i)
		{
			CHECK(v[i] == (int)i + 10);
		}

		v.remove(10, 10);

		CHECK(v.size() == 80);
		CHECK(v.capacity() >= 100);

		for (size_t i = 10; i < v.size(); ++i)
		{
			CHECK(v[i] == (int)i + 20);
		}

		v.remove(10, (size_t)-1);

		CHECK(v.size() == 10);
		CHECK(v.capacity() >= 100);

		for (size_t i = 0; i < v.size(); ++i)
		{
			CHECK(v[i] == (int)i + 10);
		}
	}
}

