// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"

#include <Eclog/Detail/ByteArray.h>

TEST_CASE("ByteArray")
{
	SUBCASE("Construct")
	{
		MemoryLeakDetector mld;

		eclog::detail::ByteArray<DebugAllocator> s;

		CHECK(s.empty());
		CHECK(s.size() == 0);
		CHECK(s.str() == "");
	}

	SUBCASE("Append")
	{
		MemoryLeakDetector mld;

		eclog::detail::ByteArray<DebugAllocator> s;

		CHECK(s.empty());

		s.append("The");
		s.append(" quick");
		s.append(" brown");
		s.append(" fox");
		s.append(" jumps");
		s.append(" over");
		s.append(" the");
		s.append(" lazy");
		s.append(' ');
		s.append('d');
		s.append('o');
		s.append('g');
		s.append('.');

		CHECK(s.str() == "The quick brown fox jumps over the lazy dog.");

		s.clear();

		CHECK(s.empty());
		CHECK(s.size() == 0);
		CHECK(s.str() == "");

		s.append('T');
		s.append('h');
		s.append('e');
		s.append(" quick");
		s.append(" brown");
		s.append(" fox");
		s.append(" jumps");
		s.append(" over");
		s.append(" the");
		s.append(" lazy");
		s.append(" dog.");

		CHECK(s.str() == "The quick brown fox jumps over the lazy dog.");
	}

	SUBCASE("Insert")
	{
		MemoryLeakDetector mld;

		eclog::detail::ByteArray<DebugAllocator> s;

		CHECK(s.empty());

		s.insert(0, "fox");
		s.insert(0, "brown ");
		s.insert(0, "quick ");
		s.insert(0, "The ");
		s.insert((size_t)-1, " the");
		s.insert((size_t)-1, " lazy");
		s.insert((size_t)-1, " dog.");
		s.insert(19, " jumps");
		s.insert(25, " over");

		CHECK(s.str() == "The quick brown fox jumps over the lazy dog.");

		s.clear();

		CHECK(s.empty());
		CHECK(s.size() == 0);
		CHECK(s.str() == "");

		s.insert(0, "fox");
		s.insert(0, "brown ");
		s.insert(0, "quick ");
		s.insert(0, "The ");
		s.insert((size_t)-1, " the");
		s.insert((size_t)-1, " lazy");
		s.insert((size_t)-1, " dog.");
		s.insert(19, " jumps");
		s.insert(25, " over");

		CHECK(s.str() == "The quick brown fox jumps over the lazy dog.");
	}

	SUBCASE("Remove")
	{
		MemoryLeakDetector mld;

		eclog::detail::ByteArray<DebugAllocator> s("The quick brown fox jumps over the lazy dog.");

		s.remove(10, 6);
		s.remove(29, 5);

		CHECK(s.str() == "The quick fox jumps over the dog.");

		s.remove(0, 10);

		CHECK(s.str() == "fox jumps over the dog.");

		s.remove(15, 4);

		CHECK(s.str() == "fox jumps over dog.");

		s.remove(3);

		CHECK(s.str() == "fox");
	}

	SUBCASE("Reserve")
	{
		MemoryLeakDetector mld;

		eclog::detail::ByteArray<DebugAllocator> s("The quick brown fox");

		CHECK(s.size() == 19);
		CHECK(s.capacity() == 19);

		s.reserve(44);

		CHECK(s.size() == 19);
		CHECK(s.capacity() == 44);
		CHECK(s.str() == "The quick brown fox");

		s.append(" jumps");
		s.append(" over");
		s.append(" the");
		s.append(" lazy");
		s.append(" dog.");

		CHECK(s.size() == 44);
		CHECK(s.capacity() == 44);
		CHECK(s.str() == "The quick brown fox jumps over the lazy dog.");
	}

	SUBCASE("Swap")
	{
		MemoryLeakDetector mld;

		eclog::detail::ByteArray<DebugAllocator> s1("Hello World!");
		eclog::detail::ByteArray<DebugAllocator> s2("The quick brown fox jumps over the lazy dog.");

		swap(s1, s2);

		CHECK(s1.str() == "The quick brown fox jumps over the lazy dog.");
		CHECK(s2.str() == "Hello World!");
	}
}

