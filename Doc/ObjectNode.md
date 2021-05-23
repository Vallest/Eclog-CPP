# ObjectNode

```c++
class ObjectNode
```

Inherited from: [ValueNode](ValueNode.md).

Required header: `<Eclog/ObjectNode.h>`

The [ObjectNode](ObjectNode.md) abstract class represents an object node in a document tree (See [Document](Document.md)).

## Member classes

| Name                            | Description                                                  |
| ------------------------------- | ------------------------------------------------------------ |
| [Element](ObjectNodeElement.md) | Provides an interface for accessing an element (key-value pair) in the object. |
| `Iterator`                      | Provides a STL-style bidirectional iterator for the object.  |
| `ConstIterator`                 | Provides a STL-style const bidirectional iterator for the object. |

* * *

## Member functions

| Name                                                         | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [clear](#clear)                                              | Removes all elements.                                        |
| [empty](#empty)                                              | Checks if this object is empty.                              |
| [size](#size)                                                | Returns the number of elements.                              |
| [begin](#begin)                                              | Returns an iterator to the first element.                    |
| [end](#end)                                                  | Returns an iterator to the past-the-end element.             |
| [first](#first)                                              | Returns the first element.                                   |
| [last](#last)                                                | Returns the last element.                                    |
| [contains](#contains)                                        | Checks if a specified key exists.                            |
| [find](#find)                                                | Finds an element with a specified key.                       |
| [findNull](#findnull-findboolean-findstring-findnumber-findobject-and-findarray) | Finds a null value with a specified key.                     |
| [findBoolean](#findnull-findboolean-findstring-findnumber-findobject-and-findarray) | Finds a Boolean value with a specified key.                  |
| [findString](#findnull-findboolean-findstring-findnumber-findobject-and-findarray) | Finds a string value with a specified key.                   |
| [findNumber](#findnull-findboolean-findstring-findnumber-findobject-and-findarray) | Finds a number value with a specified key.                   |
| [findObject](#findnull-findboolean-findstring-findnumber-findobject-and-findarray) | Finds an object value with a specified key.                  |
| [findArray](#findnull-findboolean-findstring-findnumber-findobject-and-findarray) | Finds an array value with a specified key.                   |
| [get](#get)                                                  | Gets an element with a specified key.                        |
| [getValue](#getvalue)                                        | Gets a value with a specified key.                           |
| [getNull](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a null value with a specified key.                      |
| [getBoolean](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a Boolean value with a specified key.                   |
| [getString](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a string value with a specified key.                    |
| [getNumber](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a number value with a specified key.                    |
| [getObject](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets an object value with a specified key.                   |
| [getArray](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets an array value with a specified key.                    |
| [getOrAddValue](#getoraddvalue)                              | Gets or adds a value with a specified key.                   |
| [getOrAddNull](#getoraddnull-getoraddboolean-getoraddstring-getoraddnumber-getoraddobject-and-getoraddarray) | Gets or adds a null value with a specified key.              |
| [getOrAddBoolean](#getoraddnull-getoraddboolean-getoraddstring-getoraddnumber-getoraddobject-and-getoraddarray) | Gets or adds a Boolean value with a specified key.           |
| [getOrAddString](#getoraddnull-getoraddboolean-getoraddstring-getoraddnumber-getoraddobject-and-getoraddarray) | Gets or adds a string value with a specified key.            |
| [getOrAddNumber](#getoraddnull-getoraddboolean-getoraddstring-getoraddnumber-getoraddobject-and-getoraddarray) | Gets or adds a number value with a specified key.            |
| [getOrAddObject](#getoraddnull-getoraddboolean-getoraddstring-getoraddnumber-getoraddobject-and-getoraddarray) | Gets or adds an object value with a specified key.           |
| [getOrAddArray](#getoraddnull-getoraddboolean-getoraddstring-getoraddnumber-getoraddobject-and-getoraddarray) | Gets or adds an array value with a specified key.            |
| [append](#append)                                            | Inserts an element at the end.                               |
| [insert](#insert)                                            | Inserts an element before a given position.                  |
| [appendForce](#appendforce)                                  | Inserts an element at the end.                               |
| [insertForce](#insertforce)                                  | Inserts an element before a given position.                  |
| [merge](#merge)                                              | Merges a patch object into this object.                      |
| [remove](#remove)                                            | Removes specified elements.                                  |
| [parse](#parse)                                              | Parses an Eclog text and replaces elements with the parsing result. |
| [render](#render)                                            | Renders this object and outputs the Eclog text result to a given output stream. |
| [toStdString](#tostdstring)                                  | Renders this object and returns the Eclog text result as a C++ string. |
| [assign](#assign)                                            | Assigns new elements to this object.                         |

* * *

### clear

```c++
virtual void clear();
```

Removes all elements.

#### Iterator validity

All iterators related to this object are invalidated, except the [end](#end) iterators.

#### Complexity

Linear in size.

* * *

### empty

```c++
virtual bool empty() const;
```

Checks if this object is empty.

#### Return value

`bool` *true* if this object is empty, *false* otherwise.

#### Complexity

Constant.

* * *

### size

```c++
virtual size_t size() const;
```

Returns the number of elements.

#### Return value

`size_t` Number of elements in this object.

#### Complexity

Constant.

* * *

### begin

```c++
virtual Iterator begin();
virtual ConstIterator begin() const;
```

Returns an iterator to the first element.

If this object is empty, the returned iterator will be equal to [end](#end).

#### Return value

`Iterator` Iterator to the first element.

`ConstIterator` Iterator to the first element.

#### Complexity

Constant.

* * *

### end

```c++
virtual Iterator end();
virtual ConstIterator end() const;
```

Returns an iterator to the past-the-end element.

This element acts as a placeholder; attempting to access it results in `OutOfRange` fault.

#### Return value

`Iterator` Iterator to the past-the-end element.

`ConstIterator` Iterator to the past-the-end element.

#### Complexity

Constant.

* * *

### first

```c++
Element& first();
```

Returns the first element.

#### Return value

[Element](ObjectNodeElement.md)`&` Reference to the first element.

#### Errors

An `OutOfRange` fault occurs if this object is empty.

#### Complexity

Constant.

* * *

### last

```c++
Element& last();
```

Returns the last element.

#### Return value

[Element](ObjectNodeElement.md)`&` Reference to the last element.

#### Errors

An `OutOfRange` fault occurs if this object is empty.

#### Complexity

Constant.

* * *

### contains

```c++
virtual bool contains(cstring key) const;
```

Checks if the specified key exists.

#### Parameters

[cstring](cstring.md) **key** Key to search for.

#### Return value

`bool` *true* if the specified key exists, *false* otherwise.

#### Complexity

Logarithmic in size.

* * *

### find

```c++
virtual Iterator find(cstring key);
virtual ConstIterator find(cstring key) const;
```

Finds an element with the specified key.

#### Parameters

[cstring](cstring.md) **key** Key of the element to search for.

#### Return value

`Iterator` Iterator to the element if found, [end](#end) otherwise.

`ConstIterator` Iterator to the element if found, [end](#end) otherwise.

#### Complexity

Logarithmic in size.


* * *

### findNull, findBoolean, findString, findNumber, findObject, and findArray

```c++
Iterator findNull(cstring key);
ConstIterator findNull(cstring key) const;

Iterator findBoolean(cstring key);
ConstIterator findBoolean(cstring key) const;

Iterator findString(cstring key);
ConstIterator findString(cstring key) const;

Iterator findNumber(cstring key);
ConstIterator findNumber(cstring key) const;

Iterator findObject(cstring key);
ConstIterator findObject(cstring key) const;

Iterator findArray(cstring key);
ConstIterator findArray(cstring key) const;
```

Finds a value of a specific type with the specified key.

#### Parameters

[cstring](cstring.md) **key** Key of the element to search for.

#### Return value

`Iterator` Iterator to the element if found, [end](#end) otherwise.

`ConstIterator` Iterator to the element if found, [end](#end) otherwise.

#### Complexity

Logarithmic in size.

* * *

### get

```c++
Element& get(cstring key);
const Element& get(cstring key) const;
```

Gets an element with the specified key.

#### Parameters

[cstring](cstring.md) **key** Key of the element to search for.

#### Return value

[Element](ObjectNodeElement.md)`&` Reference to the element.

`const` [Element](ObjectNodeElement.md)`&` Reference to the element.

#### Errors

An `OutOfRange` fault occurs if the specified key does not exist.

#### Complexity

Logarithmic in size.

* * *

### getValue

```c++
ValueNode& getValue(cstring key);
const ValueNode& getValue(cstring key) const;
```

Gets a value with the specified key.

#### Parameters

[cstring](cstring.md) **key** Key of the element to search for.

#### Return value

[ValueNode](ValueNode.md)`&` Reference to the value node.

`const` [ValueNode](ValueNode.md)`&` Reference to the value node.

#### Errors

An `OutOfRange` fault occurs if the specified key does not exist.

#### Complexity

Logarithmic in size.

* * *

### getNull, getBoolean, getString, getNumber, getObject, and getArray

```c++
NullNode& getNull(cstring key);
const NullNode& getNull(cstring key) const;

BooleanNode& getBoolean(cstring key);
const BooleanNode& getBoolean(cstring key) const;

StringNode& getString(cstring key);
const StringNode& getString(cstring key) const;

NumberNode& getNumber(cstring key);
const NumberNode& getNumber(cstring key) const;

ObjectNode& getObject(cstring key);
const ObjectNode& getObject(cstring key) const;

ArrayNode& getArray(cstring key);
const ArrayNode& getArray(cstring key) const;
```

Gets a value with the specified key and casts the value to a specified type of value.

#### Parameters

[cstring](cstring.md) **key** Key of the element to search for.

#### Return value

(value node type)`&` Reference to the value node.

`const` (value node type)`&` Reference to the value node.

#### Errors

An `OutOfRange` fault occurs if the specified key does not exist.

A `BadCast` fault occurs if the value node is not of the specified type.

#### Complexity

Logarithmic in size.

* * *

### getOrAddValue

```c++
ValueNode& getOrAddValue(const KeyDesc& key,
    const ValueDesc& defaultValue = null);
```

Gets a value with the specified key, or inserts a value with the specified key at the [end](#end), if the key does not exist.

#### Parameters

[cstring](cstring.md) **key** Key of the element.

`const` [ValueDesc](ValueDesc.md)`&` **desc** The description of the value to be inserted.

#### Return value

[ValueNode](ValueNode.md)`&` Reference to the value node.

#### Errors

If an error occurs, this object remains untouched.

#### Complexity

Logarithmic in size.


* * *

### getOrAddNull, getOrAddBoolean, getOrAddString, getOrAddNumber, getOrAddObject, and getOrAddArray

```c++
NullNode& getOrAddNull(const KeyDesc& key,
    const Null& defaultValue = null);

BooleanNode& getOrAddBoolean(const KeyDesc& key,
    bool defaultValue = false);

StringNode& getOrAddString(const KeyDesc& key,
    const StringDesc& defaultValue = cstring());

NumberNode& getOrAddNumber(const KeyDesc& key,
    const NumberDesc& defaultValue = 0);

ObjectNode& getOrAddObject(const KeyDesc& key,
    const ObjectDesc& defaultValue = empty_object);

ArrayNode& getOrAddArray(const KeyDesc& key,
    const ArrayDesc& defaultValue = empty_array);
```

Gets a value with the specified key and casts the value to a specific type, or inserts a value with the specified key at the [end](#end), if the key does not exist.

#### Parameters

[cstring](cstring.md) **key** Key of the element.

`bool` **defaultValue** The Boolean value to be inserted.

`const` [StringDesc](StringDesc.md)`&` **defaultValue** The description of the string value to be inserted.

`const` [NumberDesc](NumberDesc.md)`&` **defaultValue** The description of the number value to be inserted.

`const` [ObjectDesc](ObjectDesc.md)`&` **defaultValue** The description of the object value to be inserted.

`const` [ArrayDesc](ArrayDesc.md)`&` **defaultValue** The description of the array value to be inserted.

#### Return value

(value node type)`&` Reference to the value node.

`const` (value node type)`&` Reference to the value node.

#### Errors

A `BadCast` fault occurs if the value node is not of the specified type.

If an error occurs, this object remains untouched.

#### Complexity

Logarithmic in size.


* * *

### append

```c++
bool append(const Element& element);
bool append(const KeyNode& key, const ValueNode& value);
bool append(const KeyDesc& key, const ValueNode& value);
bool append(const KeyNode& key, const ValueDesc& value);
bool append(const KeyDesc& key, const ValueDesc& value);
```

Inserts an element at the [end](#end) of this object if the specified key does not exist.

#### Parameters

`const` [Element](ObjectNodeElement.md)`&` **element** The element to be inserted.

`const` [KeyNode](KeyNode.md)`&` **key** The key to be inserted.

`const` [KeyDesc](KeyDesc.md)`&` **key** The description of the key to be inserted.

`const` [ValueNode](ValueNode.md)`&` **value** The value to be inserted.

`const` [ValueDesc](ValueDesc.md)`&` **value** The description of the value to be inserted.

#### Return value

`bool` *true* if the insertion took place, *false* otherwise.

#### Errors

If an error occurs, this object remains untouched.

#### Iterator validity

No changes.

#### Complexity

Logarithmic in size.

* * *

### insert

```c++
virtual Pair<Iterator, bool> insert(Iterator pos,
    const Element& element);

virtual Pair<Iterator, bool> insert(Iterator pos,
    const KeyNode& key, const ValueNode& value);

virtual Pair<Iterator, bool> insert(Iterator pos,
    const KeyDesc& key, const ValueNode& value);

virtual Pair<Iterator, bool> insert(Iterator pos,
    const KeyNode& key, const ValueDesc& value);

virtual Pair<Iterator, bool> insert(Iterator pos,
    const KeyDesc& key, const ValueDesc& value);
```

Inserts an element before the given position if the specified key does not exist.

#### Parameters

`Iterator` **pos** Position in this object where the new element will be inserted before.

`const` [Element](ObjectNodeElement.md)`&` **element** The element to be inserted.

`const` [KeyNode](KeyNode.md)`&` **key** The key to be inserted.

`const` [KeyDesc](KeyDesc.md)`&` **key** The description of the key to be inserted.

`const` [ValueNode](ValueNode.md)`&` **value** The value to be inserted.

`const` [ValueDesc](ValueDesc.md)`&` **value** The description of the value to be inserted.

#### Return value

[Pair](Pair.md)`<Iterator, bool>` A pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a Boolean denoting whether the insertion took place.

#### Errors

If an error occurs, this object remains untouched.

#### Iterator validity

No changes.

#### Complexity

Logarithmic in size.

* * *

### appendForce

```c++
void appendForce(const Element& element);
void appendForce(const KeyNode& key, const ValueNode& value);
void appendForce(const KeyDesc& key, const ValueNode& value);
void appendForce(const KeyNode& key, const ValueDesc& value);
void appendForce(const KeyDesc& key, const ValueDesc& value);
```

Inserts an element at the [end](#end).

After the new element is inserted, an old element with the same key is removed if it exists.

#### Parameters

`const` [Element](ObjectNodeElement.md)`&` **element** The element to be inserted.

`const` [KeyNode](KeyNode.md)`&` **key** The key to be inserted.

`const` [KeyDesc](KeyDesc.md)`&` **key** The description of the key to be inserted.

`const` [ValueNode](ValueNode.md)`&` **value** The value to be inserted.

`const` [ValueDesc](ValueDesc.md)`&` **value** The description of the value to be inserted.

#### Errors

If an error occurs, this object remains untouched.

#### Iterator validity

No changes.

#### Complexity

Logarithmic in size.

* * *

### insertForce

```c++
virtual Iterator insertForce(Iterator pos,
    const Element& element);

virtual Iterator insertForce(Iterator pos,
    const KeyNode& key, const ValueNode& value);

virtual Iterator insertForce(Iterator pos,
    const KeyDesc& key, const ValueNode& value);

virtual Iterator insertForce(Iterator pos,
    const KeyNode& key, const ValueDesc& value);

virtual Iterator insertForce(Iterator pos,
    const KeyDesc& key, const ValueDesc& value);
```

Inserts an element before the given position.

After the new element is inserted, an old element with the same key is removed if it exists.

#### Parameters

`Iterator` **pos** Position in this object where the new element will be inserted before.

`const` [Element](ObjectNodeElement.md)`&` **element** The element to be inserted.

`const` [KeyNode](KeyNode.md)`&` **key** The key to be inserted.

`const` [KeyDesc](KeyDesc.md)`&` **key** The description of the key to be inserted.

`const` [ValueNode](ValueNode.md)`&` **value** The value to be inserted.

`const` [ValueDesc](ValueDesc.md)`&` **value** The description of the value to be inserted.

#### Return value

`Iterator` Iterator to the inserted element.

#### Errors

If an error occurs, this object remains untouched.

#### Iterator validity

No changes.

#### Complexity

Logarithmic in size.

* * *

### merge

```c++
virtual void merge(const ObjectDesc& patch);
virtual void merge(const ObjectNode& patch);
```

Merges a patch object into this object.

This function follows the processing rules of [JSON Merge Patch (RFC 7386)](https://tools.ietf.org/html/rfc7386), which is described in the following pseudo-code:

```
merge(patch)
{
    for each key/value pair in patch
    {
        if value is null
        {
            if key exists in this {
                remove the key/value pair from this
            }
        }
        else if value is object
        {
            if this[key] is not object {
                this[key] = empty object
            }

            this[key].merge(value)
        }
        else
        {
            this[key] = value
        }
    }
}
```

#### Parameters

`const` [ObjectDesc](ObjectDesc.md)`&` **patch** The description of the patch object.

`const` [ObjectNode](ObjectNode.md)`&` **patch** The patch object.

#### Errors

If an error occurs, this object remains untouched.

#### Iterator validity

No changes.

#### Complexity

Linear in the number of elements of the patch.


* * *

### remove

```c++
virtual void remove(Iterator pos);
virtual size_t remove(Iterator first, Iterator last);
virtual bool remove(cstring key);
```

Removes specified elements.

#### Parameters

`Iterator` **pos** Iterator to the element to be removed.

`Iterator` **first**, **last** Range of elements to be removed.

[cstring](cstring.md) **key** Key of the element to be removed.

#### Return value

`size_t` Number of removed elements.

`bool` *true* if an element was removed, *false* otherwise.

#### Iterator validity

Iterators referring to removed elements are invalidated.

#### Complexity

Linear in the number of elements to be removed.

* * *

### parse

```c++
virtual void parse(Context& ctx);
virtual void parse(Context& ctx, ErrorCode& ec);
virtual void parse(InputStream& stream);
virtual void parse(InputStream& stream, ErrorCode& ec);
virtual void parse(cstring str);
virtual void parse(cstring str, ErrorCode& ec);
virtual void parse(std::istream& stream);
virtual void parse(std::istream& stream, ErrorCode& ec);
virtual void parse(const std::string& str);
virtual void parse(const std::string& str, ErrorCode& ec);
virtual void parse(const char* str);
virtual void parse(const char* str, ErrorCode& ec);
```

Parses an Eclog text and replaces elements with the parsing result.

#### Parameters

[Context](Context.md)`&` **ctx** The parsing context.

[InputStream](InputStream.md)`&` **stream** The input stream to be parsed.

[cstring](cstring.md) **str** The text string to be parsed.

`std::istream&` **stream** The input stream to be parsed.

`const std::string&` **str** The text string to be parsed.

`const char*` **str** The text string to be parsed.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Errors

If an error occurs, this object remains untouched.

#### Iterator validity

All iterators related to this object are invalidated, except the [end](#end) iterators.

* * *

### render

```c++
virtual void render(OutputStream& stream) const;
virtual void render(OutputStream& stream, ErrorCode& ec) const;
virtual void render(OutputStream& stream, const RendererConfig& rc) const;
virtual void render(OutputStream& stream, const RendererConfig& rc, ErrorCode& ec) const;
virtual void render(std::ostream& stream) const;
virtual void render(std::ostream& stream, ErrorCode& ec) const;
virtual void render(std::ostream& stream, const RendererConfig& rc) const;
virtual void render(std::ostream& stream, const RendererConfig& rc, ErrorCode& ec) const;
```

Renders this object and outputs the Eclog text result to the given output stream.

#### Parameters

[OutputStream](OutputStream.md)`&` **stream** The output stream to write to.

`std::ostream&` **stream** The output stream to write to.

`const` [RendererConfig](RendererConfig.md)`&` **rc** The renderer configuration.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

* * *

### toStdString

```c++
std::string toStdString() const;
std::string toStdString(ErrorCode& ec) const;
std::string toStdString(const RendererConfig& rc) const;
std::string toStdString(const RendererConfig& rc, ErrorCode& ec) const;
```

Renders this object and returns the Eclog text result as a C++ string.

#### Parameters

`const` [RendererConfig](RendererConfig.md)`&` **rc** The renderer configuration.

[ErrorCode](ErrorCode.md)`&` **ec** Set to indicate what error occurred, if any.

#### Return value

`std::string` The Eclog text result.


* * *

### assign

```c++
virtual void assign(const ObjectDesc& desc);
virtual void assign(const ObjectNode& other);
```

Assigns new elements to this object, replacing its current elements.

#### Parameters

`const` [ObjectDesc](ObjectDesc.md)`&` **desc** An object description.

`const` [ObjectNode](ObjectNode.md)`&` **other** Another object.

#### Errors

If an error occurs, this object remains untouched.

#### Iterator validity

All iterators related to this object are invalidated, except the [end](#end) iterators.

#### Complexity

Linear in the number of elements to be removed and to be copied.

