# Allocator Requirements

Encapsulates strategies for allocation and deallocation.

An *Allocator* must be a class type, and given

- `A`, an *Allocator* type
- `size`, a value of type `size_t`
- `ptr`, a value of type `void*`, obtained by calling `A::allocate`

the following expressions must be valid and have their specified effects:

| Expression           | Return type  | Requirements                                                 |
| -------------------- | ------------ | ------------------------------------------------------------ |
| `A::allocate(size)`  | `void*`      | Allocates **size** bytes of uninitialized storage space and returns a pointer to the storage space. |
| `A::deallocate(ptr)` | *(not used)* | Deallocates storage space pointed by **ptr**, which is earlier obtained from `allocate`. |

