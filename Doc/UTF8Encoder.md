# UTF8Encoder

```c++
class UTF8Encoder
```

Required header: `<Eclog/UTF8Encoder.h>`

The [UTF8Encoder](UTF8Encoder.md) class represents a UTF-8 encoder.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [putChar](#putchar) | Inserts a Unicode character into the stream. |

* * *

### (constructor)

```c++
explicit UTF8Encoder(OutputStream& os);
```

Constructs a [UTF8Encoder](UTF8Encoder.md).

#### Parameters

[OutputStream](OutputStream.md)`&` **os** The UTF-8 encoded stream to write to.

* * *

### putChar

```c++
void putChar(int ch);
void putChar(int ch, ErrorCode& ec);
```

Inserts Unicode character **ch** into the stream.

#### Parameters

`int` **ch** Unicode code point.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

