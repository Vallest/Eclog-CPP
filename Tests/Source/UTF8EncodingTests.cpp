// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"
#include "Random.h"

#include <Eclog/MemoryOutputStream.h>
#include <Eclog/MemoryInputStream.h>
#include <Eclog/Allocator.h>
#include <Eclog/UTF8Decoder.h>
#include <Eclog/UTF8Encoder.h>

#include <vector>

#include <time.h>

namespace {

	class RandomCodepointGenerator {
	public:
		int generate()
		{
			static const unsigned int mask[4] = { 0x7f, 0x7ff, 0xffff, 0x1fffff };

			unsigned int length = rand_.next() & 3;

			for (;;)
			{
				int cp = (int)(rand_.next() & mask[length]);

				if (((cp >> 11) == 0x1b)) {
					continue;
				}

				return cp;
			}
		}

	private:
		Random rand_;
	};

}

TEST_CASE("UTF8 Encoding")
{
	static const size_t count = 32768;

	std::vector<int> codepoints;

	RandomCodepointGenerator g;

	eclog::BasicMemoryOutputStream<DebugAllocator> os;

	eclog::UTF8Encoder encoder(os);

	eclog::ErrorCode ec;

	for (size_t i = 0; i < count; ++i)
	{
		int cp = g.generate();

		encoder.putChar(cp, ec);

		CHECK(!ec);

		codepoints.push_back(cp);
	}

	CHECK(codepoints.size() == count);

	eclog::MemoryInputStream is(os.data(), os.size());

	eclog::UTF8Decoder decoder(is);

	for (size_t i = 0;; ++i)
	{
		int cp = decoder.getChar(ec);

		CHECK(!ec);

		if (cp == -1)
		{
			CHECK(i == codepoints.size());
			break;
		}

		CHECK(i < codepoints.size());
		CHECK(cp == codepoints[i]);
	}
}

