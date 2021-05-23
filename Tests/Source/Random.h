// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_TEST_RANDOM_H_
#define ECLOG_TEST_RANDOM_H_

#include <time.h>

class Random {
public:
	explicit Random(unsigned int seed) : n_(seed)
	{
	}

	Random() : n_((unsigned int)time(0))
	{
	}

	unsigned int next()
	{
		/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
		n_ ^= n_ << 13;
		n_ ^= n_ >> 17;
		n_ ^= n_ << 5;

		return n_;
	}

private:
	unsigned int n_;
};

#endif // ECLOG_TEST_RANDOM_H_

