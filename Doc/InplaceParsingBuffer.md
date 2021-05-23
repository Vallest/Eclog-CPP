# InplaceParsingBuffer

```c++
class InplaceParsingBuffer
```

Inherited from: [ParsingBuffer](ParsingBuffer.md).

Required header: `<Eclog/InplaceParsingBuffer.h>`

The [InplaceParsingBuffer](InplaceParsingBuffer.md) class wraps a memory buffer as a [ParsingBuffer](ParsingBuffer.md).

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
explicit InplaceParsingBuffer(void* buffer, size_t maxSize);
```

Constructs an [InplaceParsingBuffer](InplaceParsingBuffer.md).

#### Parameters

`void*` **buffer** Pointer to the buffer.

`size_t` **maxSize** The maximum size of the buffer in bytes.

