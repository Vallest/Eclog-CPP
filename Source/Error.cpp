// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#include <Eclog/Error.h>
#include <Eclog/Detail/Assert.h>

#define ECLOG_DEFINE_ERROR_ID(Class, Id) \
	const ErrorId& Class::id() \
	{ \
		static ErrorId errid(Id); \
		return errid; \
	}

namespace vallest {
namespace eclog {

	ECLOG_DEFINE_ERROR_ID(Error, "Error")
	ECLOG_DEFINE_ERROR_ID(RuntimeError, "RuntimeError")
	ECLOG_DEFINE_ERROR_ID(BufferOverflow, "BufferOverflow")
	ECLOG_DEFINE_ERROR_ID(LogicError, "LogicError")
	ECLOG_DEFINE_ERROR_ID(OutOfRange, "OutOfRange")
	ECLOG_DEFINE_ERROR_ID(LengthError, "LengthError")
	ECLOG_DEFINE_ERROR_ID(InvalidArgument, "InvalidArgument")
	ECLOG_DEFINE_ERROR_ID(InvalidOperation, "InvalidOperation")
	ECLOG_DEFINE_ERROR_ID(IOError, "IOError")
	ECLOG_DEFINE_ERROR_ID(UnicodeError, "UnicodeError")
	ECLOG_DEFINE_ERROR_ID(DecodeError, "DecodeError")
	ECLOG_DEFINE_ERROR_ID(EncodeError, "EncodeError")
	ECLOG_DEFINE_ERROR_ID(OutOfMemory, "OutOfMemory")
	ECLOG_DEFINE_ERROR_ID(ParseError, "ParseError")
	ECLOG_DEFINE_ERROR_ID(BadCast, "BadCast")

	const char* getErrorMessage(Success)
	{
		return "success";
	}

	const char* getErrorMessage(ErrorCodeEnum e)
	{
		switch (e)
		{
		case ec_runtime_error:
			return "runtime error";

		case ec_buffer_overflow:
			return "buffer overflow";

		case ec_logic_error:
			return "logic error";

		case ec_out_of_range:
			return "out of range";

		case ec_length_error:
			return "length error";

		case ec_invalid_argument:
			return "invalid argument";

		case ec_invalid_operation:
			return "invalid operation";

		case ec_io_error:
			return "io error";

		case ec_unicode_error:
			return "unicode error";

		case ec_decode_error:
			return "decode error";

		case ec_encode_error:
			return "encode error";

		case ec_out_of_memory:
			return "out of memory";

		case ec_parse_error:
			return "parse error";

		case ec_bad_cast:
			return "bad cast";

		default:
			ECLOG_ASSERT(false);
			return "";
		}
	}

	const char* getErrorMessage(ParseErrorEnum e)
	{
		switch (e)
		{
		case pe_unexpected_end_of_file:
			return "unexpected end of file";

		case pe_unexpected_character:
			return "unexpected character";

		case pe_unrecognized_escape:
			return "unrecognized escape";

		case pe_invalid_unicode_escape:
			return "invalid unicode escape";

        case pe_invalid_utf16_surrogate:
            return "invalid UTF-16 surrogate";

		case pe_unescaped_control_character:
			return "unescaped control character";

		case pe_string_delimiter_too_long:
			return "string delimiter too long";

		case pe_invalid_string_delimiter:
			return "invalid string delimiter";

		case pe_empty_string_delimiter:
			return "empty string delimiter";

		case pe_invalid_key:
			return "invalid key";

		case pe_user_asked_for_termination:
			return "user asked for termination";

		default:
			ECLOG_ASSERT(false);
			return "";
		}
	}

	const ErrorId& getErrorId(ErrorCodeEnum e)
	{
		switch (e)
		{
		case ec_runtime_error:
			return RuntimeError::id();

		case ec_buffer_overflow:
			return BufferOverflow::id();

		case ec_logic_error:
			return LogicError::id();

		case ec_out_of_range:
			return OutOfRange::id();

		case ec_length_error:
			return LengthError::id();

		case ec_invalid_argument:
			return InvalidArgument::id();

		case ec_invalid_operation:
			return InvalidOperation::id();

		case ec_io_error:
			return IOError::id();

		case ec_unicode_error:
			return UnicodeError::id();

		case ec_decode_error:
			return DecodeError::id();

		case ec_encode_error:
			return EncodeError::id();

		case ec_out_of_memory:
			return OutOfMemory::id();

		case ec_parse_error:
			return ParseError::id();

		case ec_bad_cast:
			return BadCast::id();

		default:
			ECLOG_ASSERT(false);
			return Error::id();
		}
	}

	template<typename T>
	const T* getDefaultError(typename detail::EnableIf<detail::IsBaseOf<Error, T> >::Type*)
	{
		static T err;
		return &err;
	}

	template const RuntimeError* getDefaultError(void*);
	template const BufferOverflow* getDefaultError(void*);
	template const LogicError* getDefaultError(void*);
	template const OutOfRange* getDefaultError(void*);
	template const LengthError* getDefaultError(void*);
	template const InvalidArgument* getDefaultError(void*);
	template const InvalidOperation* getDefaultError(void*);
	template const IOError* getDefaultError(void*);
	template const UnicodeError* getDefaultError(void*);
	template const DecodeError* getDefaultError(void*);
	template const EncodeError* getDefaultError(void*);
	template const OutOfMemory* getDefaultError(void*);
	template const BadCast* getDefaultError(void*);

} // eclog
} // vallest

