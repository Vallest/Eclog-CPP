# Key

```c++
class Key
```

Inherited from: [cstring](cstring.md).

Required header: `<Eclog/Key.h>`

The [Key](Key.md) class represents an encountered key while parsing.

## Member functions

| Name | Description |
| ---- | ---- |
| [notation](#notation) | Gets the string notation of this key. |
| [delimiter](#delimiter) | Gets the string delimiter of this key. |

* * *

### notation

```c++
StringNotation notation() const;
```

Gets the string notation of this key.

#### Return value

[StringNotation](StringNotation.md) The string notation.

* * *

### delimiter

```c++
cstring delimiter() const;
```

Gets the string delimiter of this key (Only meaningful for raw string and heredoc string).

#### Return value

[cstring](cstring.md) The string delimiter.

