// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_CSTRING_H_
#define ECLOG_CPP_CSTRING_H_

#include <Eclog/Error.h>
#include <Eclog/MemoryInputStream.h>
#include <Eclog/UTF8Decoder.h>
#include <Eclog/Detail/Algorithm.h>
#include <Eclog/Detail/SafeBool.h>
#include <Eclog/Detail/Assert.h>

#include <ostream>

#include <string.h> // strlen, memcmp
#include <stddef.h> // size_t

namespace eclog {

	class cstring {
	public:
		typedef detail::SafeBool::BoolType BoolType;

	public:
		cstring() : begin_(0), end_(0)
		{
		}

		cstring(const char* str) :
			begin_(str), end_(str ? str + strlen(str) : 0)
		{
		}

		explicit cstring(const char* str, size_t length)
		{
			ECLOG_ASSERT(str && str + length >= str);

			begin_ = str;
			end_ = str + length;
		}

		explicit cstring(const char* begin, const char* end)
		{
			ECLOG_ASSERT(begin && end && end >= begin);

			begin_ = begin;
			end_ = end;
		}

		bool empty() const
		{
			return begin_ == end_;
		}

		size_t size() const
		{
			return (size_t)end_ - (size_t)begin_;
		}

		const char& operator[](size_t pos) const
		{
			ECLOG_ASSERT(pos < size());

			return begin_[pos];
		}

		const char* data() const
		{
			return begin_;
		}

		const char* begin() const
		{
			return begin_;
		}

		const char* end() const
		{
			return end_;
		}

		int compare(const cstring& other) const
		{
			if (size() < other.size()) {
				return -1;
			}
			else if (size() > other.size()) {
				return 1;
			}
			else {
				return memcmp(data(), other.data(), size());
			}
		}

		bool startsWith(const cstring& str) const
		{
			if (size() >= str.size())
			{
				return substr(0, str.size()).compare(str) == 0;
			}

			return false;
		}

		bool endsWith(const cstring& str) const
		{
			if (size() >= str.size())
			{
				return substr(size() - str.size()).compare(str) == 0;
			}

			return false;
		}

		cstring substr(size_t pos, size_t count = -1) const
		{
			if (pos > size()) {
				ECLOG_FAULT(OutOfRange);
			}

			if (count > size() - pos) {
				count = size() - pos;
			}

			return cstring(begin_ + pos, count);
		}

		bool operator==(const cstring& other) const
		{
			return compare(other) == 0;
		}

		bool operator!=(const cstring& other) const
		{
			return !(*this == other);
		}

		bool operator<(const cstring& other) const
		{
			return compare(other) < 0;
		}

		bool operator>(const cstring& other) const
		{
			return other < *this;
		}

		bool operator<=(const cstring& other) const
		{
			return !(*this > other);
		}

		bool operator>=(const cstring& other) const
		{
			return !(*this < other);
		}

		bool validate(size_t* position = 0) const
		{
			MemoryInputStream stream(data(), size());

			UTF8Decoder decoder(stream);

			ErrorCode ec;

			while (decoder.getChar(ec) >= 0) {
			}

			if (position) {
				*position = (size_t)decoder.position();
			}

			return !ec;
		}

		operator BoolType() const
		{
			return detail::SafeBool::make(begin_ != 0);
		}

		bool operator!() const
		{
			return begin_ == 0;
		}

	private:
		const char* begin_;
		const char* end_;
	};

	inline bool operator==(const char* a, const cstring& b)
	{
		return b == a;
	}

	inline bool operator!=(const char* a, const cstring& b)
	{
		return !(a == b);
	}

	inline bool operator<(const char* a, const cstring& b)
	{
		return b > a;
	}

	inline bool operator>(const char* a, const cstring& b)
	{
		return b < a;
	}

	inline bool operator<=(const char* a, const cstring& b)
	{
		return !(a > b);
	}

	inline bool operator>=(const char* a, const cstring& b)
	{
		return !(a < b);
	}

	inline std::ostream& operator<<(std::ostream& stream, const cstring& str)
	{
		std::ios::iostate state = std::ios::goodbit;
		std::ostream::sentry sentry(stream);

		if (sentry)
		{
			size_t pad = (stream.width() <= 0 || (size_t)stream.width() <= str.size()) ?
				0 : (size_t)stream.width() - str.size();

			if ((stream.flags() & std::ios::adjustfield) != std::ios::left)
			{
				while (pad)
				{
					if (std::char_traits<char>::eq_int_type(
						stream.rdbuf()->sputc(stream.fill()),
						std::char_traits<char>::eof()))
					{
						state |= std::ios::badbit;
						break;
					}

					--pad;
				}
			}

			if (state == std::ios::goodbit)
			{
				if (stream.rdbuf()->sputn(str.data(), str.size()) == (std::streamsize)str.size())
				{
					while (pad)
					{
						if (std::char_traits<char>::eq_int_type(
							stream.rdbuf()->sputc(stream.fill()),
							std::char_traits<char>::eof()))
						{
							state |= std::ios::badbit;
							break;
						}

						--pad;
					}
				}
				else
				{
					state |= std::ios::badbit;
				}
			}

			stream.width(0);
		}
		else
		{
			state |= std::ios::badbit;
		}

		stream.setstate(state);

		return stream;
	}

} // eclog

#endif // ECLOG_CPP_CSTRING_H_

