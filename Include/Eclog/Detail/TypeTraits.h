// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_TYPETRAITS_H_
#define ECLOG_CPP_DETAIL_TYPETRAITS_H_

#include <limits> // std::numeric_limits

namespace eclog {

	namespace detail {

		template<typename From, typename To>
		class IsConvertible {
		private:
			typedef char True[1];
			typedef char False[2];

			static True& test(To);
			static False& test(...);

			static From from();

		public:
			enum {
				value = (sizeof(test(from())) == sizeof(True)) ? 1 : 0
			};
		};

		template<typename Base, typename Derived>
		class IsBaseOf {
		public:
			enum {
				value = IsConvertible<const Derived*, const Base*>::value
			};
		};

		template <bool B, class T = void>
		class EnableIfCond {
		};

		template <class T>
		class EnableIfCond<true, T> {
		public:
			typedef T Type;
		};

		template <class Cond, class T = void>
		class EnableIf : public EnableIfCond<Cond::value, T> {
		};

		template<typename T>
		class RemoveCV {
		public:
			typedef T Type;
		};

		template<typename T>
		class RemoveCV<const T> {
		public:
			typedef T Type;
		};

		template<typename T>
		class RemoveCV<volatile T> {
		public:
			typedef T Type;
		};

		template<typename T>
		class RemoveCV<const volatile T> {
		public:
			typedef T Type;
		};

		template<typename IntType>
		class IsSigned {
		public:
			enum {
				value = std::numeric_limits<IntType>::is_signed ? 1 : 0
			};
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_TYPETRAITS_H_

