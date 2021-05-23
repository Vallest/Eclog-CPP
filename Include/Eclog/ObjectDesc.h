// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_OBJECTDESC_H_
#define ECLOG_CPP_OBJECTDESC_H_

#include <Eclog/ValueDesc.h>

namespace eclog {

	class ObjectDesc : public ValueDesc {
	public:
		ObjectDesc() : ValueDesc(empty_object)
		{
		}

		ObjectDesc(EmptyObjectTag) : ValueDesc(empty_object)
		{
		}

		ObjectDesc(const Pair<KeyDesc, ValueDesc>* p, size_t size) : ValueDesc(p, size)
		{
		}

		template<size_t N>
		ObjectDesc(const Pair<KeyDesc, ValueDesc> (&v)[N]) : ValueDesc(v, N)
		{
		}
	};

} // eclog

#endif // ECLOG_CPP_OBJECTDESC_H_

