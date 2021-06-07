// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_KEY_H_
#define ECLOG_CPP_KEY_H_

#include <Eclog/StringNotation.h>
#include <Eclog/cstring.h>

namespace eclog {

	class Key : public cstring {
	public:
		Key()
		{
		}

		explicit Key(cstring str, StringNotation notation, size_t delimiterSize) :
			cstring(str.begin() + delimiterSize, str.end()),
			notation_(notation),
			delimiter_(str.begin(), str.begin() + delimiterSize)
		{
			ECLOG_ASSERT(str);
			ECLOG_ASSERT(notation);
			ECLOG_ASSERT(delimiterSize <= 16 && (str.size() == 0 || str.size() > delimiterSize));
		}

		StringNotation notation() const
		{
			return notation_;
		}

		cstring delimiter() const
		{
			return delimiter_;
		}

	private:
		StringNotation notation_;

		cstring delimiter_;
	};

} // eclog

#endif // ECLOG_CPP_KEY_H_

