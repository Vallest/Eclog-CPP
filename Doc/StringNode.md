# StringNode

```c++
class StringNode
```

Inherited from: [ValueNode](ValueNode.md).

Required header: `<Eclog/StringNode.h>`

The [StringNode](StringNode.md) abstract class represents a string node in a document tree (See [Document](Document.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [value](#value) | Gets the value. |
| [setNotation](#setnotation) | Sets the string notation to be used when rendering the string. |
| [notation](#notation) | Gets the string notation to be used when rendering the string. |
| [setDelimiter](#setdelimiter) | Sets the string delimiter to be used when rendering the string. |
| [delimiter](#delimiter) | Gets the string delimiter to be used when rendering the string. |
| [toStdString](#tostdstring) | Returns the value as a C++ string. |
| [assign](#assign) | Assigns a new value to this node. |

* * *

### value

```c++
virtual cstring value() const;
```

Gets the value.

#### Return value

[cstring](cstring.md) The value.

* * *

### setNotation

```c++
virtual void setNotation(StringNotation notation);
```

Sets the string notation to be used when rendering the string.

#### Parameters

[StringNotation](StringNotation.md) **notation** The string notation.

* * *

### notation

```c++
virtual StringNotation notation() const;
```

Gets the string notation to be used when rendering the string.

#### Return value

[StringNotation](StringNotation.md)  The string notation.

* * *

### setDelimiter

```c++
virtual void setDelimiter(cstring delimiter);
virtual void setDelimiter(cstring delimiter, ErrorCode& ec);
```

Sets the string delimiter to be used when rendering the string.

#### Parameters

[cstring](cstring.md) **delimiter** The string delimiter.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidArgument` error occurs if **delimiter** is invalid.

* * *

### delimiter

```c++
virtual cstring delimiter() const;
```

Gets the string delimiter to be used when rendering the string.

#### Return value

[cstring](cstring.md) The string delimiter.

* * *

### toStdString

```c++
std::string toStdString() const;
```

Returns the value as a C++ string.

#### Return value

`std::string` The value as a C++ string.

* * *

### assign

```c++
virtual void assign(const StringDesc& desc);
virtual void assign(const StringNode& other);
```

Assigns a new value to this node.

#### Parameters

`const` [StringDesc](StringDesc.md)`&` A string description.

`const` [StringNode](StringNode.md)`&` **other** Another string node.

#### Errors

If an error occurs, the value of this node remains untouched.

