# parseObject

```c++
template<typename Handler>
void parseObject(Context& ctx, Handler handler);

template<typename Handler>
void parseObject(Context& ctx, Handler handler, ErrorCode& ec);
```

Required header: `<Eclog/Parse.h>`

The [parseObject](parseObject.md) function parses the current object from the input source and reports the encountered top-level key-value pairs to a user-defined handler.

## Parameters

[Context](Context.md)`&` **ctx** The parsing context.

`Handler` **handler** The handler to be called when a key-value pair is encountered.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

## Requirements

`Handler` must be a callable type, and given

-  `handler`, a value of type `Handler`
- `key`, a value of type [Key](Key.md)
- `value`, a value of type [Value](Value.md)

the following expression must be valid:

```c++
handler(key, value)
```

