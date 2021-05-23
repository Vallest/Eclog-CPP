# IOError

```c++
class IOError
```

Inherited from: [Error](Error.md).

Required header: `<Eclog/Error.h>`

The [IOError](IOError.md) class defines a type of error object that reports IO errors.

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