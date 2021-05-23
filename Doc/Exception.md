# Exception

```c++
class Exception
```

Inherited from: `std::exception`.
Inherited by: [BadCastException](BadCastException.md), [IOErrorException](IOErrorException.md), [LogicErrorException](LogicErrorException.md), [OutOfMemoryException](OutOfMemoryException.md), [ParseErrorException](ParseErrorException.md), [RuntimeErrorException](RuntimeErrorException.md), and [UnicodeErrorException](UnicodeErrorException.md).

Required header: `<Eclog/Error.h>`

The [Exception](Exception.md) class defines a type of object to be thrown as exception. It is the superclass of all exceptions.

## Member functions

| Name | Description |
| ---- | ---- |
| [what](#what) | Gets the error message. |

* * *

### what

```c++
virtual const char* what() const throw();
```

Gets the error message.

#### Return value

`const char*` The error message.

