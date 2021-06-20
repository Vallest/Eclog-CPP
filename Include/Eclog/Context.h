// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_CONTEXT_H_
#define ECLOG_CPP_CONTEXT_H_

#include <Eclog/Detail/Context.h>

namespace vallest {
namespace eclog {

	class Context : private detail::Context {
	public:
		explicit Context(InputStream& stream, ParsingBuffer& buffer) :
			detail::Context(stream, buffer)
		{
		}

		void terminate()
		{
			detail::Context::terminate();
		}
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_CONTEXT_H_

