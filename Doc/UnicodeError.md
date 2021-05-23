# UnicodeError

```c++
class UnicodeError
```

Inherited from: [Error](Error.md).
Inherited by: [DecodeError](DecodeError.md), and [EncodeError](EncodeError.md).

Required header: `<Eclog/Error.h>`

The [UnicodeError](UnicodeError.md) class defines a type of error object that reports Unicode errors.

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