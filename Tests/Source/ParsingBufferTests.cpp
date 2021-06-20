// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"
#include "Random.h"

#include <Eclog/DynamicParsingBuffer.h>
#include <Eclog/InplaceParsingBuffer.h>
#include <Eclog/ParsingBuffer.h>
#include <Eclog/cstring.h>

#include <vector>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>

using namespace vallest;

namespace {

	typedef std::pair<void*, eclog::cstring> Stub;

	std::string genRandChars(size_t x)
	{
		std::ostringstream os;

		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;

		os << std::hex << "<(" << x << "]}";

		return os.str();
	}

	void check(std::vector<Stub>& stubs)
	{
		for (size_t i = 0; i < stubs.size(); ++i)
		{
			CHECK(stubs[i].second == genRandChars(i).c_str());
			CHECK(*(stubs[i].second.data() + stubs[i].second.size()) == 0);
		}
	}

	void push(eclog::ParsingBuffer& parsingBuffer, std::vector<Stub>& stubs)
	{
		void* ptr = parsingBuffer.claim();

		CHECK(parsingBuffer.length() == 0);

		bool shrinking = stubs.size() % 5 == 0;

		std::string chars = genRandChars(stubs.size());

		if (shrinking)
		{
			std::string t;

			for (size_t i = 0; i < 16; ++i) {
				t += chars;
			}

			chars = t;
		}

		for (size_t i = 0; i < chars.size(); ++i)
		{
			parsingBuffer.putChar(chars[i]);
		}

		if (shrinking)
		{
			chars = chars.substr(0, chars.size() / 16);

			parsingBuffer.shrink(chars.size());
		}

		CHECK(parsingBuffer.length() == chars.size());
		CHECK(parsingBuffer.str() == chars.c_str());

		stubs.push_back(std::make_pair(ptr, parsingBuffer.str()));
	}

	void pop(eclog::ParsingBuffer& parsingBuffer, std::vector<Stub>& stubs)
	{
		parsingBuffer.discard(stubs.back().first);
		stubs.pop_back();
	}

	void test(eclog::ParsingBuffer& parsingBuffer)
	{
		std::vector<Stub> stubs;
		Random rand(23098);

		for (size_t i = 0; i < 100; ++i)
		{
			size_t pushCount = 1 + rand.next() % 4;
			size_t popCount = 1 + rand.next() % pushCount;

			for (size_t j = 0; j < pushCount; ++j)
			{
				push(parsingBuffer, stubs);
			}

			for (size_t j = 0; j < popCount; ++j)
			{
				pop(parsingBuffer, stubs);
			}

			check(stubs);
		}

		check(stubs);

		while (!stubs.empty())
		{
			pop(parsingBuffer, stubs);
		}
	}

}

TEST_CASE("Parsing Buffer")
{
	SUBCASE("DynamicParsingBuffer")
	{
		MemoryLeakDetector mld;

		eclog::BasicDynamicParsingBuffer<DebugAllocator> parsingBuffer;

		test(parsingBuffer);
	}

	SUBCASE("InlineParsingBuffer")
	{
		char buffer[1024];

		eclog::InplaceParsingBuffer parsingBuffer(buffer, 1024);

		test(parsingBuffer);
	}
}

