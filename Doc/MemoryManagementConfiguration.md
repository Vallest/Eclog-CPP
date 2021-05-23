# Memory Management Configuration

**ECLOG_DEFAULT_ALLOCATOR**

Define this macro to change the default allocator to a user-defined allocator (See [Allocator Requirements](AllocatorRequirements.md)).

The default definition:

```
#define ECLOG_DEFAULT_ALLOCATOR eclog::Allocator
```

