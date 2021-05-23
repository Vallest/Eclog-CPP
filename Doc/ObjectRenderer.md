# ObjectRenderer

```c++
class ObjectRenderer
```

Required header: `<Eclog/ObjectRenderer.h>`

The [ObjectRenderer](ObjectRenderer.md) class represents an object renderer.

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [beginObject](#beginobject) | Begins rendering an object. |
| [endObject](#endobject) | Ends rendering the current object. |
| [beginArray](#beginarray) | Begins rendering an array. |
| [endArray](#endarray) | Ends rendering the current array. |
| [renderMember](#rendermember) | Renders a key-value pair. |
| [renderEmptyLines](#renderemptylines) | Renders one or more empty lines. |
| [renderComment](#rendercomment) | Renders a comment. |
| [beginInline](#begininline) | Begins an inline-block. |
| [endInline](#endinline) | Ends an inline-block. |
| [operator RendererHandle](#operator-rendererhandle) | Returns a handle to this renderer. |

* * *

### (constructor)

```c++
explicit ObjectRenderer(RendererHandle parent);
explicit ObjectRenderer(ObjectRenderer& parent);
```

Constructs an [ObjectRenderer](ObjectRenderer.md).

#### Parameters

`RendererHandle` **parent** Handle to the parent renderer.

[ObjectRenderer](ObjectRenderer.md)`&` **parent** Reference to the parent renderer.

* * *

### beginObject

```c++
void beginObject(const KeyDesc& key);
void beginObject(const KeyDesc& key, ErrorCode& ec);
```

Begins rendering an object.

The key-value pairs of the object must be rendered with a new object renderer (an [ObjectRenderer](ObjectRenderer.md) instance) constructed from this renderer.

Each call to this method must be paired with a call to [endObject](#endobject).

#### Parameters

`const` [KeyDesc](KeyDesc.md)`&` **key** The description of the key of the nested object.

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
void beginArray(const KeyDesc& key);
void beginArray(const KeyDesc& key, ErrorCode& ec);
```

Begins rendering an array.

The values of the array must be rendered with a new array renderer (an [ArrayRenderer](ArrayRenderer.md) instance) constructed from this renderer.

Each call to this method must be paired with a call to [endArray](#endarray).

#### Parameters

`const` [KeyDesc](KeyDesc.md)`&` **key** The description of the key of the nested array.

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
void renderMember(const KeyDesc& key, const ValueDesc& value);
void renderMember(const KeyDesc& key, const ValueDesc& value, ErrorCode& ec);
```

Renders a key-value pair.

#### Parameters

`const` [KeyDesc](KeyDesc.md)`&` **key** The description of the key.

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

