// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Licensed under the MIT License.
//
// This file is auto-generated, do not edit.

#ifndef ECLOG_CPP_H_
#define ECLOG_CPP_H_

namespace vallest {
namespace eclog {
namespace detail {

	class NonCopyable {
	protected:
		NonCopyable() {}
		~NonCopyable() {}

	private:
		NonCopyable(const NonCopyable&);
		NonCopyable& operator=(const NonCopyable&);
	};

} // detail
} // eclog
} // vallest

#if __cplusplus >= 201703L
	#define ECLOG_FALLTHROUGH [[fallthrough]];
#elif defined(__clang__)
	#if defined(__has_cpp_attribute)
		#if __has_cpp_attribute(clang::fallthrough)
			#define ECLOG_FALLTHROUGH [[clang::fallthrough]];
		#endif
	#endif
#elif defined(__GNUC__)
	#if defined(__has_cpp_attribute)
		#if __has_cpp_attribute(fallthrough)
			#define ECLOG_FALLTHROUGH __attribute__((fallthrough));
		#endif
	#endif
#endif

#ifndef ECLOG_FALLTHROUGH
	#define ECLOG_FALLTHROUGH
#endif

#if (defined(__cpp_rvalue_references) && __cpp_rvalue_references >= 200610) || (defined(_MSC_VER) && _MSC_VER >= 1600)
	#define ECLOG_RVALUE_REFERENCES
#endif

#if defined(_MSC_VER)
	#define ECLOG_WARNING_PUSH __pragma(warning(push))
	#define ECLOG_WARNING_POP __pragma(warning(pop))
	#define ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR
	#define ECLOG_WARNING_IGNORE_SIGN_COMPARE __pragma(warning(disable:4018 4389))
	#define ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST __pragma(warning(disable:4355))
#elif defined(__GNUC__)
	#define ECLOG_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define ECLOG_WARNING_POP _Pragma("GCC diagnostic pop")
	#define ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR _Pragma("GCC diagnostic ignored \"-Wdelete-non-virtual-dtor\"")
	#define ECLOG_WARNING_IGNORE_SIGN_COMPARE _Pragma("GCC diagnostic ignored \"-Wsign-compare\"")
	#define ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
#else
	#define ECLOG_WARNING_PUSH
	#define ECLOG_WARNING_POP
	#define ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR
	#define ECLOG_WARNING_IGNORE_SIGN_COMPARE
	#define ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
#endif

#if __cplusplus >= 201103L
	#define ECLOG_OVERRIDE override
#elif defined(_MSC_VER) && _MSC_VER > 1600
	#define ECLOG_OVERRIDE override
#endif

#ifndef ECLOG_OVERRIDE
	#define ECLOG_OVERRIDE
#endif

#include <limits> // std::numeric_limits

namespace vallest {
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
} // vallest

namespace vallest {
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
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T>
	inline void swap(T& a, T& b)
	{
		T t = a;
		a = b;
		b = t;
	}

	template<typename T, size_t Size>
	inline size_t arraySize(const T(&)[Size])
	{
		return Size;
	}

} // detail
} // eclog
} // vallest

#include <exception>
#include <ostream>
#include <new>

#include <string.h> // strcmp

#if !defined(ECLOG_NO_EXCEPTIONS)
	#define ECLOG_THROW(E, ...) throw E(__VA_ARGS__)
	#define ECLOG_TRY try
	#define ECLOG_CATCH(X) catch (X)
	#define ECLOG_CATCH_ALL catch(...)
	#define ECLOG_RETHROW throw
#else
	#define ECLOG_THROW(E, ...) ECLOG_TERMINATE
	#define ECLOG_TRY if (true)
	#define ECLOG_CATCH(x) if (false)
	#define ECLOG_CATCH_ALL if (false)
	#define ECLOG_RETHROW ((void)0)
#endif

#if !defined(ECLOG_TERMINATE)
	#define ECLOG_TERMINATE std::terminate()
#endif

#if !defined(ECLOG_ERROR_ALLOC)
	#define ECLOG_ERROR_ALLOC(Size) ::operator new(Size)
	#define ECLOG_ERROR_DEALLOC(Ptr) ::operator delete(Ptr)
#endif

#define ECLOG_ON_ERROR(Code) \
	if (ec && *ec) { Code; }

#define ECLOG_ERROR(Name, ...) \
	if (ec) { *ec = vallest::eclog::makeErrorCode<vallest::eclog::Name>(__VA_ARGS__); } \
	else { ECLOG_THROW(vallest::eclog::Name##Exception, __VA_ARGS__); }

#define ECLOG_FAULT(Name, ...) \
	ECLOG_THROW(vallest::eclog::Name##Exception, __VA_ARGS__)

#if defined(_MSC_VER) && _MSC_VER <= 1600
	#define ECLOG_NOTHROW
#else
	#define ECLOG_NOTHROW throw()
#endif

namespace vallest {
namespace eclog {

	enum Success {
		success,
	};

	enum ErrorCodeEnum {
		ec_runtime_error,
		ec_buffer_overflow,
		ec_logic_error,
		ec_out_of_range,
		ec_length_error,
		ec_invalid_argument,
		ec_invalid_operation,
		ec_io_error,
		ec_unicode_error,
		ec_decode_error,
		ec_encode_error,
		ec_out_of_memory,
		ec_parse_error,
		ec_bad_cast,
	};

	enum ParseErrorEnum {
		pe_unexpected_end_of_file,
		pe_unexpected_character,
		pe_unrecognized_escape,
		pe_invalid_unicode_escape,
		pe_invalid_utf16_surrogate,
		pe_unescaped_control_character,
		pe_string_delimiter_too_long,
		pe_invalid_string_delimiter,
		pe_empty_string_delimiter,
		pe_invalid_key,
		pe_user_asked_for_termination,
	};

	const char* getErrorMessage(Success);
	const char* getErrorMessage(ErrorCodeEnum);
	const char* getErrorMessage(ParseErrorEnum);

	class Exception : public std::exception {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return "unknown";
		}
	};

	class RuntimeErrorException : public Exception {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_runtime_error);
		}
	};

	class BufferOverflowException : public RuntimeErrorException {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_buffer_overflow);
		}
	};

	class LogicErrorException : public Exception {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_logic_error);
		}
	};

	class OutOfRangeException : public LogicErrorException {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_out_of_range);
		}
	};

	class LengthErrorException : public LogicErrorException {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_length_error);
		}
	};

	class InvalidArgumentException : public LogicErrorException {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_invalid_argument);
		}
	};

	class InvalidOperationException : public LogicErrorException {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_invalid_operation);
		}
	};

	class IOErrorException : public Exception {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_io_error);
		}
	};

	class UnicodeErrorException : public Exception {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_unicode_error);
		}
	};

	class DecodeErrorException : public UnicodeErrorException {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_decode_error);
		}
	};

	class EncodeErrorException : public UnicodeErrorException {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_encode_error);
		}
	};

	class OutOfMemoryException : public Exception {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_out_of_range);
		}
	};

	class ParseErrorException : public Exception {
	public:
		explicit ParseErrorException(int lineNumber, int columnNumber, ParseErrorEnum error)
			: lineNumber_(lineNumber), columnNumber_(columnNumber), error_(error)
		{
		}

	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(error_);
		}

	public:
		int lineNumber() const
		{
			return lineNumber_;
		}

		int columnNumber() const
		{
			return columnNumber_;
		}

		ParseErrorEnum error() const
		{
			return error_;
		}

	private:
		int lineNumber_;
		int columnNumber_;
		ParseErrorEnum error_;
	};

	class BadCastException : public Exception {
	public:
		virtual const char* what() const ECLOG_NOTHROW
		{
			return getErrorMessage(ec_bad_cast);
		}
	};

	class ErrorId : private detail::NonCopyable {
	public:
		explicit ErrorId(const char* id) : id_(id)
		{
		}

		bool operator==(const ErrorId& other) const
		{
			return strcmp(id_, other.id_) == 0;
		}

		bool operator!=(const ErrorId& other) const
		{
			return !(*this == other);
		}

	private:
		const char* id_;
	};

	const ErrorId& getErrorId(ErrorCodeEnum e);

	class Error {
	public:
		virtual ~Error()
		{
		}

	public:
		static void* operator new(size_t size)
		{
			return ECLOG_ERROR_ALLOC(size);
		}

		static void operator delete(void* ptr)
		{
			ECLOG_ERROR_DEALLOC(ptr);
		}

	public:
		static const ErrorId& id();

	public:
		template<typename T>
		bool isA(typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type* = 0) const
		{
			return isA(T::id());
		}

		virtual bool isA(const ErrorId& id) const
		{
			return Error::id() == id;
		}

		virtual const ErrorId& getId() const = 0;

		virtual bool equals(const Error& other, bool strict) const = 0;

		virtual const Error* clone() const = 0;

		virtual const char* message() const = 0;
	};

	template<typename T>
	inline const T& cast(const Error& err, typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type* = 0)
	{
		if (err.isA<T>()) {
			return (const T&)err;
		}
		else {
			ECLOG_FAULT(BadCast);
		}
	}

	class RuntimeError : public Error {
	public:
		RuntimeError()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (RuntimeError::id() == id || Error::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const RuntimeError* clone() const ECLOG_OVERRIDE
		{
			return new RuntimeError();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_runtime_error);
		}
	};

	class BufferOverflow : public RuntimeError {
	public:
		BufferOverflow()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (BufferOverflow::id() == id || RuntimeError::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const BufferOverflow* clone() const ECLOG_OVERRIDE
		{
			return new BufferOverflow();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_buffer_overflow);
		}
	};

	class LogicError : public Error {
	public:
		LogicError()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (LogicError::id() == id || Error::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const LogicError* clone() const ECLOG_OVERRIDE
		{
			return new LogicError();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_logic_error);
		}
	};

	class OutOfRange : public LogicError {
	public:
		OutOfRange()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (OutOfRange::id() == id || LogicError::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const OutOfRange* clone() const ECLOG_OVERRIDE
		{
			return new OutOfRange();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_out_of_range);
		}
	};

	class LengthError : public LogicError {
	public:
		LengthError()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (LengthError::id() == id || LogicError::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const LengthError* clone() const ECLOG_OVERRIDE
		{
			return new LengthError();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_length_error);
		}
	};

	class InvalidArgument : public LogicError {
	public:
		InvalidArgument()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (InvalidArgument::id() == id || LogicError::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const InvalidArgument* clone() const ECLOG_OVERRIDE
		{
			return new InvalidArgument();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_invalid_argument);
		}
	};

	class InvalidOperation : public LogicError {
	public:
		InvalidOperation()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (InvalidOperation::id() == id || LogicError::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const InvalidOperation* clone() const ECLOG_OVERRIDE
		{
			return new InvalidOperation();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_invalid_operation);
		}
	};

	class IOError : public Error {
	public:
		IOError()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (IOError::id() == id || Error::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const IOError* clone() const ECLOG_OVERRIDE
		{
			return new IOError();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_io_error);
		}
	};

	class UnicodeError : public Error {
	public:
		UnicodeError()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (UnicodeError::id() == id || Error::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const UnicodeError* clone() const ECLOG_OVERRIDE
		{
			return new UnicodeError();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_unicode_error);
		}
	};

	class DecodeError : public UnicodeError {
	public:
		DecodeError()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (DecodeError::id() == id || UnicodeError::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const DecodeError* clone() const ECLOG_OVERRIDE
		{
			return new DecodeError();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_decode_error);
		}
	};

	class EncodeError : public UnicodeError {
	public:
		EncodeError()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (EncodeError::id() == id || UnicodeError::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const EncodeError* clone() const ECLOG_OVERRIDE
		{
			return new EncodeError();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_encode_error);
		}
	};

	class OutOfMemory : public Error {
	public:
		OutOfMemory()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (OutOfMemory::id() == id || Error::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const OutOfMemory* clone() const ECLOG_OVERRIDE
		{
			return new OutOfMemory();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_out_of_memory);
		}
	};

	class ParseError : public Error {
	public:
		explicit ParseError(int line, int column, ParseErrorEnum error)
			: line_(line), column_(column), error_(error)
		{
		}

		ParseError(const ParseError& other)
			: line_(other.line_), column_(other.column_), error_(other.error_)
		{
		}

		ParseError& operator=(const ParseError& other)
		{
			if (this != &other)
			{
				line_ = other.line_;
				column_ = other.column_;
				error_ = other.error_;
			}

			return *this;
		}

		bool equals(const ParseError& other) const
		{
			if (line_ != other.line_ || column_ != other.column_ || error_ != other.error_) {
				return false;
			}

			return true;
		}

		int line() const
		{
			return line_;
		}

		int column() const
		{
			return column_;
		}

		ParseErrorEnum error() const
		{
			return error_;
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (ParseError::id() == id || Error::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool strict) const ECLOG_OVERRIDE
		{
			return (other.getId() == id()) &&
				(!strict || equals(cast<ParseError>(other)));
		}

		virtual const ParseError* clone() const ECLOG_OVERRIDE
		{
			return new ParseError(*this);
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(error_);
		}

	private:
		int line_;
		int column_;
		ParseErrorEnum error_;
	};

	class BadCast : public Error {
	public:
		BadCast()
		{
		}

	public:
		static const ErrorId& id();

	public:
		virtual bool isA(const ErrorId& id) const ECLOG_OVERRIDE
		{
			return (BadCast::id() == id || Error::isA(id));
		}

		virtual const ErrorId& getId() const ECLOG_OVERRIDE
		{
			return id();
		}

		virtual bool equals(const Error& other, bool) const ECLOG_OVERRIDE
		{
			return other.getId() == id();
		}

		virtual const BadCast* clone() const ECLOG_OVERRIDE
		{
			return new BadCast();
		}

		virtual const char* message() const ECLOG_OVERRIDE
		{
			return getErrorMessage(ec_bad_cast);
		}
	};

	class ErrorCode {
	public:
		typedef detail::SafeBool::BoolType BoolType;

	public:
		ErrorCode() : error_(0), isDefault_(false)
		{
		}

		explicit ErrorCode(const Error* error, bool isDefault = false) : error_(error), isDefault_(isDefault)
		{
		}

		ErrorCode(const ErrorCode& other) : error_(other.cloneError()), isDefault_(other.isDefault_)
		{
		}

		ErrorCode& operator=(const ErrorCode& other)
		{
			if (this != &other)
			{
				const Error* error = other.cloneError();
				bool isDefault = other.isDefault_;

				destroyError();

				error_ = error;
				isDefault_ = isDefault;
			}

			return *this;
		}

#if defined(ECLOG_RVALUE_REFERENCES)
		ErrorCode& operator=(ErrorCode&& other)
		{
			if (this != &other)
			{
				detail::swap(error_, other.error_);
				detail::swap(isDefault_, other.isDefault_);
			}

			return *this;
		}
#endif

		~ErrorCode()
		{
			destroyError();
		}

		operator BoolType() const
		{
			return detail::SafeBool::make(error_ != 0);
		}

		bool operator!() const
		{
			return error_ == 0;
		}

		bool operator==(const ErrorCode& other) const
		{
			if (!*this && !other) {
				return true;
			}
			else if ((!*this && other) || (*this && !other)) {
				return false;
			}
			else {
				return error().equals(other.error(), false);
			}
		}

		bool operator!=(const ErrorCode& other) const
		{
			return !(*this == other);
		}

		bool operator==(ErrorCodeEnum e) const
		{
			return *this && error().getId() == getErrorId(e);
		}

		bool operator!=(ErrorCodeEnum e) const
		{
			return !(*this == e);
		}

		bool operator==(Success) const
		{
			return !*this;
		}

		bool operator!=(Success) const
		{
			return !(*this == success);
		}

		const char* message() const
		{
			return error_ ? error_->message() : getErrorMessage(success);
		}

		const Error& error() const
		{
			return *error_;
		}

	private:
		const Error* cloneError() const
		{
			if (error_ && !isDefault_) {
				return error_->clone();
			}
			else {
				return error_;
			}
		}

		void destroyError()
		{
			if (error_ && !isDefault_) {
				delete error_;
			}
		}

	private:
		const Error* error_;
		bool isDefault_;
	};

	template<typename T>
	const T* getDefaultError(typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type* = 0);

	template<typename T>
	inline ErrorCode makeErrorCode(typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type* = 0)
	{
		return ErrorCode(getDefaultError<T>(), true);
	}

	template<typename T, typename A1>
	inline ErrorCode makeErrorCode(A1 arg1, typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type* = 0)
	{
		return ErrorCode(new T(arg1));
	}

	template<typename T, typename A1, typename A2>
	inline ErrorCode makeErrorCode(A1 arg1, A2 arg2, typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type* = 0)
	{
		return ErrorCode(new T(arg1, arg2));
	}

	template<typename T, typename A1, typename A2, typename A3>
	inline ErrorCode makeErrorCode(A1 arg1, A2 arg2, A3 arg3, typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type* = 0)
	{
		return ErrorCode(new T(arg1, arg2, arg3));
	}

	inline bool operator==(Success a, const ErrorCode& b)
	{
		return b == a;
	}

	inline bool operator!=(Success a, const ErrorCode& b)
	{
		return !(a == b);
	}

	inline bool operator==(ErrorCodeEnum a, const ErrorCode& b)
	{
		return b == a;
	}

	inline bool operator!=(ErrorCodeEnum a, const ErrorCode& b)
	{
		return !(a == b);
	}

	inline std::ostream& operator<<(std::ostream& stream, const ErrorCode& ec)
	{
		stream << ec.message();
		return stream;
	}

} // eclog
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {

	class InputStream {
	public:
		virtual bool state() const = 0;
		virtual bool eof() const = 0;

		virtual size_t read(char* buffer, size_t size) = 0;
	};

} // eclog
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	class UTF8Decoder : private NonCopyable {
	public:
		explicit UTF8Decoder(InputStream& is) :
			is_(is), p_(buffer_), avail_(0), hasChar_(false), position_(0)
		{
		}

		int peekChar(ErrorCode* ec)
		{
			if (hasChar_) {
				return char_;
			}

			char_ = decode(ec);
			hasChar_ = (char_ >= 0);

			return char_;
		}

		int getChar(ErrorCode* ec)
		{
			if (hasChar_)
			{
				hasChar_ = false;
				++position_;
				return char_;
			}

			int ch = decode(ec);

			position_ += (ch >= 0);

			return ch;
		}

		long long position() const
		{
			return position_;
		}

	private:
		int decode(ErrorCode* ec);

	private:
		InputStream& is_;

		unsigned char buffer_[128];
		unsigned char* p_;
		size_t avail_;

		bool hasChar_;
		int char_;

		long long position_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class UTF8Decoder : private detail::UTF8Decoder {
	public:
		explicit UTF8Decoder(InputStream& is) : detail::UTF8Decoder(is)
		{
		}

		int peekChar()
		{
			return detail::UTF8Decoder::peekChar(0);
		}

		int peekChar(ErrorCode& ec)
		{
			return detail::UTF8Decoder::peekChar(&ec);
		}

		int getChar()
		{
			return detail::UTF8Decoder::getChar(0);
		}

		int getChar(ErrorCode& ec)
		{
			return detail::UTF8Decoder::getChar(&ec);
		}

		long long position() const
		{
			return detail::UTF8Decoder::position();
		}
	};

} // eclog
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {

	class OutputStream {
	public:
		virtual bool state() const = 0;

		virtual void write(const char* buffer, size_t size) = 0;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class UTF8Encoder : private NonCopyable {
	public:
		explicit UTF8Encoder(OutputStream& os) : os_(os)
		{
		}

		void putChar(int ch, ErrorCode* ec)
		{
			encode(ch, ec);
		}

	private:
		void encode(int ch, ErrorCode* ec);

	private:
		OutputStream& os_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class UTF8Encoder : private detail::UTF8Encoder {
	public:
		explicit UTF8Encoder(OutputStream& os) : detail::UTF8Encoder(os)
		{
		}

		void putChar(int ch)
		{
			detail::UTF8Encoder::putChar(ch, 0);
		}

		void putChar(int ch, ErrorCode& ec)
		{
			detail::UTF8Encoder::putChar(ch, &ec);
		}
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T>
	inline T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	inline T max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <typename Iterator, typename OutputIterator>
	inline void copy(Iterator first, Iterator last, OutputIterator first2)
	{
		while (first != last)
		{
			*first2 = *first;
			++first2;
			++first;
		}
	}

	template <typename Iterator>
	inline void reverse(Iterator first, Iterator last)
	{
		while (first != last && first != --last)
		{
			swap(*first, *last);
			++first;
		}
	}

	template<class Iterator>
	inline void rotate(Iterator first, Iterator mid, Iterator last)
	{
		reverse(first, mid);
		reverse(mid, last);
		reverse(first, last);
	}

} // detail
} // eclog
} // vallest

#include <string.h> // memcpy

namespace vallest {
namespace eclog {

	class MemoryInputStream : public InputStream, private detail::NonCopyable {
	public:
		explicit MemoryInputStream(const void* data, size_t size) :
			first_((const char*)data), last_((const char*)data + size)
		{
		}

	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return !eof();
		}

		virtual bool eof() const ECLOG_OVERRIDE
		{
			return first_ == last_;
		}

		virtual size_t read(char* buffer, size_t size) ECLOG_OVERRIDE
		{
			size_t n = detail::min<size_t>(last_ - first_, size);

			memcpy(buffer, first_, n);

			first_ += n;

			return n;
		}

	private:
		const char* first_;
		const char* last_;
	};

} // eclog
} // vallest

#include <assert.h>

#ifdef NDEBUG
	#define ECLOG_ASSERT(x) (void)(x)
#else
	#define ECLOG_ASSERT(x) assert(x)
#endif

#include <ostream>

#include <string.h> // strlen, memcmp
#include <stddef.h> // size_t

namespace vallest {
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
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {

	class ParsingBuffer {
	public:
		virtual void* claim() = 0;

		virtual void discard(void*) = 0;

		virtual size_t length() const = 0;

		virtual char* address() = 0;

		virtual cstring str() const = 0;

		virtual void putChar(int ch) = 0;

		virtual void shrink(size_t length) = 0;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class Context : private NonCopyable {
	public:
		explicit Context(InputStream& stream, ParsingBuffer& buffer) :
			decoder_(stream), buffer_(buffer),
			line_(1), lineBeginPos_(0), nestingLevel_(0),
			terminated_(false)
		{
		}

		UTF8Decoder& decoder()
		{
			return decoder_;
		}

		ParsingBuffer& buffer()
		{
			return buffer_;
		}

		void addLine()
		{
			lineBeginPos_ = decoder_.position();
			++line_;
		}

		int line() const
		{
			return line_;
		}

		int column() const
		{
			return (int)(decoder_.position() - lineBeginPos_) + 1;
		}

		void beginNested()
		{
			++nestingLevel_;
		}

		void endNested()
		{
			--nestingLevel_;
		}

		int nestingLevel() const
		{
			return nestingLevel_;
		}

		void terminate()
		{
			terminated_ = true;
		}

		bool terminated() const
		{
			return terminated_;
		}

	private:
		UTF8Decoder decoder_;
		ParsingBuffer& buffer_;

		int line_;
		long long lineBeginPos_;

		int nestingLevel_;

		bool terminated_;
	};

} // detail
} // eclog
} // vallest

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

namespace vallest {
namespace eclog {

	enum StringNotation {
		string_notation_unquoted = 1,
		string_notation_quoted,
		string_notation_raw,
		string_notation_heredoc,
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class Key : public cstring {
	public:
		Key()
		{
		}

		explicit Key(cstring str, StringNotation notation, size_t delimiterSize) :
			cstring(str.begin() + delimiterSize, str.end()),
			notation_(notation),
			delimiter_(str.begin(), str.begin() + delimiterSize)
		{
			ECLOG_ASSERT(str);
			ECLOG_ASSERT(notation);
			ECLOG_ASSERT(delimiterSize <= 16 && (str.size() == 0 || str.size() > delimiterSize));
		}

		StringNotation notation() const
		{
			return notation_;
		}

		cstring delimiter() const
		{
			return delimiter_;
		}

	private:
		StringNotation notation_;

		cstring delimiter_;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class Null {
	public:
		bool operator==(const Null&) const
		{
			return true;
		}

		bool operator!=(const Null&) const
		{
			return false;
		}
	};

	extern Null null;

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	enum ValueType {
		value_type_null,
		value_type_boolean,
		value_type_string,
		value_type_number,
		value_type_object,
		value_type_array,
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	enum NumberInfo {
		number_info_has_sign = 1 << 0,
		number_info_has_neg_sign = 1 << 1,
		number_info_has_frac = 1 << 2,
		number_info_has_exp = 1 << 3,
		number_info_inf = 1 << 4,
		number_info_nan = 1 << 5,
	};

} // eclog
} // vallest

#define ECLOG_HIGH32(n) (uint32_t)((n) >> 32)
#define ECLOG_LOW32(n) (uint32_t)((n) & 0xffffffff)
#define ECLOG_MAKE64(high, low) ((((uint64_t)(high)) << 32) | ((uint64_t)(low)))

#if defined(_MSC_VER)
	#if _MSC_VER >= 1600
		#include <stdint.h>
	#endif
#else
	#include <stdint.h>
#endif

#if __SIZEOF_INT128__ == 16
	#define ECLOG_HAS_INT128
#endif

namespace vallest {
namespace eclog {

#if defined(_MSC_VER) && !defined(_STDINT)
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;
	typedef unsigned __int64 uint64_t;
#else
	typedef ::uint16_t uint16_t;
	typedef ::uint32_t uint32_t;
	typedef ::uint64_t uint64_t;
#endif

#ifdef ECLOG_HAS_INT128
	typedef unsigned __int128 uint128_t;
#endif

} // eclog
} // vallest

#include <string.h> // memcpy

namespace vallest {
namespace eclog {
namespace detail {

	class Binary64 {
	public:
		static const uint64_t sign_mask = ECLOG_MAKE64(0x80000000, 0x00000000);
		static const uint64_t exponent_mask = ECLOG_MAKE64(0x7ff00000, 0x00000000);
		static const uint64_t significand_mask = ECLOG_MAKE64(0x000fffff, 0xffffffff);
		static const uint64_t hidden_bit = ECLOG_MAKE64(0x00100000, 0x00000000);
		static const int physical_significand_size = 52;
		static const int significand_size = 53;

	private:
		static const int exponent_bias = 0x3ff + physical_significand_size;
		static const int subnormal_exponent = -exponent_bias + 1;
		static const int max_exponent = 0x7ff - exponent_bias;
		static const uint64_t infinity_value = ECLOG_MAKE64(0x7ff00000, 0x00000000);
		static const uint64_t nan_value = ECLOG_MAKE64(0x7ff00000, 0x00000001);

	public:
		Binary64(double d)
		{
			assign(d);
		}

		Binary64(uint64_t d64) : d64_(d64)
		{
		}

		void assign(double d)
		{
			memcpy(&d64_, &d, sizeof(uint64_t));
		}

		double value() const
		{
			double val;
			memcpy(&val, &d64_, sizeof(uint64_t));

			return val;
		}

		double previousValue() const
		{
			if (d64_ == (infinity_value | sign_mask)) {
				return value();
			}

			if (sign() < 0) {
				return Binary64(d64_ + 1).value();
			}
			else if (significand() == 0) {
				return -0.0;
			}
			else {
				return Binary64(d64_ - 1).value();
			}
		}

		double nextValue() const
		{
			if (d64_ == infinity_value) {
				return value();
			}

			if (sign() < 0 && significand() == 0) {
				return 0.0;
			}

			if (sign() < 0) {
				return Binary64(d64_ - 1).value();
			}
			else {
				return Binary64(d64_ + 1).value();
			}
		}

		int sign() const
		{
			return ((d64_ & sign_mask) == 0 ? 1 : -1);
		}

		bool isSubnormal() const
		{
			return ((d64_ & exponent_mask) == 0);
		}

		bool isInfinity() const
		{
			return ((d64_ & exponent_mask) == exponent_mask) && ((d64_ & significand_mask) == 0);
		}

		bool isNan() const
		{
			return ((d64_ & exponent_mask) == exponent_mask) && ((d64_ & significand_mask) != 0);
		}

		bool lowerBoundaryIsCloser() const
		{
			return ((d64_ & significand_mask) == 0 && exponent() != subnormal_exponent);
		}

		int exponent() const
		{
			if (isSubnormal()) {
				return subnormal_exponent;
			}
			else {
				return (int)((d64_ & exponent_mask) >> physical_significand_size) - exponent_bias;
			}
		}

		uint64_t significand() const
		{
			if (isSubnormal()) {
				return (d64_ & significand_mask);
			}
			else {
				return ((d64_ & significand_mask) | hidden_bit);
			}
		}

		static double infinity()
		{
			return Binary64(infinity_value).value();
		}

		static double negInfinity()
		{
			return Binary64(sign_mask | infinity_value).value();
		}

		static double nan()
		{
			return Binary64(nan_value).value();
		}

		static double negNan()
		{
			return Binary64(sign_mask | nan_value).value();
		}

	private:
		uint64_t d64_;
	};

} // detail
} // eclog
} // vallest

#include <ostream>

namespace vallest {
namespace eclog {

	class Number {
	public:
		enum UnderlyingType {
			underlying_type_double,
			underlying_type_int,
			underlying_type_uint,
			underlying_type_long,
			underlying_type_ulong,
			underlying_type_llong,
			underlying_type_ullong,
		};

	public:
		Number() : underlyingType_(underlying_type_double), double_(0)
		{
		}

		Number(double value) : underlyingType_(underlying_type_double), double_(value)
		{
		}

		Number(int value) : underlyingType_(underlying_type_int), int_(value)
		{
		}

		Number(long value) : underlyingType_(underlying_type_long), long_(value)
		{
		}

		Number(long long value) : underlyingType_(underlying_type_llong), llong_(value)
		{
		}

		Number(unsigned int value) : underlyingType_(underlying_type_uint), uint_(value)
		{
		}

		Number(unsigned long value) : underlyingType_(underlying_type_ulong), ulong_(value)
		{
		}

		Number(unsigned long long value) : underlyingType_(underlying_type_ullong), ullong_(value)
		{
		}

		UnderlyingType underlyingType() const
		{
			return underlyingType_;
		}

		int sign() const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return detail::Binary64(double_).sign();

			case underlying_type_int:
				return int_ < 0 ? -1 : 1;

			case underlying_type_long:
				return long_ < 0 ? -1 : 1;

			case underlying_type_llong:
				return llong_ < 0 ? -1 : 1;

			default:
				return 1;
			}
		}

		bool isSubnormal() const
		{
			return (underlyingType_ == underlying_type_double && detail::Binary64(double_).isSubnormal());
		}

		bool isInfinity() const
		{
			return (underlyingType_ == underlying_type_double && detail::Binary64(double_).isInfinity());
		}

		bool isNan() const
		{
			return (underlyingType_ == underlying_type_double && detail::Binary64(double_).isNan());
		}

		Number& operator=(double value)
		{
			store(value);
			return *this;
		}

		Number& operator=(int value)
		{
			store(value);
			return *this;
		}

		Number& operator=(long value)
		{
			store(value);
			return *this;
		}

		Number& operator=(long long value)
		{
			store(value);
			return *this;
		}

		Number& operator=(unsigned int value)
		{
			store(value);
			return *this;
		}

		Number& operator=(unsigned long value)
		{
			store(value);
			return *this;
		}

		Number& operator=(unsigned long long value)
		{
			store(value);
			return *this;
		}

		template<typename T>
		T load() const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return (T)double_;

			case underlying_type_int:
				return (T)int_;

			case underlying_type_uint:
				return (T)uint_;

			case underlying_type_long:
				return (T)long_;

			case underlying_type_ulong:
				return (T)ulong_;

			case underlying_type_llong:
				return (T)llong_;

			case underlying_type_ullong:
				return (T)ullong_;

			default:
				ECLOG_ASSERT(false);
				return 0;
			}
		}

		void store(double value)
		{
			underlyingType_ = underlying_type_double;
			double_ = value;
		}

		void store(int value)
		{
			underlyingType_ = underlying_type_int;
			int_ = value;
		}

		void store(long value)
		{
			underlyingType_ = underlying_type_long;
			long_ = value;
		}

		void store(long long value)
		{
			underlyingType_ = underlying_type_llong;
			llong_ = value;
		}

		void store(unsigned int value)
		{
			underlyingType_ = underlying_type_uint;
			uint_ = value;
		}

		void store(unsigned long value)
		{
			underlyingType_ = underlying_type_ulong;
			ulong_ = value;
		}

		void store(unsigned long long value)
		{
			underlyingType_ = underlying_type_ullong;
			ullong_ = value;
		}

		bool operator==(const Number& other) const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return other.equalTo(double_);

			case underlying_type_int:
				return other.equalTo(int_);

			case underlying_type_uint:
				return other.equalTo(uint_);

			case underlying_type_long:
				return other.equalTo(long_);

			case underlying_type_ulong:
				return other.equalTo(ulong_);

			case underlying_type_llong:
				return other.equalTo(llong_);

			case underlying_type_ullong:
				return other.equalTo(ullong_);

			default:
				ECLOG_ASSERT(false);
				return false;
			}
		}

		bool operator!=(const Number& other) const
		{
			return !(*this == other);
		}

		bool operator<(const Number& other) const
		{
			switch (underlyingType_)
			{
			case underlying_type_double:
				return other.greaterThan(double_);

			case underlying_type_int:
				return other.greaterThan(int_);

			case underlying_type_uint:
				return other.greaterThan(uint_);

			case underlying_type_long:
				return other.greaterThan(long_);

			case underlying_type_ulong:
				return other.greaterThan(ulong_);

			case underlying_type_llong:
				return other.greaterThan(llong_);

			case underlying_type_ullong:
				return other.greaterThan(ullong_);

			default:
				ECLOG_ASSERT(false);
				return false;
			}
		}

		bool operator>(const Number& other) const
		{
			return other < *this;
		}

		bool operator<=(const Number& other) const
		{
			return !(*this > other);
		}

		bool operator>=(const Number& other) const
		{
			return !(*this < other);
		}

		int compare(const Number& other) const
		{
			if (*this < other) {
				return -1;
			}
			else if (*this > other) {
				return 1;
			}
			else {
				return 0;
			}
		}

	public:
		static Number infinity()
		{
			return detail::Binary64::infinity();
		}

		static Number negInfinity()
		{
			return detail::Binary64::negInfinity();
		}

		static Number nan()
		{
			return detail::Binary64::nan();
		}

		static Number negNan()
		{
			return detail::Binary64::negNan();
		}

	private:
		template<typename T>
		bool equalTo(T value) const
		{
			ECLOG_WARNING_PUSH
			ECLOG_WARNING_IGNORE_SIGN_COMPARE

			switch (underlyingType_)
			{
			case underlying_type_double:
				return double_ == value;

			case underlying_type_int:
				return int_ == value;

			case underlying_type_uint:
				return uint_ == value;

			case underlying_type_long:
				return long_ == value;

			case underlying_type_ulong:
				return ulong_ == value;

			case underlying_type_llong:
				return llong_ == value;

			case underlying_type_ullong:
				return ullong_ == value;

			default:
				ECLOG_ASSERT(false);
				return false;
			}

			ECLOG_WARNING_POP
		}

		template<typename T>
		bool greaterThan(T value) const
		{
			ECLOG_WARNING_PUSH
			ECLOG_WARNING_IGNORE_SIGN_COMPARE

			switch (underlyingType_)
			{
			case underlying_type_double:
				return double_ > value;

			case underlying_type_int:
				return int_ > value;

			case underlying_type_uint:
				return uint_ > value;

			case underlying_type_long:
				return long_ > value;

			case underlying_type_ulong:
				return ulong_ > value;

			case underlying_type_llong:
				return llong_ > value;

			case underlying_type_ullong:
				return ullong_ > value;

			default:
				ECLOG_ASSERT(false);
				return false;
			}

			ECLOG_WARNING_POP
		}

	private:
		UnderlyingType underlyingType_;

		union {
			double double_;
			int int_;
			long long_;
			long long llong_;
			unsigned int uint_;
			unsigned long ulong_;
			unsigned long long ullong_;
		};
	};

#define ECLOG_DEFINE_NUMBER_OPERATORS(Type)					\
	inline bool operator==(Type a, const Number& b)			\
	{														\
		return b == a;										\
	}														\
	inline bool operator!=(Type a, const Number& b)			\
	{														\
		return !(a == b);									\
	}														\
	inline bool operator<(Type a, const Number& b)			\
	{														\
		return b > a;										\
	}														\
	inline bool operator>(Type a, const Number& b)			\
	{														\
		return b < a;										\
	}														\
	inline bool operator<=(Type a, const Number& b)			\
	{														\
		return !(a > b);									\
	}														\
	inline bool operator>=(Type a, const Number& b)			\
	{														\
		return !(a < b);									\
	}

	ECLOG_DEFINE_NUMBER_OPERATORS(double)
	ECLOG_DEFINE_NUMBER_OPERATORS(int)
	ECLOG_DEFINE_NUMBER_OPERATORS(unsigned int)
	ECLOG_DEFINE_NUMBER_OPERATORS(long)
	ECLOG_DEFINE_NUMBER_OPERATORS(unsigned long)
	ECLOG_DEFINE_NUMBER_OPERATORS(long long)
	ECLOG_DEFINE_NUMBER_OPERATORS(unsigned long long)

#undef ECLOG_DEFINE_NUMBER_OPERATORS

	inline std::ostream& operator<<(std::ostream& stream, const Number& n)
	{
		switch (n.underlyingType())
		{
		case Number::underlying_type_double:
			stream << n.load<double>();
			break;

		case Number::underlying_type_int:
			stream << n.load<int>();
			break;

		case Number::underlying_type_uint:
			stream << n.load<unsigned int>();
			break;

		case Number::underlying_type_long:
			stream << n.load<long>();
			break;

		case Number::underlying_type_ulong:
			stream << n.load<unsigned long>();
			break;

		case Number::underlying_type_llong:
			stream << n.load<long long>();
			break;

		case Number::underlying_type_ullong:
			stream << n.load<unsigned long long>();
			break;

		default:
			ECLOG_ASSERT(false);
		}

		return stream;
	}

} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	inline bool isBetween(int ch, int lower, int upper)
	{
		return (ch >= lower && ch <= upper);
	}

	inline bool isLower(int ch)
	{
		return isBetween(ch, 'a', 'z');
	}

	inline bool isUpper(int ch)
	{
		return isBetween(ch, 'A', 'Z');
	}

	inline bool isDigit(int ch)
	{
		return isBetween(ch, '0', '9');
	}

	inline bool isAlpha(int ch)
	{
		return (isLower(ch) || isUpper(ch));
	}

	inline bool isAlphanum(int ch)
	{
		return (isAlpha(ch) || isDigit(ch));
	}

} // detail
} // eclog
} // vallest

#include <limits>

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T>
	inline T minValue()
	{
		return std::numeric_limits<T>::min();
	}

	template<typename T>
	inline T maxValue()
	{
		return std::numeric_limits<T>::max();
	}

} // detail
} // eclog
} // vallest

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4146)
#endif

namespace vallest {
namespace eclog {
namespace detail {

	template<typename IntType>
	inline IntType stringToSignedInteger(const char* str, const char** outStr = 0, int* outError = 0)
	{
		bool negative = false;

		if (*str == '+') {
			++str;
		}
		else if (*str == '-') {
			++str;
			negative = true;
		}

		typename detail::RemoveCV<IntType>::Type result = 0;

		const typename detail::RemoveCV<IntType>::Type n = negative ? detail::minValue<IntType>() / 10 : detail::maxValue<IntType>() / 10;
		const int m = (int)(negative ? -(detail::minValue<IntType>() % 10) : detail::maxValue<IntType>() % 10);

		int error = 0;

		for (;;)
		{
			char ch = *str;

			if (detail::isDigit(ch))
			{
				char d = ch - '0';

				if (negative)
				{
					if (result < n || (result == n && d > m)) {
						error = -1;
					}

					result = result * 10 - d;
				}
				else
				{
					if (result > n || (result == n && d > m)) {
						error = 1;
					}

					result = result * 10 + d;
				}

				++str;
			}
			else
			{
				break;
			}
		}

		if (outStr) {
			*outStr = str;
		}

		if (outError) {
			*outError = error;
		}

		return result;
	}

	template<typename UIntType>
	inline UIntType stringToUnsignedInteger(const char* str, const char** outStr = 0, int* outError = 0)
	{
		bool negative = false;

		if (*str == '+') {
			++str;
		}
		else if (*str == '-') {
			++str;
			negative = true;
		}

		typename detail::RemoveCV<UIntType>::Type result = 0;

		const typename detail::RemoveCV<UIntType>::Type n = detail::maxValue<UIntType>() / 10;
		const int m = (int)(detail::maxValue<UIntType>() % 10);

		int error = 0;

		for (;;)
		{
			char ch = *str;

			if (detail::isDigit(ch))
			{
				char d = ch - '0';

				if (result > n || (result == n && d > m)) {
					error = 1;
				}

				result = result * 10 + d;
				++str;
			}
			else
			{
				break;
			}
		}

		if (outStr) {
			*outStr = str;
		}

		if (outError) {
			*outError = error;
		}

		return negative ? -result : result;
	}

	template<typename IntType>
	inline void integerToString(IntType value, char* buffer)
	{
		char* p = buffer;

		if (value == 0)
		{
			p[0] = '0';
			p[1] = 0;
			return;
		}

		bool negative = false;

		if (value < 0)
		{
			value = -value;
			negative = true;
		}

		while (value)
		{
			*p++ = '0' + (char)(value % 10);
			value /= 10;
		}

		if (negative) {
			*p++ = '-';
		}

		detail::reverse(buffer, p);

		*p = 0;
	}

} // detail
} // eclog
} // vallest

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

namespace vallest {
namespace eclog {
namespace detail {

	double stringToDouble(const char* str, const char** outStr = 0, int* outError = 0);
	void doubleToString(double d, char* buffer, int fracDigits = -1);

} // detail
} // eclog
} // vallest

#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable: 4127)
#endif

namespace vallest {
namespace eclog {

	class Value {
	public:
		explicit Value(ValueType type) : type_(type)
		{
			ECLOG_ASSERT(type == value_type_object || type == value_type_array);
		}

		explicit Value(ValueType type, cstring bytes) :
			type_(type), bytes_(bytes)
		{
			ECLOG_ASSERT(type == value_type_null || type == value_type_boolean);
		}

		explicit Value(ValueType type, cstring bytes, NumberInfo numberInfo) :
			type_(type), bytes_(bytes)
		{
			ECLOG_ASSERT(type == value_type_number);

			numberInfo_ = numberInfo;
		}

		explicit Value(ValueType type, cstring bytes, StringNotation notation, size_t delimiterSize) :
			type_(type), bytes_(bytes.begin() + delimiterSize, bytes.end())
		{
			ECLOG_ASSERT(type == value_type_string);

			str_.notation = notation;
			str_.dbegin = bytes.begin();
			str_.dend = bytes.begin() + delimiterSize;
		}

		ValueType type() const
		{
			return type_;
		}

		bool isNull() const
		{
			return (type_ == value_type_null);
		}

		bool isBoolean() const
		{
			return (type_ == value_type_boolean);
		}

		bool isString() const
		{
			return (type_ == value_type_string);
		}

		bool isNumber() const
		{
			return (type_ == value_type_number);
		}

		bool isObject() const
		{
			return (type_ == value_type_object);
		}

		bool isArray() const
		{
			return (type_ == value_type_array);
		}

		Null asNull() const
		{
			if (type_ != value_type_null) {
				ECLOG_FAULT(BadCast);
			}

			return null;
		}

		bool asBoolean() const
		{
			if (type_ != value_type_boolean) {
				ECLOG_FAULT(BadCast);
			}

			return (bytes_[0] == 't');
		}

		cstring asString() const
		{
			if (type_ != value_type_string) {
				ECLOG_FAULT(BadCast);
			}

			return bytes_;
		}

		Number asNumber() const
		{
			if (type_ != value_type_number) {
				ECLOG_FAULT(BadCast);
			}

			if (numberInfo_ & (number_info_has_frac | number_info_has_exp | number_info_inf | number_info_nan))
			{
				return detail::stringToDouble(bytes_.data());
			}
			else
			{
				int error;

				long long n = detail::stringToSignedInteger<long long>(bytes_.data(), 0, &error);

				if (error == 0)
				{
					if (n >= detail::minValue<int>() && n <= detail::maxValue<int>()) {
						return (int)n;
					}
					else if (n >= detail::minValue<long>() && n <= detail::maxValue<long>()) {
						return (long)n;
					}
					else {
						return n;
					}
				}

				if (numberInfo_ & number_info_has_neg_sign)
				{
					return detail::stringToDouble(bytes_.data());
				}

				unsigned long long m = detail::stringToUnsignedInteger<unsigned long long>(bytes_.data(), 0, &error);

				if (error == 0)
				{
					if (m <= detail::maxValue<unsigned int>()) {
						return (unsigned int)m;
					}
					else if (m <= detail::maxValue<unsigned long>()) {
						return (unsigned long)m;
					}
					else {
						return m;
					}
				}

				return detail::stringToDouble(bytes_.data());
			}
		}

		cstring bytes() const
		{
			return bytes_;
		}

		int numberInfo() const
		{
			return numberInfo_;
		}

		StringNotation stringNotation() const
		{
			return str_.notation;
		}

		cstring stringDelimiter() const
		{
			return cstring(str_.dbegin, str_.dend);
		}

	private:
		ValueType type_;

		cstring bytes_;

		union
		{
			int numberInfo_;

			struct
			{
				const char* dbegin;
				const char* dend;

				StringNotation notation;
			}
			str_;
		};
	};

} // eclog
} // vallest

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

namespace vallest {
namespace eclog {
namespace detail {

	class ParseHandler {
	public:
		virtual void onObjectBegin(ErrorCode*)
		{
		}

		virtual void onObjectEnd(ErrorCode*)
		{
		}

		virtual void onArrayBegin(ErrorCode*)
		{
		}

		virtual void onArrayEnd(ErrorCode*)
		{
		}

		virtual void onKey(const Key&, ErrorCode*)
		{
		}

		virtual void onValue(const Value&, ErrorCode*)
		{
		}
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	void parseObject(Context& ctx, ParseHandler& handler, ErrorCode* ec);
	void parseArray(Context& ctx, ParseHandler& handler, ErrorCode* ec);

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	inline bool checkTerminated(Context& ctx, ErrorCode* ec)
	{
		if (ctx.terminated())
		{
			ECLOG_ERROR(ParseError, ctx.line(), ctx.column(), pe_user_asked_for_termination);
			return true;
		}

		return false;
	}

	template<typename Handler>
	class ParseHandlerAdapter : public ParseHandler, private NonCopyable {
	public:
		explicit ParseHandlerAdapter(Context& ctx, Handler& handler) :
			ctx_(ctx), handler_(handler)
		{
		}

		virtual void onObjectBegin(ErrorCode* ec) ECLOG_OVERRIDE
		{
			handler_.onObjectBegin();
			checkTerminated(ctx_, ec);
		}

		virtual void onObjectEnd(ErrorCode* ec) ECLOG_OVERRIDE
		{
            handler_.onObjectEnd();
            checkTerminated(ctx_, ec);
		}

		virtual void onArrayBegin(ErrorCode* ec) ECLOG_OVERRIDE
		{
			handler_.onArrayBegin();
			checkTerminated(ctx_, ec);
		}

		virtual void onArrayEnd(ErrorCode* ec) ECLOG_OVERRIDE
		{
            handler_.onArrayEnd();
            checkTerminated(ctx_, ec);
		}

		virtual void onKey(const Key& key, ErrorCode* ec) ECLOG_OVERRIDE
		{
			handler_.onKey(key);
			checkTerminated(ctx_, ec);
		}

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject())
			{
				parseObject(ctx_, *this, ec);
			}
			else if (value.isArray())
			{
				parseArray(ctx_, *this, ec);
			}
			else
			{
				handler_.onValue(value);
				checkTerminated(ctx_, ec);
			}
		}

	private:
		Context& ctx_;
		Handler& handler_;
	};

	class IgnoreParseHandler : public ParseHandler, private NonCopyable {
    public:
        IgnoreParseHandler(Context& ctx) : ctx_(ctx)
        {
        }

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject())
			{
				parseObject(ctx_, *this, ec);
			}
			else if (value.isArray())
			{
				parseArray(ctx_, *this, ec);
			}
		}

    private:
        Context& ctx_;
    };

	inline void ignore(Context& ctx, Value value, ErrorCode* ec)
	{
		if (value.isObject())
		{
			IgnoreParseHandler handler(ctx);
			parseObject(ctx, handler, ec);
		}
		else if (value.isArray())
		{
			IgnoreParseHandler handler(ctx);
			parseArray(ctx, handler, ec);
		}
	}

	template<typename Handler>
	class ObjectParseHandlerAdapter : public ParseHandler, private NonCopyable {
	public:
		explicit ObjectParseHandlerAdapter(Context& ctx, Handler handler) :
			ctx_(ctx), handler_(handler)
		{
		}

		virtual void onKey(const Key& key, ErrorCode*) ECLOG_OVERRIDE
		{
			key_ = key;
		}

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject() || value.isArray())
			{
				const long long oldPos = ctx_.decoder().position();

				handler_(key_, value);

				if (checkTerminated(ctx_, ec)) {
					return;
				}

				if (ctx_.decoder().position() == oldPos) {
					ignore(ctx_, value, ec);
				}
			}
			else
			{
				handler_(key_, value);
				checkTerminated(ctx_, ec);
			}
		}

	private:
		Context& ctx_;
		Handler handler_;
		Key key_;
	};

	template<typename Handler>
	class ArrayParseHandlerAdapter : public ParseHandler, private NonCopyable {
	public:
		explicit ArrayParseHandlerAdapter(Context& ctx, Handler handler) :
			ctx_(ctx), handler_(handler)
		{
		}

		virtual void onValue(const Value& value, ErrorCode* ec) ECLOG_OVERRIDE
		{
			if (value.isObject() || value.isArray())
			{
				const long long oldPos = ctx_.decoder().position();

				handler_(value);

				if (checkTerminated(ctx_, ec)) {
					return;
				}

				if (ctx_.decoder().position() == oldPos) {
					ignore(ctx_, value, ec);
				}
			}
			else
			{
				handler_(value);
				checkTerminated(ctx_, ec);
			}
		}

	private:
		Context& ctx_;
		Handler handler_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	template<typename Handler>
	inline void parse(Context& ctx, Handler& handler)
	{
		detail::ParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, 0);
	}

	template<typename Handler>
	inline void parse(Context& ctx, Handler& handler, ErrorCode& ec)
	{
		detail::ParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, &ec);
	}

	template<typename Handler>
	inline void parseObject(Context& ctx, Handler handler)
	{
		detail::ObjectParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, 0);
	}

	template<typename Handler>
	inline void parseObject(Context& ctx, Handler handler, ErrorCode& ec)
	{
		detail::ObjectParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseObject((detail::Context&)ctx, adapter, &ec);
	}

	template<typename Handler>
	inline void parseArray(Context& ctx, Handler handler)
	{
		detail::ArrayParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseArray((detail::Context&)ctx, adapter, 0);
	}

	template<typename Handler>
	inline void parseArray(Context& ctx, Handler handler, ErrorCode& ec)
	{
		detail::ArrayParseHandlerAdapter<Handler> adapter((detail::Context&)ctx, handler);
		detail::parseArray((detail::Context&)ctx, adapter, &ec);
	}

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	enum Linebreak {
		CR = 1,
		LF,
		CRLF,
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	struct RendererConfig {
	public:
		enum Scheme {
			scheme_typical,
			scheme_json_compatible,
		};

		enum Formatting {
			formatting_regular,
			formatting_compact,
		};

		enum IndentCharacter {
			indent_character_tab,
			indent_character_space,
		};

	public:
		explicit RendererConfig(Scheme scheme = scheme_typical)
		{
			formatting = formatting_regular;
			linebreak = LF;
			indentCharacter = indent_character_tab;
			indentSize = 1;
            insertSpaceAfterColon = true;
            placeOpenBracketOnNewLineForObjects = true;
            placeOpenBracketOnNewLineForArrays = true;

			if (scheme == scheme_typical)
			{
				encloseRootObjectWithCurlyBrackets = false;
				useQuotedStringsOnly = false;
				useCommasToSeparateItems = false;
				useStringsToRepresentInfinitiesAndNaNs = false;
				enableComments = true;
			}
			else if (scheme == scheme_json_compatible)
			{
				encloseRootObjectWithCurlyBrackets = true;
				useQuotedStringsOnly = true;
				useCommasToSeparateItems = true;
				useStringsToRepresentInfinitiesAndNaNs = true;
				enableComments = false;
			}
		}

	public:
		Formatting formatting;

		Linebreak linebreak;

		IndentCharacter indentCharacter;
		int indentSize;

        bool insertSpaceAfterColon;

        bool placeOpenBracketOnNewLineForObjects;

        bool placeOpenBracketOnNewLineForArrays;

		bool encloseRootObjectWithCurlyBrackets;

		bool useQuotedStringsOnly;

		bool useCommasToSeparateItems;

		bool useStringsToRepresentInfinitiesAndNaNs;

		bool enableComments;
	};

} // eclog
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T, size_t MaxSize>
	class InlineArray {
	public:
		InlineArray() : size_(0)
		{
		}

		void clear()
		{
			size_ = 0;
		}

		size_t maxSize() const
		{
			return MaxSize;
		}

		size_t size() const
		{
			return size_;
		}

		void resize(size_t size)
		{
			ECLOG_ASSERT(size <= MaxSize);
			size_ = size;
		}

		T& operator[](size_t index)
		{
			return array_[index];
		}

		const T& operator[](size_t index) const
		{
			return array_[index];
		}

		void pushBack(const T& value)
		{
			ECLOG_ASSERT(size_ < MaxSize);
			array_[size_++] = value;
		}

		void popBack()
		{
			ECLOG_ASSERT(size_ > 0);
			--size_;
		}

		T* data()
		{
			return array_;
		}

		const T* data() const
		{
			return array_;
		}

	private:
		T array_[MaxSize];

		size_t size_;
	};

} // detail
} // eclog
} // vallest

#include <string.h> // memcpy
#include <stddef.h> // size_t

namespace vallest {
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
} // vallest

namespace vallest {
namespace eclog {

	class KeyDesc {
	public:
		KeyDesc(const char* str) : str_(str), notation_(string_notation_unquoted)
		{
		}

		KeyDesc(cstring str, StringNotation notation = string_notation_unquoted, cstring delimiter = cstring()) :
			str_(str), notation_(notation), delimiter_(delimiter)
		{
			if (!detail::StringDelimiter::validate(delimiter_)) {
				ECLOG_FAULT(InvalidArgument);
			}
		}

		cstring str() const
		{
			return str_;
		}

		StringNotation notation() const
		{
			return notation_;
		}

		cstring delimiter() const
		{
			return delimiter_;
		}

	private:
		cstring str_;

		StringNotation notation_;
		cstring delimiter_;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	enum EmptyObjectTag {
		empty_object,
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	enum EmptyArrayTag {
		empty_array,
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	template<typename T1, typename T2>
	struct Pair {
	public:
		typedef T1 FirstType;
		typedef T2 SecondType;

	public:
		Pair()
		{
		}

		Pair(const T1& arg1, const T2& arg2) : first(arg1), second(arg2)
		{
		}

		template<typename U1, typename U2>
		Pair(const Pair<U1, U2>& other) : first(other.first), second(other.second)
		{
		}

	public:
		T1 first;
		T2 second;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class ValueDesc {
	public:
		ValueDesc(Null) : type_(value_type_null)
		{
		}

		ValueDesc(bool value) : type_(value_type_boolean), bool_(value)
		{
		}

		ValueDesc(const char* value) : type_(value_type_string)
		{
			cstring string(value);

			str_.begin = string.begin();
			str_.end = string.end();
			str_.dbegin = 0;
			str_.dend = 0;
			str_.notation = string_notation_unquoted;
		}

		ValueDesc(cstring value, StringNotation notation = string_notation_unquoted, cstring delimiter = cstring()) : type_(value_type_string)
		{
			if (!detail::StringDelimiter::validate(delimiter)) {
				ECLOG_FAULT(InvalidArgument);
			}

			str_.begin = value.begin();
			str_.end = value.end();
			str_.dbegin = delimiter.begin();
			str_.dend = delimiter.end();
			str_.notation = notation;
		}

		ValueDesc(const Number& value, int fracDigits = -1) : type_(value_type_number)
		{
			number_.underlyingType = value.underlyingType();

			switch (value.underlyingType())
			{
			case Number::underlying_type_double:
				number_.d = value.load<double>();
				break;

			case Number::underlying_type_int:
				number_.i = value.load<int>();
				break;

			case Number::underlying_type_uint:
				number_.ui = value.load<unsigned int>();
				break;

			case Number::underlying_type_long:
				number_.l = value.load<long>();
				break;

			case Number::underlying_type_ulong:
				number_.ul = value.load<unsigned long>();
				break;

			case Number::underlying_type_llong:
				number_.ll = value.load<long long>();
				break;

			case Number::underlying_type_ullong:
				number_.ull = value.load<unsigned long long>();
				break;

			default:
				ECLOG_ASSERT(false);
			}

			number_.fracDigits = fracDigits;
		}

		ValueDesc(double value, int fracDigits = -1) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_double;
			number_.d = value;
			number_.fracDigits = fracDigits;
		}

		ValueDesc(int value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_int;
			number_.i = value;
			number_.fracDigits = -1;
		}

		ValueDesc(long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_long;
			number_.l = value;
			number_.fracDigits = -1;
		}

		ValueDesc(long long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_llong;
			number_.ll = value;
			number_.fracDigits = -1;
		}

		ValueDesc(unsigned int value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_uint;
			number_.ui = value;
			number_.fracDigits = -1;
		}

		ValueDesc(unsigned long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_ulong;
			number_.ul = value;
			number_.fracDigits = -1;
		}

		ValueDesc(unsigned long long value) : type_(value_type_number)
		{
			number_.underlyingType = Number::underlying_type_ullong;
			number_.ull = value;
			number_.fracDigits = -1;
		}

		ValueDesc(EmptyObjectTag) : type_(value_type_object)
		{
			object_.p = 0;
			object_.size = 0;
		}

		ValueDesc(const Pair<KeyDesc, ValueDesc>* p, size_t size) : type_(value_type_object)
		{
			object_.p = p;
			object_.size = size;
		}

		template<size_t N>
		ValueDesc(const Pair<KeyDesc, ValueDesc>(&v)[N]) : type_(value_type_object)
		{
			object_.p = v;
			object_.size = N;
		}

		ValueDesc(EmptyArrayTag) : type_(value_type_array)
		{
			array_.p = 0;
			array_.size = 0;
		}

		ValueDesc(const ValueDesc* p, size_t size) : type_(value_type_array)
		{
			array_.p = p;
			array_.size = size;
		}

		template<size_t N>
		ValueDesc(const ValueDesc(&v)[N]) : type_(value_type_array)
		{
			array_.p = v;
			array_.size = N;
		}

	public:
		ValueType type() const
		{
			return type_;
		}

		bool boolean() const
		{
			ECLOG_ASSERT(type_ == value_type_boolean);
			return bool_;
		}

		cstring string() const
		{
			ECLOG_ASSERT(type_ == value_type_string);
			return str_.begin ? cstring(str_.begin, str_.end) : cstring();
		}

		StringNotation stringNotation() const
		{
			ECLOG_ASSERT(type_ == value_type_string);
			return str_.notation;
		}

		cstring stringDelimiter() const
		{
			ECLOG_ASSERT(type_ == value_type_string);
			return str_.dbegin ? cstring(str_.dbegin, str_.dend) : cstring();
		}

		Number number() const
		{
			ECLOG_ASSERT(type_ == value_type_number);

			switch (number_.underlyingType)
			{
			case Number::underlying_type_double:
				return number_.d;

			case Number::underlying_type_int:
				return number_.i;

			case Number::underlying_type_uint:
				return number_.ui;

			case Number::underlying_type_long:
				return number_.l;

			case Number::underlying_type_ulong:
				return number_.ul;

			case Number::underlying_type_llong:
				return number_.ll;

			case Number::underlying_type_ullong:
				return number_.ull;

			default:
				ECLOG_ASSERT(false);
				return 0;
			}
		}

		int fracDigits() const
		{
			ECLOG_ASSERT(type_ == value_type_number);
			return number_.fracDigits;
		}

		const Pair<KeyDesc, ValueDesc>* object() const
		{
			return object_.p;
		}

		size_t objectSize() const
		{
			return object_.size;
		}

		const ValueDesc* array() const
		{
			return array_.p;
		}

		size_t arraySize() const
		{
			return array_.size;
		}

	private:
		ValueType type_;

		union
		{
			bool bool_;

			struct
			{
				const char* begin;
				const char* end;
				const char* dbegin;
				const char* dend;

				StringNotation notation;
			}
			str_;

			struct
			{
				Number::UnderlyingType underlyingType;

				union {
					double d;
					int i;
					long l;
					long long ll;
					unsigned int ui;
					unsigned long ul;
					unsigned long long ull;
				};

				int fracDigits;
			}
			number_;

			struct
			{
				const Pair<KeyDesc, ValueDesc>* p;
				size_t size;
			}
			object_;

			struct
			{
				const ValueDesc* p;
				size_t size;
			}
			array_;
		};
	};

} // eclog
} // vallest

namespace vallest {
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
} // vallest

namespace vallest {
namespace eclog {

	class Renderer;
	class ObjectRenderer;
	class ArrayRenderer;

	struct RendererHandle {
	private:
		friend class Renderer;
		friend class ObjectRenderer;
		friend class ArrayRenderer;

	private:
		explicit RendererHandle(void* p1, void* p2)
		{
			this->p1 = p1;
			this->p2 = p2;
		}

	private:
		void* p1;
		void* p2;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class NumberDesc : public ValueDesc {
	public:
		NumberDesc(const Number& value, int fracDigits = -1) : ValueDesc(value, fracDigits) {}
		NumberDesc(double value, int fracDigits = -1) : ValueDesc(value, fracDigits) {}
		NumberDesc(int value) : ValueDesc(value) {}
		NumberDesc(long value) : ValueDesc(value) {}
		NumberDesc(long long value) : ValueDesc(value) {}
		NumberDesc(unsigned int value) : ValueDesc(value) {}
		NumberDesc(unsigned long value) : ValueDesc(value) {}
		NumberDesc(unsigned long long value) : ValueDesc(value) {}
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class StringDesc : public ValueDesc {
	public:
		StringDesc(const char* value) : ValueDesc(value)
		{
		}

		StringDesc(cstring value, StringNotation notation = string_notation_unquoted, cstring delimiter = cstring())
			: ValueDesc(value, notation, delimiter)
		{
		}
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class Renderer : private NonCopyable {
	private:
		enum {
			separator_linebreak = 1,
			separator_comma,
		};

	public:
		explicit Renderer(OutputStream& stream, const RendererConfig& rendererConfig);

		void beginObject(const KeyDesc& key, ErrorCode* ec);
		void beginObject(ErrorCode* ec);
		void endObject(ErrorCode* ec);

		void beginArray(const KeyDesc& key, ErrorCode* ec);
		void beginArray(ErrorCode* ec);
		void endArray(ErrorCode* ec);

		void renderMember(const KeyDesc& key, const ValueDesc& value, ErrorCode* ec);
		void renderMember(const ValueDesc& value, ErrorCode* ec);

		void renderEmptyLines(int count, ErrorCode* ec);

		void renderComment(cstring comment, ErrorCode* ec);

		int beginInline();
		int endInline();

		void close(ErrorCode* ec);

		const RendererConfig& rendererConfig() const;

	private:
		void beginItem(ErrorCode* ec);
		void endItem();

		void beginStruct(ErrorCode* ec);
		void endStruct(ErrorCode* ec);

		void renderValueInternal(const ValueDesc& value, ErrorCode* ec);

		void renderString(cstring str, StringNotation notation, cstring delimiter, ErrorCode* ec);

		void renderQuotedString(cstring str, ErrorCode* ec);
		void renderUnquotedString(cstring str, ErrorCode* ec);
		void renderRawString(cstring str, cstring delimiter, ErrorCode* ec);
		void renderHeredoc(cstring str, cstring delimiter, ErrorCode* ec);

		void renderNumber(const Number& number, int fracDigits, ErrorCode* ec);

		void renderLinebreak(ErrorCode* ec);
		void renderIndent(ErrorCode* ec);
		void renderSeparator(ErrorCode* ec);
		void renderSpace(ErrorCode* ec);
		void renderLeftCurlyBracket(ErrorCode* ec);
		void renderRightCurlyBracket(ErrorCode* ec);
		void renderLeftSquareBracket(ErrorCode* ec);
		void renderRightSquareBracket(ErrorCode* ec);
		void renderColon(ErrorCode* ec);
		void renderComma(ErrorCode* ec);
		void renderSequence(cstring s, ErrorCode* ec);
		void renderChar(int ch, ErrorCode* ec);

		void increaseNestingLevel();
		void decreaseNestingLevel();
		int nestingLevel() const;

		void increaseIndent();
		void decreaseIndent();
		int indent() const;

		void setError(int error = 1);
		int error() const;

	private:
		UTF8Encoder encoder_;
		RendererConfig rc_;

		int nestingLevel_;
		int indent_;
		bool beginOfLine_;
		int separator_;
		int inline_;

		int error_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	enum RendererState {
		renderer_state_init = 0,
		renderer_state_element = 1,
		renderer_state_object = 2,
		renderer_state_array = 3,
		renderer_state_closed = 4,

		renderer_state_ref_1 = 1 << 4,
		renderer_state_ref_2 = 2 << 4,
		renderer_state_root = 3 << 4,
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class Renderer : private detail::NonCopyable {
	public:
		explicit Renderer(OutputStream& stream, const RendererConfig& rendererConfig = RendererConfig()) :
			renderer_(stream, rendererConfig), state_(detail::renderer_state_init)
		{
			initialize();
		}

		void beginRootObject()
		{
			changeStateBeginRootObject();

			renderer_.beginObject(0);
		}

		void endRootObject()
		{
			changeStateEndRootObject();

			renderer_.endObject(0);
		}

		void beginRootObject(ErrorCode& ec)
		{
			changeStateBeginRootObject();

			renderer_.beginObject(&ec);
		}

		void endRootObject(ErrorCode& ec)
		{
			changeStateEndRootObject();

			renderer_.endObject(&ec);
		}

		void renderRootObject(const ObjectDesc& root)
		{
			changeStateRoot();

			renderer_.renderMember(root, 0);
		}

		void renderRootObject(const ObjectDesc& root, ErrorCode& ec)
		{
			changeStateRoot();

			renderer_.renderMember(root, &ec);
		}

		void renderEmptyLines(int count)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, 0);
		}

		void renderEmptyLines(int count, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, &ec);
		}

		void renderComment(cstring comment)
		{
			checkStateElement();

			renderer_.renderComment(comment, 0);
		}

		void renderComment(cstring comment, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderComment(comment, &ec);
		}

		int beginInline()
		{
			checkStateElement();

			return renderer_.beginInline();
		}

		int endInline()
		{
			checkStateElement();

			return renderer_.endInline();
		}

		void close()
		{
			close(0);
		}

		void close(ErrorCode& ec)
		{
			close(&ec);
		}

		operator RendererHandle()
		{
			return RendererHandle(&renderer_, &state_);
		}

	private:
		void initialize()
		{
			checkState(state_, detail::renderer_state_init);
			changeState(state_, detail::renderer_state_element);
		}

		void checkStateElement()
		{
			checkState(state_, detail::renderer_state_element, detail::renderer_state_element | detail::renderer_state_root);
		}

		void changeStateBeginRootObject()
		{
			checkState(state_, detail::renderer_state_element);
			changeState(state_, detail::renderer_state_object);
		}

		void changeStateEndRootObject()
		{
			checkState(state_, detail::renderer_state_object, detail::renderer_state_object | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_element | detail::renderer_state_root);
		}

		void changeStateRoot()
		{
			checkState(state_, detail::renderer_state_element);
			changeState(state_, detail::renderer_state_element | detail::renderer_state_root);
		}

		void close(ErrorCode* ec)
		{
			checkState(state_, detail::renderer_state_element, detail::renderer_state_element | detail::renderer_state_root);

			bool hasRootObject = (state_ & detail::renderer_state_root) != 0;

			changeState(state_, detail::renderer_state_closed);

			if (!hasRootObject)
			{
				renderer_.renderMember(empty_object, ec);
				ECLOG_ON_ERROR(return);
			}

			renderer_.close(ec);
			ECLOG_ON_ERROR(return);
		}

	private:
		static void checkState(int& state, int expected)
		{
			if (state != expected) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void checkState(int& state, int expected, int expected2)
		{
			if (state != expected && state != expected2) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void changeState(int& state, int to)
		{
			state = to;
		}

	private:
		detail::Renderer renderer_;

		int state_;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class NonAssignable {
	protected:
		NonAssignable() {}
		~NonAssignable() {}

	private:
		NonAssignable& operator=(const NonAssignable&);
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class ObjectRenderer : private detail::NonAssignable {
	public:
		explicit ObjectRenderer(RendererHandle parent) :
			renderer_(*(detail::Renderer*)parent.p1), parentState_(*(int*)parent.p2),
			state_(detail::renderer_state_init)
		{
			initialize();
		}

		explicit ObjectRenderer(ObjectRenderer& parent) :
			renderer_(parent.renderer_), parentState_(parent.state_),
			state_(detail::renderer_state_init)
		{
			initialize();
		}

		void beginObject(const KeyDesc& key)
		{
			changeStateBeginObject();

			renderer_.beginObject(key, 0);
		}

		void endObject()
		{
			changeStateEndObject();

			renderer_.endObject(0);
		}

		void beginObject(const KeyDesc& key, ErrorCode& ec)
		{
			changeStateBeginObject();

			renderer_.beginObject(key, &ec);
		}

		void endObject(ErrorCode& ec)
		{
			changeStateEndObject();

			renderer_.endObject(&ec);
		}

		void beginArray(const KeyDesc& key)
		{
			changeStateBeginArray();

			renderer_.beginArray(key, 0);
		}

		void endArray()
		{
			changeStateEndArray();

			renderer_.endArray(0);
		}

		void beginArray(const KeyDesc& key, ErrorCode& ec)
		{
			changeStateBeginArray();

			renderer_.beginArray(key, &ec);
		}

		void endArray(ErrorCode& ec)
		{
			changeStateEndArray();

			renderer_.endArray(&ec);
		}

		void renderMember(const KeyDesc& key, const ValueDesc& value)
		{
			checkStateElement();

			renderer_.renderMember(key, value, 0);
		}

		void renderMember(const KeyDesc& key, const ValueDesc& value, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderMember(key, value, &ec);
		}

		void renderEmptyLines(int count)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, 0);
		}

		void renderEmptyLines(int count, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, &ec);
		}

		void renderComment(cstring comment)
		{
			checkStateElement();

			renderer_.renderComment(comment, 0);
		}

		void renderComment(cstring comment, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderComment(comment, &ec);
		}

		int beginInline()
		{
			checkStateElement();

			return renderer_.beginInline();
		}

		int endInline()
		{
			checkStateElement();

			return renderer_.endInline();
		}

		operator RendererHandle()
		{
			return RendererHandle(&renderer_, &state_);
		}

	private:
		void initialize()
		{
			checkState(state_, detail::renderer_state_init);
			checkState(parentState_, detail::renderer_state_object);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_1);
		}

		void checkStateElement()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_1);
		}

		void changeStateBeginObject()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_object);
			changeState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_2);
		}

		void changeStateEndObject()
		{
			checkState(state_, detail::renderer_state_object, detail::renderer_state_object | detail::renderer_state_ref_1);
			checkState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_2);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_1);
		}

		void changeStateBeginArray()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_array);
			changeState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_2);
		}

		void changeStateEndArray()
		{
			checkState(state_, detail::renderer_state_array, detail::renderer_state_array | detail::renderer_state_ref_1);
			checkState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_2);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_object | detail::renderer_state_ref_1);
		}

	private:
		static void checkState(int& state, int expected)
		{
			if (state != expected) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void checkState(int& state, int expected, int expected2)
		{
			if (state != expected && state != expected2) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void changeState(int& state, int to)
		{
			state = to;
		}

	private:
		detail::Renderer& renderer_;

		int& parentState_;

		int state_;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class ArrayRenderer : private detail::NonAssignable {
	public:
		explicit ArrayRenderer(RendererHandle parent) :
			renderer_(*(detail::Renderer*)parent.p1), parentState_(*(int*)parent.p2),
			state_(detail::renderer_state_init)
		{
			initialize();
		}

		explicit ArrayRenderer(ArrayRenderer& parent) :
			renderer_(parent.renderer_), parentState_(parent.state_),
			state_(detail::renderer_state_init)
		{
			initialize();
		}

		void beginObject()
		{
			changeStateBeginObject();

			renderer_.beginObject(0);
		}

		void endObject()
		{
			changeStateEndObject();

			renderer_.endObject(0);
		}

		void beginObject(ErrorCode& ec)
		{
			changeStateBeginObject();

			renderer_.beginObject(&ec);
		}

		void endObject(ErrorCode& ec)
		{
			changeStateEndObject();

			renderer_.endObject(&ec);
		}

		void beginArray()
		{
			changeStateBeginArray();

			renderer_.beginArray(0);
		}

		void endArray()
		{
			changeStateEndArray();

			renderer_.endArray(0);
		}

		void beginArray(ErrorCode& ec)
		{
			changeStateBeginArray();

			renderer_.beginArray(&ec);
		}

		void endArray(ErrorCode& ec)
		{
			changeStateEndArray();

			renderer_.endArray(&ec);
		}

		void renderMember(const ValueDesc& value)
		{
			checkStateElement();

			renderer_.renderMember(value, 0);
		}

		void renderMember(const ValueDesc& value, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderMember(value, &ec);
		}

		void renderEmptyLines(int count)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, 0);
		}

		void renderEmptyLines(int count, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, &ec);
		}

		void renderComment(cstring comment)
		{
			checkStateElement();

			renderer_.renderComment(comment, 0);
		}

		void renderComment(cstring comment, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderComment(comment, &ec);
		}

		int beginInline()
		{
			checkStateElement();

			return renderer_.beginInline();
		}

		int endInline()
		{
			checkStateElement();

			return renderer_.endInline();
		}

		operator RendererHandle()
		{
			return RendererHandle(&renderer_, &state_);
		}

	private:
		void initialize()
		{
			checkState(state_, detail::renderer_state_init);
			checkState(parentState_, detail::renderer_state_array);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
		}

		void checkStateElement()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
		}

		void changeStateBeginObject()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_object);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
		}

		void changeStateEndObject()
		{
			checkState(state_, detail::renderer_state_object, detail::renderer_state_object | detail::renderer_state_ref_1);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
		}

		void changeStateBeginArray()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_array);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
		}

		void changeStateEndArray()
		{
			checkState(state_, detail::renderer_state_array, detail::renderer_state_array | detail::renderer_state_ref_1);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
		}

	private:
		static void checkState(int& state, int expected)
		{
			if (state != expected) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void checkState(int& state, int expected, int expected2)
		{
			if (state != expected && state != expected2) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void changeState(int& state, int to)
		{
			state = to;
		}

	private:
		detail::Renderer& renderer_;

		int& parentState_;

		int state_;
	};

} // eclog
} // vallest

#include <stdlib.h> // malloc

#ifndef ECLOG_DEFAULT_ALLOCATOR
	#define ECLOG_DEFAULT_ALLOCATOR vallest::eclog::Allocator
#endif

namespace vallest {
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
} // vallest

#include <string.h> // memcpy, memmove
#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T, typename Alloc>
	class PODArray {
	public:
		PODArray() : size_(0), capacity_(0), v_(0)
		{
		}

		PODArray(const T* data, size_t size) : size_(0), capacity_(0), v_(0)
		{
			append(data, size);
		}

		PODArray(const PODArray& other) : size_(0), capacity_(0), v_(0)
		{
			assign(other);
		}

		~PODArray()
		{
			reset(0, 0, 0);
		}

		PODArray& operator=(const PODArray& other)
		{
			if (this != &other) {
				assign(other);
			}

			return *this;
		}

		void clear()
		{
			size_ = 0;
		}

		bool empty() const
		{
			return size_ == 0;
		}

		size_t size() const
		{
			return size_;
		}

		size_t maxSize() const
		{
			return maxValue<size_t>() / sizeof(T);
		}

		size_t capacity() const
		{
			return capacity_;
		}

		void reserve(size_t capacity)
		{
			if (capacity > maxSize()) {
				ECLOG_FAULT(LengthError);
			}

			if (capacity > capacity_) {
				reset(makeCopy(capacity), size_, capacity);
			}
		}

		T& operator[](size_t index)
		{
			ECLOG_ASSERT(index < size_);
			return v_[index];
		}

		const T& operator[](size_t index) const
		{
			ECLOG_ASSERT(index < size_);
			return v_[index];
		}

		T& front()
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[0];
		}

		const T& front() const
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[0];
		}

		T& back()
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[size_ - 1];
		}

		const T& back() const
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[size_ - 1];
		}

		T* data()
		{
			return v_;
		}

		const T* data() const
		{
			return v_;
		}

		size_t insert(size_t index, const T& value)
		{
			return insert(index, &value, 1);
		}

		size_t insert(size_t index, const T* ptr, size_t count)
		{
			ECLOG_ASSERT(ptr != 0);

			if (count > maxSize() - size_) {
				ECLOG_FAULT(LengthError);
			}

			if (index >= size_)
			{
				append(ptr, count);
			}
			else if (count <= capacity_ - size_)
			{
				memmove(v_ + index + count, v_ + index, sizeof(T) * (size_ - index));

				memcpy(v_ + index, ptr, sizeof(T) *count);

				size_ += count;
			}
			else
			{
				size_t capacity = growTo(size_ + count);

				T* v = (T*)Alloc::allocate(sizeof(T) * capacity);

				memcpy(v + index, ptr, sizeof(T) * count);

				if (v_)
				{
					memcpy(v, v_, sizeof(T) * index);
					memcpy(v + index + count, v_ + index, sizeof(T) * (size_ - index));
				}

				reset(v, size_ + count, capacity);
			}

			return index;
		}

		void pushBack(const T& value)
		{
			append(&value, 1);
		}

		void popBack()
		{
			ECLOG_ASSERT(size_ > 0);
			size_ -= 1;
		}

		void append(const T* ptr, size_t count)
		{
			ECLOG_ASSERT(ptr != 0);

			if (count > maxSize() - size_) {
				ECLOG_FAULT(LengthError);
			}

			if (count <= capacity_ - size_)
			{
				memcpy(v_ + size_, ptr, sizeof(T) * count);

				size_ += count;
			}
			else
			{
				size_t capacity = growTo(size_ + count);

				T* v = makeCopy(capacity);

				memcpy(v + size_, ptr, sizeof(T) * count);

				reset(v, size_ + count, capacity);
			}
		}

		void remove(size_t index, size_t count = 1)
		{
			if (index < size_)
			{
				if (count > size_ - index) {
					count = size_ - index;
				}

				memmove(v_ + index, v_ + index + count, sizeof(T) * (size_ - index - count));

				size_ -= count;
			}
		}

		void swap(PODArray& other)
		{
			detail::swap(size_, other.size_);
			detail::swap(capacity_, other.capacity_);
			detail::swap(v_, other.v_);
		}

	private:
		void reset(T* v, size_t size, size_t capacity)
		{
			if (v_) {
				Alloc::deallocate(v_);
			}

			size_ = size;
			capacity_ = capacity;
			v_ = v;
		}

		T* makeCopy(size_t size) const
		{
			if (size > maxSize()) {
				ECLOG_FAULT(LengthError);
			}

			T* v = (T*)Alloc::allocate(sizeof(T) * size);

			if (v_) {
				memcpy(v, v_, sizeof(T) * min(size_, size));
			}

			return v;
		}

		size_t growTo(size_t size) const
		{
			size_t capacity = maxSize() - capacity_ / 2 < capacity_ ?
				0 : capacity_ + capacity_ / 2;

			return max(capacity, size);
		}

		void assign(const PODArray& other)
		{
			if (other.size_ == 0)
			{
				clear();
			}
			else if (capacity_ >= other.size_)
			{
				memcpy(v_, other.v_, sizeof(T) * other.size_);

				size_ = other.size_;
			}
			else
			{
				PODArray t(other.v_, other.size_);

				swap(t);
			}
		}

	private:
		size_t size_;
		size_t capacity_;
		T* v_;
	};

	template<typename T, typename Alloc>
	inline void swap(PODArray<T, Alloc>& a, PODArray<T, Alloc>& b)
	{
		a.swap(b);
	}

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Alloc>
	class ByteArray {
	public:
		ByteArray()
		{
		}

		ByteArray(cstring str)
		{
			init(str);
		}

		ByteArray(const ByteArray& other) : v_(other.v_)
		{
		}

		ByteArray& operator=(const ByteArray& other)
		{
			if (this != &other) {
				v_ = other.v_;
			}

			return *this;
		}

		ByteArray& operator=(cstring str)
		{
			ByteArray t(str);

			swap(t);

			return *this;
		}

		void clear()
		{
			v_.clear();
		}

		bool empty() const
		{
			return size() == 0;
		}

		size_t size() const
		{
			return v_.empty() ? 0 : v_.size() - 1;
		}

		size_t maxSize() const
		{
			return v_.maxSize() - 1;
		}

		size_t capacity() const
		{
			return v_.capacity() - 1;
		}

		void reserve(size_t capacity)
		{
			v_.reserve(capacity + 1);
		}

		char& operator[](size_t pos)
		{
			ECLOG_ASSERT(pos < size());
			return v_[pos];
		}

		const char& operator[](size_t pos) const
		{
			ECLOG_ASSERT(pos < size());
			return v_[pos];
		}

		char* data()
		{
			return v_.data();
		}

		const char* data() const
		{
			return v_.data();
		}

		cstring str() const
		{
			return size() ? cstring(data(), size()) : "";
		}

		void insert(size_t pos, char byte)
		{
			if (v_.empty())
			{
				init(cstring(&byte, 1));
			}
			else
			{
				if (pos > size()) {
					pos = size();
				}

				v_.insert(pos, byte);
			}
		}

		void insert(size_t pos, cstring str)
		{
			if (v_.empty())
			{
				init(str);
			}
			else if (str)
			{
				if (pos > size()) {
					pos = size();
				}

				v_.insert(pos, str.data(), str.size());
			}
		}

		void append(char byte)
		{
			insert(size(), byte);
		}

		void append(cstring str)
		{
			insert(size(), str);
		}

		void remove(size_t pos, size_t count = -1)
		{
			if (pos >= size()) {
				return;
			}

			if (count > size() - pos) {
				count = size() - pos;
			}

			v_.remove(pos, count);
		}

		void swap(ByteArray& other)
		{
			v_.swap(other.v_);
		}

	private:
		void init(cstring str)
		{
			if (str)
			{
				v_.reserve(str.size() + 1);
				v_.append(str.data(), str.size());
				v_.append("", 1);
			}
		}

	private:
		PODArray<char, Alloc> v_;
	};

	template<typename Alloc>
	inline void swap(ByteArray<Alloc>& a, ByteArray<Alloc>& b)
	{
		a.swap(b);
	}

} // detail
} // eclog
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T>
	inline T* construct(void* ptr)
	{
		return new(ptr) T();
	}

	template<typename T, typename A1>
	inline T* construct(void* ptr, const A1& arg1)
	{
		return new(ptr) T(arg1);
	}

	template<typename T, typename A1, typename A2>
	inline T* construct(void* ptr, const A1& arg1, const A2& arg2)
	{
		return new(ptr) T(arg1, arg2);
	}

	template<typename T, typename A1, typename A2, typename A3>
	inline T* construct(void* ptr, const A1& arg1, const A2& arg2, const A3& arg3)
	{
		return new(ptr) T(arg1, arg2, arg3);
	}

	template<typename T>
	inline void destruct(T* ptr)
	{
		(void)ptr;

		ECLOG_WARNING_PUSH
		ECLOG_WARNING_IGNORE_DELETE_NON_VIRTUAL_DTOR
		ptr->~T();
		ECLOG_WARNING_POP
	}

	template<typename T>
	inline void destructRange(T* first, T* last)
	{
		for (; first != last; ++first) {
			destruct(first);
		}
	}

	template<typename T, typename InputIterator>
	inline void constructN(void* ptr, size_t n, InputIterator it)
	{
		T* last = (T*)ptr;

		ECLOG_TRY
		{
			for (size_t i = 0; i < n; ++i)
			{
				construct<T>(last, *it);
				++last;
				++it;
			}
		}
		ECLOG_CATCH_ALL
		{
			destructRange((T*)ptr, last);
			ECLOG_RETHROW;
		}
	}

	template<typename T, typename Alloc>
	inline T* create()
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr);
		}
		ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
			ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc, typename A1>
	inline T* create(const A1& arg1)
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr, arg1);
		}
		ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
			ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc, typename A1, typename A2>
	inline T* create(const A1& arg1, const A2& arg2)
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr, arg1, arg2);
		}
			ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
		ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc, typename A1, typename A2, typename A3>
	inline T* create(const A1& arg1, const A2& arg2, const A3& arg3)
	{
		T* ptr = (T*)Alloc::allocate(sizeof(T));

		ECLOG_TRY
		{
			construct<T>(ptr, arg1, arg2, arg3);
		}
			ECLOG_CATCH_ALL
		{
			Alloc::deallocate(ptr);
		ECLOG_RETHROW;
		}

		return ptr;
	}

	template<typename T, typename Alloc>
	inline void destroy(T* ptr)
	{
		destruct<T>(ptr);
		Alloc::deallocate(ptr);
	}

	template<typename T, typename Alloc>
	class UniquePtr : private NonCopyable {
	public:
		explicit UniquePtr(T* ptr) : ptr_(ptr)
		{
		}

		~UniquePtr()
		{
			if (ptr_) {
				destroy<T, Alloc>(ptr_);
			}
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}

		T* get() const
		{
			return ptr_;
		}

		void reset(T* ptr = 0)
		{
			if (ptr_) {
				destroy<T, Alloc>(ptr_);
			}

			ptr_ = ptr;
		}

		T* release()
		{
			T* ptr = ptr_;
			ptr_ = 0;
			return ptr;
		}

	private:
		T* ptr_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	template<typename Alloc>
	class BasicDynamicParsingBuffer : public ParsingBuffer, private detail::NonCopyable {
	private:
		ECLOG_WARNING_PUSH
		ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
		class BytesBuffer : public OutputStream {
		public:
			BytesBuffer() : encoder_(*this)
			{
			}

		public:
			virtual bool state() const ECLOG_OVERRIDE
			{
				return true;
			}

			virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
			{
				bytes_.append(cstring(buffer, size));
			}

		public:
			size_t size() const
			{
				return bytes_.size();
			}

			char* data()
			{
				return bytes_.data();
			}

			cstring str() const
			{
				return bytes_.str();
			}

			void putChar(int ch)
			{
				encoder_.putChar(ch);
			}

			void shrink(size_t size)
			{
				bytes_.remove(size);
			}

		private:
			UTF8Encoder encoder_;

			detail::ByteArray<Alloc> bytes_;
		};
		ECLOG_WARNING_POP

	public:
		BasicDynamicParsingBuffer() : bytesBuffer_(0)
		{
		}

	public:
		virtual void* claim() ECLOG_OVERRIDE
		{
			bytesBuffer_ = detail::create<BytesBuffer, Alloc>();

			return bytesBuffer_;
		}

		virtual void discard(void* ptr) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ == 0 || ptr == bytesBuffer_);
			detail::destroy<BytesBuffer, Alloc>((BytesBuffer*)ptr);

			bytesBuffer_ = 0;
		}

		virtual size_t length() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			return bytesBuffer_->size();
		}

		virtual char* address() ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			return bytesBuffer_->data();
		}

		virtual cstring str() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			return bytesBuffer_->str();
		}

		virtual void putChar(int ch) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			bytesBuffer_->putChar(ch);
		}

		virtual void shrink(size_t length) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_ != 0);
			bytesBuffer_->shrink(length);
		}

	private:
		BytesBuffer* bytesBuffer_;
	};

	typedef BasicDynamicParsingBuffer<ECLOG_DEFAULT_ALLOCATOR> DynamicParsingBuffer;

} // eclog
} // vallest

#include <string.h> // memcpy

namespace vallest {
namespace eclog {

	class InplaceParsingBuffer : public ParsingBuffer, private detail::NonCopyable {
	private:
		ECLOG_WARNING_PUSH
		ECLOG_WARNING_IGNORE_USE_THIS_IN_INITIALIZER_LIST
		class BytesBuffer : public OutputStream {
		public:
			BytesBuffer() : encoder_(*this), buffer_(0), maxSize_(0), size_(0)
			{
			}

		public:
			virtual bool state() const ECLOG_OVERRIDE
			{
				return true;
			}

			virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
			{
				ECLOG_ASSERT(buffer_ && size_ > 0);

				if (size > maxSize_ - size_) {
					ECLOG_FAULT(BufferOverflow);
				}

				memcpy(buffer_ + size_ - 1, buffer, size);

				buffer_[size_ - 1 + size] = 0;

				size_ += size;
			}

		public:
			void reset(char* buffer, size_t maxSize)
			{
				if (buffer)
				{
					if (maxSize < 1) {
						ECLOG_FAULT(BufferOverflow);
					}

					buffer_ = buffer;
					maxSize_ = maxSize;
					size_ = 1;

					buffer_[0] = 0;
				}
				else
				{
					buffer_ = 0;
					maxSize_ = 0;
					size_ = 0;
				}
			}

			size_t size() const
			{
				return size_;
			}

			char* data()
			{
				return buffer_;
			}

			const char* data() const
			{
				return buffer_;
			}

			cstring str() const
			{
				return buffer_ ? cstring(buffer_, size_ - 1) : "";
			}

			void putChar(int ch)
			{
				encoder_.putChar(ch);
			}

			void shrink(size_t size)
			{
				ECLOG_ASSERT(size_ >= 1 && size <= size_ - 1);
				size_ = size + 1;

				buffer_[size] = 0;
			}

		private:
			UTF8Encoder encoder_;

			char* buffer_;
			size_t maxSize_;
			size_t size_;
		};
		ECLOG_WARNING_POP

	public:
		explicit InplaceParsingBuffer(void* buffer, size_t maxSize) :
			buffer_((char*)buffer), maxSize_(maxSize), size_(0)
		{
			ECLOG_ASSERT(buffer && maxSize > 0);
		}
	
	public:
		virtual void* claim() ECLOG_OVERRIDE
		{
			if (bytesBuffer_.data())
			{
				ECLOG_ASSERT(bytesBuffer_.size() > 0);
				size_ += bytesBuffer_.size();
			}

			bytesBuffer_.reset(buffer_ + size_, maxSize_ - size_);

			return buffer_ + size_;
		}

		virtual void discard(void* ptr) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data() == 0 || ptr == bytesBuffer_.data());
			ECLOG_ASSERT(ptr >= buffer_ && ptr < buffer_ + maxSize_);
			size_ = (char*)ptr - buffer_;

			bytesBuffer_.reset(0, 0);
		}

		virtual size_t length() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			return bytesBuffer_.str().size();
		}

		virtual char* address() ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			return bytesBuffer_.data();
		}

		virtual cstring str() const ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			return bytesBuffer_.str();
		}

		virtual void putChar(int ch) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			bytesBuffer_.putChar(ch);
		}

		virtual void shrink(size_t length) ECLOG_OVERRIDE
		{
			ECLOG_ASSERT(bytesBuffer_.data());
			bytesBuffer_.shrink(length);
		}

	private:
		char* buffer_;
		size_t maxSize_;
		size_t size_;

		BytesBuffer bytesBuffer_;
	};

} // eclog
} // vallest

#include <istream>

namespace vallest {
namespace eclog {

	class StdStreamInputStream : public InputStream, private detail::NonCopyable {
	public:
		explicit StdStreamInputStream(std::istream& stream) :
			stream_(stream)
		{
		}

	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return !stream_.fail();
		}

		virtual bool eof() const ECLOG_OVERRIDE
		{
			return stream_.eof();
		}

		virtual size_t read(char* buffer, size_t size) ECLOG_OVERRIDE
		{
			stream_.read(buffer, size);

			return (size_t)stream_.gcount();
		}

	private:
		std::istream& stream_;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	template<typename Alloc>
	class BasicMemoryOutputStream : public OutputStream, private detail::NonCopyable {
	public:
		BasicMemoryOutputStream()
		{
		}

	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return true;
		}

		virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
		{
			bytes_.append(cstring(buffer, size));
		}

	public:
		size_t size() const
		{
			return bytes_.size();
		}

		char* data()
		{
			return bytes_.data();
		}

		const char* data() const
		{
			return bytes_.data();
		}

	private:
		detail::ByteArray<Alloc> bytes_;
	};

	typedef BasicMemoryOutputStream<ECLOG_DEFAULT_ALLOCATOR> MemoryOutputStream;

} // eclog
} // vallest

#include <ostream>

namespace vallest {
namespace eclog {

	class StdStreamOutputStream : public OutputStream, private detail::NonCopyable {
	public:
		explicit StdStreamOutputStream(std::ostream& stream) :
			stream_(stream)
		{
		}

		virtual bool state() const ECLOG_OVERRIDE
		{
			return stream_ ? true : false;
		}

		virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
		{
			stream_.write(buffer, size);
		}

	private:
		std::ostream& stream_;
	};

} // eclog
} // vallest

#include <string>

namespace vallest {
namespace eclog {

	class StdStringOutputStream : public OutputStream, private detail::NonCopyable {
	public:
		virtual bool state() const ECLOG_OVERRIDE
		{
			return true;
		}

		virtual void write(const char* buffer, size_t size) ECLOG_OVERRIDE
		{
			str_.append(buffer, size);
		}

	public:
		std::string& str()
		{
			return str_;
		}

		const std::string& str() const
		{
			return str_;
		}

	private:
		std::string str_;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	enum NodeType {
		node_type_key,
		node_type_null,
		node_type_boolean,
		node_type_string,
		node_type_number,
		node_type_object,
		node_type_array,
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class Node {
	protected:
		~Node() {} // prevents calling delete

	public:
		virtual NodeType nodeType() const = 0;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class KeyNode : public Node {
	protected:
		~KeyNode() {} // prevents calling delete

	public:
		virtual cstring str() const = 0;

		virtual void setNotation(StringNotation notation) = 0;
		virtual StringNotation notation() const = 0;

		virtual void setDelimiter(cstring delimiter) = 0;
		virtual void setDelimiter(cstring delimiter, ErrorCode& ec) = 0;
		virtual cstring delimiter() const = 0;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class NullNode;
	class BooleanNode;
	class StringNode;
	class NumberNode;
	class ObjectNode;
	class ArrayNode;

	class ValueNode : public Node {
	protected:
		~ValueNode() {} // prevents calling delete

	public:
		bool isNull() const
		{
			return (nodeType() == node_type_null);
		}

		bool isBoolean() const
		{
			return (nodeType() == node_type_boolean);
		}

		bool isString() const
		{
			return (nodeType() == node_type_string);
		}

		bool isNumber() const
		{
			return (nodeType() == node_type_number);
		}

		bool isObject() const
		{
			return (nodeType() == node_type_object);
		}

		bool isArray() const
		{
			return (nodeType() == node_type_array);
		}

		NullNode& asNull()
		{
			if (!isNull()) {
				ECLOG_FAULT(BadCast);
			}

			return *(NullNode*)this;
		}

		BooleanNode& asBoolean()
		{
			if (!isBoolean()) {
				ECLOG_FAULT(BadCast);
			}

			return *(BooleanNode*)this;
		}

		StringNode& asString()
		{
			if (!isString()) {
				ECLOG_FAULT(BadCast);
			}

			return *(StringNode*)this;
		}

		NumberNode& asNumber()
		{
			if (!isNumber()) {
				ECLOG_FAULT(BadCast);
			}

			return *(NumberNode*)this;
		}

		ObjectNode& asObject()
		{
			if (!isObject()) {
				ECLOG_FAULT(BadCast);
			}

			return *(ObjectNode*)this;
		}

		ArrayNode& asArray()
		{
			if (!isArray()) {
				ECLOG_FAULT(BadCast);
			}

			return *(ArrayNode*)this;
		}

		const NullNode& asNull() const
		{
			if (!isNull()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const NullNode*)this;
		}

		const BooleanNode& asBoolean() const
		{
			if (!isBoolean()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const BooleanNode*)this;
		}

		const StringNode& asString() const
		{
			if (!isString()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const StringNode*)this;
		}

		const NumberNode& asNumber() const
		{
			if (!isNumber()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const NumberNode*)this;
		}

		const ObjectNode& asObject() const
		{
			if (!isObject()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const ObjectNode*)this;
		}

		const ArrayNode& asArray() const
		{
			if (!isArray()) {
				ECLOG_FAULT(BadCast);
			}

			return *(const ArrayNode*)this;
		}
	};

} // eclog
} // vallest

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

#include <stddef.h> // ptrdiff_t, size_t
#include <istream>
#include <ostream>
#include <string>

namespace vallest {
namespace eclog {

	class ObjectNode : public ValueNode {
	protected:
		~ObjectNode() {} // prevents calling delete

	public:
		class Iterator;
		class ConstIterator;

		class Element {
		private:
			friend class Iterator;
			friend class ConstIterator;

		protected:
			~Element() {} // prevents calling delete

		public:
			virtual KeyNode& key() = 0;
			virtual const KeyNode& key() const = 0;

			virtual ValueNode& value() = 0;
			virtual const ValueNode& value() const = 0;

			virtual void updateValue(const ValueNode& value) = 0;
			virtual void updateValue(const ValueDesc& desc) = 0;

		protected:
			virtual Element* prev() = 0;
			virtual const Element* prev() const = 0;

			virtual Element* next() = 0;
			virtual const Element* next() const = 0;
		};

		class Iterator {
		public:
			Iterator();
			Iterator(Element* p);
			Iterator(const Iterator& other);

			Iterator& operator=(const Iterator& other);

			Iterator& operator++();
			Iterator operator++(int);
			Iterator& operator--();
			Iterator operator--(int);

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;

			Element* get() const;
			Element* operator->();
			Element& operator*();

		private:
			Element* p_;
		};

		class ConstIterator {
		public:
			ConstIterator();
			ConstIterator(const Element* p);
			ConstIterator(Iterator it);
			ConstIterator(const ConstIterator& other);

			ConstIterator& operator=(const ConstIterator& other);

			ConstIterator& operator++();
			ConstIterator operator++(int);
			ConstIterator& operator--();
			ConstIterator operator--(int);

			bool operator==(const ConstIterator& other) const;
			bool operator!=(const ConstIterator& other) const;

			const Element* get() const;
			const Element* operator->();
			const Element& operator*();

		private:
			const Element* p_;
		};

	public:
		virtual void clear() = 0;

		virtual bool empty() const = 0;
		virtual size_t size() const = 0;

		virtual Iterator begin() = 0;
		virtual Iterator end() = 0;

		virtual ConstIterator begin() const = 0;
		virtual ConstIterator end() const = 0;

		Element& first();
		Element& last();

		const Element& first() const;
		const Element& last() const;

		virtual bool contains(cstring key) const = 0;

		virtual Iterator find(cstring key) = 0;
		virtual ConstIterator find(cstring key) const = 0;

		Iterator findNull(cstring key);
		Iterator findBoolean(cstring key);
		Iterator findString(cstring key);
		Iterator findNumber(cstring key);
		Iterator findObject(cstring key);
		Iterator findArray(cstring key);

		ConstIterator findNull(cstring key) const;
		ConstIterator findBoolean(cstring key) const;
		ConstIterator findString(cstring key) const;
		ConstIterator findNumber(cstring key) const;
		ConstIterator findObject(cstring key) const;
		ConstIterator findArray(cstring key) const;

		Element& get(cstring key);
		ValueNode& getValue(cstring key);
		NullNode& getNull(cstring key);
		BooleanNode& getBoolean(cstring key);
		StringNode& getString(cstring key);
		NumberNode& getNumber(cstring key);
		ObjectNode& getObject(cstring key);
		ArrayNode& getArray(cstring key);

		const Element& get(cstring key) const;
		const ValueNode& getValue(cstring key) const;
		const NullNode& getNull(cstring key) const;
		const BooleanNode& getBoolean(cstring key) const;
		const StringNode& getString(cstring key) const;
		const NumberNode& getNumber(cstring key) const;
		const ObjectNode& getObject(cstring key) const;
		const ArrayNode& getArray(cstring key) const;

		ValueNode& getOrAddValue(const KeyDesc& key, const ValueDesc& defaultValue = null);
		NullNode& getOrAddNull(const KeyDesc& key, const Null& defaultValue = null);
		BooleanNode& getOrAddBoolean(const KeyDesc& key, bool defaultValue = false);
		StringNode& getOrAddString(const KeyDesc& key, const StringDesc& defaultValue = cstring());
		NumberNode& getOrAddNumber(const KeyDesc& key, const NumberDesc& defaultValue = 0);
		ObjectNode& getOrAddObject(const KeyDesc& key, const ObjectDesc& defaultValue = empty_object);
		ArrayNode& getOrAddArray(const KeyDesc& key, const ArrayDesc& defaultValue = empty_array);

		bool append(const Element& element);
		bool append(const KeyNode& key, const ValueNode& value);
		bool append(const KeyDesc& key, const ValueNode& value);
		bool append(const KeyNode& key, const ValueDesc& value);
		bool append(const KeyDesc& key, const ValueDesc& value);

		virtual Pair<Iterator, bool> insert(Iterator pos, const Element& element) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueNode& value) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueNode& value) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueDesc& value) = 0;
		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueDesc& value) = 0;

		void appendForce(const Element& element);
		void appendForce(const KeyNode& key, const ValueNode& value);
		void appendForce(const KeyDesc& key, const ValueNode& value);
		void appendForce(const KeyNode& key, const ValueDesc& value);
		void appendForce(const KeyDesc& key, const ValueDesc& value);

		virtual Iterator insertForce(Iterator pos, const Element& element) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueNode& value) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueNode& value) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueDesc& value) = 0;
		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueDesc& value) = 0;

		virtual void merge(const ObjectDesc& patch) = 0;
		virtual void merge(const ObjectNode& patch) = 0;

		virtual void remove(Iterator pos) = 0;
		virtual size_t remove(Iterator first, Iterator last) = 0;
		virtual bool remove(cstring key) = 0;

		virtual void parse(Context& ctx) = 0;
		virtual void parse(Context& ctx, ErrorCode& ec) = 0;
		virtual void parse(InputStream& stream) = 0;
		virtual void parse(InputStream& stream, ErrorCode& ec) = 0;
		virtual void parse(cstring str) = 0;
		virtual void parse(cstring str, ErrorCode& ec) = 0;
		virtual void parse(std::istream& stream) = 0;
		virtual void parse(std::istream& stream, ErrorCode& ec) = 0;
		virtual void parse(const std::string& str) = 0;
		virtual void parse(const std::string& str, ErrorCode& ec) = 0;
		virtual void parse(const char* str) = 0;
		virtual void parse(const char* str, ErrorCode& ec) = 0;

		virtual void render(OutputStream& stream) const = 0;
		virtual void render(OutputStream& stream, ErrorCode& ec) const = 0;
		virtual void render(OutputStream& stream, const RendererConfig& rc) const = 0;
		virtual void render(OutputStream& stream, const RendererConfig& rc, ErrorCode& ec) const = 0;
		virtual void render(std::ostream& stream) const = 0;
		virtual void render(std::ostream& stream, ErrorCode& ec) const = 0;
		virtual void render(std::ostream& stream, const RendererConfig& rc) const = 0;
		virtual void render(std::ostream& stream, const RendererConfig& rc, ErrorCode& ec) const = 0;

		std::string toStdString() const;
		std::string toStdString(ErrorCode& ec) const;
		std::string toStdString(const RendererConfig& rc) const;
		std::string toStdString(const RendererConfig& rc, ErrorCode& ec) const;

		virtual void assign(const ObjectDesc& desc) = 0;
		virtual void assign(const ObjectNode& other) = 0;
	};

	inline ObjectNode::Iterator::Iterator() : p_(0)
	{
	}

	inline ObjectNode::Iterator::Iterator(Element* p) : p_(p)
	{
	}

	inline ObjectNode::Iterator::Iterator(const Iterator& other) : p_(other.p_)
	{
	}

	inline ObjectNode::Iterator& ObjectNode::Iterator::operator=(const Iterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ObjectNode::Iterator& ObjectNode::Iterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ObjectNode::Iterator ObjectNode::Iterator::operator++(int)
	{
		Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ObjectNode::Iterator& ObjectNode::Iterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ObjectNode::Iterator ObjectNode::Iterator::operator--(int)
	{
		Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ObjectNode::Iterator::operator==(const Iterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ObjectNode::Iterator::operator!=(const Iterator& other) const
	{
		return p_ != other.p_;
	}

	inline ObjectNode::Element* ObjectNode::Iterator::get() const
	{
		return p_;
	}

	inline ObjectNode::Element* ObjectNode::Iterator::operator->()
	{
		return p_;
	}

	inline ObjectNode::Element& ObjectNode::Iterator::operator*()
	{
		return *p_;
	}

	inline ObjectNode::ConstIterator::ConstIterator() : p_(0)
	{
	}

	inline ObjectNode::ConstIterator::ConstIterator(const Element* p) : p_(p)
	{
	}

	inline ObjectNode::ConstIterator::ConstIterator(Iterator it) : p_(it.get())
	{
	}

	inline ObjectNode::ConstIterator::ConstIterator(const ConstIterator& other) : p_(other.p_)
	{
	}

	inline ObjectNode::ConstIterator& ObjectNode::ConstIterator::operator=(const ConstIterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ObjectNode::ConstIterator& ObjectNode::ConstIterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ObjectNode::ConstIterator ObjectNode::ConstIterator::operator++(int)
	{
		const Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ObjectNode::ConstIterator& ObjectNode::ConstIterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ObjectNode::ConstIterator ObjectNode::ConstIterator::operator--(int)
	{
		const Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ObjectNode::ConstIterator::operator==(const ConstIterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ObjectNode::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return p_ != other.p_;
	}

	inline const ObjectNode::Element* ObjectNode::ConstIterator::get() const
	{
		return p_;
	}

	inline const ObjectNode::Element* ObjectNode::ConstIterator::operator->()
	{
		return p_;
	}

	inline const ObjectNode::Element& ObjectNode::ConstIterator::operator*()
	{
		return *p_;
	}

	inline ObjectNode::Element& ObjectNode::first()
	{
		return *begin();
	}

	inline ObjectNode::Element& ObjectNode::last()
	{
		return *--end();
	}

	inline const ObjectNode::Element& ObjectNode::first() const
	{
		return *begin();
	}

	inline const ObjectNode::Element& ObjectNode::last() const
	{
		return *--end();
	}

	inline ObjectNode::Iterator ObjectNode::findNull(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isNull()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findBoolean(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isBoolean()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findString(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isString()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findNumber(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isNumber()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findObject(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isObject()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Iterator ObjectNode::findArray(cstring key)
	{
		Iterator it = find(key);

		if (it != end() && it->value().isArray()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findNull(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isNull()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findBoolean(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isBoolean()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findString(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isString()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findNumber(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isNumber()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findObject(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isObject()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::ConstIterator ObjectNode::findArray(cstring key) const
	{
		ConstIterator it = find(key);

		if (it != end() && it->value().isArray()) {
			return it;
		}
		else {
			return end();
		}
	}

	inline ObjectNode::Element& ObjectNode::get(cstring key)
	{
		Iterator it = find(key);

		if (it == end()) {
			ECLOG_FAULT(OutOfRange);
		}

		return *it;
	}

	inline ValueNode& ObjectNode::getValue(cstring key)
	{
		return get(key).value();
	}

	inline NullNode& ObjectNode::getNull(cstring key)
	{
		return getValue(key).asNull();
	}

	inline BooleanNode& ObjectNode::getBoolean(cstring key)
	{
		return getValue(key).asBoolean();
	}

	inline StringNode& ObjectNode::getString(cstring key)
	{
		return getValue(key).asString();
	}

	inline NumberNode& ObjectNode::getNumber(cstring key)
	{
		return getValue(key).asNumber();
	}

	inline ObjectNode& ObjectNode::getObject(cstring key)
	{
		return getValue(key).asObject();
	}

	inline ArrayNode& ObjectNode::getArray(cstring key)
	{
		return getValue(key).asArray();
	}

	inline const ObjectNode::Element& ObjectNode::get(cstring key) const
	{
		ConstIterator it = find(key);

		if (it == end()) {
			ECLOG_FAULT(OutOfRange);
		}

		return *it;
	}

	inline const ValueNode& ObjectNode::getValue(cstring key) const
	{
		return get(key).value();
	}

	inline const NullNode& ObjectNode::getNull(cstring key) const
	{
		return getValue(key).asNull();
	}

	inline const BooleanNode& ObjectNode::getBoolean(cstring key) const
	{
		return getValue(key).asBoolean();
	}

	inline const StringNode& ObjectNode::getString(cstring key) const
	{
		return getValue(key).asString();
	}

	inline const NumberNode& ObjectNode::getNumber(cstring key) const
	{
		return getValue(key).asNumber();
	}

	inline const ObjectNode& ObjectNode::getObject(cstring key) const
	{
		return getValue(key).asObject();
	}

	inline const ArrayNode& ObjectNode::getArray(cstring key) const
	{
		return getValue(key).asArray();
	}

	inline ValueNode& ObjectNode::getOrAddValue(const KeyDesc& key, const ValueDesc& defaultValue)
	{
		Iterator it = find(key.str());

		if (it != end()) {
			return it->value();
		}

		append(key, defaultValue);

		return last().value();
	}

	inline NullNode& ObjectNode::getOrAddNull(const KeyDesc& key, const Null& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asNull();
	}

	inline BooleanNode& ObjectNode::getOrAddBoolean(const KeyDesc& key, bool defaultValue)
	{
		return getOrAddValue(key, defaultValue).asBoolean();
	}

	inline StringNode& ObjectNode::getOrAddString(const KeyDesc& key, const StringDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asString();
	}

	inline NumberNode& ObjectNode::getOrAddNumber(const KeyDesc& key, const NumberDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asNumber();
	}

	inline ObjectNode& ObjectNode::getOrAddObject(const KeyDesc& key, const ObjectDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asObject();
	}

	inline ArrayNode& ObjectNode::getOrAddArray(const KeyDesc& key, const ArrayDesc& defaultValue)
	{
		return getOrAddValue(key, defaultValue).asArray();
	}

	inline bool ObjectNode::append(const ObjectNode::Element& element)
	{
		return insert(end(), element).second;
	}

	inline bool ObjectNode::append(const KeyNode& key, const ValueNode& value)
	{
		return insert(end(), key, value).second;
	}

	inline bool ObjectNode::append(const KeyDesc& key, const ValueNode& value)
	{
		return insert(end(), key, value).second;
	}

	inline bool ObjectNode::append(const KeyNode& key, const ValueDesc& value)
	{
		return insert(end(), key, value).second;
	}

	inline bool ObjectNode::append(const KeyDesc& key, const ValueDesc& value)
	{
		return insert(end(), key, value).second;
	}

	inline void ObjectNode::appendForce(const ObjectNode::Element& element)
	{
		insertForce(end(), element);
	}

	inline void ObjectNode::appendForce(const KeyNode& key, const ValueNode& value)
	{
		insertForce(end(), key, value);
	}

	inline void ObjectNode::appendForce(const KeyDesc& key, const ValueNode& value)
	{
		insertForce(end(), key, value);
	}

	inline void ObjectNode::appendForce(const KeyNode& key, const ValueDesc& value)
	{
		insertForce(end(), key, value);
	}

	inline void ObjectNode::appendForce(const KeyDesc& key, const ValueDesc& value)
	{
		insertForce(end(), key, value);
	}

	inline std::string ObjectNode::toStdString() const
	{
		StdStringOutputStream stream;

		render(stream);

		std::string str;

		str.swap(stream.str());

		return str;
	}

	inline std::string ObjectNode::toStdString(ErrorCode& ec) const
	{
		StdStringOutputStream stream;

		render(stream, ec);

		std::string str;

		str.swap(stream.str());

		return str;
	}

	inline std::string ObjectNode::toStdString(const RendererConfig& rc) const
	{
		StdStringOutputStream stream;

		render(stream, rc);

		std::string str;

		str.swap(stream.str());

		return str;
	}

	inline std::string ObjectNode::toStdString(const RendererConfig& rc, ErrorCode& ec) const
	{
		StdStringOutputStream stream;

		render(stream, rc, ec);

		std::string str;

		str.swap(stream.str());

		return str;
	}

} // eclog
} // vallest

#include <stddef.h> // ptrdiff_t

namespace vallest {
namespace eclog {

	class ArrayNode : public ValueNode {
	protected:
		~ArrayNode() {} // prevents calling delete

	public:
		class Iterator;
		class ConstIterator;

		class Element {
		private:
			friend class Iterator;
			friend class ConstIterator;

		protected:
			~Element() {} // prevents calling delete

		public:
			virtual ValueNode& value() = 0;
			virtual const ValueNode& value() const = 0;

			virtual void updateValue(const ValueNode& value) = 0;
			virtual void updateValue(const ValueDesc& desc) = 0;

		protected:
			virtual Element* prev(ptrdiff_t n = 1) = 0;
			virtual const Element* prev(ptrdiff_t n = 1) const = 0;

			virtual Element* next(ptrdiff_t n = 1) = 0;
			virtual const Element* next(ptrdiff_t n = 1) const = 0;

			virtual ptrdiff_t distance(const Element* other) const = 0;
		};

		class Iterator {
		public:
			Iterator();
			Iterator(Element* p);
			Iterator(const Iterator& other);

			Iterator& operator=(const Iterator& other);

			Iterator& operator+=(ptrdiff_t n);
			Iterator& operator-=(ptrdiff_t n);

			Iterator& operator++();
			Iterator operator++(int);
			Iterator& operator--();
			Iterator operator--(int);

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;
			bool operator<(const Iterator& other) const;
			bool operator>(const Iterator& other) const;
			bool operator<=(const Iterator& other) const;
			bool operator>=(const Iterator& other) const;

			Iterator operator+(ptrdiff_t n) const;
			Iterator operator-(ptrdiff_t n) const;
			ptrdiff_t operator-(const Iterator& other) const;

			Element* get() const;
			Element* operator->();
			Element& operator*();

		private:
			Element* p_;
		};

		class ConstIterator {
		public:
			ConstIterator();
			ConstIterator(const Element* p);
			ConstIterator(Iterator it);
			ConstIterator(const ConstIterator& other);

			ConstIterator& operator=(const ConstIterator& other);

			ConstIterator& operator+=(ptrdiff_t n);
			ConstIterator& operator-=(ptrdiff_t n);

			ConstIterator& operator++();
			ConstIterator operator++(int);
			ConstIterator& operator--();
			ConstIterator operator--(int);

			bool operator==(const ConstIterator& other) const;
			bool operator!=(const ConstIterator& other) const;
			bool operator<(const ConstIterator& other) const;
			bool operator>(const ConstIterator& other) const;
			bool operator<=(const ConstIterator& other) const;
			bool operator>=(const ConstIterator& other) const;

			ConstIterator operator+(ptrdiff_t n) const;
			ConstIterator operator-(ptrdiff_t n) const;
			ptrdiff_t operator-(const ConstIterator& other) const;

			const Element* get() const;
			const Element* operator->();
			const Element& operator*();

		private:
			const Element* p_;
		};

	public:
		virtual void clear() = 0;

		virtual bool empty() const = 0;
		virtual size_t size() const = 0;

		virtual Iterator begin() = 0;
		virtual Iterator end() = 0;

		virtual ConstIterator begin() const = 0;
		virtual ConstIterator end() const = 0;

		Element& first();
		Element& last();

		const Element& first() const;
		const Element& last() const;

		virtual size_t indexOf(const Element& element) const = 0;

		virtual Element& at(size_t index) = 0;
		virtual const Element& at(size_t index) const = 0;

		ValueNode& getValue(size_t index);
		NullNode& getNull(size_t index);
		BooleanNode& getBoolean(size_t index);
		StringNode& getString(size_t index);
		NumberNode& getNumber(size_t index);
		ObjectNode& getObject(size_t index);
		ArrayNode& getArray(size_t index);

		const ValueNode& getValue(size_t index) const;
		const NullNode& getNull(size_t index) const;
		const BooleanNode& getBoolean(size_t index) const;
		const StringNode& getString(size_t index) const;
		const NumberNode& getNumber(size_t index) const;
		const ObjectNode& getObject(size_t index) const;
		const ArrayNode& getArray(size_t index) const;

		void append(const Element& element);
		void append(const ValueNode& value);
		void append(const ValueDesc& value);

		virtual Iterator insert(Iterator pos, const Element& element) = 0;
		virtual Iterator insert(Iterator pos, const ValueNode& value) = 0;
		virtual Iterator insert(Iterator pos, const ValueDesc& value) = 0;

		virtual void remove(Iterator pos) = 0;
		virtual void remove(Iterator first, Iterator last) = 0;
		virtual void remove(size_t index) = 0;
		virtual void remove(size_t index, size_t count) = 0;

		virtual void assign(const ArrayDesc& desc) = 0;
		virtual void assign(const ArrayNode& other) = 0;
	};

	inline ArrayNode::Iterator::Iterator() : p_(0)
	{
	}

	inline ArrayNode::Iterator::Iterator(Element* p) : p_(p)
	{
	}

	inline ArrayNode::Iterator::Iterator(const Iterator& other) : p_(other.p_)
	{
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator=(const Iterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator+=(ptrdiff_t n)
	{
		p_ = p_->next(n);

		return *this;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator-=(ptrdiff_t n)
	{
		p_ = p_->prev(n);

		return *this;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator++(int)
	{
		Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ArrayNode::Iterator& ArrayNode::Iterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator--(int)
	{
		Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ArrayNode::Iterator::operator==(const Iterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ArrayNode::Iterator::operator!=(const Iterator& other) const
	{
		return !(*this == other);
	}

	inline bool ArrayNode::Iterator::operator<(const Iterator& other) const
	{
		return p_->distance(other.p_) > 0;
	}

	inline bool ArrayNode::Iterator::operator>(const Iterator& other) const
	{
		return other < *this;
	}

	inline bool ArrayNode::Iterator::operator<=(const Iterator& other) const
	{
		return !(*this > other);
	}

	inline bool ArrayNode::Iterator::operator>=(const Iterator& other) const
	{
		return !(*this < other);
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator+(ptrdiff_t n) const
	{
		return p_->next(n);
	}

	inline ArrayNode::Iterator ArrayNode::Iterator::operator-(ptrdiff_t n) const
	{
		return p_->prev(n);
	}

	inline ptrdiff_t ArrayNode::Iterator::operator-(const Iterator& other) const
	{
		return other.p_->distance(p_);
	}

	inline ArrayNode::Element* ArrayNode::Iterator::get() const
	{
		return p_;
	}

	inline ArrayNode::Element* ArrayNode::Iterator::operator->()
	{
		return p_;
	}

	inline ArrayNode::Element& ArrayNode::Iterator::operator*()
	{
		return *p_;
	}

	inline ArrayNode::Iterator operator+(ptrdiff_t n, ArrayNode::Iterator it)
	{
		return it + n;
	}

	inline ArrayNode::ConstIterator::ConstIterator() : p_(0)
	{
	}

	inline ArrayNode::ConstIterator::ConstIterator(const ArrayNode::Element* p) : p_(p)
	{
	}

	inline ArrayNode::ConstIterator::ConstIterator(Iterator it) : p_(it.get())
	{
	}

	inline ArrayNode::ConstIterator::ConstIterator(const ConstIterator& other) : p_(other.p_)
	{
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator=(const ConstIterator& other)
	{
		p_ = other.p_;

		return *this;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator+=(ptrdiff_t n)
	{
		p_ = p_->next(n);

		return *this;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator-=(ptrdiff_t n)
	{
		p_ = p_->prev(n);

		return *this;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator++()
	{
		p_ = p_->next();

		return *this;
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator++(int)
	{
		const ArrayNode::Element* p = p_;

		p_ = p_->next();

		return p;
	}

	inline ArrayNode::ConstIterator& ArrayNode::ConstIterator::operator--()
	{
		p_ = p_->prev();

		return *this;
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator--(int)
	{
		const ArrayNode::Element* p = p_;

		p_ = p_->prev();

		return p;
	}

	inline bool ArrayNode::ConstIterator::operator==(const ConstIterator& other) const
	{
		return p_ == other.p_;
	}

	inline bool ArrayNode::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !(*this == other);
	}

	inline bool ArrayNode::ConstIterator::operator<(const ConstIterator& other) const
	{
		return p_->distance(other.p_) > 0;
	}

	inline bool ArrayNode::ConstIterator::operator>(const ConstIterator& other) const
	{
		return other < *this;
	}

	inline bool ArrayNode::ConstIterator::operator<=(const ConstIterator& other) const
	{
		return !(*this > other);
	}

	inline bool ArrayNode::ConstIterator::operator>=(const ConstIterator& other) const
	{
		return !(*this < other);
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator+(ptrdiff_t n) const
	{
		return p_->next(n);
	}

	inline ArrayNode::ConstIterator ArrayNode::ConstIterator::operator-(ptrdiff_t n) const
	{
		return p_->prev(n);
	}

	inline ptrdiff_t ArrayNode::ConstIterator::operator-(const ConstIterator& other) const
	{
		return other.p_->distance(p_);
	}

	inline const ArrayNode::Element* ArrayNode::ConstIterator::get() const
	{
		return p_;
	}

	inline const ArrayNode::Element* ArrayNode::ConstIterator::operator->()
	{
		return p_;
	}

	inline const ArrayNode::Element& ArrayNode::ConstIterator::operator*()
	{
		return *p_;
	}

	inline ArrayNode::ConstIterator operator+(ptrdiff_t n, ArrayNode::ConstIterator it)
	{
		return it + n;
	}

	inline ArrayNode::Element& ArrayNode::first()
	{
		return *begin();
	}

	inline ArrayNode::Element& ArrayNode::last()
	{
		return *--end();
	}

	inline const ArrayNode::Element& ArrayNode::first() const
	{
		return *begin();
	}

	inline const ArrayNode::Element& ArrayNode::last() const
	{
		return *--end();
	}

	inline ValueNode& ArrayNode::getValue(size_t index)
	{
		return at(index).value();
	}

	inline NullNode& ArrayNode::getNull(size_t index)
	{
		return getValue(index).asNull();
	}

	inline BooleanNode& ArrayNode::getBoolean(size_t index)
	{
		return getValue(index).asBoolean();
	}

	inline StringNode& ArrayNode::getString(size_t index)
	{
		return getValue(index).asString();
	}

	inline NumberNode& ArrayNode::getNumber(size_t index)
	{
		return getValue(index).asNumber();
	}

	inline ObjectNode& ArrayNode::getObject(size_t index)
	{
		return getValue(index).asObject();
	}

	inline ArrayNode& ArrayNode::getArray(size_t index)
	{
		return getValue(index).asArray();
	}

	inline const ValueNode& ArrayNode::getValue(size_t index) const
	{
		return at(index).value();
	}

	inline const NullNode& ArrayNode::getNull(size_t index) const
	{
		return getValue(index).asNull();
	}

	inline const BooleanNode& ArrayNode::getBoolean(size_t index) const
	{
		return getValue(index).asBoolean();
	}

	inline const StringNode& ArrayNode::getString(size_t index) const
	{
		return getValue(index).asString();
	}

	inline const NumberNode& ArrayNode::getNumber(size_t index) const
	{
		return getValue(index).asNumber();
	}

	inline const ObjectNode& ArrayNode::getObject(size_t index) const
	{
		return getValue(index).asObject();
	}

	inline const ArrayNode& ArrayNode::getArray(size_t index) const
	{
		return getValue(index).asArray();
	}

	inline void ArrayNode::append(const ArrayNode::Element& element)
	{
		insert(end(), element);
	}

	inline void ArrayNode::append(const ValueNode& value)
	{
		insert(end(), value);
	}

	inline void ArrayNode::append(const ValueDesc& value)
	{
		insert(end(), value);
	}

} // eclog
} // vallest

#include <limits.h>

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Alloc>
	class DocumentParseHandler : private NonCopyable {
	public:
		explicit DocumentParseHandler(ObjectNode& root) : root_(root), hasKey_(false)
		{
		}

	public:
		void onObjectBegin()
		{
			if (hasKey_)
			{
				currentObject().appendForce(makeDesc(key_), empty_object);

				push(currentObject().last().value());

				hasKey_ = false;
			}
			else if (!stack_.empty())
			{
				currentArray().append(empty_object);

				push(currentArray().last().value());
			}
			else
			{
				push(root_);
			}
		}

		void onObjectEnd()
		{
			pop();
		}

		void onArrayBegin()
		{
			if (hasKey_)
			{
				currentObject().appendForce(makeDesc(key_), empty_array);

				push(currentObject().last().value());

				hasKey_ = false;
			}
			else
			{
				currentArray().append(empty_array);

				push(currentArray().last().value());
			}
		}

		void onArrayEnd()
		{
			pop();
		}

		void onKey(const Key& key)
		{
			key_ = key;

			hasKey_ = true;
		}

		void onValue(const Value& value)
		{
			if (hasKey_)
			{
				currentObject().appendForce(makeDesc(key_), makeDesc(value));

				hasKey_ = false;
			}
			else
			{
				currentArray().append(makeDesc(value));
			}
		}

	private:
		void push(ValueNode& node)
		{
			stack_.pushBack(&node);
		}

		void pop()
		{
			stack_.popBack();
		}

		ObjectNode& currentObject()
		{
			return *(ObjectNode*)stack_.back();
		}

		ArrayNode& currentArray()
		{
			return *(ArrayNode*)stack_.back();
		}

	private:
		static KeyDesc makeDesc(const Key& key)
		{
			return KeyDesc(key, key.notation(), key.delimiter());
		}

		static ValueDesc makeDesc(const Value& value)
		{
			switch (value.type())
			{
			case value_type_null:
				return ValueDesc(null);

			case value_type_boolean:
				return ValueDesc(value.asBoolean());

			case value_type_string:
				return ValueDesc(value.asString(), value.stringNotation(), value.stringDelimiter());

			case value_type_number:
				return ValueDesc(value.asNumber());

			default:
				ECLOG_ASSERT(false);
				return ValueDesc(null);
			}
		}

	private:
		ObjectNode& root_;

		bool hasKey_;
		Key key_;

		PODArray<void*, Alloc> stack_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class NullNode : public ValueNode {
	protected:
		~NullNode() {} // prevents calling delete

	public:
		virtual Null value() const = 0;

		virtual void assign(const Null&) = 0;
		virtual void assign(const NullNode&) = 0;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class BooleanNode : public ValueNode {
	protected:
		~BooleanNode() {} // prevents calling delete

	public:
		virtual bool value() const = 0;

		virtual void assign(bool value) = 0;
		virtual void assign(const BooleanNode& other) = 0;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class StringNode : public ValueNode {
	protected:
		~StringNode() {} // prevents calling delete

	public:
		virtual cstring value() const = 0;

		virtual void setNotation(StringNotation notation) = 0;
		virtual StringNotation notation() const = 0;

		virtual void setDelimiter(cstring delimiter) = 0;
		virtual void setDelimiter(cstring delimiter, ErrorCode& ec) = 0;
		virtual cstring delimiter() const = 0;

		virtual void assign(const StringDesc& desc) = 0;
		virtual void assign(const StringNode& other) = 0;
	};

} // eclog
} // vallest

namespace vallest {
namespace eclog {

	class NumberNode : public ValueNode {
	protected:
		~NumberNode() {} // prevents calling delete

	public:
		virtual Number value() const = 0;

		double valueDouble() const;
		int valueInt() const;
		unsigned int valueUInt() const;
		long valueLong() const;
		unsigned long valueULong() const;
		long long valueLLong() const;
		unsigned long long valueULLong() const;

		virtual void setFracDigits(int fracDigits) = 0;
		virtual int fracDigits() const = 0;

		virtual void assign(const NumberDesc& desc) = 0;
		virtual void assign(const NumberNode& other) = 0;
	};

	inline double NumberNode::valueDouble() const
	{
		return value().load<double>();
	}

	inline int NumberNode::valueInt() const
	{
		return value().load<int>();
	}

	inline unsigned int NumberNode::valueUInt() const
	{
		return value().load<unsigned int>();
	}

	inline long NumberNode::valueLong() const
	{
		return value().load<long>();
	}

	inline unsigned long NumberNode::valueULong() const
	{
		return value().load<unsigned long>();
	}

	inline long long NumberNode::valueLLong() const
	{
		return value().load<long long>();
	}

	inline unsigned long long NumberNode::valueULLong() const
	{
		return value().load<unsigned long long>();
	}

} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class DocumentRenderer : private NonCopyable {
	public:
		explicit DocumentRenderer(OutputStream& stream, const RendererConfig& rc = RendererConfig()) : renderer_(stream, rc)
		{
		}

		void render(const ObjectNode& root, ErrorCode* ec)
		{
			renderer_.beginObject(ec);
			ECLOG_ON_ERROR(return);

			renderObject(root, ec);
			ECLOG_ON_ERROR(return);

			renderer_.endObject(ec);
			ECLOG_ON_ERROR(return);

			renderer_.close(ec);
			ECLOG_ON_ERROR(return);
		}

	private:
		void renderObject(const ObjectNode& node, ErrorCode* ec)
		{
			for (ObjectNode::ConstIterator it = node.begin(); it != node.end(); ++it)
			{
				const KeyNode& keyNode = it->key();
				const ValueNode& valueNode = it->value();

				if (valueNode.isObject())
				{
					renderer_.beginObject(makeDesc(keyNode), ec);
					ECLOG_ON_ERROR(return);

					renderObject((const ObjectNode&)valueNode, ec);
					ECLOG_ON_ERROR(return);

					renderer_.endObject(ec);
					ECLOG_ON_ERROR(return);
				}
				else if (valueNode.isArray())
				{
					renderer_.beginArray(makeDesc(keyNode), ec);
					ECLOG_ON_ERROR(return);

					renderArray((const ArrayNode&)valueNode, ec);
					ECLOG_ON_ERROR(return);

					renderer_.endArray(ec);
					ECLOG_ON_ERROR(return);
				}
				else
				{
					renderer_.renderMember(makeDesc(keyNode), makeDesc(valueNode), ec);
					ECLOG_ON_ERROR(return);
				}
			}
		}

		void renderArray(const ArrayNode& node, ErrorCode* ec)
		{
			for (ArrayNode::ConstIterator it = node.begin(); it != node.end(); ++it)
			{
				const ValueNode& valueNode = it->value();

				if (valueNode.isObject())
				{
					renderer_.beginObject(ec);
					ECLOG_ON_ERROR(return);

					renderObject((const ObjectNode&)valueNode, ec);
					ECLOG_ON_ERROR(return);

					renderer_.endObject(ec);
					ECLOG_ON_ERROR(return);
				}
				else if (valueNode.isArray())
				{
					renderer_.beginArray(ec);
					ECLOG_ON_ERROR(return);

					renderArray((const ArrayNode&)valueNode, ec);
					ECLOG_ON_ERROR(return);

					renderer_.endArray(ec);
					ECLOG_ON_ERROR(return);
				}
				else
				{
					renderer_.renderMember(makeDesc(valueNode), ec);
					ECLOG_ON_ERROR(return);
				}
			}
		}

		static KeyDesc makeDesc(const KeyNode& keyNode)
		{
			return KeyDesc(keyNode.str(), keyNode.notation(), keyNode.delimiter());
		}

		static ValueDesc makeDesc(const ValueNode& valueNode)
		{
			switch (valueNode.nodeType())
			{
			case node_type_null:
				return ValueDesc(null);

			case node_type_boolean:
				return ValueDesc(((const BooleanNode&)valueNode).value());

			case node_type_string:
				return ValueDesc(((const StringNode&)valueNode).value(), ((const StringNode&)valueNode).notation(), ((const StringNode&)valueNode).delimiter());

			case node_type_number:
				return ValueDesc(((const NumberNode&)valueNode).value(), ((const NumberNode&)valueNode).fracDigits());

			default:
				ECLOG_ASSERT(false);
				return ValueDesc(null);
			}
		}

	private:
		Renderer renderer_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T, typename Factory>
	class NodePtr : private NonCopyable {
	public:
		explicit NodePtr(T* ptr = 0) : ptr_(ptr)
		{
		}

		~NodePtr()
		{
			if (ptr_) {
				Factory::destroy(ptr_);
			}
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}

		T* get() const
		{
			return ptr_;
		}

		void reset(T* ptr = 0)
		{
			if (ptr_) {
				Factory::destroy(ptr_);
			}

			ptr_ = ptr;
		}

		T* release()
		{
			T* ptr = ptr_;
			ptr_ = 0;
			return ptr;
		}

	private:
		T* ptr_;
	};

} // detail
} // eclog
} // vallest

// RbTree (based on the red-black tree implementation of STLport)
//
// Copyright (c) 1994
// Hewlett-Packard Company
// 
// Copyright (c) 1996,1997
// Silicon Graphics Computer Systems, Inc.
// 
// Copyright (c) 1997
// Moscow Center for SPARC Technology
// 
// Copyright (c) 1999
// Boris Fomitchev
// 
// This material is provided "as is", with absolutely no warranty
// expressed or implied. Any use is at your own risk.
// 
// Permission to use or copy this software for any purpose is hereby
// granted without fee, provided the above notices are retained on
// all copies. Permission to modify the code and to distribute
// modified code is granted, provided the above notices are retained,
// and a notice that the code was modified is included with the above
// copyright notice.

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Node, typename Traits, typename Compare>
	class RbTree : private NonCopyable {
	private:
		typedef typename Traits::ColorType ColorType;

	public:
		RbTree() : size_(0)
		{
			setColor(&head_, red());
			setParent(&head_, 0);
			setLeft(&head_, &head_);
			setRight(&head_, &head_);
		}

		void clear()
		{
			if (size_ != 0)
			{
				setParent(&head_, 0);
				setLeft(&head_, &head_);
				setRight(&head_, &head_);

				size_ = 0;
			}
		}

		bool empty() const
		{
			return (size_ == 0);
		}

		size_t size() const
		{
			return size_;
		}

		Node* begin()
		{
			return getLeft(&head_);
		}

		const Node* begin() const
		{
			return getLeft(&head_);
		}

		Node* end()
		{
			return &head_;
		}

		const Node* end() const
		{
			return &head_;
		}

		template<typename Key>
		Node* find(const Key& key)
		{
			return find<Key, Node*>(key, getParent(&head_), &head_);
		}

		template<typename Key>
		const Node* find(const Key& key) const
		{
			return find<Key, const Node*>(key, getParent(&head_), &head_);
		}

		Pair<Node*, bool> insertUnique(Node* node)
		{
			setLeft(node, 0);
			setRight(node, 0);

			Node* p = &head_;
			Node* p2 = getParent(&head_);

			bool comp = true;

			while (p2 != 0)
			{
				p = p2;
				comp = compare(*node, *p2);
				p2 = comp ? getLeft(p2) : getRight(p2);
			}

			Node* p3 = p;

			if (comp)
			{
				if (p3 == getLeft(&head_))
				{
					insert(p, node, p);

					return Pair<Node*, bool>(node, true);
				}
				else
				{
					p3 = decrement(p3);
				}
			}

			if (compare(*p3, *node))
			{
				insert(p, node, p2);

				return Pair<Node*, bool>(node, true);
			}

			return Pair<Node*, bool>(p3, false);
		}

		void erase(Node* node)
		{
			Node* root = getParent(&head_);
			Node* leftmost = getLeft(&head_);
			Node* rightmost = getRight(&head_);

			rebalanceForErase(node, root, leftmost, rightmost);

			setParent(&head_, root);
			setLeft(&head_, leftmost);
			setRight(&head_, rightmost);

			--size_;
		}

		void swap(RbTree& other)
		{
			if (other.empty())
			{
				if (!empty())
				{
					Node* root = getParent(&head_);
					Node* leftmost = getLeft(&head_);
					Node* rightmost = getRight(&head_);

					setParent(&head_, 0);
					setLeft(&head_, &head_);
					setRight(&head_, &head_);

					setParent(&other.head_, root);
					setLeft(&other.head_, leftmost);
					setRight(&other.head_, rightmost);

					setParent(root, &other.head_);

					detail::swap(size_, other.size_);
				}
			}
			else if (empty())
			{
				other.swap(*this);
			}
			else
			{
				Node* root = getParent(&head_);
				Node* leftmost = getLeft(&head_);
				Node* rightmost = getRight(&head_);

				setParent(&head_, getParent(&other.head_));
				setLeft(&head_, getLeft(&other.head_));
				setRight(&head_, getRight(&other.head_));
				setParent(getParent(&head_), &head_);

				setParent(&other.head_, root);
				setLeft(&other.head_, leftmost);
				setRight(&other.head_, rightmost);
				setParent(getParent(&other.head_), &other.head_);

				detail::swap(size_, other.size_);
			}
		}

		bool verify() const
		{
			Node* root = getParent(&head_);
			Node* leftmost = getLeft(&head_);
			Node* rightmost = getRight(&head_);

			if (size() == 0 || begin() == end())
			{
				return ((size() == 0) && (begin() == end()) && (leftmost == &head_) && (rightmost == &head_));
			}

			int len = blackCount(leftmost, root);

			for (const Node* p = begin(); p != end(); p = increment(p))
			{
				const Node* left = getLeft(p);
				const Node* right = getRight(p);

				if (getColor(p) == red())
				{
					if ((left && getColor(left) == red()) || (right && getColor(right) == red())) {
						return false;
					}
				}

				if (left && compare(*p, *left)) {
					return false;
				}

				if (right && compare(*right, *p)) {
					return false;
				}

				if (!left && !right && blackCount(p, root) != len) {
					return false;
				}
			}

			if (leftmost != minimum(root)) {
				return false;
			}

			if (rightmost != maximum(root)) {
				return false;
			}

			return true;
		}

	public:
		template<typename NodePtr>
		static NodePtr increment(NodePtr node)
		{
			if (getRight(node) != 0)
			{
				node = minimum(getRight(node));
			}
			else
			{
				Node* p = getParent(node);

				while (node == getRight(p))
				{
					node = p;
					p = getParent(p);
				}

				if (getRight(node) != p) {
					node = p;
				}
			}

			return node;
		}

		template<typename NodePtr>
		static NodePtr decrement(NodePtr node)
		{
			if (getColor(node) == red() && getParent(getParent(node)) == node)
			{
				node = getRight(node);
			}
			else if (getLeft(node) != 0)
			{
				node = maximum(getLeft(node));
			}
			else
			{
				NodePtr p = getParent(node);

				while (node == getLeft(p))
				{
					node = p;
					p = getParent(p);
				}

				node = p;
			}

			return node;
		}

	private:
		static Node* getParent(const Node* node)
		{
			return Traits::getParent(node);
		}

		static void setParent(Node* node, Node* parent)
		{
			Traits::setParent(node, parent);
		}

		static Node* getLeft(const Node* node)
		{
			return Traits::getLeft(node);
		}

		static void setLeft(Node* node, Node* left)
		{
			Traits::setLeft(node, left);
		}

		static Node* getRight(const Node* node)
		{
			return Traits::getRight(node);
		}

		static void setRight(Node* node, Node* right)
		{
			Traits::setRight(node, right);
		}

		static ColorType getColor(const Node* node)
		{
			return Traits::getColor(node);
		}

		static void setColor(Node* node, ColorType color)
		{
			Traits::setColor(node, color);
		}

		static ColorType red()
		{
			return Traits::red();
		}

		static ColorType black()
		{
			return Traits::black();
		}

		template<typename T1, typename T2>
		static bool compare(const T1& a, const T2& b)
		{
			return Compare()(a, b);
		}

		static Node* minimum(Node* node)
		{
			while (getLeft(node) != 0) {
				node = getLeft(node);
			}

			return node;
		}

		static Node* maximum(Node* node)
		{
			while (getRight(node) != 0) {
				node = getRight(node);
			}

			return node;
		}

		static void rotateLeft(Node* node, Node*& root)
		{
			Node* p = getRight(node);

			setRight(node, getLeft(p));

			if (getLeft(p) != 0) {
				setParent(getLeft(p), node);
			}

			setParent(p, getParent(node));

			if (node == root) {
				root = p;
			}
			else if (node == getLeft(getParent(node))) {
				setLeft(getParent(node), p);
			}
			else {
				setRight(getParent(node), p);
			}

			setLeft(p, node);
			setParent(node, p);
		}

		static void rotateRight(Node* node, Node*& root)
		{
			Node* p = getLeft(node);

			setLeft(node, getRight(p));

			if (getRight(p) != 0) {
				setParent(getRight(p), node);
			}

			setParent(p, getParent(node));

			if (node == root) {
				root = p;
			}
			else if (node == getRight(getParent(node))) {
				setRight(getParent(node), p);
			}
			else {
				setLeft(getParent(node), p);
			}

			setRight(p, node);
			setParent(node, p);
		}

		static void rebalance(Node* node, Node*& root)
		{
			setColor(node, red());

			while (node != root && getColor(getParent(node)) == red())
			{
				if (getParent(node) == getLeft(getParent(getParent(node))))
				{
					Node* p = getRight(getParent(getParent(node)));

					if (p && getColor(p) == red())
					{
						setColor(getParent(node), black());
						setColor(p, black());
						setColor(getParent(getParent(node)), red());
						node = getParent(getParent(node));
					}
					else
					{
						if (node == getRight(getParent(node)))
						{
							node = getParent(node);
							rotateLeft(node, root);
						}

						setColor(getParent(node), black());
						setColor(getParent(getParent(node)), red());
						rotateRight(getParent(getParent(node)), root);
					}
				}
				else
				{
					Node* p = getLeft(getParent(getParent(node)));

					if (p && getColor(p) == red())
					{
						setColor(getParent(node), black());
						setColor(p, black());
						setColor(getParent(getParent(node)), red());
						node = getParent(getParent(node));
					}
					else
					{
						if (node == getLeft(getParent(node)))
						{
							node = getParent(node);
							rotateRight(node, root);
						}

						setColor(getParent(node), black());
						setColor(getParent(getParent(node)), red());
						rotateLeft(getParent(getParent(node)), root);
					}
				}
			}

			setColor(root, black());
		}

		static Node* rebalanceForErase(Node* node, Node*& root, Node*& leftmost, Node*& rightmost)
		{
			Node* p = node;
			Node* p2;
			Node* p3;

			if (getLeft(p) == 0)
			{
				p2 = getRight(p);
			}
			else if (getRight(p) == 0)
			{
				p2 = getLeft(p);
			}
			else
			{
				p = minimum(getRight(p));
				p2 = getRight(p);
			}

			if (p != node)
			{
				setParent(getLeft(node), p);
				setLeft(p, getLeft(node));

				if (p != getRight(node))
				{
					p3 = getParent(p);

					if (p2) {
						setParent(p2, getParent(p));
					}

					setLeft(getParent(p), p2);
					setRight(p, getRight(node));
					setParent(getRight(node), p);
				}
				else
				{
					p3 = p;
				}

				if (root == node) {
					root = p;
				}
				else if (getLeft(getParent(node)) == node) {
					setLeft(getParent(node), p);
				}
				else {
					setRight(getParent(node), p);
				}

				setParent(p, getParent(node));

				ColorType t = getColor(p);
				setColor(p, getColor(node));
				setColor(node, t);

				p = node;
			}
			else
			{
				p3 = getParent(p);

				if (p2) {
					setParent(p2, getParent(p));
				}

				if (root == node) {
					root = p2;
				}
				else if (getLeft(getParent(node)) == node) {
					setLeft(getParent(node), p2);
				}
				else {
					setRight(getParent(node), p2);
				}

				if (leftmost == node)
				{
					if (getRight(node) == 0) {
						leftmost = getParent(node);
					}
					else {
						leftmost = minimum(p2);
					}
				}

				if (rightmost == node)
				{
					if (getLeft(node) == 0) {
						rightmost = getParent(node);
					}
					else {
						rightmost = maximum(p2);
					}
				}
			}

			if (getColor(p) != red())
			{
				while (p2 != root && (p2 == 0 || getColor(p2) == black()))
				{
					if (p2 == getLeft(p3))
					{
						Node* p4 = getRight(p3);

						if (getColor(p4) == red())
						{
							setColor(p4, black());
							setColor(p3, red());
							rotateLeft(p3, root);
							p4 = getRight(p3);
						}

						if ((getLeft(p4) == 0 || getColor(getLeft(p4)) == black()) && (getRight(p4) == 0 || getColor(getRight(p4)) == black()))
						{
							setColor(p4, red());
							p2 = p3;
							p3 = getParent(p3);
						}
						else
						{
							if (getRight(p4) == 0 || getColor(getRight(p4)) == black())
							{
								if (getLeft(p4)) {
									setColor(getLeft(p4), black());
								}

								setColor(p4, red());
								rotateRight(p4, root);
								p4 = getRight(p3);
							}

							setColor(p4, getColor(p3));
							setColor(p3, black());

							if (getRight(p4)) {
								setColor(getRight(p4), black());
							}

							rotateLeft(p3, root);
							break;
						}
					}
					else
					{
						Node* p4 = getLeft(p3);

						if (getColor(p4) == red())
						{
							setColor(p4, black());
							setColor(p3, red());
							rotateRight(p3, root);
							p4 = getLeft(p3);
						}

						if ((getRight(p4) == 0 || getColor(getRight(p4)) == black()) && (getLeft(p4) == 0 || getColor(getLeft(p4)) == black()))
						{
							setColor(p4, red());
							p2 = p3;
							p3 = getParent(p3);
						}
						else
						{
							if (getLeft(p4) == 0 || getColor(getLeft(p4)) == black())
							{
								if (getRight(p4)) {
									setColor(getRight(p4), black());
								}

								setColor(p4, red());
								rotateLeft(p4, root);
								p4 = getLeft(p3);
							}

							setColor(p4, getColor(p3));
							setColor(p3, black());

							if (getLeft(p4)) {
								setColor(getLeft(p4), black());
							}

							rotateRight(p3, root);
							break;
						}
					}
				}

				if (p2) {
					setColor(p2, black());
				}
			}

			return p;
		}

		template<typename Key, typename NodePtr>
		static NodePtr find(const Key& key, NodePtr root, NodePtr end)
		{
			NodePtr p = end;
			NodePtr p2 = root;

			while (p2 != 0)
			{
				if (!compare(*p2, key))
				{
					p = p2;
					p2 = getLeft(p2);
				}
				else
				{
					p2 = getRight(p2);
				}
			}

			if (p != end)
			{
				if (compare(key, *p)) {
					p = end;
				}
			}

			return p;
		}

		Node* insert(Node* parent, Node* node, Node* onLeft = 0, Node* onRight = 0)
		{
			if (parent == &head_)
			{
				setLeft(parent, node);
				setParent(&head_, node);
				setRight(&head_, node);
			}
			else if (onRight == 0 && (onLeft != 0 || compare(*node, *parent)))
			{
				setLeft(parent, node);

				if (parent == getLeft(&head_)) {
					setLeft(&head_, node);
				}
			}
			else
			{
				setRight(parent, node);

				if (parent == getRight(&head_)) {
					setRight(&head_, node);
				}
			}

			setParent(node, parent);

			Node* root = getParent(&head_);

			rebalance(node, root);

			setParent(&head_, root);

			++size_;

			return node;
		}

		int blackCount(const Node* node, const Node* root) const
		{
			if (node == 0) {
				return 0;
			}

			int count = getColor(node) == black() ? 1 : 0;

			if (node == root) {
				return count;
			}
			else {
				return count + blackCount(getParent(node), root);
			}
		}

	private:
		Node head_;
		size_t size_;
	};

	template<typename Node, typename Traits, typename Compare>
	inline void swap(RbTree<Node, Traits, Compare>& a, RbTree<Node, Traits, Compare>& b)
	{
		a.swap(b);
	}

} // detail
} // eclog
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Node, typename Traits>
	class LinkedList : private NonCopyable {
	public:
		LinkedList() : size_(0)
		{
			setPrev(&head_, &head_);
			setNext(&head_, &head_);
		}

		void clear()
		{
			if (size_ != 0)
			{
				setPrev(&head_, &head_);
				setNext(&head_, &head_);

				size_ = 0;
			}
		}

		bool empty() const
		{
			return (size_ == 0);
		}

		size_t size() const
		{
			return size_;
		}

		Node* begin()
		{
			return getNext(&head_);
		}

		const Node* begin() const
		{
			return getNext(&head_);
		}

		Node* end()
		{
			return &head_;
		}

		const Node* end() const
		{
			return &head_;
		}

		Node* front()
		{
			return getNext(&head_);
		}

		const Node* front() const
		{
			return getNext(&head_);
		}

		Node* back()
		{
			return getPrev(&head_);
		}

		const Node* back() const
		{
			return getPrev(&head_);
		}

		void pushBack(Node* node)
		{
			insertBefore(node, end());
		}

		void popBack()
		{
			erase(back());
		}

		void pushFront(Node* node)
		{
			insertBefore(node, begin());
		}

		void popFront()
		{
			erase(front());
		}

		void insertBefore(Node* node, Node* refNode)
		{
			setPrev(node, getPrev(refNode));
			setNext(node, refNode);
			setNext(getPrev(refNode), node);
			setPrev(refNode, node);

			++size_;
		}

		void insertAfter(Node* node, Node* refNode)
		{
			insertBefore(node, getNext(refNode));
		}

		void replace(Node* node, Node* oldNode)
		{
			setNext(node, getNext(oldNode));
			setPrev(node, getPrev(oldNode));
			setNext(getPrev(node), node);
			setPrev(getNext(node), node);
		}

		void erase(Node* node)
		{
			setNext(getPrev(node), getNext(node));
			setPrev(getNext(node), getPrev(node));

			--size_;
		}

		void swap(LinkedList& other)
		{
			if (other.empty())
			{
				if (!empty())
				{
					Node* next = getNext(&head_);
					Node* prev = getPrev(&head_);

					setPrev(&head_, &head_);
					setNext(&head_, &head_);

					setNext(&other.head_, next);
					setPrev(&other.head_, prev);
					setPrev(getNext(&other.head_), &other.head_);
					setNext(getPrev(&other.head_), &other.head_);

					detail::swap(size_, other.size_);
				}
			}
			else if (empty())
			{
				other.swap(*this);
			}
			else
			{
				Node* next = getNext(&head_);
				Node* prev = getPrev(&head_);

				setNext(&head_, getNext(&other.head_));
				setPrev(&head_, getPrev(&other.head_));
				setPrev(getNext(&head_), &head_);
				setNext(getPrev(&head_), &head_);

				setNext(&other.head_, next);
				setPrev(&other.head_, prev);
				setPrev(getNext(&other.head_), &other.head_);
				setNext(getPrev(&other.head_), &other.head_);

				detail::swap(size_, other.size_);
			}
		}

	public:
		template<typename NodePtr>
		static NodePtr increment(NodePtr node)
		{
			return getNext(node);
		}

		template<typename NodePtr>
		static NodePtr decrement(NodePtr node)
		{
			return getPrev(node);
		}

	private:
		static Node* getPrev(const Node* node)
		{
			return Traits::getPrev(node);
		}

		static void setPrev(Node* node, Node* prev)
		{
			Traits::setPrev(node, prev);
		}

		static Node* getNext(const Node* node)
		{
			return Traits::getNext(node);
		}

		static void setNext(Node* node, Node* next)
		{
			Traits::setNext(node, next);
		}

	private:
		Node head_;
		size_t size_;
	};

	template<typename Node, typename Traits>
	inline void swap(LinkedList<Node, Traits>& a, LinkedList<Node, Traits>& b)
	{
		a.swap(b);
	}

} // detail
} // eclog
} // vallest

#include <stddef.h> // ptrdiff_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Factory>
	class ObjectNodeImpl : public ObjectNode, private NonCopyable {
	private:
		struct RbTreeNode
		{
			int color;
			RbTreeNode* parent;
			RbTreeNode* left;
			RbTreeNode* right;
		};

		class LinkedListNode : public ObjectNode::Element {
		public:
			virtual KeyNode& key() ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual const KeyNode& key() const ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual ValueNode& value() ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual const ValueNode& value() const ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual void updateValue(const ValueNode&) ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual void updateValue(const ValueDesc&) ECLOG_OVERRIDE
			{
				ECLOG_FAULT(OutOfRange);
			}

			virtual LinkedListNode* prev() ECLOG_OVERRIDE
			{
				return prev_;
			}

			virtual const LinkedListNode* prev() const ECLOG_OVERRIDE
			{
				return prev_;
			}

			virtual LinkedListNode* next() ECLOG_OVERRIDE
			{
				return next_;
			}

			virtual const LinkedListNode* next() const ECLOG_OVERRIDE
			{
				return next_;
			}

		public:
			void setPrev(LinkedListNode* prev)
			{
				prev_ = prev;
			}

			void setNext(LinkedListNode* next)
			{
				next_ = next;
			}

		private:
			LinkedListNode* prev_;
			LinkedListNode* next_;
		};

		class Element : public LinkedListNode {
		public:
			virtual KeyNode& key() ECLOG_OVERRIDE
			{
				return *key_;
			}

			virtual const KeyNode& key() const ECLOG_OVERRIDE
			{
				return *key_;
			}

			virtual ValueNode& value() ECLOG_OVERRIDE
			{
				return *value_;
			}

			virtual const ValueNode& value() const ECLOG_OVERRIDE
			{
				return *value_;
			}

			virtual void updateValue(const ValueNode& value) ECLOG_OVERRIDE
			{
				ValueNode* p = Factory::create(value);

				Factory::destroy(value_);

				value_ = p;
			}

			virtual void updateValue(const ValueDesc& desc) ECLOG_OVERRIDE
			{
				ValueNode* p = Factory::create(desc);

				Factory::destroy(value_);

				value_ = p;
			}

		public:
			void setKey(KeyNode* key)
			{
				key_ = key;
			}

			void setValue(ValueNode* value)
			{
				value_ = value;
			}

			RbTreeNode* rbTreeNode()
			{
				return &rbTreeNode_;
			}

		public:
			static Element* getBaseAddress(RbTreeNode* p)
			{
				return (Element*)((char*)p - Element().offsetOfRbTreeNode());
			}

			static const Element* getBaseAddress(const RbTreeNode* p)
			{
				return (const Element*)((const char*)p - Element().offsetOfRbTreeNode());
			}

		private:
			ptrdiff_t offsetOfRbTreeNode() const
			{
				return (const char*)&rbTreeNode_ - (const char*)this;
			}

		private:
			KeyNode* key_;
			ValueNode* value_;
			RbTreeNode rbTreeNode_;
		};

		struct RbTreeNodeTraits
		{
			typedef int ColorType;

			static RbTreeNode* getParent(const RbTreeNode* node)
			{
				return node->parent;
			}

			static void setParent(RbTreeNode* node, RbTreeNode* parent)
			{
				node->parent = parent;
			}

			static RbTreeNode* getLeft(const RbTreeNode* node)
			{
				return node->left;
			}

			static void setLeft(RbTreeNode* node, RbTreeNode* left)
			{
				node->left = left;
			}

			static RbTreeNode* getRight(const RbTreeNode* node)
			{
				return node->right;
			}

			static void setRight(RbTreeNode* node, RbTreeNode* right)
			{
				node->right = right;
			}

			static ColorType getColor(const RbTreeNode* node)
			{
				return node->color;
			}

			static void setColor(RbTreeNode* node, ColorType color)
			{
				node->color = color;
			}

			static ColorType red()
			{
				return 0;
			}

			static ColorType black()
			{
				return 1;
			}
		};

		struct RbTreeNodeCompare
		{
			bool operator()(const cstring& a, const RbTreeNode& b) const
			{
				return a < Element::getBaseAddress(&b)->key().str();
			}

			bool operator()(const RbTreeNode& a, const cstring& b) const
			{
				return Element::getBaseAddress(&a)->key().str() < b;
			}

			bool operator()(const RbTreeNode& a, const RbTreeNode& b) const
			{
				return Element::getBaseAddress(&a)->key().str() < Element::getBaseAddress(&b)->key().str();
			}
		};

		struct LinkedListNodeTraits
		{
			static LinkedListNode* getPrev(const LinkedListNode* p)
			{
				return (LinkedListNode*)p->prev();
			}

			static void setPrev(LinkedListNode* p, LinkedListNode* prev)
			{
				p->setPrev(prev);
			}

			static LinkedListNode* getNext(const LinkedListNode* p)
			{
				return (LinkedListNode*)p->next();
			}

			static void setNext(LinkedListNode* p, LinkedListNode* next)
			{
				p->setNext(next);
			}
		};

		typedef RbTree<RbTreeNode, RbTreeNodeTraits, RbTreeNodeCompare> Tree;
		typedef LinkedList<LinkedListNode, LinkedListNodeTraits> List;

		typedef typename Factory::AllocType Alloc;

	public:
		ObjectNodeImpl()
		{
		}

		explicit ObjectNodeImpl(const ValueDesc& desc)
		{
			assign((const ObjectDesc&)desc);
		}

		explicit ObjectNodeImpl(const ObjectNode& other)
		{
			assign(other);
		}

		~ObjectNodeImpl()
		{
			remove(begin(), end());
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_object;
		}

		virtual void clear() ECLOG_OVERRIDE
		{
			remove(begin(), end());
		}

		virtual bool empty() const ECLOG_OVERRIDE
		{
			return list_.empty();
		}

		virtual size_t size() const ECLOG_OVERRIDE
		{
			return list_.size();
		}

		virtual Iterator begin() ECLOG_OVERRIDE
		{
			return list_.begin();
		}

		virtual Iterator end() ECLOG_OVERRIDE
		{
			return list_.end();
		}

		virtual ConstIterator begin() const ECLOG_OVERRIDE
		{
			return list_.begin();
		}

		virtual ConstIterator end() const ECLOG_OVERRIDE
		{
			return list_.end();
		}

		virtual bool contains(cstring key) const ECLOG_OVERRIDE
		{
			return tree_.find(key) != tree_.end();
		}

		virtual Iterator find(cstring key) ECLOG_OVERRIDE
		{
			RbTreeNode* p = tree_.find(key);

			if (p == tree_.end()) {
				return list_.end();
			}

			return Element::getBaseAddress(p);
		}

		virtual ConstIterator find(cstring key) const ECLOG_OVERRIDE
		{
			const RbTreeNode* p = tree_.find(key);

			if (p == tree_.end()) {
				return list_.end();
			}

			return Element::getBaseAddress(p);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const ObjectNode::Element& element) ECLOG_OVERRIDE
		{
			return insert(pos.get(), element.key(), element.value());
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const ObjectNode::Element& element) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), element.key(), element.value());
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insertForce(pos.get(), key, value);
		}

		virtual void merge(const ObjectDesc& patch) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t(patch);

			merge(t);
		}

		virtual void merge(const ObjectNode& patch) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t(patch);

			merge(t);
		}

		virtual void remove(Iterator pos) ECLOG_OVERRIDE
		{
			tree_.erase(((Element*)pos.get())->rbTreeNode());
			list_.erase((LinkedListNode*)pos.get());

			Factory::destroy(&pos->key());
			Factory::destroy(&pos->value());

			destroy<Element, Alloc>((Element*)pos.get());
		}

		virtual size_t remove(Iterator first, Iterator last) ECLOG_OVERRIDE
		{
			size_t count = 0;

			while (first != last)
			{
				remove(first++);

				++count;
			}

			return count;
		}

		virtual bool remove(cstring key) ECLOG_OVERRIDE
		{
			ObjectNode::Iterator it = find(key);

			if (it != end())
			{
				remove(it);
				return true;
			}

			return false;
		}

		virtual void parse(eclog::Context& ctx) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t;

			DocumentParseHandler<typename Factory::AllocType> handler(t);

			eclog::parse(ctx, handler);

			swap(t);
		}

		virtual void parse(eclog::Context& ctx, ErrorCode& ec) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t;

			DocumentParseHandler<typename Factory::AllocType> handler(t);

			eclog::parse(ctx, handler, ec);

			if (ec) {
				return;
			}

			swap(t);
		}

		virtual void parse(InputStream& stream) ECLOG_OVERRIDE
		{
			BasicDynamicParsingBuffer<typename Factory::AllocType> buffer;
			eclog::Context ctx(stream, buffer);

			parse(ctx);
		}

		virtual void parse(InputStream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			BasicDynamicParsingBuffer<typename Factory::AllocType> buffer;
			eclog::Context ctx(stream, buffer);

			parse(ctx, ec);
		}

		virtual void parse(cstring str) ECLOG_OVERRIDE
		{
			MemoryInputStream stream(str.data(), str.size());

			parse(stream);
		}

		virtual void parse(cstring str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			MemoryInputStream stream(str.data(), str.size());

			parse(stream, ec);
		}
		
		virtual void parse(std::istream& stream) ECLOG_OVERRIDE
		{
			StdStreamInputStream is(stream);

			parse(is);
		}

		virtual void parse(std::istream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			StdStreamInputStream is(stream);

			parse(is, ec);
		}

		virtual void parse(const std::string& str) ECLOG_OVERRIDE
		{
			parse(cstring(str.data(), str.size()));
		}

		virtual void parse(const std::string& str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			parse(cstring(str.data(), str.size()), ec);
		}

		virtual void parse(const char* str) ECLOG_OVERRIDE
		{
			parse(cstring(str));
		}

		virtual void parse(const char* str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			parse(cstring(str), ec);
		}

		virtual void render(OutputStream& stream) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream);

			renderer.render(*this, 0);
		}

		virtual void render(OutputStream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream);

			renderer.render(*this, &ec);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream, rc);

			renderer.render(*this, 0);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			detail::DocumentRenderer renderer(stream, rc);

			renderer.render(*this, &ec);
		}

		virtual void render(std::ostream& stream) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os);
		}

		virtual void render(std::ostream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os, ec);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os, rc);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			StdStreamOutputStream os(stream);

			render(os, rc, ec);
		}

		virtual void assign(const ObjectDesc& desc) ECLOG_OVERRIDE
		{
			ObjectNodeImpl t;

			for (size_t i = 0; i < desc.objectSize(); ++i)
			{
				t.appendForce(desc.object()[i].first, desc.object()[i].second);
			}

			swap(t);
		}

		virtual void assign(const ObjectNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			ObjectNodeImpl t;

			for (ObjectNode::ConstIterator it = other.begin(); it != other.end(); ++it)
			{
				t.append(it->key(), it->value());
			}

			swap(t);
		}

	public:
		void swap(ObjectNodeImpl& other)
		{
			detail::swap(tree_, other.tree_);
			detail::swap(list_, other.list_);
		}

	private:
		template<typename K, typename V>
		Pair<Element*, bool> insert(ObjectNode::Element* pos, const K& keyArg, const V& valueArg)
		{
			NodePtr<KeyNode, Factory> key(Factory::create(keyArg));

			UniquePtr<Element, Alloc> p(create<Element, Alloc>());

			p->setKey(key.get());

			Pair<RbTreeNode*, bool> result = tree_.insertUnique(p->rbTreeNode());

			if (result.second)
			{
				NodePtr<ValueNode, Factory> value;

				ECLOG_TRY
				{
					value.reset(Factory::create(valueArg));
				}
					ECLOG_CATCH_ALL
				{
					tree_.erase(p->rbTreeNode());
					ECLOG_RETHROW;
				}

				list_.insertBefore(p.get(), (LinkedListNode*)pos);

				key.release();
				p->setValue(value.release());

				return Pair<Element*, bool>(p.release(), true);
			}
			else
			{
				return Pair<Element*, bool>(Element::getBaseAddress(result.first), false);
			}
		}

		template<typename K, typename V>
		Element* insertForce(ObjectNode::Element* pos, const K& keyArg, const V& valueArg)
		{
			NodePtr<KeyNode, Factory> key(Factory::create(keyArg));
			NodePtr<ValueNode, Factory> value(Factory::create(valueArg));

			UniquePtr<Element, Alloc> p(create<Element, Alloc>());

			p->setKey(key.get());
			p->setValue(value.get());

			list_.insertBefore(p.get(), (LinkedListNode*)pos);

			Pair<RbTreeNode*, bool> result = tree_.insertUnique(p->rbTreeNode());

			if (result.second)
			{
				key.release();
				value.release();

				return p.release();
			}
			else
			{
				Element* p2 = Element::getBaseAddress(result.first);

				list_.erase(p2);
				list_.replace(p2, p.get());

				Factory::destroy(&p2->key());
				Factory::destroy(&p2->value());

				p2->setKey(key.release());
				p2->setValue(value.release());

				return p2;
			}
		}

		void merge(ObjectNodeImpl& patch)
		{
			LinkedListNode* p = patch.list_.begin();

			while (p != patch.list_.end())
			{
				Element* patchElement = (Element*)p;
				p = p->next();

				RbTreeNode* rbTreeNode = tree_.find(patchElement->key().str());

				if (rbTreeNode == tree_.end())
				{
					if (!patchElement->value().isNull())
					{
						if (patchElement->value().isObject()) {
							removeNullNodes((ObjectNodeImpl&)patchElement->value());
						}

						patch.tree_.erase(patchElement->rbTreeNode());
						patch.list_.erase(patchElement);

						tree_.insertUnique(patchElement->rbTreeNode());
						list_.insertBefore(patchElement, list_.end());
					}

					continue;
				}

				Element* targetElement = Element::getBaseAddress(rbTreeNode);

				if (patchElement->value().isNull())
				{
					Factory::destroy(&targetElement->key());
					Factory::destroy(&targetElement->value());

					tree_.erase(targetElement->rbTreeNode());
					list_.erase(targetElement);

					destroy<Element, Alloc>(targetElement);
				}
				else if (patchElement->value().isObject() && targetElement->value().isObject())
				{
					((ObjectNodeImpl&)targetElement->value()).merge((ObjectNodeImpl&)patchElement->value());
				}
				else
				{
					if (patchElement->value().isObject()) {
						removeNullNodes((ObjectNodeImpl&)patchElement->value());
					}

					Factory::destroy(&targetElement->key());
					Factory::destroy(&targetElement->value());

					targetElement->setKey(&patchElement->key());
					targetElement->setValue(&patchElement->value());

					patch.tree_.erase(patchElement->rbTreeNode());
					patch.list_.erase(patchElement);

					destroy<Element, Alloc>(patchElement);
				}
			}
		}

		void removeNullNodes(ObjectNodeImpl& obj)
		{
			LinkedListNode* p = obj.list_.begin();

			while (p != obj.list_.end())
			{
				Element* element = (Element*)p;
				p = p->next();

				if (element->value().isNull())
				{
					obj.tree_.erase(element->rbTreeNode());
					obj.list_.erase(element);

					Factory::destroy(&element->key());
					Factory::destroy(&element->value());

					destroy<Element, Alloc>(element);
				}
				else if (element->value().isObject())
				{
					removeNullNodes((ObjectNodeImpl&)element->value());
				}
			}
		}

	private:
		Tree tree_;
		List list_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Alloc>
	class KeyNodeImpl : public KeyNode {
	public:
		explicit KeyNodeImpl(const KeyDesc& desc) :
			str_(((const KeyDesc&)desc).str()),
			notation_(((const KeyDesc&)desc).notation()),
			delimiter_(((const KeyDesc&)desc).delimiter())
		{
		}

		explicit KeyNodeImpl(const KeyNode& other) :
			str_(other.str()),
			notation_(other.notation()),
			delimiter_(other.delimiter())
		{
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_key;
		}

		virtual cstring str() const ECLOG_OVERRIDE
		{
			return str_.str();
		}

		virtual void setNotation(StringNotation notation) ECLOG_OVERRIDE
		{
			notation_ = notation;
		}

		virtual StringNotation notation() const ECLOG_OVERRIDE
		{
			return notation_;
		}

		virtual void setDelimiter(cstring delimiter) ECLOG_OVERRIDE
		{
			setDelimiter(delimiter, 0);
		}

		virtual void setDelimiter(cstring delimiter, ErrorCode& ec) ECLOG_OVERRIDE
		{
			setDelimiter(delimiter, &ec);
		}

		virtual cstring delimiter() const ECLOG_OVERRIDE
		{
			return delimiter_.str();
		}

	private:
		void setDelimiter(cstring delimiter, ErrorCode* ec)
		{
			if (!StringDelimiter::validate(delimiter))
			{
				ECLOG_ERROR(InvalidArgument);
				return;
			}

			delimiter_ = delimiter;
		}

	private:
		ByteArray<Alloc> str_;

		StringNotation notation_;
		ByteArray<Alloc> delimiter_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class NullNodeImpl : public NullNode, private NonCopyable {
	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_null;
		}

		virtual Null value() const ECLOG_OVERRIDE
		{
			return null;
		}

		virtual void assign(const Null&) ECLOG_OVERRIDE
		{
		}

		virtual void assign(const NullNode&) ECLOG_OVERRIDE
		{
		}
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class BooleanNodeImpl : public BooleanNode, private NonCopyable {
	public:
		explicit BooleanNodeImpl(const ValueDesc& desc) :
			value_(desc.boolean())
		{
		}

		explicit BooleanNodeImpl(const BooleanNode& other) :
			value_(other.value())
		{
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_boolean;
		}

		virtual bool value() const ECLOG_OVERRIDE
		{
			return value_;
		}

		virtual void assign(bool value) ECLOG_OVERRIDE
		{
			value_ = value;
		}

		virtual void assign(const BooleanNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			value_ = other.value();
		}

	private:
		bool value_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Alloc>
	class StringNodeImpl : public StringNode, private NonCopyable {
	public:
		explicit StringNodeImpl(const ValueDesc& desc) :
			value_(desc.string()),
			notation_(desc.stringNotation()),
			delimiter_(desc.stringDelimiter())
		{
		}

		explicit StringNodeImpl(const StringNode& other) :
			value_(other.value()),
			notation_(other.notation()),
			delimiter_(other.delimiter())
		{
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_string;
		}

		virtual cstring value() const ECLOG_OVERRIDE
		{
			return value_.str();
		}

		virtual void setNotation(StringNotation notation) ECLOG_OVERRIDE
		{
			notation_ = notation;
		}

		virtual StringNotation notation() const ECLOG_OVERRIDE
		{
			return notation_;
		}

		virtual void setDelimiter(cstring delimiter) ECLOG_OVERRIDE
		{
			setDelimiter(delimiter, 0);
		}

		virtual void setDelimiter(cstring delimiter, ErrorCode& ec) ECLOG_OVERRIDE
		{
			setDelimiter(delimiter, &ec);
		}

		virtual cstring delimiter() const ECLOG_OVERRIDE
		{
			return delimiter_.str();
		}

		virtual void assign(const StringDesc& desc) ECLOG_OVERRIDE
		{
			ByteArray<Alloc> value(desc.string());
			ByteArray<Alloc> delimiter(desc.stringDelimiter());

			swap(value_, value);
			swap(delimiter_, delimiter);

			notation_ = desc.stringNotation();
		}

		virtual void assign(const StringNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			ByteArray<Alloc> value(other.value());
			ByteArray<Alloc> delimiter(other.delimiter());

			swap(value_, value);
			swap(delimiter_, delimiter);

			notation_ = other.notation();
		}

	private:
		void setDelimiter(cstring delimiter, ErrorCode* ec)
		{
			if (!StringDelimiter::validate(delimiter))
			{
				ECLOG_ERROR(InvalidArgument);
				return;
			}

			delimiter_ = delimiter;
		}

	private:
		ByteArray<Alloc> value_;

		StringNotation notation_;
		ByteArray<Alloc> delimiter_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	class NumberNodeImpl : public NumberNode, private NonCopyable {
	public:
		explicit NumberNodeImpl(const ValueDesc& desc) :
			value_(desc.number()),
			fracDigits_(desc.fracDigits())
		{
		}

		explicit NumberNodeImpl(const NumberNode& other)
		{
			assign(other);
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_number;
		}

		virtual Number value() const ECLOG_OVERRIDE
		{
			return value_;
		}

		virtual void setFracDigits(int fracDigits) ECLOG_OVERRIDE
		{
			fracDigits_ = fracDigits;
		}

		virtual int fracDigits() const ECLOG_OVERRIDE
		{
			return fracDigits_;
		}

		virtual void assign(const NumberDesc& desc) ECLOG_OVERRIDE
		{
			value_ = desc.number();
			fracDigits_ = desc.fracDigits();
		}

		virtual void assign(const NumberNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			value_ = other.value();
			fracDigits_ = other.fracDigits();
		}

	private:
		Number value_;

		int fracDigits_;
	};

} // detail
} // eclog
} // vallest

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename T, typename Alloc>
	class Vector {
	public:
		Vector() : size_(0), capacity_(0), v_(0)
		{
		}

		Vector(const Vector& other) : size_(0), capacity_(0), v_(0)
		{
			assign(other);
		}

		~Vector()
		{
			reset(0, 0, 0);
		}

		Vector& operator=(const Vector& other)
		{
			if (this != &other) {
				assign(other);
			}

			return *this;
		}

		bool empty() const
		{
			return size_ == 0;
		}

		size_t size() const
		{
			return size_;
		}

		size_t maxSize() const
		{
			return maxValue<size_t>() / sizeof(T);
		}

		size_t capacity() const
		{
			return capacity_;
		}

		void reserve(size_t capacity)
		{
			if (capacity > maxSize()) {
				ECLOG_FAULT(LengthError);
			}

			if (capacity > capacity_) {
				reset(makeCopy(capacity), size_, capacity);
			}
		}

		size_t indexOf(const T& value) const
		{
			return &value - v_;
		}

		T& operator[](size_t index)
		{
			ECLOG_ASSERT(index < size_);
			return v_[index];
		}

		const T& operator[](size_t index) const
		{
			ECLOG_ASSERT(index < size_);
			return v_[index];
		}

		T& front()
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[0];
		}

		const T& front() const
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[0];
		}

		T& back()
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[size_ - 1];
		}

		const T& back() const
		{
			ECLOG_ASSERT(size_ > 0);
			return v_[size_ - 1];
		}

		T* data()
		{
			return v_;
		}

		const T* data() const
		{
			return v_;
		}

		void clear()
		{
			destructRange(v_, v_ + size_);

			size_ = 0;
		}

		void insert(size_t index, const T& value)
		{
			pushBack(value);

			if (index < size_) {
				rotate(v_ + index, v_ + (size_ - 1), v_ + size_);
			}
		}

		void pushBack(const T& value)
		{
			if (size_ == maxSize()) {
				ECLOG_FAULT(LengthError);
			}

			if (size_ < capacity_)
			{
				construct<T>(v_ + size_, value);

				size_ += 1;
			}
			else
			{
				size_t capacity = growTo(size_ + 1);

				T* v = makeCopy(capacity);

				ECLOG_TRY
				{
					construct<T>(v + size_, value);
				}
				ECLOG_CATCH_ALL
				{
					reset(v, size_, capacity);
					ECLOG_RETHROW;
				}

				reset(v, size_ + 1, capacity);
			}
		}

		void popBack()
		{
			ECLOG_ASSERT(size_ > 0);

			destruct<T>(v_ + (size_ - 1));

			size_ -= 1;
		}

		void remove(size_t index, size_t count = 1)
		{
			if (index < size_ && count > 0)
			{
				if (count > size_ - index) {
					count = size_ - index;
				}

				copy(v_ + index + count, v_ + size_, v_ + index);

				destructRange(v_ + size_ - count, v_ + size_);

				size_ -= count;
			}
		}

		void swap(Vector& other)
		{
			detail::swap(size_, other.size_);
			detail::swap(capacity_, other.capacity_);
			detail::swap(v_, other.v_);
		}

	private:
		void destroyAll()
		{
			destructRange(v_, v_ + size_);

			Alloc::deallocate(v_);
		}

		void reset(T* v, size_t size, size_t capacity)
		{
			destroyAll();

			size_ = size;
			capacity_ = capacity;
			v_ = v;
		}

		T* makeCopy(size_t size) const
		{
			if (size > maxSize()) {
				ECLOG_FAULT(LengthError);
			}

			T* v = (T*)Alloc::allocate(sizeof(T) * size);

			if (v_)
			{
				ECLOG_TRY
				{
					constructN<T>(v, min(size_, size), v_);
				}
				ECLOG_CATCH_ALL
				{
					Alloc::deallocate(v);
					ECLOG_RETHROW;
				}
			}

			return v;
		}

		size_t growTo(size_t size) const
		{
			size_t capacity = maxSize() - capacity_ / 2 < capacity_ ?
				0 : capacity_ + capacity_ / 2;

			return max(capacity, size);
		}

		void assign(const Vector& other)
		{
			if (other.size_ == 0)
			{
				clear();
			}
			else if (capacity_ >= other.size_)
			{
				copy(other.v_, other.v_ + min(size_, other.size_), v_);

				if (other.size_ > size_) {
					constructN<T>(v_ + size_, other.size_ - size_, other.v_ + size_);
				}
				else if (other.size_ < size_) {
					destructRange(v_ + other.size_, v_ + size_);
				}

				size_ = other.size_;
			}
			else
			{
				reset(other.makeCopy(other.size_), other.size_, other.size_);
			}
		}

	private:
		size_t size_;
		size_t capacity_;
		T* v_;
	};

	template<typename T, typename Alloc>
	inline void swap(Vector<T, Alloc>& a, Vector<T, Alloc>& b)
	{
		a.swap(b);
	}

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Factory>
	class ArrayNodeImpl : public ArrayNode, private NonCopyable {
	private:
		class Element : public ArrayNode::Element {
		public:
			Element() : value_(0)
			{
			}

			explicit Element(ValueNode* value) : value_(value)
			{
			}

		public:
			virtual ValueNode& value() ECLOG_OVERRIDE
			{
				if (!value_) {
					ECLOG_FAULT(OutOfRange);
				}

				return *value_;
			}

			virtual const ValueNode& value() const ECLOG_OVERRIDE
			{
				if (!value_) {
					ECLOG_FAULT(OutOfRange);
				}

				return *value_;
			}

			virtual void updateValue(const ValueNode& value) ECLOG_OVERRIDE
			{
				ValueNode* p = Factory::create(value);

				Factory::destroy(value_);

				value_ = p;
			}

			virtual void updateValue(const ValueDesc& desc) ECLOG_OVERRIDE
			{
				ValueNode* p = Factory::create(desc);

				Factory::destroy(value_);

				value_ = p;
			}

			virtual Element* prev(ptrdiff_t n = 1) ECLOG_OVERRIDE
			{
				return this - n;
			}

			virtual const Element* prev(ptrdiff_t n = 1) const ECLOG_OVERRIDE
			{
				return this - n;
			}

			virtual Element* next(ptrdiff_t n = 1) ECLOG_OVERRIDE
			{
				return this + n;
			}

			virtual const Element* next(ptrdiff_t n = 1) const ECLOG_OVERRIDE
			{
				return this + n;
			}

			virtual ptrdiff_t distance(const ArrayNode::Element* other) const ECLOG_OVERRIDE
			{
				return (Element*)other - this;
			}

		private:
			ValueNode* value_;
		};

		typedef typename Factory::AllocType Alloc;

	public:
		ArrayNodeImpl()
		{
			v_.pushBack(Element());
		}

		explicit ArrayNodeImpl(const ValueDesc& desc)
		{
			v_.pushBack(Element());

			assign((const ArrayDesc&)desc);
		}

		explicit ArrayNodeImpl(const ArrayNode& other)
		{
			v_.pushBack(Element());

			assign(other);
		}

		~ArrayNodeImpl()
		{
			remove(0, size());
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return node_type_array;
		}

		virtual void clear() ECLOG_OVERRIDE
		{
			remove(0, size());
		}

		virtual bool empty() const ECLOG_OVERRIDE
		{
			return size() == 0;
		}

		virtual size_t size() const ECLOG_OVERRIDE
		{
			return v_.size() - 1;
		}

		virtual Iterator begin() ECLOG_OVERRIDE
		{
			return v_.data();
		}

		virtual Iterator end() ECLOG_OVERRIDE
		{
			return v_.data() + size();
		}

		virtual ConstIterator begin() const ECLOG_OVERRIDE
		{
			return v_.data();
		}

		virtual ConstIterator end() const ECLOG_OVERRIDE
		{
			return v_.data() + size();
		}

		virtual size_t indexOf(const ArrayNode::Element& element) const ECLOG_OVERRIDE
		{
			return v_.indexOf((const Element&)element);
		}

		virtual ArrayNode::Element& at(size_t index) ECLOG_OVERRIDE
		{
			if (index >= size()) {
				ECLOG_FAULT(OutOfRange);
			}

			return v_[index];
		}

		virtual const ArrayNode::Element& at(size_t index) const ECLOG_OVERRIDE
		{
			if (index >= size()) {
				ECLOG_FAULT(OutOfRange);
			}

			return v_[index];
		}

		virtual Iterator insert(Iterator pos, const ArrayNode::Element& element) ECLOG_OVERRIDE
		{
			return insert(pos.get(), element.value());
		}

		virtual Iterator insert(Iterator pos, const ValueNode& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), value);
		}

		virtual Iterator insert(Iterator pos, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return insert(pos.get(), value);
		}

		virtual void remove(Iterator pos) ECLOG_OVERRIDE
		{
			remove(indexOf(*pos), 1);
		}

		virtual void remove(Iterator first, Iterator last) ECLOG_OVERRIDE
		{
			size_t firstIndex = indexOf(*first);
			size_t lastIndex = indexOf(*last);
			size_t count = lastIndex - firstIndex;

			remove(firstIndex, count);
		}

		virtual void remove(size_t index) ECLOG_OVERRIDE
		{
			remove(index, 1);
		}

		virtual void remove(size_t index, size_t count) ECLOG_OVERRIDE
		{
			if (index < size() && count > 0)
			{
				if (count > size() - index) {
					count = size() - index;
				}

				for (size_t i = index; i < index + count; ++i) {
					Factory::destroy(&v_[i].value());
				}

				v_.remove(index, count);
			}
		}

		virtual void assign(const ArrayDesc& desc) ECLOG_OVERRIDE
		{
			ArrayNodeImpl t;

			for (size_t i = 0; i < desc.arraySize(); ++i)
			{
				t.insert(t.end(), desc.array()[i]);
			}

			detail::swap(v_, t.v_);
		}

		virtual void assign(const ArrayNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			ArrayNodeImpl t;

			for (ArrayNode::ConstIterator it = other.begin(); it != other.end(); ++it)
			{
				t.insert(t.end(), it->value());
			}

			detail::swap(v_, t.v_);
		}

	private:
		template<typename V>
		ArrayNode::Element* insert(ArrayNode::Element* pos, const V& valueArg)
		{
			NodePtr<ValueNode, Factory> value(Factory::create(valueArg));

			size_t index = indexOf(*pos);

			v_.insert(index, Element(value.get()));

			value.release();

			return v_.data() + index;
		}

	private:
		Vector<Element, Alloc> v_;
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Alloc>
	class NodeFactory {
	public:
		typedef Alloc AllocType;

	private:
		typedef KeyNodeImpl<Alloc> KeyNodeType;
		typedef NullNodeImpl NullNodeType;
		typedef BooleanNodeImpl BooleanNodeType;
		typedef StringNodeImpl<Alloc> StringNodeType;
		typedef NumberNodeImpl NumberNodeType;
		typedef ObjectNodeImpl<NodeFactory> ObjectNodeType;
		typedef ArrayNodeImpl<NodeFactory> ArrayNodeType;

	public:
		static KeyNode* create(const KeyNode& key)
		{
			return detail::create<KeyNodeType, Alloc>(key);
		}

		static KeyNode* create(const KeyDesc& key)
		{
			return detail::create<KeyNodeType, Alloc>(key);
		}

		static ValueNode* create(const ValueNode& value)
		{
			switch (value.nodeType())
			{
			case node_type_null:
				return detail::create<NullNodeType, Alloc>();

			case node_type_boolean:
				return detail::create<BooleanNodeType, Alloc>((const BooleanNode&)value);

			case node_type_string:
				return detail::create<StringNodeType, Alloc>((const StringNode&)value);

			case node_type_number:
				return detail::create<NumberNodeType, Alloc>((const NumberNode&)value);

			case node_type_object:
				return detail::create<ObjectNodeType, Alloc>((const ObjectNode&)value);

			case node_type_array:
				return detail::create<ArrayNodeType, Alloc>((const ArrayNode&)value);

			default:
				ECLOG_ASSERT(false);
				return 0;
			}
		}

		static ValueNode* create(const ValueDesc& desc)
		{
			switch (desc.type())
			{
			case value_type_null:
				return detail::create<NullNodeType, Alloc>();

			case value_type_boolean:
				return detail::create<BooleanNodeType, Alloc>(desc);

			case value_type_string:
				return detail::create<StringNodeType, Alloc>(desc);

			case value_type_number:
				return detail::create<NumberNodeType, Alloc>(desc);

			case value_type_object:
				return detail::create<ObjectNodeType, Alloc>(desc);

			case value_type_array:
				return detail::create<ArrayNodeType, Alloc>(desc);

			default:
				ECLOG_ASSERT(false);
				return 0;
			}
		}

		static void destroy(Node* ptr)
		{
			switch (ptr->nodeType())
			{
			case node_type_key:
				detail::destroy<KeyNodeType, Alloc>((KeyNodeType*)ptr);
				break;

			case node_type_null:
				detail::destroy<NullNodeType, Alloc>((NullNodeType*)ptr);
				break;

			case node_type_boolean:
				detail::destroy<BooleanNodeType, Alloc>((BooleanNodeType*)ptr);
				break;

			case node_type_string:
				detail::destroy<StringNodeType, Alloc>((StringNodeType*)ptr);
				break;

			case node_type_number:
				detail::destroy<NumberNodeType, Alloc>((NumberNodeType*)ptr);
				break;

			case node_type_object:
				detail::destroy<ObjectNodeType, Alloc>((ObjectNodeType*)ptr);
				break;

			case node_type_array:
				detail::destroy<ArrayNodeType, Alloc>((ArrayNodeType*)ptr);
				break;

			default:
				ECLOG_ASSERT(false);
				break;
			}
		}
	};

} // detail
} // eclog
} // vallest

namespace vallest {
namespace eclog {

	template<typename Alloc>
	class BasicDocument : public ObjectNode {
	public:
		BasicDocument()
		{
		}

		BasicDocument(const ObjectDesc& desc) : impl_(desc)
		{
		}

		BasicDocument(const ObjectNode& other) : impl_(other)
		{
		}

		BasicDocument(const BasicDocument& other) : impl_(other)
		{
		}

		BasicDocument& operator=(const ObjectDesc& desc)
		{
			assign(desc);
			return *this;
		}

		BasicDocument& operator=(const ObjectNode& other)
		{
			assign(other);
			return *this;
		}

		BasicDocument& operator=(const BasicDocument& other)
		{
			assign(other);
			return *this;
		}

		void swap(BasicDocument& other)
		{
			impl_.swap(other.impl_);
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return impl_.nodeType();
		}

		virtual void clear() ECLOG_OVERRIDE
		{
			impl_.clear();
		}

		virtual bool empty() const ECLOG_OVERRIDE
		{
			return impl_.empty();
		}

		virtual size_t size() const ECLOG_OVERRIDE
		{
			return impl_.size();
		}

		virtual Iterator begin() ECLOG_OVERRIDE
		{
			return impl_.begin();
		}

		virtual Iterator end() ECLOG_OVERRIDE
		{
			return impl_.end();
		}

		virtual ConstIterator begin() const ECLOG_OVERRIDE
		{
			return impl_.begin();
		}

		virtual ConstIterator end() const ECLOG_OVERRIDE
		{
			return impl_.end();
		}

		virtual bool contains(cstring key) const ECLOG_OVERRIDE
		{
			return impl_.contains(key);
		}

		virtual Iterator find(cstring key) ECLOG_OVERRIDE
		{
			return impl_.find(key);
		}

		virtual ConstIterator find(cstring key) const ECLOG_OVERRIDE
		{
			return impl_.find(key);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const Element& element) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, element);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const Element& element) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, element);
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual void merge(const ObjectDesc& patch) ECLOG_OVERRIDE
		{
			impl_.merge(patch);
		}

		virtual void merge(const ObjectNode& patch) ECLOG_OVERRIDE
		{
			impl_.merge(patch);
		}

		virtual void remove(Iterator pos) ECLOG_OVERRIDE
		{
			impl_.remove(pos);
		}

		virtual size_t remove(Iterator first, Iterator last) ECLOG_OVERRIDE
		{
			return impl_.remove(first, last);
		}

		virtual bool remove(cstring key) ECLOG_OVERRIDE
		{
			return impl_.remove(key);
		}

		virtual void parse(Context& ctx) ECLOG_OVERRIDE
		{
			impl_.parse(ctx);
		}

		virtual void parse(Context& ctx, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(ctx, ec);
		}

		virtual void parse(InputStream& stream) ECLOG_OVERRIDE
		{
			impl_.parse(stream);
		}

		virtual void parse(InputStream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(stream, ec);
		}

		virtual void parse(cstring str) ECLOG_OVERRIDE
		{
			impl_.parse(str);
		}

		virtual void parse(cstring str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(str, ec);
		}

		virtual void parse(std::istream& stream) ECLOG_OVERRIDE
		{
			impl_.parse(stream);
		}

		virtual void parse(std::istream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(stream, ec);
		}

		virtual void parse(const std::string& str) ECLOG_OVERRIDE
		{
			impl_.parse(str);
		}

		virtual void parse(const std::string& str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(str, ec);
		}

		virtual void parse(const char* str) ECLOG_OVERRIDE
		{
			impl_.parse(str);
		}

		virtual void parse(const char* str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(str, ec);
		}

		virtual void render(OutputStream& stream) const ECLOG_OVERRIDE
		{
			impl_.render(stream);
		}

		virtual void render(OutputStream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, ec);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc, ec);
		}

		virtual void render(std::ostream& stream) const ECLOG_OVERRIDE
		{
			impl_.render(stream);
		}

		virtual void render(std::ostream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, ec);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc, ec);
		}

		virtual void assign(const ObjectDesc& desc) ECLOG_OVERRIDE
		{
			impl_.assign(desc);
		}

		virtual void assign(const ObjectNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			impl_.assign(other);
		}

	private:
		detail::ObjectNodeImpl<detail::NodeFactory<Alloc> > impl_;
	};

	template<typename Alloc>
	inline void swap(BasicDocument<Alloc>& a, BasicDocument<Alloc>& b)
	{
		a.swap(b);
	}

	typedef BasicDocument<ECLOG_DEFAULT_ALLOCATOR> Document;

} // eclog
} // vallest

#endif // ECLOG_CPP_H_

