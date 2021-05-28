# Eclog-CPP

Eclog-CPP is a cross-platform C++ library for parsing and rendering [Eclog](https://eclog.org) (a superset of JSON) texts.



## Features

- C++98 compatible
- No external dependencies
- No complex build system
- Supports both exceptions and error codes
- Supports in-place parsing



## Table of Contents

- [Compatibility](#compatibility)
- [Integration](#integration)
- [Memory Management](#memory-management)
- [Thread Safety](#thread-safety)
- [Error Handling](#error-handling)
- [Quick Start Guide](#quick-start-guide)
  - [Event-Based Parsing](#event-based-parsing)
    - [Parsing with `parse`](#parsing-with-parse)
    - [Parsing with `parseObject` & `parseArray`](#parsing-with-parseobject--parsearray)
    - [Termination](#termination)
    - [In-Place Parsing](#in-place-parsing)
  - [Rendering](#rendering)
    - [Renderer Classes](#renderer-classes)
    - [Configuring the Renderer](#configuring-the-renderer)
  - [Document](#Document)
    - [Loading and Saving Documents](#loading-and-saving-documents)
    - [Accessing Document Data](#accessing-document-data)
    - [Modifying Document Data](#modifying-document-data)
    - [Applying Merge Patches](#applying-merge-patches)
- [Reference](#reference)



## Compatibility

The following platform and compiler combinations have been tested:

- Linux using g++ 5.4/7.5
- Linux using Clang 6.0/11.1
- Windows using Visual C++ 8/10/14/15/16
- macOS using Xcode 12
- iOS (macOS using Xcode 12)
- Android (Windows using Android Studio 4.1.2)



## Integration

Eclog-CPP is self-contained; no specific build process is required. To integrate Eclog-CPP into your project, first add the `Include` directory to the header search path. Then add the source files located in
the `Source` directory to the sources. That's all.

A portable and compact version is also provided; all header files and source files are merged into two files, `Eclog.h` and `Eclog.cpp`, in the `Compact` directory. You can easily copy the two files into your project, which allows all the classes and functions to be used by including only one header file in your code.



## Memory Management

Dynamic container classes in Eclog-CPP allow you to have memory management through the use of allocators. Each dynamic container has a template parameter specifying the allocator to be used. You can specify different memory management schemes on either a global or per-container basis by overriding the default allocator template parameter (See [Allocator Requirements](Doc/AllocatorRequirements.md) and [Memory Management Configuration](Doc/MemoryManagementConfiguration.md)).



## Thread Safety

Eclog-CPP offers conditional thread safety. It is safe to make concurrent use of distinct objects but unsafe to make concurrent use of a single object.



## Error Handling

Eclog-CPP supports both general error handling approaches: exceptions and error codes. You'll see that many functions and class methods in Eclog-CPP are overloaded on the two different error reporting mechanisms. For example,

```c++
template<typename Handler>
void parse(Context& ctx, Handler& handler);

template<typename Handler>
void parse(Context& ctx, Handler& handler, ErrorCode& ec);
```

Generally speaking, overloaded functions with an [ErrorCode](Doc/ErrorCode.md) parameter use error codes to report errors, while overloaded functions without an [ErrorCode](Doc/ErrorCode.md) parameter use exceptions to report errors.

An example of using exceptions to handle errors:

```c++
try {
    eclog::parse(ctx, handler);
}
catch (eclog::ParseErrorException& e)
{
    std::cout << "Parse error at line " << e.lineNumber()
        << ", column " << e.columnNumber()
        << ", " << e.what() << std::endl;
}
catch (eclog::Exception& e)
{
    std::cout << e.what() << std::endl;
}
```

An example of using error codes to handle errors:

```c++
eclog::ErrorCode ec;

eclog::parse(ctx, handler, ec);

if (ec == eclog::ec_parse_error)
{
    const eclog::ParseError& e = eclog::cast<eclog::ParseError>(ec.error());

    std::cout << "Parse error at line " << e.line()
        << ", column " << e.column()
        << ", " << e.message() << std::endl;
}
else if (ec)
{
    std::cout << ec.message() << std::endl;
}
```

Error codes and exceptions in Eclog-CPP are nearly equivalent except for critical errors. Most critical errors (or faults), such as logic errors and out-of-memory errors, are unrecoverable at runtime. Hence a function with an [ErrorCode](Doc/ErrorCode.md) parameter may also throw exceptions.

If exceptions are unavailable in your project, you can suppress the throwing of exceptions (see [Error Handling Configuration](Doc/ErrorHandlingConfiguration.md)).



## Quick Start Guide

### Event-Based Parsing

Event-based parsing is simple: when an element is encountered, the parsing engine reports it directly to the handler you specify. It is more efficient than tree-based parsing for many types of applications. Eclog-CPP offers two parsing APIs for different situations.

#### Parsing with `parse`

The [parse](Doc/parse.md) function is the primary interface of event-based parsing, enabling you to go through the elements of an Eclog text in a single function call.

You provide an input stream ([InputStream](Doc/InputStream.md) instance) that specifies the input source and a parsing buffer ([ParsingBuffer](Doc/ParsingBuffer.md) instance) used to hold intermediate results during the parsing. Next, use the input stream and parsing buffer instances to create a parsing context ([Context](Doc/Context.md) instance). Finally, call [parse](Doc/parse.md) with the parsing context and your handler as the arguments. For example,

[Note: Eclog-CPP provides several implementations of [InputStream](Doc/InputStream.md) and [ParsingBuffer](Doc/ParsingBuffer.md); you can also use custom implementations when necessary.]

```c++
std::fstream fs("Person.ecl", std::ios::in | std::ios::binary);

eclog::StdStreamInputStream stream(fs);
eclog::DynamicParsingBuffer buffer;

eclog::Context ctx(stream, buffer);

MyHandler handler;

eclog::parse(ctx, handler);
```

The [handler requirements of parse](Doc/parse.md#requirements) are syntax-oriented; any class that satisfies the requirements can be used as a handler class. For instance,

```c++
class MyHandler {
public:
    void onObjectBegin();
    void onObjectEnd();
    void onArrayBegin();
    void onArrayEnd();
    void onKey(const eclog::Key& key);
    void onValue(const eclog::Value& value);
};
```

Given the following example Eclog file,

```
# Person.ecl
firstName: John
lastName: Smith
age: 27
address:
{
    streetAddress: "21 2nd Street"
    city: "New York"
    state: NY
    postalCode: "10021-3100"
}
phoneNumbers:
[
    { type: home, number: "212 555-1234" }
    { type: office, number: "646 555-4567" }
]
```

your handler will receive the following sequence of events during the parsing process:

```
onObjectBegin
onKey "firstName"
onValue "John"
onKey "lastName"
onValue "Smith"
onKey "age"
onValue 27
onKey "address"
onObjectBegin
onKey "streetAddress"
onValue "21 2nd Street"
onKey "city"
onValue "New York"
onKey "state"
onValue "NY"
onKey "postalCode"
onValue "10021-3100"
onObjectEnd
onKey "phoneNumbers"
onArrayBegin
onObjectBegin
onKey "type"
onValue "home"
onKey "number"
onValue "212 555-1234"
onObjectEnd
onObjectBegin
onKey "type"
onValue "office"
onKey "number"
onValue "646 555-4567"
onObjectEnd
onArrayEnd
onObjectEnd
```

#### Parsing with `parseObject` & `parseArray`

As an alternative interface to [parse](Doc/parse.md), the [parseObject](Doc/parseObject.md) and [parseArray](Doc/parseArray.md) functions allow you to handle only the top-level members of an object or array in the corresponding handler. This can be handy for producing more readable code, especially when working with lambda expressions.

First, create a parsing context in the same way as detailed in the previous section. Then, call [parseObject](Doc/parseObject.md) with the parsing context and your handler as the arguments. This example takes a lambda expression as the handler:

```c++
const char* text = "a: Foo, b: {c: true, d: [1, 2]}, e: [3, Bar], f: null";

eclog::MemoryInputStream stream(text, strlen(text));
eclog::DynamicParsingBuffer buffer;

eclog::Context ctx(stream, buffer);

eclog::parseObject(ctx, [&](eclog::Key key, eclog::Value value)
{
    std::cout << key << std::endl;
});
```

The output of the above code is:

```
a
b
e
f
```

As you can see, the handler receives only the top-level members. When you need to go deep into a nested object or array, call [parseObject](Doc/parseObject.md) or [parseArray](Doc/parseArray.md) at that point. Let's modify the example above to retrieve array `d`'s members:

```c++
const char* text = "a: Foo, b: {c: true, d: [1, 2]}, e: [3, Bar], f: null";

eclog::MemoryInputStream stream(text, strlen(text));
eclog::DynamicParsingBuffer buffer;

eclog::Context ctx(stream, buffer);

eclog::parseObject(ctx, [&](eclog::Key key, eclog::Value value)
{
    if (key == "b")
    {
        eclog::parseObject(ctx, [&](eclog::Key key, eclog::Value value)
        {
            if (key == "d")
            {
                eclog::parseArray(ctx, [&](eclog::Value value)
                {
                    std::cout << value.asNumber() << std::endl;
                });
            }
        });
    }
});
```

The output from the modified code is

```
1
2
```

#### Termination

If you want to terminate a parsing process, call [Context::terminate](Doc/Context.md#terminate) in your handler. For example,

```c++
const char* text = "a: Apple, b: Banana, c: Lemon, d: Pear, e: Orange";

eclog::MemoryInputStream stream(text, strlen(text));
eclog::DynamicParsingBuffer buffer;

eclog::Context ctx(stream, buffer);

try
{
    eclog::parseObject(ctx, [&](eclog::Key key, eclog::Value value)
    {
        std::cout << value.asString() << std::endl;

        if (key == "c") {
            ctx.terminate();
        }
    });
}
catch (eclog::ParseErrorException& e)
{
    if (e.error() == eclog::pe_user_asked_for_termination) {
        std::cout << "(terminated)" << std::endl;
    }
}
```

The output of the above code is the following:

```
Apple
Banana
Lemon
(terminated)
```

#### In-Place Parsing

Eclog-CPP supports in-place parsing, which is parsing an Eclog text stored in a contiguous memory buffer without dynamic memory allocations. Consider the following example:

```c++
char array[2048];

size_t length = loadFile("Person.ecl", array, sizeof(array) - 1);

eclog::MemoryInputStream stream(array, length);
eclog::InplaceParsingBuffer buffer(array, sizeof(array));

eclog::Context ctx(stream, buffer);

MyHandler handler;

eclog::parse(ctx, handler);
```

As the above code shows, [InplaceParsingBuffer](Doc/InplaceParsingBuffer.md) and [MemoryInputStream](Doc/MemoryInputStream.md) can safely share the same memory buffer—although [InplaceParsingBuffer](Doc/InplaceParsingBuffer.md) stores intermediate results in the shared buffer, it will never overwrite the part that [MemoryInputStream](Doc/MemoryInputStream.md) is going to read.

[Note: In extreme cases, the buffer length required by [InplaceParsingBuffer](Doc/InplaceParsingBuffer.md) is 1 byte more than [MemoryInputStream](Doc/MemoryInputStream.md). The reason for this is that there is a hidden null character after the last character of all strings returned by parsing buffers to make the strings compatible with C APIs.]



### Rendering

Rendering is the reverse of parsing, meaning it is the process of converting data into an Eclog text. Eclog-CPP offers renderer classes to help you render Eclog texts efficiently.

#### Renderer Classes

The renderer classes (i.e., [Renderer](Doc/Renderer.md), [ObjectRenderer](Doc/ObjectRenderer.md), and [ArrayRenderer](Doc/ArrayRenderer.md)) allow you to render (or compose) Eclog texts in the immediate mode.

You provide an output stream ([OutputStream](Doc/OutputStream.md) instance) that specifies the output target. Then, create the primary renderer ([Renderer](Doc/Renderer.md) instance) from the output stream. Next, use object renderers ([ObjectRenderer](Doc/ObjectRenderer.md) instances) and array renderers ([ArrayRenderer](Doc/ArrayRenderer.md) instances) to render objects, arrays, and their members in the order you go through the Eclog text. Finally, close the primary renderer.

This is an example of rendering an Eclog text to the standard output:

[Note: Eclog-CPP provides several implementations of [OutputStream](Doc/OutputStream.md); you can also use custom implementations when necessary.]

```c++
eclog::StdStreamOutputStream stream(std::cout);

eclog::Renderer renderer(stream);

renderer.beginRootObject();
{
    eclog::ObjectRenderer root(renderer);

    root.renderMember("title", "Main Window");

    root.renderMember("id", eclog::StringDesc("main_window",
        eclog::string_notation_unquoted));

    root.renderMember("width", 400);
    root.renderMember("height", 400);
}
renderer.endRootObject();

renderer.close();
```

The output of the above code is

```
title: "Main Window"
id: main_window
width: 400
height: 400
```

You may notice that this example renders the root object with an object renderer created from the primary renderer. Renderers are handled in a hierarchical structure. To render an object, you first begin the object's rendering. Then, create a new object renderer from the renderer that began the rendering. Next, render its members by alternating calls to `renderMember` on the renderer. Finally, end the object's rendering. The steps for rendering an array are similar to those for rendering an object.

Let's modify the example above to add a nested object:

```c++
eclog::StdStreamOutputStream stream(std::cout);

eclog::Renderer renderer(stream);

renderer.beginRootObject();
{
    eclog::ObjectRenderer root(renderer);

    root.renderMember("title", "Main Window");

    root.renderMember("id", eclog::StringDesc("main_window",
        eclog::string_notation_unquoted));

    root.beginObject("menu");
    {
        eclog::ObjectRenderer menu(root);

        menu.renderMember("id", eclog::StringDesc("main_menu",
            eclog::string_notation_unquoted));

        menu.beginArray("items");
        {
            eclog::ArrayRenderer items(menu);

            items.renderMember("File");
            items.renderMember("Edit");
        }
        menu.endArray();
    }
    root.endObject();

    root.renderMember("width", 400);
    root.renderMember("height", 400);
}
renderer.endRootObject();

renderer.close();
```

The output of the above code is

```
title: "Main Window"
id: main_window
menu:
{
    id: main_menu
    items:
    [
        "File"
        "Edit"
    ]
}
width: 400
height: 400
```

#### Configuring the Renderer

You can configure an Eclog text's rendering by providing the primary renderer with a renderer configuration ([RendererConfig](Doc/RendererConfig.md) instance). Let's modify the example in the previous section to make it create a JSON-compatible Eclog text:

```c++
eclog::StdStreamOutputStream stream(std::cout);

eclog::RendererConfig rc(eclog::RendererConfig::scheme_json_compatible);

rc.indentCharacter = eclog::RendererConfig::indent_character_space;
rc.indentSize = 2;
rc.placeOpenBracketOnNewLineForObjects = false;
rc.placeOpenBracketOnNewLineForArrays = false;

eclog::Renderer renderer(stream, rc);

renderer.beginRootObject();
{
    eclog::ObjectRenderer root(renderer);

    root.renderMember("title", "Main Window");

    root.renderMember("id", eclog::StringDesc("main_window",
        eclog::string_notation_unquoted));

    root.beginObject("menu");
    {
        eclog::ObjectRenderer menu(root);

        menu.renderMember("id", eclog::StringDesc("main_menu",
            eclog::string_notation_unquoted));

        menu.beginArray("items");
        {
            eclog::ArrayRenderer items(menu);

            items.renderMember("File");
            items.renderMember("Edit");
        }
        menu.endArray();
    }
    root.endObject();

    root.renderMember("width", 400);
    root.renderMember("height", 400);
}
renderer.endRootObject();

renderer.close();
```

The output of the above code is

```
{
  "title": "Main Window",
  "id": "main_window",
  "menu": {
    "id": "main_menu",
    "items": [
      "File",
      "Edit"
    ]
  },
  "width": 400,
  "height": 400
}
```



### Document

A document ([Document](Doc/Document.md) instance) is a dynamic container that stores an Eclog text in memory as a tree; each key and value is stored as a typed node in the document tree. The [Document](Doc/Document.md) class implements the [ObjectNode](Doc/ObjectNode.md) interface; hence, we can say a document is an object node ([ObjectNode](Doc/ObjectNode.md) instance), the root node. By using documents, you can easily load, access, modify, and save Eclog texts.

#### Loading and Saving Documents

To load an Eclog text into a document (or an object node), use the `parse` method. For example,

```c++
eclog::Document doc;

// Load from a string
doc.parse("server: localhost, ports: [8000, 8001], connection_max: 5000");
```

Another example is the following:

```c++
eclog::Document doc;

std::fstream is("Config.ecl", std::ios::in | std::ios::binary);

// Load from a file
doc.parse(is);
```

To save a document (or an object node) as an Eclog text, use the `render` method. For example,

```c++
eclog::Document doc;

// ...

std::fstream os("Config.ecl", std::ios::out | std::ios::binary);

// Save to a file
doc.render(os);
```

#### Accessing Document Data

If you want to access an element of a document (or an object node), you can use the `find` or `get` methods.

An example of accessing elements of a document with type-constrained `find` methods:

```c++
// Find a string value by key
eclog::ObjectNode::Iterator it = doc.findString("firstName");

if (it != doc.end())
{
    eclog::StringNode& firstName = it->value().asString();

    std::cout << firstName.value() << std::endl;
}

// Find a number value by key
it = doc.findNumber("age");

if (it != doc.end())
{
    eclog::NumberNode& age = it->value().asNumber();

    std::cout << age.value() << std::endl;
}
```

An example of accessing elements of a document with type-constrained `get` methods:

```c++
try
{
    // Get a string value by key
    std::cout << doc.getString("firstName").value() << std::endl;

    // Get a number value by key
    std::cout << doc.getNumber("age").value() << std::endl;
}
catch (eclog::OutOfRangeException& e)
{
    // ...
}
catch (eclog::BadCastException& e)
{
    // ...
}
```

You can replace the `get` methods with the `getOrAdd` methods to ensure that an element exists before accessing it. For example,

```c++
// If the object node doesn't exist, an empty object is added
eclog::ObjectNode& address = doc.getOrAddObject("address");

// You can specify the default value through the second argument
eclog::StringNode& city = address.getOrAddString("city", "New York");
```

You can access an element of an array node ([ArrayNode](Doc/ArrayNode.md) instance) by referring to its index, such as in this example:

```c++
eclog::ArrayNode& pNums = doc.getArray("phoneNumbers");

for (size_t i = 0; i < pNums.size(); ++i)
{
    // Get the nth element of the array
    eclog::ArrayNode::Element& element = pNums.at(i);

    // ...
}
```

This example accesses an array element by using a type-constrained `get` method:

```c++
if (!pNums.empty())
{
    // Get the first object node of the array
    eclog::ObjectNode& pNum = pNums.getObject(0);

    // ...
}
```

You can iterate over an object node or array node by using iterators or C++11 range-based for loop, as in the following:

```c++
for (eclog::ObjectNode::Iterator it = doc.begin(); it != doc.end(); ++it)
{
    eclog::ObjectNode::Element& element = *it;

    std::cout << element.key().str() << std::endl;
}

eclog::ArrayNode& pNums = doc.getArray("phoneNumbers");

for (eclog::ArrayNode::Iterator it = pNums.begin(); it != pNums.end(); ++it)
{
    eclog::ArrayNode::Element& element = *it;

    // ...
}
```

This is an example of C++11 range-based for loop:

```c++
for (auto& element : doc)
{
    std::cout << element.key().str() << std::endl;
}

for (auto& element : doc.getArray("phoneNumbers"))
{
    // ...
}
```

#### Modifying Document Data

If you want to add a new element into an object node or array node, you can use the `append` or `insert` methods. For example,

```c++
eclog::Document doc;

doc.append("title", "Main Window");

// Add an empty object
doc.append("menu", eclog::empty_object);

eclog::ObjectNode& menu = doc.last().value().asObject();

// Add an empty array
menu.append("items", eclog::empty_array);

eclog::ArrayNode& menuItems = menu.last().value().asArray();

menuItems.append("File");
menuItems.append("Edit");

// Insert a string before a given position
doc.insert(doc.find("menu"), "id",
    eclog::StringDesc("main_window", eclog::string_notation_unquoted));

doc.append("width", 400);
doc.append("height", 400);
```

If you want to remove an element from an object node or array node, you can use the overloads of the `remove` method. For example,

```c++
// Remove a value from an object by key
doc.remove("title");

// Remove a value from an object by position
doc.remove(doc.begin());

// Remove a value from an array by index
menuItems.remove(1);
```

You can update the value of an element by using the `updateValue` method, as in the following example:

```c++
doc.get("width").updateValue(500);
doc.get("height").updateValue(500);

// This will replace the array with a null value
menu.get("items").updateValue(eclog::null);
```

#### Applying Merge Patches

Eclog-CPP supports merge patches and conforms to the processing rules defined in the JSON Merge Patch [(RFC 7396)](http://tools.ietf.org/html/rfc7396) standard. For example, given the following original Eclog text,

```
a: b, c: {d: e, f: g}
```

changing the value of `a` and removing `f` can be described with this merge patch:

```
a: z, c: {f: null}
```

To apply a merge patch to a target document, call the `merge` method on the target document with the merge patch document as the argument, like this:

```c++
eclog::Document doc;

doc.parse("a: b, c: {d: e, f: g}");

eclog::Document patch;

patch.parse("a: z, c: {f: null}");

doc.merge(patch);

std::cout << doc.toStdString();
```

The output of the above code is

```
a: z
c:
{
    d: e
}
```



## Reference

<table>
  <tr>
    <th colspan="4">Core</th>
  </tr>
  <tr>
    <td><strong>Abstract Classes</strong><br><a href="Doc/Node.md">Node</a><br><a href="Doc/KeyNode.md">KeyNode</a><br><a href="Doc/ValueNode.md">ValueNode</a><br><a href="Doc/NullNode.md">NullNode</a><br><a href="Doc/BooleanNode.md">BooleanNode</a><br><a href="Doc/StringNode.md">StringNode</a><br><a href="Doc/NumberNode.md">NumberNode</a><br><a href="Doc/ObjectNode.md">ObjectNode</a><br><a href="Doc/ArrayNode.md">ArrayNode</a><br><br><br><br><br><br><br><br><br></td>
    <td><strong>Classes</strong><br><a href="Doc/Document.md">Document</a><br><a href="Doc/KeyDesc.md">KeyDesc</a><br><a href="Doc/ValueDesc.md">ValueDesc</a><br><a href="Doc/StringDesc.md">StringDesc</a><br><a href="Doc/NumberDesc.md">NumberDesc</a><br><a href="Doc/ObjectDesc.md">ObjectDesc</a><br><a href="Doc/ArrayDesc.md">ArrayDesc</a><br><a href="Doc/Context.md">Context</a><br><a href="Doc/Key.md">Key</a><br><a href="Doc/Value.md">Value</a><br><a href="Doc/Renderer.md">Renderer</a><br><a href="Doc/ObjectRenderer.md">ObjectRenderer</a><br><a href="Doc/ArrayRenderer.md">ArrayRenderer</a><br><a href="Doc/RendererConfig.md">RendererConfig</a><br><a href="Doc/Null.md">Null</a><br><a href="Doc/cstring.md">cstring</a><br><a href="Doc/Allocator.md">Allocator</a><br></td>
    <td><strong>Free Functions</strong><br><a href="Doc/parse.md">parse</a><br><a href="Doc/parseObject.md">parseObject</a><br><a href="Doc/parseArray.md">parseArray</a><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br></td>
    <td><strong>Global Variables</strong><br><a href="Doc/g_null.md">null</a><br><br><strong>Enumerations</strong><br><a href="Doc/Linebreak.md">Linebreak</a><br><a href="Doc/StringNotation.md">StringNotation</a><br><a href="Doc/ValueType.md">ValueType</a><br><a href="Doc/NumberInfo.md">NumberInfo</a><br><a href="Doc/NodeType.md">NodeType</a><br><a href="Doc/EmptyObjectTag.md">EmptyObjectTag</a><br><a href="Doc/EmptyArrayTag.md">EmptyArrayTag</a><br><br><br><br><br><br><br><br></td>
  </tr>
</table>
<table>
  <tr>
    <th colspan="4">I/O Streams</th>
  </tr>
  <tr>
    <td><strong>Abstract Classes</strong><br><a href="Doc/InputStream.md">InputStream</a><br><a href="Doc/OutputStream.md">OutputStream</a><br><br><br><br></td>
    <td><strong>Classes</strong><br><a href="Doc/MemoryInputStream.md">MemoryInputStream</a><br><a href="Doc/StdStreamInputStream.md">StdStreamInputStream</a><br><a href="Doc/MemoryOutputStream.md">MemoryOutputStream</a><br><a href="Doc/StdStreamOutputStream.md">StdStreamOutputStream</a><br><a href="Doc/StdStringOutputStream.md">StdStringOutputStream</a><br></td>
  </tr>
</table>
<table>
  <tr>
    <th colspan="4">Parsing Buffers</th>
  </tr>
  <tr>
    <td><strong>Abstract Classes</strong><br><a href="Doc/ParsingBuffer.md">ParsingBuffer</a><br><br></td>
    <td><strong>Classes</strong><br><a href="Doc/DynamicParsingBuffer.md">DynamicParsingBuffer</a><br><a href="Doc/InplaceParsingBuffer.md">InplaceParsingBuffer</a><br></td>
  </tr>
</table>
<table>
  <tr>
    <th colspan="4">Error Handling</th>
  </tr>
  <tr>
    <td><strong>Exception Classes</strong><br><a href="Doc/Exception.md">Exception</a><br><a href="Doc/RuntimeErrorException.md">RuntimeErrorException</a><br><a href="Doc/BufferOverflowException.md">BufferOverflowException</a><br><a href="Doc/LogicErrorException.md">LogicErrorException</a><br><a href="Doc/OutOfRangeException.md">OutOfRangeException</a><br><a href="Doc/LengthErrorException.md">LengthErrorException</a><br><a href="Doc/InvalidArgumentException.md">InvalidArgumentException</a><br><a href="Doc/InvalidOperationException.md">InvalidOperationException</a><br><a href="Doc/IOErrorException.md">IOErrorException</a><br><a href="Doc/UnicodeErrorException.md">UnicodeErrorException</a><br><a href="Doc/DecodeErrorException.md">DecodeErrorException</a><br><a href="Doc/EncodeErrorException.md">EncodeErrorException</a><br><a href="Doc/OutOfMemoryException.md">OutOfMemoryException</a><br><a href="Doc/ParseErrorException.md">ParseErrorException</a><br><a href="Doc/BadCastException.md">BadCastException</a><br></td>
    <td><strong>Error Classes</strong><br><a href="Doc/Error.md">Error</a><br><a href="Doc/RuntimeError.md">RuntimeError</a><br><a href="Doc/BufferOverflow.md">BufferOverflow</a><br><a href="Doc/LogicError.md">LogicError</a><br><a href="Doc/OutOfRange.md">OutOfRange</a><br><a href="Doc/LengthError.md">LengthError</a><br><a href="Doc/InvalidArgument.md">InvalidArgument</a><br><a href="Doc/InvalidOperation.md">InvalidOperation</a><br><a href="Doc/IOError.md">IOError</a><br><a href="Doc/UnicodeError.md">UnicodeError</a><br><a href="Doc/DecodeError.md">DecodeError</a><br><a href="Doc/EncodeError.md">EncodeError</a><br><a href="Doc/OutOfMemory.md">OutOfMemory</a><br><a href="Doc/ParseError.md">ParseError</a><br><a href="Doc/BadCast.md">BadCast</a><br></td>
    <td><strong>Classes</strong><br><a href="Doc/ErrorCode.md">ErrorCode</a><br><a href="Doc/ErrorId.md">ErrorId</a><br><br><strong>Free Functions</strong><br><a href="Doc/cast.md">cast</a><br><br><br><br><br><br><br><br><br><br><br></td>
    <td><strong>Enumerations</strong><br><a href="Doc/Success.md">Success</a><br><a href="Doc/ErrorCodeEnum.md">ErrorCodeEnum</a><br><a href="Doc/ParseErrorEnum.md">ParseErrorEnum</a><br><br><br><br><br><br><br><br><br><br><br><br><br></td>
  </tr>
</table>
<table>
  <tr>
    <th colspan="4">Misc</th>
  </tr>
  <tr>
    <td><strong>Utility</strong><br><a href="Doc/UTF8Decoder.md">UTF8Decoder</a><br><a href="Doc/UTF8Encoder.md">UTF8Encoder</a><br></td>
    <td><strong>Requirements</strong><br><a href="Doc/AllocatorRequirements.md">Allocator Requirements</a><br><br></td>
    <td><strong>Macros</strong><br><a href="Doc/MemoryManagementConfiguration.md">Memory Management Configuration</a><br><a href="Doc/ErrorHandlingConfiguration.md">Error Handling Configuration</a><br></td>
  </tr>
</table>
