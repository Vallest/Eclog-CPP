# Renderer

```c++
class Renderer
```

Required header: `<Eclog/Renderer.h>`

The [Renderer](Renderer.md) class represents an Eclog text renderer.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [beginRootObject](#beginrootobject) | Begins rendering the root object. |
| [endRootObject](#endrootobject) | Ends rendering the root object. |
| [renderRootObject](#renderrootobject) | Renders the root object directly with an object description. |
| [renderEmptyLines](#renderemptylines) | Renders one or more empty lines. |
| [renderComment](#rendercomment) | Renders a comment. |
| [beginInline](#begininline) | Begins an inline-block. |
| [endInline](#endinline) | Ends an inline-block. |
| [close](#close) | Closes the renderer. |
| [operator RendererHandle](#operator-rendererhandle) | Returns a handle to this renderer. |

* * *

### (constructor)

```c++
explicit Renderer(OutputStream& stream,
    const RendererConfig& rendererConfig = RendererConfig());
```

Constructs a [Renderer](Renderer.md).

#### Parameters

[OutputStream](OutputStream.md)`&` **stream** The output stream to write to.

[RendererConfig](RendererConfig.md)`&` **rendererConfig** The renderer configuration.

* * *

### beginRootObject

```c++
void beginRootObject();
void beginRootObject(ErrorCode& ec);
```

Begins rendering the root object.

The key-value pairs of the root object must be rendered with a new object renderer (an [ObjectRenderer](ObjectRenderer.md) instance) constructed from this renderer.

Call to this method must be paired with a call to [endRootObject](#endrootobject).

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if the root object is being rendered or has been rendered.

* * *

### endRootObject

```c++
void endRootObject();
void endRootObject(ErrorCode& ec);
```

Ends rendering the root object.

The object renderer of the root object, if there is one, is invalidated after this call.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if the root object is not currently being rendered.

An `InvalidOperation` fault occurs if there is currently a deeply nested object or array that is being rendered.

* * *

### renderRootObject

```c++
void renderRootObject(const ObjectDesc& root);
void renderRootObject(const ObjectDesc& root, ErrorCode& ec);
```

Renders the root object directly with an object description.

#### Parameters

`const` [ObjectDesc](ObjectDesc.md)`&` **root** The description of the root object.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if the root object is being rendered or has been rendered.

* * *

### renderEmptyLines

```c++
void renderEmptyLines(int count);
void renderEmptyLines(int count, ErrorCode& ec);
```

Renders one or more empty lines.

#### Parameters

`int` **count** Number of empty lines.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if the root object is currently being rendered.

* * *

### renderComment

```c++
void renderComment(cstring comment);
void renderComment(cstring comment, ErrorCode& ec);
```

Renders a comment.

#### Parameters

[cstring](cstring.md) **comment** The comment.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if the root object is currently being rendered.

* * *

### beginInline

```c++
int beginInline();
```

Begins an inline-block.

#### Return value

`int` The nesting level of the inline block.

#### Errors

An `InvalidOperation` fault occurs if the root object is currently being rendered.

* * *

### endInline

```c++
int endInline();
```

Ends an inline-block.

#### Return value

`int` The nesting level of the inline block.

#### Errors

An `InvalidOperation` fault occurs if the root object is currently being rendered.

* * *

### close

```c++
void close();
void close(ErrorCode& ec);
```

Closes the renderer.

This renderer is invalidated after this operation.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if the root object is currently being rendered.

* * *

### operator RendererHandle

```
operator RendererHandle();
```

Returns a handle to this renderer.

#### Return value

`RendererHandle` Handle to this renderer.

