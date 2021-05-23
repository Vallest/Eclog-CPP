# ObjectDesc

```c++
class ObjectDesc
```

Inherited from: [ValueDesc](ValueDesc.md).

Required header: `<Eclog/ObjectDesc.h>`

The [ObjectDesc](ObjectDesc.md) class is a description of an object.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
ObjectDesc(EmptyObjectTag);                                          (1)
ObjectDesc(const Pair<KeyDesc, ValueDesc>* p, size_t size);          (2)

template<size_t N>
ObjectDesc(const Pair<KeyDesc, ValueDesc>(&v)[N]);                   (3)
```

Constructs an [ObjectDesc](ObjectDesc.md).

(1) Constructs the value description for an empty object.

(2-3) Constructs the value description for an object.

#### Parameters

[EmptyObjectTag](EmptyObjectTag.md) Tag dispatching.

`const` [Pair](Pair.md)`<`[KeyDesc](KeyDesc.md)`,` [ValueDesc](ValueDesc.md)`>*` **p** Pointer to an array of key-value description pairs.

`const` [Pair](Pair.md)`<`[KeyDesc](KeyDesc.md)`,` [ValueDesc](ValueDesc.md)`> (&`**v**`)[N]` An array of key-value description pairs.

`size_t` **size** Size of the description array.

