# InvalidArgument

```c++
class InvalidArgument
```

Inherited from: [LogicError](LogicError.md).

Required header: `<Eclog/Error.h>`

The [InvalidArgument](InvalidArgument.md) class defines a type of error object that reports invalid argument errors.

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