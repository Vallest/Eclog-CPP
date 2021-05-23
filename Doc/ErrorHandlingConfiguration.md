# Error Handling Configuration

**ECLOG_NO_EXCEPTIONS**

Define this macro to suppress the throwing of exceptions.

If defined, all internal throw expressions will be replaced with `ECLOG_TERMINATE`. 



**ECLOG_TERMINATE**

Define this macro to change the terminate handler.

The default definition:

```c++
#define ECLOG_TERMINATE std::terminate
```



**ECLOG_ERROR_ALLOC** & **ECLOG_ERROR_DEALLOC**

Define these two macros to change the dynamic memory management functions used by error objects.

In fact, the most error objects are static and do not use dynamic memory storage, except [ParseError](ParseError) objects.

The default definition:

```c++
#define ECLOG_ERROR_ALLOC(Size) ::operator new(Size)
#define ECLOG_ERROR_DEALLOC(Ptr) ::operator delete(Ptr)
```



