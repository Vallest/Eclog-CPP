# RuntimeError

```c++
class RuntimeError
```

Inherited from: [Error](Error.md).
Inherited by: [BufferOverflow](BufferOverflow.md).

Required header: `<Eclog/Error.h>`

The [RuntimeError](RuntimeError.md) class defines a type of error object that reports runtime errors.

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

