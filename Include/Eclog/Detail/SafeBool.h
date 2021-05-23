// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_SAFEBOOL_H_
#define ECLOG_CPP_DETAIL_SAFEBOOL_H_

namespace eclog {

	namespace detail {

		class SafeBool {
		public:
			typedef void (SafeBool::*BoolType)() const;

		public:
			static BoolType make(bool value)
			{
				return value ? &SafeBool::boolTrue : 0;
			}

		private:
			void boolTrue() const
			{
			}
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_SAFEBOOL_H_

