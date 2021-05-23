# ParsingBuffer

```c++
class ParsingBuffer
```

Inherited by: [DynamicParsingBuffer](DynamicParsingBuffer.md), and [InplaceParsingBuffer](InplaceParsingBuffer.md).

Required header: `<Eclog/ParsingBuffer.h>`

The [ParsingBuffer](ParsingBuffer.md) abstract class represents a buffer that stores intermediate results during a parsing process.

## Member functions

| Name | Description |
| ---- | ---- |
| [claim](#claim) | Claims a new bytes buffer and makes it the current buffer. |
| [discard](#discard) | Removes the last claimed bytes buffer. |
| [length](#length) | Returns the length of the current bytes buffer. |
| [address](#address) | Returns a pointer to the first byte of the current bytes buffer. |
| [str](#str) | Returns the current bytes buffer as a string. |
| [putChar](#putChar) | Puts a Unicode character at the end of the current bytes buffer. |
| [shrink](#shrink) | Truncates the current bytes buffer. |

* * *

### claim

```c++
virtual void* claim();
```

Claims a new bytes buffer and makes it the current buffer.

#### Return value

`void*` Pointer to the internal descriptor.

* * *

### discard

```c++
virtual void discard(void* ptr);
```

Removes the last claimed bytes buffer.

#### Parameters

`void*` **ptr** Pointer earlier obtained from [claim](#claim).

* * *

### length

Returns the length of the current bytes buffer.

```c++
virtual size_t length() const;
```

#### Return value

`size_t` The length.

* * *

### address

```c++
virtual char* address();
```

Returns a pointer to the first byte of the current bytes buffer.

#### Return value

`char*` Pointer to the first byte.

* * *

### str

```c++
virtual cstring str() const;
```

Returns the current bytes buffer as a string. There is a null character after the last character of the returned string, making the string compatible with C-style APIs.

#### Return value

[cstring](cstring.md) The string.

* * *

### putChar

```c++
virtual void putChar(int ch);
```

Puts the UTF-8 encoded bytes of Unicode character **ch** at the end of the current bytes buffer.

#### Parameters

`int` **ch** Unicode code point.

* * *

### shrink

```c++
virtual void shrink(size_t length);
```

Truncates the current bytes buffer.

#### Parameters

`size_t` **length** The new length of the current bytes buffer; always less than or equal to [length](#length).

