# UTF8Decoder

```c++
class UTF8Decoder
```

Required header: `<Eclog/UTF8Decoder.h>`

The [UTF8Decoder](UTF8Decoder.md) class represents a UTF-8 decoder.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [peekChar](#peekchar) | Reads the next Unicode character from the input stream without extracting it. |
| [getChar](#getchar) | Extracts the next Unicode character from the input stream. |
| [position](#position) | Returns the position of the current character. |

* * *

### (constructor)

```c++
explicit UTF8Decoder(InputStream& is);
```

Constructs a [UTF8Decoder](UTF8Decoder.md).

#### Parameters

[InputStream](InputStream.md)`&` **os** The UTF-8 encoded stream to read from.

* * *

### peekChar

```c++
int peekChar();
int peekChar(ErrorCode& ec);
```

Reads the next Unicode character from the input stream without extracting it.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Return value

`int` Unicode code point.

* * *

### getChar

```c++
int getChar();
int getChar(ErrorCode& ec);
```

Extracts the next Unicode character from the input stream.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Return value

`int` Unicode code point.

* * *

### position

```c++
long long position() const;
```

Returns the position of the current character.

#### Return value

`long long` The current position.

