# Value

```c++
class Value
```

Required header: `<Eclog/Value.h>`

The [Value](Value.md) class represents an encountered value while parsing.

## Member functions

| Name | Description |
| ---- | ---- |
| [type](#type) | Gets the type of this value. |
| [isNull](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this value is a null. |
| [isBoolean](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this value is a Boolean. |
| [isString](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this value is a string. |
| [isNumber](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this value is a number. |
| [isObject](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this value is an object. |
| [isArray](#isnull-isboolean-isstring-isnumber-isobject-and-isarray) | Determines whether this value is an array. |
| [asNull](#asnull-asboolean-asstring-and-asnumber) | Casts this value to a null. |
| [asBoolean](#asnull-asboolean-asstring-and-asnumber) | Casts this value to a Boolean. |
| [asString](#asnull-asboolean-asstring-and-asnumber) | Casts this value to a string. |
| [asNumber](#asnull-asboolean-asstring-and-asnumber) | Casts this value to a number. |
| [bytes](#bytes) | Gets the UTF-8 byte sequence of this value. |
| [numberInfo](#numberinfo) | Gets the number information. |
| [stringNotation](#stringnotation) | Gets the string notation. |
| [stringDelimiter](#stringdelimiter) | Gets the string delimiter. |

* * *

### type

```c++
ValueType type() const;
```

Gets the type of this value.

#### Return value

[ValueType](ValueType.md) Type of this value.

* * *

### isNull, isBoolean, isString, isNumber, isObject, and isArray

```c++
bool isNull() const;
bool isBoolean() const;
bool isString() const;
bool isNumber() const;
bool isObject() const;
bool isArray() const;
```

Determines whether this value is of a specific type.

#### Return value

`bool` *true* if this value is of a specific type, *false* otherwise.

* * *

### asNull, asBoolean, asString, and asNumber

```c++
Null asNull() const;
bool asBoolean() const;
cstring asString() const;
Number asNumber() const;
```

Casts this value to a specific type.

#### Return value

[Null](Null.md) Null value.

`bool` Boolean value.

[cstring](cstring.md) String value.

[Number](Number.md) Number value.

#### Errors

A `BadCast` fault occurs if this value is not of the specific type.

* * *

### bytes

```c++
cstring bytes() const;
```

Gets the UTF-8 byte sequence of this value.

#### Return value

[cstring](cstring.md) The byte sequence.

* * *

### numberInfo

```c++
int numberInfo() const;
```

Gets the number information (Only meaningful for number value).

#### Return value

`int` The number information, which is a bitmask value (See [NumberInfo](NumberInfo.md)).

* * *

### stringNotation

```c++
StringNotation stringNotation() const;
```

Gets the string notation (Only meaningful for string value).

#### Return value

[StringNotation](StringNotation.md) The string notation of the string.

* * *

### stringDelimiter

```c++
cstring stringDelimiter() const;
```

Gets the string delimiter (Only meaningful for raw string and heredoc string).

#### Return value

[cstring](cstring.md) The string delimiter of the string.



