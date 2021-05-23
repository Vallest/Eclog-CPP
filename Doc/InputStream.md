# InputStream

```c++
class InputStream
```

Inherited by: [MemoryInputStream](MemoryInputStream.md) and [StdStreamInputStream](StdStreamInputStream.md).

Required header: `<Eclog/InputStream.h>`

The [InputStream](InputStream.md) abstract class represents an input stream of characters.

## Member functions

| Name | Description |
| ---- | ---- |
| [state](#state) | Checks whether the stream is in good state. |
| [eof](#eof) | Checks whether EOF is reached. |
| [read](#read) | Extracts characters from the stream. |

* * *

### state

```c++
virtual bool state() const;
```

Checks whether the stream is in good state; the good state does not affect by EOF.

#### Return value

`bool` **true** if the stream is good, *false* otherwise.

* * *

### eof

```c++
virtual bool eof() const;
```

Checks whether EOF is reached.

#### Return value

`bool` *true* if EOF is reached, *false* otherwise.

* * *

### read

```c++
virtual size_t read(char* buffer, size_t size);
```

Extracts characters from the stream and stores them into the buffer.

#### Parameters

`char*` **buffer** The buffer to store the characters to.

`size_t` **size** Maximum number of characters to read.

#### Return value

`size_t` The number of characters actually extracted.



