# BooleanNode

```c++
class BooleanNode
```

Inherited from: [ValueNode](ValueNode.md).

Required header: `<Eclog/BooleanNode.h>`

The [BooleanNode](BooleanNode.md) abstract class represents a Boolean node in a document tree (See [Document](Document.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [value](#value) | Gets the value. |
| [assign](#assign) | Assigns a new value to this node. |

* * *

### value

```c++
virtual bool value() const;
```

Gets the value.

#### Return value

`bool` The value.

* * *

### assign

```c++
virtual void assign(bool value);
virtual void assign(const BooleanNode& other);
```

Assigns a new value to this node.

#### Parameters

`bool` **value** A Boolean value.

[BooleanNode](BooleanNode.md)`&` **other** Another Boolean node.


