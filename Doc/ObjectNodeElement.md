# ObjectNode::Element

```c++
class ObjectNode::Element
```

The [ObjectNode::Element](ObjectNodeElement.md) abstract class provides an interface for accessing an element (key-value pair) in an object node (See [ObjectNode](ObjectNode.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [key](#key) | Gets the key of the element. |
| [value](#value) | Gets the value of the element. |
| [updateValue](#updateValue) | Updates the value.             |

* * *

### key

```c++
virtual KeyNode& key();
virtual const KeyNode& key() const;
```

Gets the key of the element.

#### Return value

[KeyNode](KeyNode.md)`&` Reference to the key node.

`const` [KeyNode](KeyNode.md)`&` Reference to the key node.

* * *

### value

```c++
virtual ValueNode& value();
virtual const ValueNode& value() const;
```

Gets the value of the element.

#### Return value

[ValueNode](ValueNode.md)`&` Reference to the value node.

`const` [ValueNode](ValueNode.md)`&` Reference to the value node.

* * *

### updateValue

```c++
virtual void updateValue(const ValueNode& value);
virtual void updateValue(const ValueDesc& desc);
```

Updates the value.

#### Parameters

`const` [ValueNode](ValueNode.md)`&` **value** A value node.

`const` [ValueDesc](ValueDesc.md)`&` **desc** A value description.

