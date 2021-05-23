# ValueNode

```c++
class ValueNode
```

Inherited from: [Node](Node.md).
Inherited by: [NullNode](NullNode.md), [BooleanNode](BooleanNode.md), [StringNode](StringNode.md), [NumberNode](NumberNode.md), [ObjectNode](ObjectNode.md), and [ArrayNode](ArrayNode.md).

Required header: `<Eclog/ValueNode.h>`

The [ValueNode](ValueNode.md) abstract class represents a value node in a document tree (See [Document](Document.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [isNull](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this node is a null node. |
| [isBoolean](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this node is a Boolean node. |
| [isString](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this node is a string node. |
| [isNumber](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this node is a number node. |
| [isObject](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this node is an object node. |
| [isArray](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this node is an array node. |
| [asNull](#asnull-asboolean-asstring-asnumber-asobject-and-asarray) | Casts this node to a null node. |
| [asBoolean](#asnull-asboolean-asstring-asnumber-asobject-and-asarray) | Casts this node to a Boolean node. |
| [asString](#asnull-asboolean-asstring-asnumber-asobject-and-asarray) | Casts this node to a string node. |
| [asNumber](#asnull-asboolean-asstring-asnumber-asobject-and-asarray) | Casts this node to a number node. |
| [asObject](#asnull-asboolean-asstring-asnumber-asobject-and-asarray) | Casts this node to an object node. |
| [asArray](#asnull-asboolean-asstring-asnumber-asobject-and-asarray) | Casts this node to an array node. |

* * *

### isNull, isBoolean, isString, isNumber, isObject, and isArray

```c++
bool isNull() const;
bool isBoolean() const;
bool isString() const;
bool isNumber() const;
bool isObject() const;
bool isArray() const;
```

Determines whether this node is of a specified type.

#### Return value

`bool` *true* if this node is of the specified type, *false* otherwise.

* * *

### asNull, asBoolean, asString, asNumber, asObject, and asArray

```c++
NullNode& asNull();
const NullNode& asNull() const;
BooleanNode& asBoolean();
const BooleanNode& asBoolean() const;
StringNode& asString();
const StringNode& asString() const;
NumberNode& asNumber();
const NumberNode& asNumber() const;
ObjectNode& asObject();
const ObjectNode& asObject() const;
ArrayNode& asArray();
const ArrayNode& asArray() const;
```

Casts this node to a specific type.

#### Return value

(node type)`&` Reference to this node.

`const` (node type)`&` Reference to this node.

#### Errors

A `BadCast` fault occurs if this node is not of the specified type.

