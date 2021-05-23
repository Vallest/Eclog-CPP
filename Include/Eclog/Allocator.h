// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_ALLOCATOR_H_
#define ECLOG_CPP_ALLOCATOR_H_

#include <Eclog/Error.h>

#include <stdlib.h> // malloc

#ifndef ECLOG_DEFAULT_ALLOCATOR
	#define ECLOG_DEFAULT_ALLOCATOR eclog::Allocator
#endif

namespace eclog {

	class Allocator {
	public:
		static void* allocate(size_t size)
		{
			void* ptr = malloc(size);

			if (!ptr) {
				ECLOG_FAULT(OutOfMemory);
			}

			return ptr;
		}

		static void deallocate(void* ptr)
		{
			free(ptr);
		}
	};

} // eclog

#endif // ECLOG_CPP_ALLOCATOR_H_

