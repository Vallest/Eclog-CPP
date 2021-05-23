// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_NUMBERINFO_H_
#define ECLOG_CPP_NUMBERINFO_H_

namespace eclog {

	enum NumberInfo {
		number_info_has_sign = 1 << 0,
		number_info_has_neg_sign = 1 << 1,
		number_info_has_frac = 1 << 2,
		number_info_has_exp = 1 << 3,
		number_info_inf = 1 << 4,
		number_info_nan = 1 << 5,
	};

} // eclog

#endif // ECLOG_CPP_NUMBERINFO_H_

