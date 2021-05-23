// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NUMBERDESC_H_
#define ECLOG_CPP_NUMBERDESC_H_

#include <Eclog/ValueDesc.h>

namespace eclog {

	class NumberDesc : public ValueDesc {
	public:
		NumberDesc(const Number& value, int fracDigits = -1) : ValueDesc(value, fracDigits) {}
		NumberDesc(double value, int fracDigits = -1) : ValueDesc(value, fracDigits) {}
		NumberDesc(int value) : ValueDesc(value) {}
		NumberDesc(long value) : ValueDesc(value) {}
		NumberDesc(long long value) : ValueDesc(value) {}
		NumberDesc(unsigned int value) : ValueDesc(value) {}
		NumberDesc(unsigned long value) : ValueDesc(value) {}
		NumberDesc(unsigned long long value) : ValueDesc(value) {}
	};

} // eclog

#endif // ECLOG_CPP_NUMBERDESC_H_

