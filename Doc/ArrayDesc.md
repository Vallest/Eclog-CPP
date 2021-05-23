# ArrayDesc

```c++
class ArrayDesc
```

Inherited from: [ValueDesc](ValueDesc.md).

Required header: `<Eclog/ArrayDesc.h>`

The [ArrayDesc](ArrayDesc.md) class is a description of an array.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
ArrayDesc(EmptyArrayTag);                                           (1)
ArrayDesc(const ValueDesc* p, size_t size);                         (2)

template<size_t N>
ArrayDesc(const ValueDesc(&v)[N]);                                  (3)
```

Constructs an [ArrayDesc](ArrayDesc.md).

(1) Constructs the value description for an empty array.

(2-3) Constructs the value description for an array.

#### Parameters

[EmptyArrayTag](EmptyArrayTag.md) Tag dispatching.

`const` [ValueDesc](ValueDesc.md)`*` **p** Pointer to an array of value descriptions.

`const` [ValueDesc](ValueDesc.md)`(&`**v**`)[N]` An array of value descriptions.

`size_t` **size** Size of the description array.

