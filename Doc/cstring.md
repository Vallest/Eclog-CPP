# cstring

```c++
class cstring
```

Required header: `<Eclog/cstring.h>`

The [cstring](cstring.md) class wraps a UTF-8 byte array as a string. As an alternative to `const char*`, a [cstring](cstring.md) allows null characters at any position.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [empty](#empty) | Checks if this string is empty. |
| [size](#size) | Returns the number of bytes. |
| [operator[]](#operator-1) | Returns a reference to the byte at specified location. |
| [data](#data) | Returns a pointer to the first byte. |
| [begin](#begin) | Returns a pointer to the first byte. |
| [end](#end) | Returns a pointer to the past-the-end byte. |
| [compare](#compare) | Compares this string with another string. |
| [startsWith](#startswith) | Determines whether this string begins with the specified string. |
| [endsWith](#endswith) | Determines whether this string ends with the specified string. |
| [validate](#validate) | Validates this string. |
| [substr](#substr) | Returns a substring. |
| [operator==](#operator-operator-operator-operator-operator-and-operator) | Compares this string with another string. |
| [operator!=](#operator-operator-operator-operator-operator-and-operator) | Compares this string with another string. |
| [operator<](#operator-operator-operator-operator-operator-and-operator) | Compares this string with another string. |
| [operator<=](#operator-operator-operator-operator-operator-and-operator) | Compares this string with another string. |
| [operator>](#operator-operator-operator-operator-operator-and-operator) | Compares this string with another string. |
| [operator>=](#operator-operator-operator-operator-operator-and-operator) | Compares this string with another string. |
| [operator bool](#operator-bool) | Checks if this string is not null. |
| [operator!](#operator-2) | Checks if this string is null. |

* * *

## Non-member functions

| Name | Description |
| ---- | ---- |
| [operator==](#operator-operator-operator-operator-operator-and-operator-1) | Compares two strings. |
| [operator!=](#operator-operator-operator-operator-operator-and-operator-1) | Compares two strings. |
| [operator<](#operator-operator-operator-operator-operator-and-operator-1) | Compares two strings. |
| [operator>](#operator-operator-operator-operator-operator-and-operator-1) | Compares two strings. |
| [operator<=](#operator-operator-operator-operator-operator-and-operator-1) | Compares two strings. |
| [operator>=](#operator-operator-operator-operator-operator-and-operator-1) | Compares two strings. |
| [operator<<](#operator-3) | Inserts string into stream. |

* * *

### (constructor)

```c++
cstring();                                                          (1)
cstring(const char* str);                                           (2)
explicit cstring(const char* str, size_t length);                   (3)
explicit cstring(const char* begin, const char* end);               (4)
```

Constructs a [cstring](cstring.md).

(1) Default constructor. Constructs null string.

(2) Constructs the string with byte array [`str`, `str + strlen(str)`).

(3) Constructs the string with byte array [`str`, `str + length`).

(4) Constructs the string with byte array [`begin`, `end`).

#### Parameters

`const char*` **str** Pointer to a C-style string.

`size_t` **length** Number of bytes.

`const char*` **begin**, **end** Range of bytes.

* * *

### empty

```c++
bool empty() const;
```

Checks if this string is empty.

#### Return value

`bool` *true* if this string is empty, *false* otherwise.

* * *

### size

```c++
size_t size() const;
```

Returns the number of bytes.

#### Return value

`size_t` The number of bytes.

* * *

### operator[]

```c++
const char& operator[](size_t pos) const;
```

Returns a reference to the byte at specified location.

#### Parameters

`size_t` **pos** Position of the byte to return.

#### Return value

`const char&` Reference to the byte.

* * *

### data

```c++
const char* data() const;
```

Returns a pointer to the first byte.

#### Return value

`const char*` Pointer to the first byte.

* * *

### begin

```c++
const char* begin() const;
```

Returns a pointer to the first byte.

#### Return value

`const char*` Pointer to the first byte.

* * *

### end

```c++
const char* end() const;
```

Returns a pointer to the past-the-end byte.

This pointer acts as a placeholder; attempting to dereference it results in undefined behavior.

#### Return value

`const char*` Pointer to the past-the-end byte.

* * *

### compare

```c++
int compare(const cstring& other) const;
```

Compares the byte sequence of this string with another string.

#### Parameters

`const` [cstring](cstring.md)`&` **other** Another string.

#### Return value

`int` *negative value* if the first byte that does not match has a lower value in this string, *0* if this string is equal to the other string, *positive value* if the first byte that does not match has a greater value in this string.

* * *

### startsWith

```c++
bool startsWith(const cstring& str) const;
```

Determines whether this string begins with the byte sequence of the specified string.

#### Parameters

`const` [cstring](cstring.md)`&` **str** The string to search for.

#### Return value

`bool` *true* if this string begins with **str**, *false* otherwise.

* * *

### endsWith

```c++
bool endsWith(const cstring& str) const;
```

Determines whether this string ends with the byte sequence of the specified string.

#### Parameters

`const` [cstring](cstring.md)`&` **str** The string to search for.

#### Return value

`bool` *true* if this string ends with **str**, *false* otherwise.

* * *

### validate

```c++
bool validate(size_t* position = 0) const;
```

Validates the UTF-8 byte sequence of this string.

This function returns when an invalid Unicode character is encountered or the string's end is reached.

#### Parameters

`size_t*` **position** Pointer to a `size_t`, whose value is set by the function to the number of validated Unicode characters. If this parameter is a null pointer, it is not used.

#### Return value

`bool` *true* if this string is valid, *false* otherwise.


* * *

### substr

```c++
cstring substr(size_t pos, size_t count=-1) const;
```

Returns the subsequence of the byte sequence.

#### Parameters

`size_t` **pos** Position of the first byte to include.

`size_t` **count** Length of the sequence.

#### Return value

[cstring](cstring.md) The substring.

* * *

### operator==, operator!=, operator<, operator>, operator<=, and operator>=

```c++
bool operator==(const cstring& other) const;
bool operator!=(const cstring& other) const;
bool operator<(const cstring& other) const;
bool operator>(const cstring& other) const;
bool operator<=(const cstring& other) const;
bool operator>=(const cstring& other) const;
```

Compares the byte sequence of this string with another string.

#### Parameters

`const` [cstring](cstring.md)`&` **other** Another string.

#### Return value

`bool` *true* if the corresponding comparison holds, *false* otherwise.

* * *

### operator bool

```c++
operator BoolType() const;
```

Checks if this string is not null.

#### Return value

`BoolType` *true* if this string is not null, *false* otherwise.

* * *

### operator!

```c++
bool operator!() const;
```

Checks if this string is null.

#### Return value

`bool` *true* if this string is null, *false* otherwise.

* * *

### operator==, operator!=, operator<, operator>, operator<=, and operator>=

```c++
bool operator==(const char* a, const cstring& b);
bool operator!=(const char* a, const cstring& b);
bool operator<(const char* a, const cstring& b);
bool operator>(const char* a, const cstring& b);
bool operator<=(const char* a, const cstring& b);
bool operator>=(const char* a, const cstring& b);
```

Compares the byte sequences of two strings.

#### Parameters

`const char*` **a** A C-style string.

`const` [cstring](cstring.md)`&` **b** A string.

#### Return value

`bool` *true* if the corresponding comparison holds, *false* otherwise.

* * *

### operator<<

```c++
std::ostream& operator<<(std::ostream& stream, const cstring& str)
```

Inserts the byte sequence of a string into the stream.

#### Parameters

`std::ostream&` **stream** The output stream.

`const` [cstring](cstring.md)`&` **str** The string to be inserted.

#### Return value

`std::ostream&` The same as parameter **stream**.

