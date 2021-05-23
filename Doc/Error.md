# Error

```c++
class Error
```

Inherited by: [BadCast](BadCast.md), [IOError](IOError.md), [LogicError](LogicError.md), [OutOfMemory](OutOfMemory.md), [ParseError](ParseError.md), [RuntimeError](RuntimeError.md), and [UnicodeError](UnicodeError.md).

Required header: `<Eclog/Error.h>`

The [Error](Error.md) abstract class provides a consistent interface for the error inheritance hierarchy.

Each specific type of error has a corresponding named constant in the error code enumeration (See [ErrorCodeEnum](ErrorCodeEnum.md)) and a unique identifier (See [ErrorId](ErrorId.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [isA](#isa) | Checks if the error object is of a specific type. |
| [getId](#getid) | Gets the identifier of the error. |
| [equals](#equals) | Compares the error with another error. |
| [clone](#clone) | Makes a copy of the error. |
| [message](#message) | Gets the error message. |
| [id](#id) | Returns the identifier of this class. |

* * *

## Non-member functions

| Name | Description |
| ---- | ---- |
| [cast](#cast) | Converts an error object up and down along the inheritance hierarchy. |

* * *

### isA

```c++
template<typename T>
bool isA() const;

virtual bool isA(const ErrorId& id) const;
```

Checks if the error object is of a specific type (or a subtype of a specific type).

#### Template parameters

`T` The type of error to compare to.

#### Parameters

`const` [ErrorId](ErrorId.md)`&` **id** Reference to an error identifier.

#### Return value

`bool` *true* if the error object is of the specific type, *false* otherwise.

* * *

### getId

```c++
virtual const ErrorId& getId() const;
```

Gets the identifier of the error.

#### Return value

[ErrorId](ErrorId.md)`&` Reference to the identifier.

* * *

### equals

```c++
virtual bool equals(const Error* other, bool strict) const;
```

Compares the error with another error.

If **strict** is false, this function will compare only two error identifiers. Otherwise, the details of the two errors will be further compared.

#### Parameters

`const` [Error](Error.md)`*` **other** Pointer to another error.

`bool` **strict** Strict mode.

#### Return value

`bool` *true* if the error is equal to **other**, *false* otherwise.

* * *

### clone

```c++
virtual const Error* clone() const;
```

Makes a copy of the error object.

#### Return value

`const` [Error](Error.md)`*` Pointer to the copy.

* * *

### message

```c++
virtual const char* message() const;
```

Gets the error message.

#### Return value

`const char*` The error message.

* * *

### id

```c++
static const ErrorId& id();
```

Returns the identifier of this class.

#### Return value

[ErrorId](ErrorId.md)`&` Reference to the identifier.

* * *

### cast

```c++
template<typename T>
const T& cast(const Error& err);
```

Converts an error object up and down along the inheritance hierarchy.

#### Template parameters

`T` The type of error to cast to.

#### Parameters

`const` [Error](Error.md)`&` **err** An error object to cast.

#### Return value

`const T&` Reference to the error object.

#### Error

A `BadCast` fault occurs if the error object is not of the specific type.

