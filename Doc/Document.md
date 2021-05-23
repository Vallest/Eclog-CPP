# Document

```c++
template<typename Alloc>
class BasicDocument
```

Inherited from: [ObjectNode](ObjectNode.md).

Required header: `<Eclog/Document.h>`

The [BasicDocument](Document.md) class is an in-memory representation of an Eclog text for accessing and modifying; it consists of a tree-structured collection of nodes (See [Node](node.md)), which is called a document tree.

A typedef for the [default allocator](Allocator.md) is provided:

```c++
typedef BasicDocument<ECLOG_DEFAULT_ALLOCATOR> Document;
```

## Template parameters

`Alloc` [Allocator](AllocatorRequirements.md) type used to allocate internal storage.

* * *

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |
| [operator=](#operator) | Assigns new elements to this document, replacing its current elements. |
| [swap](#swap) | Exchanges the elements of this document with another document. |

* * *

### (constructor)

```c++
BasicDocument();                                                    (1)
BasicDocument(const ObjectDesc& desc);                              (2)
BasicDocument(const ObjectNode& other);                             (3)
BasicDocument(const BasicDocument& other);                          (4)
```

Constructs a [Document](Document.md).

(1) Default constructor. Constructs empty document.

(2) Constructs the document with an object description.

(3) Constructs the document with an object node.

(4) Copy constructor.

#### Parameters

`const` [ObjectDesc](ObjectDesc.md)`&` **desc** An object description.

`const` [ObjectNode](ObjectNode.md)`&` **other** Another object.

`const` [BasicDocument](Document.md)`&` **other** Another document.

* * *

### operator=

```c++
BasicDocument& operator=(const ObjectDesc& desc);
BasicDocument& operator=(const ObjectNode& other);
BasicDocument& operator=(const BasicDocument& other);
```

Assigns new elements to this document, replacing its current elements.

#### Parameters

`const` [ObjectDesc](ObjectDesc.md)`&` **desc** An object description.

`const` [ObjectNode](ObjectNode.md)`&` **other** Another object.

`const` [BasicDocument](Document.md)`&` **other** Another document.

#### Errors

If an error occurs, this document remains untouched.

#### Iterator validity

All iterators related to this object are invalidated, except the [end](#end) iterators.

#### Complexity

Linear in the number of elements to be removed and to be copied.

* * *

### swap

```c++
void swap(BasicDocument& other);
```

Exchanges the elements of the document with another document.

#### Parameters

[BasicDocument](Document.md)`&` **other** Another document.

