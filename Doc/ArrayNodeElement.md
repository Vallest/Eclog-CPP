# ArrayNode::Element

```c++
class ArrayNode::Element
```

The [ArrayNode::Element](ArrayNodeElement.md) abstract class provides an interface for accessing an element (value) in an array node (See [ArrayNode](ArrayNode.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [value](#value) | Gets the value. |
| [updateValue](#updateValue) | Updates the value. |

* * *

### value

```c++
virtual ValueNode& value();
virtual const ValueNode& value() const;
```

Gets the value.

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

