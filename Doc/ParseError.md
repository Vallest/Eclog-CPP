# ParseError

```c++
class ParseError
```

Inherited from: [Error](Error.md).

Required header: `<Eclog/Error.h>`

The [ParseError](ParseError.md) class defines a type of error object that reports parse errors.

## Member functions

| Name | Description |
| ---- | ---- |
| [line](#line) | Returns the line number the parse error occurs. |
| [column](#column) | Returns the column number the parse error occurs. |
| [error](#error) | Returns the parse error code. |
| [id](#id) | Returns the identifier of this class. |

* * *

### line

```c++
int line() const;
```

Returns the line number the parse error occurs.

#### Return value

`int` The line number the parse error occurs.

* * *

### column

```c++
int column() const;
```

Returns the column number the parse error occurs.

#### Return value

`int` The column number the parse error occurs.

* * *

### error

```c++
ParseErrorEnum error() const
```

Returns the parse error code.

#### Return value

[ParseErrorEnum](ParseErrorEnum.md) The parse error code.

* * *

### id

```c++
static const ErrorId& id();
```

Returns the identifier of this class.

#### Return value

[ErrorId](ErrorId.md)`&` Reference to the identifier.

