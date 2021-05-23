# MemoryInputStream

```c++
class MemoryInputStream
```

Inherited from: [InputStream](InputStream.md).

Required header: `<Eclog/MemoryInputStream.h>`

The [MemoryInputStream](MemoryInputStream.md) class warps a memory buffer as an [InputStream](InputStream.md).

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
explicit MemoryInputStream(const void* data, size_t size);
```

Constructs a [MemoryInputStream](MemoryInputStream.md).

#### Parameters

`const void*` **data** Pointer to the memory buffer.

`size_t` **size** Size of the memory buffer in bytes.

