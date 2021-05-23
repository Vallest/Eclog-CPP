// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_DOUBLECONVERSION_H_
#define ECLOG_CPP_DETAIL_DOUBLECONVERSION_H_

namespace eclog {

	namespace detail {

		double stringToDouble(const char* str, const char** outStr = 0, int* outError = 0);
		void doubleToString(double d, char* buffer, int fracDigits = -1);

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_DOUBLECONVERSION_H_

