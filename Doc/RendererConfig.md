# RendererConfig

```c++
struct RendererConfig
```

Required header: `<Eclog/RendererConfig.h>`

The [RendererConfig](RendererConfig.md) struct represents a renderer configuration (See [Renderer](Renderer.md)).

## Member enumerations

| Name                                | Description       |
| ----------------------------------- | ----------------- |
| [Scheme](#scheme)                   | Scheme.           |
| [Formatting](#formatting)           | Format.           |
| [IndentCharacter](#indentcharacter) | Indent character. |

* * *

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

## Member variables

| Name | Description |
| ---- | ---- |
| [formatting](#formatting-1) | Text formatting. |
| [linebreak](#linebreak) | Line-break style. |
| [indentCharacter](#indentcharacter-1) | Indent character. |
| [indentSize](#indentsize) | Indent size. |
| [insertSpaceAfterColon](#insertspaceaftercolon) | Insert space after colon. |
| [placeOpenBracketOnNewLineForObjects](#placeopenbracketonnewlineforobjects) | Place open bracket on new line for objects. |
| [placeOpenBracketOnNewLineForArrays](#placeopenbracketonnewlineforarrays) | Place open bracket on new line for arrays. |
| [encloseRootObjectWithCurlyBrackets](#encloserootobjectwithcurlybrackets) | Enclose root object with curly brackets. |
| [useQuotedStringsOnly](#usequotedstringsonly) | Use quoted strings only. |
| [useCommasToSeparateItems](#usecommastoseparateitems) | Use commas to separate items. |
| [useStringsToRepresentInfinitiesAndNaNs](#usestringstorepresentinfinitiesandnans) | Use strings to represent infinities and NaNs. |
| [enableComments](#enablecomments) | Enable comments. |

* * *

### Scheme

```c++
enum Scheme
```

**scheme_typical**

> Scheme: typical.

**scheme_json_compatible**

> Scheme: JSON-compatible.

* * *

### Formatting

```c++
enum Formatting
```

#### Values

**formatting_regular**

> Formatting: regular.

**formatting_compact**

> Formatting: compact.

* * *

### IndentCharacter

```c++
enum IndentCharacter
```

#### Values

**indent_character_tab**

> Indent character: horizontal tab.

**indent_character_space**

> Indent character: space.

* * *

### (constructor)

```c++
explicit RendererConfig(Scheme scheme = scheme_typical);
```

Constructs a [RendererConfig](RendererConfig.md).

#### Parameters

[Scheme](#scheme) **scheme** The predefined scheme for specifying the initial value of member variables.

* * *

### formatting

[Formatting](#formatting) **formatting**

Text formatting.

Typical scheme: *formatting_regular*.

JSON-compatible scheme: *formatting_regular*.

* * *

### linebreak

[Linebreak](Linebreak.md) **linebreak**

Line-break style.

Typical scheme: *LF*.

JSON-compatible scheme: *LF*.

* * *

### indentCharacter

[IndentCharacter](#indentcharacter) **indentCharacter**

Indent character.

Typical scheme: *indent_character_tab*.

JSON-compatible scheme: *indent_character_tab*.

* * *

### indentSize

`int` **indentSize**

Indent size.

Typical scheme: *1*.

JSON-compatible scheme: *1*.

* * *

### insertSpaceAfterColon

`bool` **insertSpaceAfterColon**

Insert space after colon.

Typical scheme: *true*.

JSON-compatible scheme: *true*.

### placeOpenBracketOnNewLineForObjects

`bool` placeOpenBracketOnNewLineForObjects

Place open bracket on new line for objects.

Typical scheme: *true*.

JSON-compatible scheme: *true*.

* * *

### placeOpenBracketOnNewLineForArrays

`bool` placeOpenBracketOnNewLineForArrays

Place open bracket on new line for arrays.

Typical scheme: *true*.

JSON-compatible scheme: *true*.

* * *

### encloseRootObjectWithCurlyBrackets

`bool` encloseRootObjectWithCurlyBrackets

Enclose root object with curly brackets.

Typical scheme: *false*.

JSON-compatible scheme: *true*.

* * *

### useQuotedStringsOnly

`bool` useQuotedStringsOnly

Use quoted strings only.

Typical scheme: *false*.

JSON-compatible scheme: *true*.

* * *

### useCommasToSeparateItems

`bool` useCommasToSeparateItems

Use commas to separate items.

Typical scheme: *false*.

JSON-compatible scheme: *true*.

* * *

### useStringsToRepresentInfinitiesAndNaNs

`bool` useStringsToRepresentInfinitiesAndNaNs

Use strings to represent infinities and NaNs.

Typical scheme: *false*.

JSON-compatible scheme: *true*.

* * *

### enableComments

`bool` enableComments

Enable comments.

Typical scheme: *true*.

JSON-compatible scheme: *false*.



