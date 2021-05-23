// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_STRINGDELIMITER_H_
#define ECLOG_CPP_DETAIL_STRINGDELIMITER_H_

#include <Eclog/cstring.h>
#include <Eclog/Detail/CharType.h>
#include <Eclog/Detail/InlineArray.h>

#include <string.h> // memcpy
#include <stddef.h> // size_t

namespace eclog {

	namespace detail {

		class StringDelimiter {
		public:
			void clear()
			{
				d_.clear();
			}

			size_t size() const
			{
				return d_.size();
			}

			bool assign(cstring str)
			{
				if (!validate(str)) {
					return false;
				}

				d_.resize(str.size());

				if (str.size())
				{
					memcpy(d_.data(), str.data(), str.size());
				}

				return true;
			}

			operator cstring() const
			{
				return cstring(d_.data(), d_.data() + d_.size());
			}

			static bool validate(cstring str)
			{
				if (str.size() > 16) {
					return false;
				}

				for (const char* s = str.begin(); s != str.end(); ++s)
				{
					if (!isAlphanum(*s) && *s != '_') {
						return false;
					}
				}

				return true;
			}

		private:
			InlineArray<char, 16> d_;
		};

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_STRINGDELIMITER_H_

