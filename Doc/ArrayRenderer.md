# ArrayRenderer

```c++
class ArrayRenderer
```

Required header: `<Eclog/ArrayRenderer.h>`

The [ArrayRenderer](ArrayRenderer.md) class represents an array renderer.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [beginObject](#beginobject) | Begins rendering an object. |
| [endObject](#endobject) | Ends rendering the current object. |
| [beginArray](#beginarray) | Begins rendering an array. |
| [endArray](#endarray) | Ends rendering the current array. |
| [renderMember](#rendermember) | Renders value. |
| [renderEmptyLines](#renderemptylines) | Renders one or more empty lines. |
| [renderComment](#rendercomment) | Renders a comment. |
| [beginInline](#begininline) | Begins an inline-block. |
| [endInline](#endinline) | Ends an inline-block. |
| [operator RendererHandle](#operator-rendererhandle) | Returns a handle to this renderer. |

* * *

### (constructor)

```c++
explicit ArrayRenderer(RendererHandle parent);
explicit ArrayRenderer(ArrayRenderer& parent);
```

Constructs an [ArrayRenderer](ArrayRenderer.md).

#### Parameters

`RendererHandle` **parent** Handle to the parent renderer.

[ArrayRenderer](ArrayRenderer.md)`&` **parent** Reference to the parent renderer.

* * *

### beginObject

```c++
void beginObject();
void beginObject(ErrorCode& ec);
```

Begins rendering an object.

The key-value pairs of the object must be rendered with a new object renderer (an [ObjectRenderer](ObjectRenderer.md) instance) constructed from this renderer.

Each call to this method must be paired with a call to [endObject](#endobject).

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if there is currently a nested object or array being rendered.

* * *

### endObject

```c++
void endObject();
void endObject(ErrorCode& ec);
```

Ends rendering the current object.

The object renderer of the current object, if there is one, is invalidated after this call.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if there is currently no nested object that is being rendered.

An `InvalidOperation` fault occurs if there is currently a deeply nested object or array that is being rendered.

* * *

### beginArray

```c++
void beginArray();
void beginArray(ErrorCode& ec);
```

Begins rendering an array.

The values of the array must be rendered with a new array renderer (an [ArrayRenderer](ArrayRenderer.md) instance) constructed from this renderer.

Each call to this method must be paired with a call to [endArray](#endarray).

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if there is currently a nested object or array being rendered.

* * *

### endArray

Ends rendering the current array.

The array renderer of the current array, if there is one, is invalidated after this call.

#### Parameters

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if there is currently no nested array that is being rendered.

An `InvalidOperation` fault occurs if there is currently a deeply nested object or array that is being rendered.

* * *

### renderMember

```c++
void renderMember(const ValueDesc& value);
void renderMember(const ValueDesc& value, ErrorCode& ec);
```

Renders a value.

#### Parameters

`const` [ValueDesc](ValueDesc.md)`&` **value** The description of the value.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

An `InvalidOperation` fault occurs if there is currently a nested object or array being rendered.

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

An `InvalidOperation` fault occurs if there is currently a nested object or array being rendered.

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

An `InvalidOperation` fault occurs if there is currently a nested object or array being rendered.

* * *

### beginInline

```c++
int beginInline();
```

Begins an inline-block.

#### Return value

`int` The nesting level of the inline block.

#### Errors

An `InvalidOperation` fault occurs if there is currently a nested object or array being rendered.

* * *

### endInline

```c++
int endInline();
```

Ends an inline-block.

#### Return value

`int` The nesting level of the inline block.

#### Errors

An `InvalidOperation` fault occurs if there is currently a nested object or array being rendered.

* * *

### operator RendererHandle

```
operator RendererHandle();
```

Returns a handle to this renderer.

#### Return value

`RendererHandle` Handle to this renderer.

