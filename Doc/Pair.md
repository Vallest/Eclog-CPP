# Pair

```c++
template<typename T1, typename T2>
class Pair
```

Required header: `<Eclog/Utility.h>`

The [Pair](Pair.md) class couples together a pair of elements which may be of different types (`T1` and `T2`).

## Template parameters

`T1` Type of member [first](#first).

`T2` Type of member [second](#second).


* * *

## Member types

| Name         | Description                         |
| ------------ | ----------------------------------- |
| `FirstType`  | The first template parameter (T1).  |
| `SecondType` | The second template parameter (T2). |

* * *

## Member functions

| Name | Description |
| ---- | ---- |
| [(constructor)](#constructor) | Constructor. |

* * *

## Member variables

| Name              | Description         |
| ----------------- | ------------------- |
| [first](#first)   | The first element.  |
| [second](#second) | The second element. |

* * *

### (constructor)

```c++
Pair();                                                             (1)
Pair(const T1& arg1, const T2& arg2);                               (2)

template<typename U1, typename U2>
Pair(const Pair<U1, U2>& other);                                    (3)
```

Constructs a [Pair](Pair.md).

1) Default constructor.

2) Initializes `first` with `arg1` and `second` with `arg2`. 

3) Copy constructor.

#### Parameters

`const T1&` **arg1** Value to initialize the first element.

`const T2&` **arg2** Value to initialize the second element.

`const` [Pair](Pair.md)`<U1, U2>&` **other** Another pair.

* * *

### first

`T1` **first**

The first element.

* * *

### second

`T2` **second**

The second element.

