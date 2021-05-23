# ErrorId

```c++
class ErrorId
```

Required header: `<Eclog/Error.h>`

The [ErrorId](ErrorId.md) class represents an unique identifier of an error (See [Error](Error.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [operator==](#operator-operator) | Compares the identifier with another identifier. |
| [operator!=](#operator-operator) | Compares the identifier with another identifier. |

* * *

### operator==, operator!=

```c++
bool operator==(const ErrorId& other) const;
bool operator!=(const ErrorId& other) const;
```

Compares the identifier with another identifier.

#### Parameters

`const` [ErrorId](ErrorId.md)`&` **other** Another error identifier.

#### Return value

`bool` *true* if the corresponding comparison holds, *false* otherwise.

