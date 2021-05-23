# NumberNode

```c++
class NumberNode
```

Inherited from: [ValueNode](ValueNode.md).

Required header: `<Eclog/NumberNode.h>`

The [NumberNode](NumberNode.md) abstract class represents a number node in a document tree (See [Document](Document.md)).

## Member functions

| Name | Description |
| ---- | ---- |
| [value](#value) | Gets the value. |
| [doubleValue](#valuedouble-valueint-valueuint-valuelong-valueulong-valuellong-and-valueullong) | Gets the value. |
| [intValue](#valuedouble-valueint-valueuint-valuelong-valueulong-valuellong-and-valueullong) | Gets the value. |
| [uintValue](#valuedouble-valueint-valueuint-valuelong-valueulong-valuellong-and-valueullong) | Gets the value. |
| [longValue](#valuedouble-valueint-valueuint-valuelong-valueulong-valuellong-and-valueullong) | Gets the value. |
| [ulongValue](#valuedouble-valueint-valueuint-valuelong-valueulong-valuellong-and-valueullong) | Gets the value. |
| [longlongValue](#valuedouble-valueint-valueuint-valuelong-valueulong-valuellong-and-valueullong) | Gets the  value. |
| [ulonglongValue](#valuedouble-valueint-valueuint-valuelong-valueulong-valuellong-and-valueullong) | Gets the value. |
| [setFracDigits](#setfracdigits) | Sets the number of digits after decimal point. |
| [fracDigits](#fracdigits) | Gets the number of digits after decimal point. |
| [assign](#assign) | Assigns a new value to this node. |

* * *

### value

```c++
virtual Number value() const;
```

Gets the value.

#### Return value

[Number](Number.md) The value.

* * *

### valueDouble, valueInt, valueUInt, valueLong, valueULong, valueLLong, and valueULLong

```c++
double valueDouble() const;
int valueInt() const;
unsigned int valueUInt() const;
long valueLong() const;
unsigned long valueULong() const;
long long valueLLong() const;
unsigned long long valueULLong() const;
```

Gets the value.

Numeric promotion or numeric conversion happens if the number's underlying type is different from the specified type.

#### Return value

(numeric type) The value.

* * *

### setFracDigits

```c++
virtual void setFracDigits(int fracDigits);
```

Sets the number of digits after decimal point which the rounding will be carried out toward; affects rendering only (*-1* means max digits).

#### Parameters

`int` **fracDigits** The number of digits.

* * *

### fracDigits

```c++
virtual int fracDigits() const = 0;
```

Gets the number of digits after decimal point which the rounding will be carried out toward; affects rendering only (*-1* means max digits).

#### Return value

`int` The number of digits.

* * *

### assign

```c++
virtual void assign(const NumberDesc& desc);
virtual void assign(const NumberNode& other);
```

Assigns a new value to this node.

#### Parameters

`const` [NumberDesc](NumberDesc.md)`&` **desc** A number description.

`const` [NumberNode](NumberNode.md)`&` **other** Another number node.

