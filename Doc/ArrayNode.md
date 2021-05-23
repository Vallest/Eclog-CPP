# ArrayNode

```c++
class ArrayNode
```

Inherited from: [ValueNode](ValueNode.md).

Required header: `<Eclog/ArrayNode.h>`

The [ArrayNode](ArrayNode.md) abstract class represents an array node in a document tree (See [Document](Document.md)).

## Member classes

| Name                           | Description                                                  |
| ------------------------------ | ------------------------------------------------------------ |
| [Element](ArrayNodeElement.md) | Provides an interface for accessing an element (value) in the array. |
| `Iterator`                     | Provides a STL-style random-access iterator for the array.   |
| `ConstIterator`                | Provides a STL-style const random-access iterator for the array. |

* * *

## Member functions

| Name                                                         | Description                                      |
| ------------------------------------------------------------ | ------------------------------------------------ |
| [clear](#clear)                                              | Removes all elements.                            |
| [empty](#empty)                                              | Checks if this array is empty.                   |
| [size](#size)                                                | Returns the number of elements.                  |
| [begin](#begin)                                              | Returns an iterator to the first element.        |
| [end](#end)                                                  | Returns an iterator to the past-the-end element. |
| [first](#first)                                              | Gets the first element.                          |
| [last](#last)                                                | Gets the last element.                           |
| [indexOf](#indexof)                                          | Gets the index of the specified element.         |
| [at](#at)                                                    | Gets an element by index.                        |
| [getValue](#getvalue)                                        | Gets a value by index.                           |
| [getNull](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a null value by index.                      |
| [getBoolean](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a Boolean value by index.                   |
| [getString](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a string value by index.                    |
| [getNumber](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets a number value by index.                    |
| [getObject](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets an object value by index.                   |
| [getArray](#getnull-getboolean-getstring-getnumber-getobject-and-getarray) | Gets an array value by index.                    |
| [append](#append)                                            | Inserts an element at the end.                   |
| [insert](#insert)                                            | Inserts an element before the given position.    |
| [remove](#remove)                                            | Removes specified elements.                      |
| [assign](#assign)                                            | Assigns new elements to this array.              |

* * *

### clear

```c++
virtual void clear();
```

Removes all elements.

#### Iterator validity

All iterators and pointers related to this array are invalidated.

#### Complexity

Linear in the number of elements to remove.

* * *

### empty

```c++
virtual bool empty() const;
```

Checks if this array is empty.

#### Return value

`bool` *true* if this array is empty, *false* otherwise.

#### Complexity

Constant.

* * *

### size

```c++
virtual size_t size() const;
```

Returns the number of elements.

#### Return value

`size_t` Number of elements in this array.

#### Complexity

Constant.

* * *

### begin

```c++
virtual Iterator begin();
virtual ConstIterator begin() const;
```

Returns an iterator to the first element.

If this array is empty, the returned iterator will be equal to [end](#end).

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
const Element& first() const;
```

Gets the first element.

#### Return value

[Element](ArrayNodeElement.md)`&` Reference to the first element.

`const` [Element](ArrayNodeElement.md)`&` Reference to the first element.

#### Errors

An `OutOfRange` fault occurs if this array is empty.

#### Complexity

Constant.

* * *

### last

```c++
Element& last();
const Element& last() const;
```

Gets the last element.

#### Return value

[Element](ArrayNodeElement.md)`&` Reference to the last element.

`const` [Element](ArrayNodeElement.md)`&` Reference to the last element.

#### Errors

An `OutOfRange` fault occurs if this array is empty.

#### Complexity

Constant.

* * *

### indexOf

```c++
virtual size_t indexOf(const Element& element) const;
```

Gets the index of the specified element.

#### Parameters

`const` [Element](ArrayNodeElement.md)`&` **element** An element in this array.

#### Return value

`size_t` Index of the specified element.

#### Complexity

Constant.

* * *

### at

```c++
virtual Element& at(size_t index);
virtual const Element& at(size_t index) const;
```

Gets an element by index.

#### Parameters

`size_t` **index** Index of the element.

#### Return value

[Element](ArrayNodeElement.md)`&` Reference to the element.

`const` [Element](ArrayNodeElement.md)`&` Reference to the element.

#### Errors

An `OutOfRange` fault occurs if the specified index is out of bound.

#### Complexity

Constant.

* * *

### getValue

```c++
ValueNode& getValue(size_t index);
const ValueNode& getValue(size_t index) const;
```

Gets a value by index.

#### Parameters

`size_t` **index** Index of the element.

#### Return value

[ValueNode](ValueNode.md)`&` Reference to the value node.

`const` [ValueNode](ValueNode.md)`&` Reference to the value node.

#### Errors

An `OutOfRange` fault occurs if the specified index is out of bound.

#### Complexity

Constant.

* * *

### getNull, getBoolean, getString, getNumber, getObject, and getArray

```c++
NullNode& getNull(size_t index);
const NullNode& getNull(size_t index) const;

BooleanNode& getBoolean(size_t index);
const BooleanNode& getBoolean(size_t index) const;

StringNode& getString(size_t index);
const StringNode& getString(size_t index) const;

NumberNode& getNumber(size_t index);
const NumberNode& getNumber(size_t index) const;

ObjectNode& getObject(size_t index);
const ObjectNode& getObject(size_t index) const;

ArrayNode& getArray(size_t index);
const ArrayNode& getArray(size_t index) const;
```

Gets a value by index and casts the value to a specific type.

#### Parameters

`size_t` **index** Index of the element.

#### Return value

(value node type)`&` Reference to the value node.

`const` (value node type)`&` Reference to the value node.

#### Errors

An `OutOfRange` fault occurs if the specified index is out of bound.

A `BadCast` fault occurs if the value node is not of the specified type.

#### Complexity

Constant.

* * *

### append

```c++
void append(const Element& element);
void append(const ValueNode& value);
void append(const ValueDesc& value);
```

Inserts an element at the [end](#end).

#### Parameters

`const` [Element](ArrayNodeElement.md)`&` **element** The element to be inserted.

`const` [ValueNode](ValueNode.md)`&` **value** The value to be inserted.

`const` [ValueDesc](ValueDesc.md)`&` **desc** The description of the value to be inserted.

#### Errors

If an error occurs, this array remains untouched.

#### Iterator validity

If a reallocation happens, all iterators related to this array are invalidated.

#### Complexity

Amortized constant.

* * *

### insert

```c++
virtual Iterator insert(Iterator pos, const Element& element);
virtual Iterator insert(Iterator pos, const ValueNode& value);
virtual Iterator insert(Iterator pos, const ValueDesc& value);
```

Inserts an element before the given position.

#### Parameters

`Iterator` **pos** Position in this array where the new element will be inserted before.

`const` [Element](ArrayNodeElement.md)`&` **element** The element to be inserted.

`const` [ValueNode](ValueNode.md)`&` **value** The value to be inserted.

`const` [ValueDesc](ValueDesc.md)`&` **desc** The description of the value to be inserted.

#### Return value

`Iterator` Iterator to the inserted element.

#### Errors

If an error occurs, this array remains untouched.

#### Iterator validity

If a reallocation happens, all iterators related to this array are invalidated; otherwise, all iterators to elements before the given position will remain valid.

#### Complexity

Constant plus linear in the distance between the given position and the [end](#end) of the container.

* * *

### remove

```c++
virtual void remove(Iterator pos);
virtual void remove(Iterator first, Iterator last);
virtual void remove(size_t index);
virtual void remove(size_t index, size_t count);
```

Removes specified elements.

#### Parameters

`Iterator` **pos** Iterator to the element to be removed.

`Iterator` **first**, **last** Range of elements to be removed.

`size_t` **index** Index of the element to be removed.

`size_t` **count** Number of elements to be removed.

#### Iterator validity

Iterators to removed elements and subsequent elements are invalidated.

#### Complexity

Linear in the number of elements to be removed.

* * *

### assign

```c++
virtual void assign(const ArrayDesc& desc);
virtual void assign(const ArrayNode& other);
```

Assigns new elements to this array, replacing its current elements.

#### Parameters

`const` [ArrayDesc](ArrayDesc.md)`&` **desc** An array description.

`const` [ArrayNode](ArrayNode.md)`&` **other** Another array.

#### Errors

If an error occurs, this array remains untouched.

#### Iterator validity

All iterators related to this array are invalidated.

#### Complexity

Linear in the number of elements to be removed and to be copied.

