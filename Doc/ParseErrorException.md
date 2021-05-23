# ParseErrorException

```c++
class ParseErrorException
```

Inherited from: [Exception](Exception.md).

The [ParseErrorException](ParseErrorException.md) class defines a type of exception object that reports parse errors.

## Member functions

| Name | Description |
| ---- | ---- |
| [lineNumber](#linenumber) | Returns the line number the parse error occurs. |
| [columnNumber](#columnnumber) | Returns the column number the parse error occurs. |
| [error](#error) | Returns the parse error code. |

* * *

### lineNumber

```c++
int lineNumber() const;
```

Returns the line number the parse error occurs.

#### Return value

`int` The line number the parse error occurs.

* * *

### columnNumber

```c++
int columnNumber() const;
```

Returns the column number the parse error occurs.

#### Return value

`int` The column number the parse error occurs.

* * *

### error

```c++
ParseErrorEnum error() const;
```

Returns the parse error code.

#### Return value

[ParseErrorEnum](ParseErrorEnum.md) The parse error code.



