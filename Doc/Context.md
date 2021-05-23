# Context

```c++
class Context
```

Required header: `<Eclog/Context.h>`

The [Context](Context.md) class represents a parsing context.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [terminate](#terminate) | Terminates the current parsing process. |

* * *

### (constructor)

```c++
explicit Context(InputStream& stream, ParsingBuffer& buffer);
```

Constructs a [Context](Context.md).

#### Parameters

[InputStream](InputStream.md)`&` **stream** The input stream to read from.

[ParsingBuffer](ParsingBuffer.md)`&` **buffer** The parsing buffer.

* * *

### terminate

```c++
void terminate();
```

Sets this parsing context in the terminated state; the parsing process performed on this parsing context will stop as early as possible.

#### Errors

A `ParseError` with error code *pe_user_asked_for_termination* occurs.

