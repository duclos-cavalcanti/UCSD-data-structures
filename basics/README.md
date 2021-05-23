# Basic Data Structures
- Arrays 
- Linked Lists
- Stacks and Queues
- Trees

# Introduction
## Abstract Datatype x Data Structure
1. Abstract Datatype

    describes what the operation does, not how it is done. Can be seen as an abstraction
    that defines the interface between a abstract data type and other objects.

    Ex: Priority Queue with Insert and Delete Operations

2. Data Structure

    is a formalized object that can be "actual data". This means it is possible to sotre,
    manipulate and access said data.

    Ex: Binary Tree Heap as an implementation of a Priority Queue.

# Arrays
Contiguous area of memory consisting of equal-size elements indexed by contiguous
integers.

## Features
- Constant-time access to read/write.
- Can be of single-dimensional or multi-dimensional.

## Relevant Definitions/Keywords
- Row-Major ordering/indexing vs Column-Major ordering/indexing

## API Complexity

|                | Add          | Remove       |
| :------------- | :----------: | -----------: |
| Beginning      | O(n)         | O(n)         |
| End            | O(1)         | O(1)         |
| Middle         | O(n)         | O(n)         |

### Final Notes:
- Constant Time access to any element. (Useful for binary search)
- Constant Time access to add/remove at the end.
- Linear Time access to add/remove at any arbitrary location.

# Linked Lists
## Singly-Linked Lists
Node contains a `key`, and a `next pointer`.

```
head -> Node -> Node -> NULL
        ----    ----
          7      13
```

### API Complexity

|                       | Description           | Complexity  (no tail)  | Complexity  (with tail)  |
| :-------------        | :----------:          | -----------:           | -----------:             |
| PushFront(Key)        | add to front          | O(1)                   |                          |
| Key TopFront()        | return front item     | O(1)                   |                          |
| PopFront()            | remove front item     | O(1)                   |                          |
| PushBack(Key)         | add to back           | O(n)                   | O(1)                     |
| Key TopBack()         | return back item      | O(n)                   | O(1)                     |
| PopBack()             | remove back item      | O(n)                   |                          |
| Boolean Find(Key)     | is key in list?       | O(n)                   |                          |
| Erase(Key)            | remove key from list  | O(n)                   |                          |
| Boolean Empty()       | empty list?           | O(1)                   |                          |
| AddBefore(node, key)  | adds key before node  | O(n)                   |                          |
| AddAfter(node, key)   | adds key after node   | O(1)                   |                          |

### Snippets
#### PushFront
```
def PushFront(Key):
    node <- new node
    node.key <- key
    node.next <- head
    head <- node
    if tail == nil:
        tail <- head
```

#### PopFront
```
def PopFront():
    if head == nil:
        ERROR: empty list
    head <- head.next
    if head == nil:
        tail <- nil
```

#### PushBack
```
def PushBack(Key):
    node <- new node
    node.key <- key
    node.next <- nil
    if tail == nil:
        head <- tail <- node
    else:
        tail.next <- node
        tail <- node
```

#### PopBack
```
def PopBack():
    if head == nil:
        ERROR: empty list
    if head == tail:
    head <- tail <- nil
    else
        p <- head
    while p.next.next != nil:
        p <- p.next
    p.next <- nil
    tail <- p
```

#### AddAfter
```
def AddAfter(node, key):
    node2 <- new node
    node2.key <- key
    node2.next <- node.next
    node.next = node2
    if tail == node:
        tail <- node2
```

## Doubly-Linked Lists
Node contains a `key`, a `next pointer` and a `prev pointer`.

### API Complexity

|                       | Description           | Complexity  (no tail)  | Complexity  (with tail)  |
| :-------------        | :----------:          | -----------:           | -----------:             |
| PushFront(Key)        | add to front          | O(1)                   |                          |
| Key TopFront()        | return front item     | O(1)                   |                          |
| PopFront()            | remove front item     | O(1)                   |                          |
| PushBack(Key)         | add to back           | O(n)                   | O(1)                     |
| Key TopBack()         | return back item      | O(n)                   | O(1)                     |
| PopBack()             | remove back item      | **O(1)**               |                          |
| Boolean Find(Key)     | is key in list?       | O(n)                   |                          |
| Erase(Key)            | remove key from list  | O(n)                   |                          |
| Boolean Empty()       | empty list?           | O(1)                   |                          |
| AddBefore(node, key)  | adds key before node  | **O(1)**               |                          |
| AddAfter(node, key)   | adds key after node   | O(1)                   |                          |

Doubly linked list exhibit O(1) for `PopBack` and `AddBefore`.

### Snippets
#### PushBack
```
def PushBack(Key):
    node <- new node
    node.key <- key;  node.next <- nil
    if tail == nil:
        head <- tail <- node
        node.prev <- nil
    else
        tail.next <- node
        node.prev <- tail
        tail <- node
```

#### PopBack
```
def PopBack():
    if head == nil:
        ERROR: empty list
    if head == tail:
        head <- tail <- nil
    else
        tail <- tail.prev
        tail.next <- nil
```

#### AddAfter
```
def AddAfter(node, key):
    node2 <- new node
    node2.key <- key
    node2.next <- node.next
    node2.prev <- node
    node2.next <- node2
    if node2.next != nil:
        node2.next.prev <- node2
    if tail == node:
        tail <- node2
```

### Final Notes (Linked Lists both Single and Double)

- Constant time to insert at or remove at the front.
- With tail and doubly linked, constant time to insert at or remove from the back.
- O(n) time to find arbitrary element.
- List elements need not to be contiguous.
- With doubly linked list, constant time to insert between nodes or remove a node.

# Stacks and Queues
## Stacks
Abstract data type with the following operations:
- Push(Key) - adds key to collection.
- Key Top() - returns most recently added key.
- Key Pop() - removes and returns most recently added key.
- Boolean Empty() - are there any elements?

### Example Snippet
Keeping check of closing brackets.
```
Stack stack
for char in str:
    if char in '[,(,),]':
        stack.Push(char)
    else:
        if stack.Empty():
            return False
        top <- stack.Pop()
        if (top = '[' and char != '],)') or
           (top = '(' and char != ')'):
            return False

    return stack.Empty()
```
### Implementations
- Array

Limitation: Maximum Size, which not only limits size, but also may cause wasted space.

- Linked Lists

Infinite available memory, no limit to size, no wasted space, there is overhead since
every node also stores a pointer. This is not the case for an array.

### Final Notes
- Each Stack operation is O(1): Push, Pop, Top, Empty. Regardless of implementation.
- Stacks are also known as LIFO queues. (Last in First Out)

## Queues
Abstract data type with the following operations:
- Enqueue(Key) - adds key to collection.
- Key Dequeue() - removes and returns least recently-added key.
- Boolean Empty() - are there any elements?

FIFO: First in First Out.

### Implementations
- Linked list with tail pointer.
Infinite available memory, no limit to size, no wasted space, there is overhead since
every node also stores a pointer. This is not the case for an array.

- Array

### Final Notes
- Each Queue operation is O(1): Enqueue, Dequeue, Empty. Regardless of implementation.

# Trees
