# KeyNode

```c++
class KeyNode
```

Inherited from: [Node](Node.md).

Required header: `<Eclog/KeyNode.h>`

The [KeyNode](KeyNode.md) abstract class represents a key node in a document tree (See [Document](Document.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [str](#str) | Gets the key. |
| [setNotation](#setnotation) | Sets the string notation. |
| [notation](#notation) | Gets the string notation. |
| [setDelimiter](#setdelimiter) | Sets the string delimiter. |
| [delimiter](#delimiter) | Gets the string delimiter. |

* * *

### str

```c++
virtual cstring str() const;
```

Gets the key.

#### Return value

[cstring](cstring.md) The key.

* * *

### setNotation

```c++
virtual void setNotation(StringNotation notation);
```

Sets the string notation.

#### Parameters

[StringNotation](StringNotation.md) **notation** The string notation to be used when rendering the key.

* * *

### notation

```c++
virtual StringNotation notation() const;
```

Gets the string notation.

#### Return value

[StringNotation](StringNotation.md) The string notation to be used when rendering the key.


* * *


### setDelimiter

```c++
virtual void setDelimiter(cstring delimiter);
virtual void setDelimiter(cstring delimiter, ErrorCode& ec);
```

Sets the string delimiter.

#### Parameters

[cstring](cstring.md) **delimiter** The string delimiter to be used when rendering the key.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidArgument` error occurs if **delimiter** is invalid.

* * *

### delimiter

```c++
virtual cstring delimiter() const;
```

Gets the string delimiter.

#### Return value

[cstring](cstring.md) The string delimiter to be used when rendering the key.



