# StdStreamOutputStream

```c++
class StdStreamOutputStream
```

Inherited from: [OutputStream](OutputStream.md).

Required header: `<Eclog/StdStreamOutputStream.h>`

The [StdStreamOutputStream](StdStreamOutputStream.md) class warps a C++ output stream into an [OutputStream](OutputStream.md).

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

### (constructor)

```c++
explicit StdStreamOutputStream(std::ostream& stream);
```

Constructs a [StdStreamOutputStream](StdStreamOutputStream.md).

#### Parameters

`std::ostream&` **stream** Stream to write to.

