# NullNode

```c++
class NullNode
```

Inherited from: [ValueNode](ValueNode.md).

Required header: `<Eclog/NullNode.h>`

The [NullNode](NullNode.md) abstract class represents a null node in a document tree (See [Document](Document.md)).

## Member functions

| Name              | Description     |
| ----------------- | --------------- |
| [value](#value)   | Returns *null*. |
| [assign](#assign) | Does nothing.   |

* * *

### value

```c++
virtual Null value() const;
```

Returns *null*.

* * *

### assign

```c++
virtual void assign(const Null&);
virtual void assign(const NullNode&);
```

Does nothing.

