# DynamicParsingBuffer

```c++
template<typename Alloc>
class BasicDynamicParsingBuffer
```

Inherited from: [ParsingBuffer](ParsingBuffer.md).

Required header: `<Eclog/DynamicParsingBuffer.h>`

The [BasicDynamicParsingBuffer](DynamicParsingBuffer.md) class is a parsing buffer that dynamically allocates and deallocates memory.

A typedef for the [default allocator](Allocator.md) is provided:

```c++
typedef BasicDynamicParsingBuffer<ECLOG_DEFAULT_ALLOCATOR> DynamicParsingBuffer;
```

## Template parameters

`Alloc` [Allocator](AllocatorRequirements.md) type used to allocate internal storage.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
DynamicParsingBuffer();
```

Constructs a [DynamicParsingBuffer](DynamicParsingBuffer.md).

