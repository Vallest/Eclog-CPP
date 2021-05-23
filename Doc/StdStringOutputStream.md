# StdStringOutputStream

```c++
class StdStringOutputStream
```

Inherited from: [OutputStream](OutputStream.md).

Required header: `<Eclog/StdStringOutputStream.h>`

The [StdStringOutputStream](StdStringOutputStream.md) class warps a C++ string into an [OutputStream](OutputStream.md).

## Member functions

| Name | Description |
| ---- | ---- |
| [str](#str) | Gets the string. |

* * *

### str

```c++
std::string& str();
const std::string& str() const;
```

Gets the string.

#### Return value

`std::string&` Reference to the string.

`const std::string&` Reference to the string.

