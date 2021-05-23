# BufferOverflow

```c++
class BufferOverflow
```

Inherited from: [RuntimeError](RuntimeError.md).

Required header: `<Eclog/Error.h>`

The [BufferOverflow](BufferOverflow.md) class defines a type of error object that reports buffer overflow errors.

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