# ValueDesc

```c++
class ValueDesc
```

Inherited by: [StringDesc](StringDesc.md), [NumberDesc](NumberDesc.md), [ObjectDesc](ObjectDesc.md), and [ArrayDesc](ArrayDesc.md).

Required header: `<Eclog/ValueDesc.h>`

The [ValueDesc](ValueDesc.md) class is a description of a value.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
ValueDesc(Null value);                                              (1)
ValueDesc(bool value);                                              (2)
ValueDesc(const char* value);                                       (3)

ValueDesc(cstring value,                                            (4)
    StringNotation notation = string_notation_quoted,
    cstring delimiter = cstring());

ValueDesc(const Number& value, int fracDigits = -1);                (5)
ValueDesc(double value);                                            (6)
ValueDesc(double value, int fracDigits = -1);                       (7)
ValueDesc(int value);                                               (8)
ValueDesc(long value);                                              (9)
ValueDesc(long long value);                                         (10)
ValueDesc(unsigned int value);                                      (11)
ValueDesc(unsigned long value);                                     (12)
ValueDesc(unsigned long long value);                                (13)

ValueDesc(EmptyObjectTag);                                          (14)
ValueDesc(const Pair<KeyDesc, ValueDesc>* p, size_t size);          (15)

template<size_t N>
ValueDesc(const Pair<KeyDesc, ValueDesc>(&v)[N]);                   (16)

ValueDesc(EmptyArrayTag);                                           (17)
ValueDesc(const ValueDesc* p, size_t size);                         (18)

template<size_t N>
ValueDesc(const ValueDesc(&v)[N]);                                  (19)
```

Constructs a [ValueDesc](ValueDesc.md).

(1) Constructs the value description for a null.

(2) Constructs the value description for a Boolean.

(3-4) Constructs the value description for a string.

(5-13) Constructs the value description for a number.

(14) Constructs the value description for an empty object.

(15-16) Constructs the value description for an object.

(17) Constructs the value description for an empty array.

(18-19) Constructs the value description for an array.

#### Parameters

[Null](Null.md) **value** A null.

`bool` **value** A Boolean.

`const char*` **value** A C-style string.

[cstring](cstring.md) **value** A string.

[StringNotation](StringNotation.md) **notation** The string notation to be used when rendering the string.

[cstring](cstring.md) **delimiter** The string delimiter to be used when rendering the string.

`const` [Number](Number.md)`&` **value** A number.

(numeric type) **value** A number.

`int` **fracDigits** The number of digits after decimal point which the rounding will be carried out toward; affects rendering only (*-1* means max digits).

[EmptyObjectTag](EmptyObjectTag.md) Tag dispatching.

`const` [Pair](Pair.md)`<`[KeyDesc](KeyDesc.md)`,` [ValueDesc](ValueDesc.md)`>*` **p** Pointer to an array of key-value description pairs.

`const` [Pair](Pair.md)`<`[KeyDesc](KeyDesc.md)`,` [ValueDesc](ValueDesc.md)`> (&`**v**`)[N]` An array of key-value description pairs.

[EmptyArrayTag](EmptyArrayTag.md) Tag dispatching.

`const` [ValueDesc](ValueDesc.md)`*` **p** Pointer to an array of value descriptions.

`const` [ValueDesc](ValueDesc.md)`(&`**v**`)[N]` An array of value descriptions.

`size_t` **size** Size of the description array.

#### Errors

An `InvalidArgument` fault occurs if **delimiter** is invalid.

