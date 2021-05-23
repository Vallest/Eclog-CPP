# OutOfMemory

```c++
class OutOfMemory
```

Inherited from: [Error](Error.md).

Required header: `<Eclog/Error.h>`

The [OutOfMemory](OutOfMemory.md) class defines a type of error object that reports out-of-memory errors.

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