// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NULL_H_
#define ECLOG_CPP_NULL_H_

namespace eclog {

	class Null {
	public:
		bool operator==(const Null&) const
		{
			return true;
		}

		bool operator!=(const Null&) const
		{
			return false;
		}
	};

	extern Null null;

} // eclog

#endif // ECLOG_CPP_NULL_H_

