# OutOfRange

```c++
class OutOfRange
```

Inherited from: [LogicError](LogicError.md).

Required header: `<Eclog/Error.h>`

The [OutOfRange](OutOfRange.md) class defines a type of error object that reports out-of-range errors.

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