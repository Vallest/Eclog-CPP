// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"

#include <vector>

#include <stddef.h> // size_t

namespace {

	std::vector<TestCase>& regTestCase(TestCase testCase)
	{
		static std::vector<TestCase> v;

		if (testCase.f) {
			v.push_back(testCase);
		}

		return v;
	}

	int passCount;
	int failedCount;
}

RegTestCase::RegTestCase(TestCase testCase)
{
	regTestCase(testCase);
}

void pass()
{
	++passCount;
}

void fail()
{
	++failedCount;
}

void runTestCases()
{
	std::vector<TestCase>& v = regTestCase(TestCase(0, 0));

	passCount = 0;
	failedCount = 0;

	for (size_t i = 0; i < v.size(); ++i)
	{
		getOutStream() << "TestCase: " << v[i].desc << "\n";
		v[i].f();
	}

	getOutStream() << "----------------------------------------\n";
	getOutStream() << passCount << " assertion(s) passed, " << failedCount << " failed.\n";
}

