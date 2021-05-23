# MemoryOutputStream

```c++
template<typename Alloc>
class BasicMemoryOutputStream
```

Inherited from: [OutputStream](OutputStream.md).

Required header: `<Eclog/MemoryOutputStream.h>`

The [BasicMemoryOutputStream](MemoryOutputStream.md) class is an in-memory [OutputStream](OutputStream.md) that writes bytes to an auto-growing byte buffer.

A typedef for the [default allocator](Allocator.md) is provided:

```c++
typedef BasicMemoryOutputStream<ECLOG_DEFAULT_ALLOCATOR> MemoryOutputStream;
```

## Template parameters

`Alloc` [Allocator](AllocatorRequirements.md) type used to allocate internal storage.

## Member functions

| Name | Description |
| ---- | ---- |
| [size](#size) | Returns the number of bytes that have been written to the buffer. |
| [data](#data) | Returns a pointer to the first byte in the buffer. |

* * *

### size

```c++
size_t size() const;
```

Returns the number of bytes that have been written to the buffer.

#### Return value

`size_t` Number of bytes.

* * *

### data

```c++
char* data();
const char* data() const;
```

Returns a pointer to the first byte in the buffer.

#### Return value

`char*` Pointer to the first byte.

`const char*` Pointer to the first byte.

