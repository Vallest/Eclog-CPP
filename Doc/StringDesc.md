# StringDesc

```c++
class StringDesc
```

Inherited from: [ValueDesc](ValueDesc.md).

Required header: `<Eclog/StringDesc.h>`

The [StringDesc](StringDesc.md) class is a description of a string.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
StringDesc(const char* value);

StringDesc(cstring value,
    StringNotation notation = string_notation_quoted,
    cstring delimiter = cstring());
```

Constructs a [StringDesc](StringDesc.md).

#### Parameters

`const char*` **value** A C-style string.

[cstring](cstring.md) **value** A string.

[StringNotation](StringNotation.md) **notation** The string notation to be used when rendering the string.

[cstring](cstring.md) **delimiter** The string delimiter to be used when rendering the string.

#### Errors

An `InvalidArgument` fault occurs if **delimiter** is invalid.

