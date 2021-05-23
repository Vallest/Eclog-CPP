# parseArray

```c++
template<typename Handler>
void parseArray(Context& ctx, Handler handler);

template<typename Handler>
void parseArray(Context& ctx, Handler handler, ErrorCode& ec);
```

Required header: `<Eclog/Parse.h>`

The [parseArray](parseArray.md) function parses the current array from the input source and reports the encountered top-level values to a user-defined handler.

## Parameters

[Context](Context.md)`&` **ctx** The parsing context.

`Handler` **handler** The handler to be called when a value is encountered.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

## Requirements

`Handler` must be a callable type, and given

-  `handler`, a value of type `Handler`
- `value`, a value of type [Value](Value.md)

the following expression must be valid:

```c++
handler(value)
```

