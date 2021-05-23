# StdStreamInputStream

```c++
class StdStreamInputStream
```

Inherited from: [InputStream](InputStream.md).

Required header: `<Eclog/StdStreamInputStream.h>`

The [StdStreamInputStream](StdStreamInputStream.md) class warps a `std::istream` as an [InputStream](InputStream.md).

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
explicit StdStreamInputStream(std::istream& stream);
```

Constructs an [StdStreamInputStream](StdStreamInputStream.md).

#### Parameters

`std::istream&` **stream** The stream to read from.

