# Node

```c++
class Node
```

Inherited by: [KeyNode](KeyNode.md), and [ValueNode](ValueNode.md).

Required header: `<Eclog/Node.h>`

The [Node](Node.md) abstract class represents a node in a document tree (See [Document](Document.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [nodeType](#nodetype) | Gets the type of this node. |

* * *

### nodeType

```c++
virtual NodeType nodeType() const;
```

Gets the type of this node.

#### Return value

[NodeType](NodeType.md) The type of this node.


