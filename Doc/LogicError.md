# LogicError

```c++
class LogicError
```

Inherited from: [Error](Error.md).
Inherited by: [InvalidArgument](InvalidArgument.md), [InvalidOperation](InvalidOperation.md), [LengthError](LengthError.md), and [OutOfRange](OutOfRange.md).

Required header: `<Eclog/Error.h>`

The [LogicError](LogicError.md) class defines a type of error object that reports logic errors.

## Member functions

| Name      | Description                           |
| --------- | ------------------------------------- |
| [id](#id) | Returns the identifier of this class. |

* * *

### id

```c++
static const ErrorId& id();
```

Returns the identifier of this class.

#### Return value

[ErrorId](ErrorId.md)`&` Reference to the identifier.