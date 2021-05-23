# OutputStream

```c++
class OutputStream
```

Inherited by: [MemoryOutputStream](MemoryOutputStream.md), [StdStreamOutputStream](StdStreamOutputStream.md) and [StdStringOutputStream](StdStringOutputStream.md).

Required header: `<Eclog/OutputStream.h>`

The [OutputStream](OutputStream.md) abstract class represents an output stream of characters.

## Member functions

| Name | Description |
| ---- | ---- |
| [state](#state) | Checks whether the stream is in good state. |
| [write](#write) | Inserts characters to the stream. |

* * *

### state

```c++
virtual bool state() const;
```

Checks whether the stream is in good state.

#### Return value

`bool` **true** if the stream is good, *false* otherwise.

* * *

### write

```c++
virtual void write(const char* buffer, size_t size);
```

Inserts characters to the stream.

#### Parameters

`char*` **buffer** The buffer to write.

`size_t` **size** The number of characters to write.

