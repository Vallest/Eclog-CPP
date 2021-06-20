// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_TEST_DEBUGOBJECT_H_
#define ECLOG_TEST_DEBUGOBJECT_H_

#include "UnitTesting.h"

class DebugObject {
public:
	DebugObject(int value) : value_(value)
	{
		++count_;
	}

	DebugObject(const DebugObject& other) : value_(other.value_)
	{
		++count_;
	}

	~DebugObject()
	{
		value_ = 0;
		--count_;
	}

	DebugObject& operator=(const DebugObject& other)
	{
		value_ = other.value_;
		return *this;
	}

	int value() const
	{
		return value_;
	}

public:
	static int count()
	{
		return count_;
	}

private:
	static int count_;
	int value_;
};

class ObjectLeakDetector {
public:
	ObjectLeakDetector()
	{
		if (DebugObject::count())
		{
			FAIL("object leak detected");
		}
	}

	~ObjectLeakDetector()
	{
		if (DebugObject::count())
		{
			FAIL("object leak detected");
		}
	}

private:
	ObjectLeakDetector(const ObjectLeakDetector&);
	ObjectLeakDetector& operator=(const ObjectLeakDetector&);
};

#endif // ECLOG_TEST_DEBUGOBJECT_H_

