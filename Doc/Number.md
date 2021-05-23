# Number

```c++
class Number
```

Required header: `<Eclog/Number.h>`

The [Number](Number.md) class represents a number.

## Member enumerations

| Name                              | Description      |
| --------------------------------- | ---------------- |
| [UnderlyingType](#underlyingtype) | Underlying type. |

* * *

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [underlyingType](#underlyingtype-1) | Gets the underlying type of this number. |
| [sign](#sign) | Determines the sign of this number. |
| [isSubnormal](#issubnormal) | Determines whether this number is subnormal. |
| [isInfinity](#isinfinity) | Determines whether this number is a positive or negative infinity. |
| [isNan](#isnan) | Determines whether this number is a NaN. |
| [operator=](#operator) | Assigns a new value to this number. |
| [load](#load) | Gets the value from this number. |
| [store](#store) | Assigns a new value to this number. |
| [operator==](#operator-operator-operator-operator-operator-and-operator) | Compares this number with another number. |
| [operator!=](#operator-operator-operator-operator-operator-and-operator) | Compares this number with another number. |
| [operator<](#operator-operator-operator-operator-operator-and-operator) | Compares this number with another number. |
| [operator>](#operator-operator-operator-operator-operator-and-operator) | Compares this number with another number. |
| [operator<=](#operator-operator-operator-operator-operator-and-operator) | Compares this number with another number. |
| [operator>=](#operator-operator-operator-operator-operator-and-operator) | Compares this number with another number. |

* * *

## Non-member functions

| Name | Description |
| ---- | ---- |
| [operator==](#operator-operator-operator-operator-operator-and-operator-1) | Compares two numbers. |
| [operator!=](#operator-operator-operator-operator-operator-and-operator-1) | Compares two numbers. |
| [operator<](#operator-operator-operator-operator-operator-and-operator-1) | Compares two numbers. |
| [operator>](#operator-operator-operator-operator-operator-and-operator-1) | Compares two numbers. |
| [operator<=](#operator-operator-operator-operator-operator-and-operator-1) | Compares two numbers. |
| [operator>=](#operator-operator-operator-operator-operator-and-operator-1) | Compares two numbers. |
| [operator<<](#operator-1) | Insert number into stream. |

* * *

### UnderlyingType

```c++
enum UnderlyingType
```

**underlying_type_double**

> Underlying type: `double`.

**underlying_type_int**

> Underlying type: `int`.

**underlying_type_uint**

> Underlying type: `unsigned int`.

**underlying_type_long**

> Underlying type: `long`.

**underlying_type_ulong**

> Underlying type: `unsigned long`.

**underlying_type_llong**

> Underlying type: `long long`.

**underlying_type_ullong**

> Underlying type: `unsigned long long`.

### (constructor)

```c++
Number();
Number(double value);
Number(int value);
Number(long value);
Number(long long value);
Number(unsigned int value);
Number(unsigned long value);
Number(unsigned long long value);
```

Constructs a [Number](Number.md).

#### Parameters

(numeric type) **value** A numeric value.

* * *

### underlyingType

```c++
UnderlyingType underlyingType() const;
```

Gets the underlying type of this number.

#### Return value

`UnderlyingType` The underlying type.

* * *

### sign

```c++
int sign() const;
```

Determines the sign of this number.

#### Return value

`int` *1* for positive, *-1* for negative.

* * *

### isSubnormal

```c++
bool isSubnormal() const;
```

Determines whether this number is subnormal.

### Return value

`bool` *true* if this number is subnormal, *false* otherwise.

* * *

### isInfinity

```c++
bool isInfinity() const;
```

Determines whether this number is a positive or negative infinity.

### Return value

`bool` *true* if this number is infinite, *false* otherwise.

* * *

### isNan

```c++
bool isNan() const;
```

Determines whether this number is a NaN.

### Return value

`bool` *true* if this number is a NaN, *false* otherwise.

* * *

### operator=

```c++
Number& operator=(double value);
Number& operator=(int value);
Number& operator=(long value);
Number& operator=(long long value);
Number& operator=(unsigned int value);
Number& operator=(unsigned long value);
Number& operator=(unsigned long long value);
```

Assigns a new value to this number.

#### Parameters

(numeric type) **value** A numeric value.

#### Return value

[Number](Number.md)`&` Reference to `*this`.

* * *

### load

```c++
template<typename T>
T load() const;
```

Gets the value from this number.

Numeric promotion or numeric conversion happens if the underlying type is different from the specified type.

#### Template parameters

`T` The numeric type to convert to.

#### Return value

`T` The value.

* * *

### store

```c++
void store(double value);
void store(int value);
void store(long value);
void store(long long value);
void store(unsigned int value);
void store(unsigned long value);
void store(unsigned long long value);
```

Assigns a new value to this number.

#### Parameters

(numeric type) **value** A numeric value.

* * *

### operator==, operator!=, operator<, operator>, operator<=, and operator>=

```c++
bool operator==(const Number& other) const;
bool operator!=(const Number& other) const;
bool operator<(const Number& other) const;
bool operator>(const Number& other) const;
bool operator<=(const Number& other) const;
bool operator>=(const Number& other) const;
```

Compares this number with another number.

#### Parameters

`const` [Number](Number.md)`&` **other** Another number.

#### Return value

`bool` *true* if the corresponding comparison holds, *false* otherwise.

* * *

### operator==, operator!=, operator<, operator>, operator<=, and operator>=

```c++
template<typename T>
bool operator==(const T& a, const Number& b);

template<typename T>
bool operator!=(const T& a, const Number& b);

template<typename T>
bool operator<(const T& a, const Number& b);

template<typename T>
bool operator>(const T& a, const Number& b);

template<typename T>
bool operator<=(const T& a, const Number& b);

template<typename T>
bool operator>=(const T& a, const Number& b);
```

Compares two numbers.

#### Parameters

`const T&` **a** A number to compare.

`const` [Number](Number.md)`&` **b** A number to compare.

#### Return value

`bool` *true* if the corresponding comparison holds, *false* otherwise.


* * *

### operator<<

```c++
std::ostream& operator<<(std::ostream& stream, const Number& n);
```

Insert number into stream.

#### Parameters

`std::ostream&` **stream** The stream where number is inserted.

`const` [Number](Number.md)`&` **n** The number to insert.

#### Return value

`std::ostream&` The same as parameter **stream**.



