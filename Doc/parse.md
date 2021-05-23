# parse

```c++
template<typename Handler>
void parse(Context& ctx, Handler& handler);

template<typename Handler>
void parse(Context& ctx, Handler& handler, ErrorCode& ec);
```

Required header: `<Eclog/Parse.h>`

The [parse](parse.md) function parses an Eclog text from the input source and reports parsing events to a user-defined handler.

## Parameters

[Context](Context.md)`&` **ctx** The parsing context.

`Handler&` **handler** The handler that receives the parsing events.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

## Requirements

`Handler` must be a class type, and given

-  `handler`, a value of type `Handler`
- `key`, a value of type [Key](Key.md)
- `value`, a value of type [Value](Value.md)

the following expressions must be valid:

```c++
handler.onObjectBegin()
handler.onObjectEnd()
handler.onArrayBegin()
handler.onArrayEnd()
handler.onKey(key)
handler.onValue(value)
```

