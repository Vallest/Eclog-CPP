// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#if !defined(ECLOG_TESTS_LIB)

#include "UnitTesting.h"

#include <fstream>
#include <iostream>
#include <string>

std::ostream& getOutStream()
{
	return std::cout;
}

std::string getTextFilePath(const char* filename)
{
#ifdef TEXT_PATH
	std::string textPath = TEXT_PATH;
#else
	std::string textPath = "../Text/";
#endif
	return textPath + filename;
}

bool loadTextFile(const char* filename, std::string& text)
{
	std::fstream stream(getTextFilePath(filename).c_str(), std::ios::in | std::ios::binary);

	if (!stream.is_open()) {
		return false;
	}

	stream.seekg(0, std::ios::end);

	std::streamsize size = stream.tellg();

	stream.seekg(0, std::ios::beg);

	text.resize((size_t)size);

	if (!stream.read(&text[0], (size_t)size)) {
		return false;
	}

	return true;
}

int main()
{
	runTestCases();
}

#endif // ECLOG_TESTS_LIB

