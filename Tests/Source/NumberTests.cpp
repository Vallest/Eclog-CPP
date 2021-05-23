// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include "UnitTesting.h"

#include <Eclog/Number.h>

#include <sstream>
#include <limits>

TEST_CASE("Number")
{
	SUBCASE("Construct")
	{
		eclog::Number n0;

		CHECK(n0.underlyingType() == eclog::Number::underlying_type_double);
		CHECK(n0 == 0.0);
		CHECK(0.0 == n0);
		CHECK(n0 < 1.0);
		CHECK(1.0 > n0);
		CHECK(n0 <= 1.0);
		CHECK(1.0 >= n0);
		CHECK(n0 < 1.0f);
		CHECK(1.0f > n0);
		CHECK(n0 <= 1.0f);
		CHECK(1.0f >= n0);
		CHECK(n0 < 1);
		CHECK(1 > n0);
		CHECK(n0 <= 1);
		CHECK(1 >= n0);
		CHECK(n0 <= 1ull);
		CHECK(1ull >= n0);
		CHECK(n0 == 0.0f);
		CHECK(0.0f == n0);
		CHECK(n0 == 0);
		CHECK(0 == n0);
		CHECK(n0 == 0l);
		CHECK(0l == n0);
		CHECK(n0 == 0u);
		CHECK(0u == n0);
		CHECK(n0 == 0ul);
		CHECK(0ul == n0);
		CHECK(n0 == 0ll);
		CHECK(0ll == n0);
		CHECK(n0 == 0ull);
		CHECK(0ull == n0);

		eclog::Number n1(1.0);

		CHECK(n1.underlyingType() == eclog::Number::underlying_type_double);
		CHECK(n0 < n1);
		CHECK(n1 > n0);
		CHECK(n0 <= n1);
		CHECK(n1 >= n0);
		CHECK(n0 != n1);
		CHECK(n1 != n0);
		CHECK(n1 > 0.0);
		CHECK(0.0 < n1);
		CHECK(n1 >= 0.0);
		CHECK(0.0 <= n1);
		CHECK(n1 > 0.0f);
		CHECK(0.0f < n1);
		CHECK(n1 >= 0.0f);
		CHECK(0.0f <= n1);
		CHECK(n1 > 0);
		CHECK(0 < n1);
		CHECK(n1 > 0l);
		CHECK(0l < n1);
		CHECK(n1 > 0u);
		CHECK(0u < n1);
		CHECK(n1 > 0ul);
		CHECK(0ul < n1);
		CHECK(n1 > 0ll);
		CHECK(0ll < n1);
		CHECK(n1 > 0ull);
		CHECK(0ull < n1);
		CHECK(n1 >= 0.0);
		CHECK(0.0 <= n1);
		CHECK(n1 >= 0.0f);
		CHECK(0.0f <= n1);
		CHECK(n1 >= 0);
		CHECK(0 <= n1);
		CHECK(n1 >= 0l);
		CHECK(0l <= n1);
		CHECK(n1 >= 0u);
		CHECK(0u <= n1);
		CHECK(n1 >= 0ul);
		CHECK(0ul <= n1);
		CHECK(n1 >= 0ll);
		CHECK(0ll <= n1);
		CHECK(n1 >= 0ull);
		CHECK(0ull <= n1);
		CHECK(n1 != 0.0);
		CHECK(0.0 != n1);
		CHECK(n1 != 0.0f);
		CHECK(0.0f != n1);
		CHECK(n1 != 0);
		CHECK(0 != n1);
		CHECK(n1 != 0l);
		CHECK(0l != n1);
		CHECK(n1 != 0u);
		CHECK(0u != n1);
		CHECK(n1 != 0ul);
		CHECK(0ul != n1);
		CHECK(n1 != 0ll);
		CHECK(0ll != n1);
		CHECK(n1 != 0ull);
		CHECK(0ull != n1);

		eclog::Number n2(1.0f);

		CHECK(n2.underlyingType() == eclog::Number::underlying_type_double);
		CHECK(n2 == 1);
		CHECK(1 == n2);

		eclog::Number n3(123);

		CHECK(n3.underlyingType() == eclog::Number::underlying_type_int);
		CHECK(n3 != n2);
		CHECK(n2 != n3);
		CHECK(n3 > n2);
		CHECK(n2 < n3);
		CHECK(n3 >= n2);
		CHECK(n2 <= n3);
		CHECK(n3 == 123);
		CHECK(123 == n3);
		CHECK(n3 == 123.0);
		CHECK(123.0 == n3);

		eclog::Number n4(123u);

		CHECK(n4.underlyingType() == eclog::Number::underlying_type_uint);
		CHECK(n4 == 123);
		CHECK(123 == n4);
		CHECK(n4 == 123.0);
		CHECK(123.0 == n4);

		eclog::Number n5(456l);

		CHECK(n5.underlyingType() == eclog::Number::underlying_type_long);
		CHECK(n5 == 456);
		CHECK(n5 == 456.0);

		eclog::Number n6(456ul);

		CHECK(n6.underlyingType() == eclog::Number::underlying_type_ulong);
		CHECK(n6 == 456);
		CHECK(n6 == 456.0);

		eclog::Number n7(789ll);

		CHECK(n7.underlyingType() == eclog::Number::underlying_type_llong);
		CHECK(n7 == 789);
		CHECK(n7 == 789.0);

		eclog::Number n8(789ull);

		CHECK(n8.underlyingType() == eclog::Number::underlying_type_ullong);
		CHECK(n8 == 789);
		CHECK(n8 == 789.0);
	}

	SUBCASE("Assign")
	{
		eclog::Number n;

		n = 1.0;

		CHECK(n.underlyingType() == eclog::Number::underlying_type_double);
		CHECK(n == 1.0);

		n = 1;

		CHECK(n.underlyingType() == eclog::Number::underlying_type_int);
		CHECK(n == 1.0);

		n = 2u;

		CHECK(n.underlyingType() == eclog::Number::underlying_type_uint);
		CHECK(n == 2.0);

		n = 3l;

		CHECK(n.underlyingType() == eclog::Number::underlying_type_long);
		CHECK(n == 3.0);

		n = 4ul;

		CHECK(n.underlyingType() == eclog::Number::underlying_type_ulong);
		CHECK(n == 4.0);

		n = 5ll;

		CHECK(n.underlyingType() == eclog::Number::underlying_type_llong);
		CHECK(n == 5.0);

		n = 6ull;

		CHECK(n.underlyingType() == eclog::Number::underlying_type_ullong);
		CHECK(n == 6.0);
	}

	SUBCASE("Load")
	{
		eclog::Number n;

		n = 7.0;

		CHECK(n.load<double>() == 7.0f);
		CHECK(n.load<int>() == 7.0f);
		CHECK(n.load<unsigned int>() == 7.0f);
		CHECK(n.load<long>() == 7.0f);
		CHECK(n.load<unsigned long>() == 7.0f);
		CHECK(n.load<long long>() == 7.0f);
		CHECK(n.load<unsigned long long>() == 7.0f);
	}

	SUBCASE("Store")
	{
		eclog::Number n;

		n.store(1.0);

		CHECK(n.underlyingType() == eclog::Number::underlying_type_double);
		CHECK(n == 1.0);

		n.store(1);

		CHECK(n.underlyingType() == eclog::Number::underlying_type_int);
		CHECK(n == 1.0);

		n.store(2u);

		CHECK(n.underlyingType() == eclog::Number::underlying_type_uint);
		CHECK(n == 2.0);

		n.store(3l);

		CHECK(n.underlyingType() == eclog::Number::underlying_type_long);
		CHECK(n == 3.0);

		n.store(4ul);

		CHECK(n.underlyingType() == eclog::Number::underlying_type_ulong);
		CHECK(n == 4.0);

		n.store(5ll);

		CHECK(n.underlyingType() == eclog::Number::underlying_type_llong);
		CHECK(n == 5.0);

		n.store(6ull);

		CHECK(n.underlyingType() == eclog::Number::underlying_type_ullong);
		CHECK(n == 6.0);
	}

	SUBCASE("Info")
	{
		CHECK(eclog::Number(0).sign() == 1);
		CHECK(eclog::Number(1).sign() == 1);
		CHECK(eclog::Number(-1).sign() == -1);
		CHECK(eclog::Number(1000).sign() == 1);
		CHECK(eclog::Number(-1000).sign() == -1);
		CHECK(eclog::Number(1000.0).sign() == 1);
		CHECK(eclog::Number(-1000.0).sign() == -1);

		CHECK(eclog::Number(std::numeric_limits<int>::min()).isInfinity() == false);
		CHECK(eclog::Number(std::numeric_limits<int>::min()).isNan() == false);
		CHECK(eclog::Number(std::numeric_limits<int>::max()).isInfinity() == false);
		CHECK(eclog::Number(std::numeric_limits<int>::max()).isNan() == false);
		CHECK(eclog::Number(std::numeric_limits<int>::min()).sign() == -1);
		CHECK(eclog::Number(std::numeric_limits<int>::max()).sign() == 1);

		CHECK(eclog::Number(std::numeric_limits<double>::min()).isInfinity() == false);
		CHECK(eclog::Number(std::numeric_limits<double>::min()).isNan() == false);
		CHECK(eclog::Number(std::numeric_limits<double>::max()).isInfinity() == false);
		CHECK(eclog::Number(std::numeric_limits<double>::max()).isNan() == false);
		CHECK(eclog::Number(std::numeric_limits<double>::min()).sign() == 1);
		CHECK(eclog::Number(std::numeric_limits<double>::max()).sign() == 1);
		CHECK(eclog::Number(-std::numeric_limits<double>::min()).sign() == -1);
		CHECK(eclog::Number(-std::numeric_limits<double>::max()).sign() == -1);

		CHECK(eclog::Number(0).isInfinity() == false);
		CHECK(eclog::Number(0).isNan() == false);

		CHECK(eclog::Number::infinity().isInfinity());
		CHECK(eclog::Number::negInfinity().isInfinity());
		CHECK(eclog::Number::infinity().isNan() == false);
		CHECK(eclog::Number::negInfinity().isNan() == false);
		CHECK(eclog::Number::nan().isNan());
		CHECK(eclog::Number::negNan().isNan());
		CHECK(eclog::Number::nan().isInfinity() == false);
		CHECK(eclog::Number::negNan().isInfinity() == false);
	}
}

