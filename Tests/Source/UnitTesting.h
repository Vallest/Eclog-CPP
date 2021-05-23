// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_TEST_UNITTESTING_H_
#define ECLOG_TEST_UNITTESTING_H_

#include <string>
#include <exception>
#include <ostream>

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER > 1600)
	#define ECLOG_TEST_CPP11
#endif

#define CAT_IMPL_(a, b) a##b
#define CAT(a, b) CAT_IMPL_(a, b)

#define ANONYMOUS(x) CAT(x, __LINE__)

#define REG_TEST_FUNC(f, desc) static RegTestCase ANONYMOUS(anonymousVar__) =		\
	makeTestCase(f, desc);

#define TEST_CASE_IMPL_(f, desc)													\
	static void f();                                                                \
	REG_TEST_FUNC(f, desc)                                                          \
	static void f()

#define TEST_CASE(desc) TEST_CASE_IMPL_(ANONYMOUS(anonymousFunc__), desc)

#define SUBCASE(name)

#define CHECK(x) if (x) { pass(); } else                                            \
	{ getOutStream() << "FAILED: " << __FILE__ << ":" << __LINE__ << ":\n" << #x    \
	<< "\n\n"; fail(); }

#define CHECK_MSG(x, msg) if (x) { pass(); } else                                   \
	{ getOutStream() << "FAILED: " << __FILE__ << ":" << __LINE__ << ":\n" << msg   \
	<< "\n\n"; fail(); }

#define CHECK_EQ(a, b) if (a == b) { pass(); } else                                 \
	{ getOutStream() << "FAILED: " << __FILE__ << ":" << __LINE__ << ":\n" << a     \
	<< "\nNOT EQUAL TO\n" << b << "\n\n"; fail(); }

#define CHECK_EQ_MSG(a, b, msg) if (a == b) { pass(); } else                        \
	{ getOutStream() << "FAILED: " << __FILE__ << ":" << __LINE__ << ":\n" << a     \
	<< "\nNOT EQUAL TO\n" << b << "\n" << msg << "\n\n"; fail(); }

#define FAIL(x) getOutStream() << __FILE__ << ":" << __LINE__ << ":\n" << x;        \
	std::terminate();

#define MSG(x) x

typedef void(*TestEntry)();

struct TestCase
{
	explicit TestCase(TestEntry f, const char* desc)
	{
		this->f = f;
		this->desc = desc;
	}

	TestEntry f;
	const char* desc;
};

inline TestCase makeTestCase(TestEntry f, const char* desc)
{
	return TestCase(f, desc);
}

class RegTestCase {
public:
	RegTestCase(TestCase testCase);
};

void pass();
void fail();

std::ostream& getOutStream();

bool loadTextFile(const char* filename, std::string& text);

void runTestCases();

#endif // ECLOG_TEST_UNITTESTING_H_

