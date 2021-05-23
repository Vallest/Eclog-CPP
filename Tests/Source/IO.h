// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_TEST_IO_H_
#define ECLOG_TEST_IO_H_

#include <istream>
#include <sstream>
#include <string>

inline std::istream& getLine(std::istream& is, std::string& line)
{
	std::ios_base::iostate state = std::ios_base::goodbit;

	bool changed = false;

	std::istream::sentry se(is, true);

	if (se)
	{
		line.clear();
		std::streambuf* sb = is.rdbuf();

		for (;;)
		{
			int ch = sb->sbumpc();

			if (ch == '\n')
			{
				changed = true;
				break;
			}
			else if (ch == '\r')
			{
				if (sb->sgetc() == '\n') {
					sb->sbumpc();
				}

				changed = true;
				break;
			}
			else if (ch == std::char_traits<char>::eof())
			{
				state |= std::ios_base::eofbit;
				break;
			}
			else
			{
				line += (char)ch;
				changed = true;
			}
		}
	}

	if (!changed) {
		state |= std::ios_base::failbit;
	}

	is.setstate(state);

	return (is);
}

inline std::string replaceLinebreaks(const std::string& text)
{
	std::istringstream stream(text);

	std::string result;
	std::string line;

	while (getLine(stream, line))
	{
		result += line;
		result += "\n";
	}

	return result;
}

#endif // ECLOG_TEST_IO_H_

