# KeyDesc

```c++
class KeyDesc
```

Required header: `<Eclog/KeyDesc.h>`

The [KeyDesc](KeyDesc.md) class is a description of a key that is going to be inserted into a document (See [ObjectNode](ObjectNode.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
KeyDesc(const char* str);

KeyDesc(cstring str,
    StringNotation notation = string_notation_unquoted,
    cstring delimiter = cstring());
```

Constructs a [KeyDesc](KeyDesc.md).

#### Parameters

`const char*` **str** The key.

[cstring](cstring.md) **str** The key.

[StringNotation](StringNotation.md) **notation** The string notation to be used when rendering the key.

[cstring](cstring.md) **delimiter** The string delimiter to be used when rendering the key.

#### Errors

An `InvalidArgument` fault occurs if **str** is empty or **delimiter** is invalid.

