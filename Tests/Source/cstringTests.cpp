// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"

#include <Eclog/cstring.h>

#include <sstream>
#include <iomanip>

TEST_CASE("cstring")
{
	SUBCASE("Construct")
	{
		eclog::cstring s1;
		CHECK(!s1);

		const char* p = "Hello World";

		eclog::cstring s2(p);
		CHECK(s2 == "Hello World");

		eclog::cstring s3(p, 5);
		CHECK(s3 == "Hello");

		eclog::cstring s4(p, p + 5);
		CHECK(s4 == "Hello");

		eclog::cstring c1(s1);
		CHECK(c1 == s1);
	}

	SUBCASE("Empty")
	{
		eclog::cstring s1("");

		CHECK((s1 ? 1 : 0) == 1);
		CHECK(s1.empty());
		CHECK(s1.size() == 0);

		eclog::cstring s2;

		CHECK(s2 == s1);
	}

	SUBCASE("Access")
	{
		eclog::cstring s("Hello World");

		CHECK(s.size() == 11);
		CHECK(s[0] == 'H');
		CHECK(s[1] == 'e');
		CHECK(s[2] == 'l');
		CHECK(s[3] == 'l');
		CHECK(s[4] == 'o');
		CHECK(s[5] == ' ');
		CHECK(s[6] == 'W');
		CHECK(s[7] == 'o');
		CHECK(s[8] == 'r');
		CHECK(s[9] == 'l');
		CHECK(s[10] == 'd');
	}

	SUBCASE("Assignment")
	{
		eclog::cstring s1 = "Hello";
		eclog::cstring s2 = "";

		s2 = s1;

		CHECK(s1 == "Hello");
		CHECK(s2 == "Hello");

		s1 = "Hello World";

		CHECK(s1.size() == 11);
		CHECK(s1 == "Hello World");
	}

	SUBCASE("Sub String")
	{
		eclog::cstring s("Hello World");

		CHECK(s.substr(0, 5) == "Hello");
		CHECK(s.substr(0, 0) == "");
		CHECK(s.substr(11) == "");
		CHECK(s.startsWith("Hello"));
		CHECK(s.endsWith("World"));
	}

	SUBCASE("Compare")
	{
		eclog::cstring s1 = "box";
		eclog::cstring s2 = "boy";

		CHECK(s1 <= "boy");
		CHECK("boy" >= s1);
		CHECK(s1 >= "box");
		CHECK("box" <= s2);
		CHECK("boy" == s2);
		CHECK("boy" != s1);

		CHECK(s1.compare(s2) < 0);
		CHECK(s2.compare(s1) > 0);

		s1 = "new";
		s2 = "modern";

		CHECK(s1 < s2);
		CHECK(s2 > s1);
		CHECK(s1 != s2);
	}

	SUBCASE("Validate")
	{
		size_t pos;

		eclog::cstring s1;

		CHECK(s1.validate());

		eclog::cstring s2("");

		CHECK(s2.validate());

		eclog::cstring s3("Hello World!");

		CHECK(s3.validate());

		eclog::cstring s4("\xE4\xBD\xA0\xE5\xA5\xBD\xEF\xBC\x8C\xE4\xB8\x96\xE7\x95\x8C\xEF\xBC\x81");

		CHECK(s4.validate(&pos));
		CHECK(pos == 6);

		eclog::cstring s5("\x46\x6F\x6F\x20\xC2\xA9\x20\x62\x61\x72\x20\xF0\x9D\x8C\x86\x20\x62\x61\x7A\x20\xE2\x98\x83\x20\x71\x75\x78");

		CHECK(s5.validate());

		eclog::cstring e1("\xE4\xBD\xA0\xE5\xA5\xBD\xEF\xBC\x8C\xE4\xB8\x96\xE7\x15\x8C\xEF\xBC\x81");

		CHECK(!e1.validate(&pos));
		CHECK(pos == 4);
	}

	SUBCASE("Output Stream")
	{
		eclog::cstring s = "Hello";

		std::ostringstream os;

		os << s << "\n";
		os << std::setw(8) << std::left << s << "\n";
		os << std::setw(10) << std::right << s << "\n";

		CHECK(os.str() == "Hello\nHello   \n     Hello\n");
	}
}

