// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_TEST_DEBUGALLOCATOR_H_
#define ECLOG_TEST_DEBUGALLOCATOR_H_

#include "UnitTesting.h"

#include <stdlib.h> // malloc, free

class DebugAllocator {
public:
	static void* allocate(size_t size)
	{
		void* ptr = malloc(sizeof(size_t) + size);

		if (!ptr) {
			FAIL("out of memory");
		}

		*(size_t*)ptr = size;

		total_ += size;

		return (char*)ptr + sizeof(size_t);
	}

	static void deallocate(void* ptr)
	{
		if (!ptr) {
			return;
		}

		ptr = (char*)ptr - sizeof(size_t);

		size_t size = *(size_t*)ptr;

		free(ptr);

		total_ -= size;
	}

	static size_t total()
	{
		return total_;
	}

private:
	static size_t total_;
};

class MemoryLeakDetector {
public:
	MemoryLeakDetector()
	{
		if (DebugAllocator::total())
		{
			FAIL("memory leak detected");
		}
	}

	~MemoryLeakDetector()
	{
		if (DebugAllocator::total())
		{
			FAIL("memory leak detected");
		}
	}

private:
	MemoryLeakDetector(const MemoryLeakDetector&);
	MemoryLeakDetector& operator=(const MemoryLeakDetector&);
};

#endif // ECLOG_TEST_DEBUGALLOCATOR_H_

