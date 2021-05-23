# NumberDesc

```c++
class NumberDesc
```

Inherited from: [ValueDesc](ValueDesc.md).

Required header: `<Eclog/NumberDesc.h>`

The [NumberDesc](NumberDesc.md) class is a description of a number.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
NumberDesc(const Number& value, int fracDigits = -1);
NumberDesc(double value);
NumberDesc(double value, int fracDigits = -1);
NumberDesc(int value);
NumberDesc(long value);
NumberDesc(long long value);
NumberDesc(unsigned int value);
NumberDesc(unsigned long value);
NumberDesc(unsigned long long value);
```

Constructs a [NumberDesc](NumberDesc.md).

#### Parameters

`const` [Number](Number.md)`&` **value** A number.

(numeric type) **value** A number.

`int` **fracDigits** The number of digits after decimal point which the rounding will be carried out toward; affects rendering only (*-1* means max digits).

