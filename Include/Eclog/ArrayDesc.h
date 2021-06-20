// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_ARRAYDESC_H_
#define ECLOG_CPP_ARRAYDESC_H_

#include <Eclog/ValueDesc.h>

namespace vallest {
namespace eclog {

	class ArrayDesc : public ValueDesc {
	public:
		ArrayDesc() : ValueDesc(empty_array)
		{
		}

		ArrayDesc(EmptyArrayTag) : ValueDesc(empty_array)
		{
		}

		ArrayDesc(const ValueDesc* p, size_t size) : ValueDesc(p, size)
		{
		}

		template<size_t N>
		ArrayDesc(const ValueDesc (&v)[N]) : ValueDesc(v, N)
		{
		}
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_ARRAYDESC_H_

