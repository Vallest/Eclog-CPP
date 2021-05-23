# ErrorCode

```c++
class ErrorCode
```

Required header: `<Eclog/Error.h>`

The [ErrorCode](ErrorCode.md) class represents an error code, which can be compared to *success* (See [Success](Success.md)) or a named constant in the error code enumeration (See [ErrorCodeEnum](ErrorCodeEnum.md)). An error code also holds an error object (See [Error](Error.md)), which can provide structured error information like an exception.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [destructor](#destructor) | Destructor. |
| [operator=](#operator) | Copy assignment. |
| [operator bool](#operator-bool) | Checks if the error code is not equal to *success*. |
| [operator!](#operator-1) | Checks if the error code is equal to *success*. |
| [operator==](#operator-and-operator) | Compares the error code with another error code or a named constant. |
| [operator!=](#operator-and-operator) | Compares the error code with another error code or a named constant. |
| [message](#message) | Gets the error message. |
| [error](#error) | Gets the error object. |

* * *

## Non-member functions

| Name | Description |
| ---- | ---- |
| [operator==](#operator-and-operator-1) | Compares a named constant with an error code. |
| [operator!=](#operator-and-operator-1) | Compares a named constant with an error code. |
| [operator<<](#operator-2) | Insert error message into stream. |

* * *

### (constructor)

```c++
ErrorCode();                                                        (1)
ErrorCode(const ErrorCode& other);                                  (2)
```

Constructs an [ErrorCode](ErrorCode.md).

(1) Default constructor. Constructs an error code equal to *success* (See [Success](Success.md)).

(2) Copy constructor.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **other** Another error code.

* * *

### (destructor)

```c++
~ErrorCode();
```

Destroys the [ErrorCode](ErrorCode.md).

* * *

### operator=

```c++
ErrorCode& operator=(const ErrorCode& other);
```

Copy assignment.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **other** Another error code.

#### Return value

[ErrorCode](ErrorCode.md)`&` Reference to `*this`.

* * *

### operator bool

```c++
operator BoolType() const;
```

Checks if the error code is not equal to *success* (See [Success](Success.md)).

#### Return value

`BoolType` *true* if the error code is not equal to *success*, *false* otherwise.

* * *

### operator!

```c++
bool operator!() const;
```

Checks if the error code is equal to *success* (See [Success](Success.md)).

#### Return value

`BoolType` *true* if the error code is equal to *success*, *false* otherwise.

* * *

### operator== and operator!=

```c++
bool operator==(const ErrorCode& other) const;
bool operator!=(const ErrorCode& other) const;
bool operator==(ErrorCodeEnum e) const;
bool operator!=(ErrorCodeEnum e) const;
bool operator==(Success) const;
bool operator!=(Success) const;
```

Compares the error code with another error code or a named constant.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **other** Another error code to compare.

[ErrorCodeEnum](ErrorCodeEnum.md) **e** Named constant to compare.

[Success](Success.md) Success to compare.

#### Return value

`bool` *true* if the corresponding comparison holds, *false* otherwise.


* * *

### message

```c++
const char* message() const;
```

Gets the error message.

#### Return value

`const char*` The error message.

* * *

### error

```c++
const Error& error() const;
```

Gets the error object.

#### Return value

`const` [Error](Error.md)`&` Reference to the error object.

* * *

### operator== and operator!=

```c++
bool operator==(Success a, const ErrorCode& b);
bool operator!=(Success a, const ErrorCode& b);
bool operator==(ErrorCodeEnum a, const ErrorCode& b);
bool operator!=(ErrorCodeEnum a, const ErrorCode& b);
```

Compares a named constant with an error code.

#### Parameters

[Success](Success.md) **a** Success to compare.

[ErrorCodeEnum](ErrorCodeEnum.md) **a** Named constant to compare.

`const` [ErrorCode](ErrorCode.md)`&` **b** Error code to compare.

#### Return value

`bool` *true* if the corresponding comparison holds, *false* otherwise.

* * *

### operator<<

```c++
std::ostream& operator<<(std::ostream& stream, const ErrorCode& ec);
```

Insert error message into stream.

#### Parameters

`std::ostream&` **stream** The stream where characters are inserted.

`const` [ErrorCode](ErrorCode.md)`&` **ec** Error code to get the error message from.

#### Return value

`std::ostream&` The same as parameter **stream**.

