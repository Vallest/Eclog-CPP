# Null

```c++
class Null
```

Required header: `<Eclog/Null.h>`

The [Null](Null.md) class represents a null.

## Member functions

| Name | Description |
| ---- | ---- |
| [operator==](#operator-operator-operator-operator-operator-and-operator) | Returns *true*. |
| [operator!=](#operator-operator-operator-operator-operator-and-operator) | Returns *false*. |

* * *

### operator== and operator!=

```c++
bool operator==(const Null&) const;                                 (1)
bool operator!=(const Null&) const;                                 (2)
```

Null has only one value, which is *null*; therefore, (1) always returns *true*, and (2) always returns *false*.

