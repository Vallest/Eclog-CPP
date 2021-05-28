// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_ERROR_H_
#define ECLOG_CPP_ERROR_H_

#include <Eclog/Detail/NonCopyable.h>
#include <Eclog/Detail/CompilerSpecific.h>
#include <Eclog/Detail/TypeTraits.h>
#include <Eclog/Detail/SafeBool.h>
#include <Eclog/Detail/Utility.h>

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
	if (ec) { *ec = eclog::makeErrorCode<eclog::Name>(__VA_ARGS__); } \
	else { ECLOG_THROW(eclog::Name##Exception, __VA_ARGS__); }

#define ECLOG_FAULT(Name, ...) \
	ECLOG_THROW(eclog::Name##Exception, __VA_ARGS__)

#if defined(_MSC_VER) && _MSC_VER <= 1600
	#define ECLOG_NOTHROW
#else
	#define ECLOG_NOTHROW throw()
#endif

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
		pe_empty_key,
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

}

#endif // ECLOG_CPP_ERROR_H_

