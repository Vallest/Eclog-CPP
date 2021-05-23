// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"
#include "DebugAllocator.h"
#include "DebugParseHandlers.h"
#include "IO.h"

#include <Eclog/MemoryInputStream.h>
#include <Eclog/DynamicParsingBuffer.h>
#include <Eclog/InplaceParsingBuffer.h>
#include <Eclog/Parse.h>

#include <sstream>
#include <string>
#include <vector>

namespace {

	const char* testcases[] =
	{
		"Null.ecl",
		"Null.json",
		"Boolean.ecl",
		"Boolean.json",
		"QuotedString.ecl",
		"QuotedString.json",
		"UnquotedString.ecl",
		"RawString.ecl",
		"StringConcatenation.ecl",
		"Heredoc.ecl",
		"Number.ecl",
		"Number.json",
		"Object.ecl",
		"Object.json",
		"Array.ecl",
		"Array.json",
		"Nesting.ecl",
		"Nesting.json",
		"Inline.ecl",
		"Inline.json",
		"TrailingComma.ecl",
		"Person.ecl",
		"Person.json",
	};

	void testParse(const std::string& testCase, const std::string& eclog, const std::string& checklist)
	{
		MemoryLeakDetector mld;

		eclog::MemoryInputStream stream(eclog.data(), eclog.size());
		eclog::BasicDynamicParsingBuffer<DebugAllocator> buffer;

		eclog::Context ctx(stream, buffer);

		DebugParseHandler handler;

		eclog::ErrorCode ec;

		eclog::parse(ctx, handler, ec);

		if (ec)
		{
			if (ec == eclog::ec_parse_error)
			{
				const eclog::ParseError& pe = eclog::cast<eclog::ParseError>(ec.error());

				getOutStream() << "Parse error at line " << pe.line() << " column " << pe.column()
					<< ", " << pe.message() << ":\n" << eclog.c_str() << "\n";
			}
			else
			{
				getOutStream() << ec.message() << "\n";
			}

			return;
		}

		std::istringstream s1(handler.result());
		std::istringstream s2(checklist);

		std::string line1;
		std::string line2;

		size_t ln = 1;

		while (getLine(s1, line1) && getLine(s2, line2))
		{
			CHECK_EQ_MSG(line1, line2, "TEST CASE: " + testCase);
			++ln;
		}

		CHECK_MSG(!(getLine(s1, line1) || getLine(s2, line2)), MSG("Checklist length mismatch"));
	}

	void testParse2(const std::string& testCase, const std::string& eclog, const std::string& checklist)
	{
		MemoryLeakDetector mld;

		std::vector<char> v(eclog.size() + 1);

		memcpy(&v[0], eclog.data(), eclog.size());

		eclog::MemoryInputStream stream(&v[0], eclog.size());
		eclog::InplaceParsingBuffer buffer(&v[0], v.size());

		eclog::Context ctx(stream, buffer);

		DebugParseHandler handler;

		eclog::ErrorCode ec;

		DebugObjectParseHandler kvpHandler(ctx, handler, ec);

		handler.onObjectBegin();

		eclog::parseObject(ctx, kvpHandler, ec);

		handler.onObjectEnd();

		if (ec)
		{
			if (ec == eclog::ec_parse_error)
			{
				const eclog::ParseError& pe = eclog::cast<eclog::ParseError>(ec.error());

				getOutStream() << "Parse error at line " << pe.line() << " column " << pe.column()
					<< ", " << pe.message() << ":\n" << eclog.c_str() << "\n";
			}
			else
			{
				getOutStream() << ec.message() << "\n";
			}

			return;
		}

		std::istringstream s1(handler.result());
		std::istringstream s2(checklist);

		std::string line1;
		std::string line2;

		size_t ln = 1;

		while (getLine(s1, line1) && getLine(s2, line2))
		{
			CHECK_EQ_MSG(line1, line2, "TEST CASE: " + testCase);
			++ln;
		}

		CHECK_MSG(!(getLine(s1, line1) || getLine(s2, line2)), MSG("Checklist length mismatch"));
	}
}

TEST_CASE("Parse")
{
	SUBCASE("MinimumValid")
	{
		testParse("MinimumValid", "", "object\nobject_end\n");
	}

	SUBCASE("Spaces")
	{
		testParse("Spaces", " \t \n\r\n\r  \r\r\n\n \t  \r\n \n \r \t", "object\nobject_end\n");
	}

	SUBCASE("Comments")
	{
		testParse("Comments", "#Comments\n#Comments\n#Comments", "object\nobject_end\n");
	}

	for (size_t i = 0; i < sizeof(testcases)/sizeof(*testcases); ++i)
	{
		SUBCASE(testcases[i])
		{
			std::string eclogFilename = testcases[i];
			std::string checklistFilename = eclogFilename + ".check";

			std::string text;
			std::string checklist;

			if (!loadTextFile(eclogFilename.c_str(), text))
			{
				getOutStream() << "Failed to load " << eclogFilename << "\n";
				continue;
			}

			if (!loadTextFile(checklistFilename.c_str(), checklist))
			{
				getOutStream() << "Failed to load " << checklistFilename << "\n";
				continue;
			}

			testParse(testcases[i], text, replaceLinebreaks(checklist));
		}
	}
}

TEST_CASE("Parse #2")
{
	SUBCASE("MinimumValid")
	{
		testParse2("MinimumValid", "", "object\nobject_end\n");
	}

	SUBCASE("Spaces")
	{
		testParse2("Spaces", " \t \n\r\n\r  \r\r\n\n \t  \r\n \n \r \t", "object\nobject_end\n");
	}

	SUBCASE("Comments")
	{
		testParse2("Comments", "#Comments\n#Comments\n#Comments", "object\nobject_end\n");
	}

	SUBCASE("Compact")
	{
		testParse2("Compact", "a:b", "object\nkey \"a\"\nvalue \"b\" type string\nobject_end\n");
	}

	for (size_t i = 0; i < sizeof(testcases) / sizeof(*testcases); ++i)
	{
		SUBCASE(testcases[i])
		{
			std::string eclogFilename = testcases[i];
			std::string checklistFilename = eclogFilename + ".check";

			std::string text;
			std::string checklist;

			if (!loadTextFile(eclogFilename.c_str(), text))
			{
				getOutStream() << "Failed to load " << eclogFilename << "\n";
				continue;
			}

			if (!loadTextFile(checklistFilename.c_str(), checklist))
			{
				getOutStream() << "Failed to load " << checklistFilename << "\n";
				continue;
			}

			testParse2(testcases[i], text, replaceLinebreaks(checklist));
		}
	}
}

#if defined(ECLOG_TEST_CPP11)
TEST_CASE("Parse #CPP11")
{
	MemoryLeakDetector mld;

	std::string text;

	if (!loadTextFile("Person.ecl", text))
	{
		getOutStream() << "Failed to load Person.ecl\n";
		return;
	}

	eclog::MemoryInputStream stream(text.data(), text.size());
	eclog::BasicDynamicParsingBuffer<DebugAllocator> buffer;

	eclog::Context ctx(stream, buffer);

	int count = 0;

	eclog::parseObject(ctx, [&](eclog::Key key, eclog::Value)
	{
		if (key == "phoneNumbers")
		{
			eclog::parseArray(ctx, [&](eclog::Value)
			{
				eclog::parseObject(ctx, [&](eclog::Key key, eclog::Value value)
				{
					if (key == "number")
					{
						if (count == 0) {
							CHECK_EQ(value.asString(), "212 555-1234");
						}
						else if (count == 1) {
							CHECK_EQ(value.asString(), "646 555-4567");
						}
						else if (count == 2) {
							CHECK_EQ(value.asString(), "123 456-7890");
						}

						++count;
					}
				});
			});
		}
	});

	CHECK_EQ(count, 3);
}
#endif // ECLOG_TEST_CPP11

