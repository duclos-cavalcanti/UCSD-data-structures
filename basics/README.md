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

# 1. Arrays
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

# 2. Linked Lists
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
```python
def PushFront(Key):
    node <- new node
    node.key <- key
    node.next <- head
    head <- node
    if tail == nil:
        tail <- head
```

#### PopFront
```python
def PopFront():
    if head == nil:
        ERROR: empty list
    head <- head.next
    if head == nil:
        tail <- nil
```

#### PushBack
```python
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
```python
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
```python
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
```python
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
```python
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
```python
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

# 3. Stacks and Queues
## Stacks
Abstract data type with the following operations:
- Push(Key) - adds key to collection.
- Key Top() - returns most recently added key.
- Key Pop() - removes and returns most recently added key.
- Boolean Empty() - are there any elements?

### Example Snippet
Keeping check of closing brackets.
```python
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

# 4. Trees
Trees are a recursive definition. It is either
* empty, or
* a node with:
    * key
    * list of child **trees**
    * (optional) parent*

## Terminology
1. **Tree**'s grow down.
2. **Parents** are above children
3. **Root**, uppermost node
4. **Ancestor** is a parent, or a parent's parent
5. **Descendent** is inverse of Ancesto
6. **Siblings**, two or more nodes sharing the same parents
7. **Leaves**, nodes with no children
8. **Interior** Nodes, all nodes that aren't leaves
9. **Level**, one plus the number of edges between the root and the node
    * Root's level is **1**!!!!
10. **Height**, maximum depth of a subtree node and the farthest leaf
    * A Leaf's height is **1**!!!!
11. **Forest**, a collection of trees


## Use Cases
Trees may be used for different purposes. They generally indicate relationship between nodes and their groups, 

* Syntax Trees
    * Grammar: relational breakdown of a sentence, each node may be a component within the grammar
  structure or even the head of a sub-structure.

    * Math: mathematical breakdown of expressions.

    * Code: relational breakdown of instructions. (Abstract Syntax Tree)

* 'Hierarchy' Trees
    * Animal Kingdom
    * Geography

Trees are also used quite a lot in search problems. Given the abstract notion of trees and
the flexibility of node relationships, one can create trees with structural constraints
that facilitate search problems.

### Binary Search Tree
* empty, or
* a node with:
    * key
    * left*
    * right*
    * (optional) parent*

* Only contains two children per node.
* At the root node, it's value is greater than or equal to all of its nodes in the left
  child and is less the the nodes in the right child.
* This relationship is mantained through all nodes in the tree,
* Facilitates search problems that contain range of values tremendously.


## Features
- Have a recursive definition, API's may also be recursively defined, less deterministic
  algorithm complexity

## Snippets
#### Height
```python
def Height(Tree):
    if tree = nil:
        return 0
    return 1 + Max(Height(tree.left), Height(tree.right))
```

#### Size (Total number of nodes)
```python
def Size(Tree):
    if tree = nil:
        return 0
    return 1 + Size(tree.left) + Height(tree.right)
```

## Tree Traversal
### Depth First x Breadth First Search

|                       | Description                                                               | APIs                                                  |
| :-------------        | :----------:                                                              | -----------:                                          |
| DFS                   | Completely Traverse one sub-tree before exploring a sibling tree          | InOrdertraversal,PreOrderTraversal,PostOrderTraversal |
| BFS                   | Completely Traverse all nodes at one level before progressing to the next | LevelTraversal                                        |

### DFS Snippets
When we use recursive calls in a DFS manner, we are invoking 
another frame on the stack. This way we are implicitly saving
information of where we are on the stack.

```python
def InOrderTraversal(Tree):
# Traverses 'left' side of the tree first, 
# beginning at the leaves, then goes to
# the 'right' nodes. 
    if tree = nil:
        return
    InOrderTraversal(tree.left)
    print(tree.key)
    InOrderTraversal(tree.right)

# Gives us a mid-orders because we know
# all the elements in the left child are
# in fact less than or equal to the node
# itself.
```

```python
def PreOrderTraversal(Tree):
# Traverses 'left' side of the tree first, 
# beginning at the Root, then goes to
# the 'right' nodes. 
    if tree = nil:
        return
    print(tree.key)
    PreOrderTraversal(tree.left)
    PreOrderTraversal(tree.right)

```

```python
def PostOrderTraversal(Tree):
# Traverses 'left' side of the tree first, 
# beginning at the leaves, then goes to
# the 'right' nodes. 
    if tree = nil:
        return
    PostOrderTraversal(tree.left)
    PostOrderTraversal(tree.right)
    print(tree.key)

# Is a much more defined way of traversing
# the tree giving preference to left nodes.
# Better defined than InOrderTraversal. Root
# is the very last to be printed.
```
### BFS Snippets
BFS also has an implicit use of a data structure like DFS. In this case a queue
is used instead.
```python
def LevelTraversal(Tree):
# Prefers left children.
# Goes on a level like basis, which
# is expected due to the Queue approach.
    if tree = nil:
        return
    Queue q;
    q,Enqueue(tree)
    while not q.Empty():
        node <- q.Dequeue()
        print(node)
        if node.left != nil:
            q.Enqueue(node.left)
        if node.right != nil:
            q.Enqueue(node.right)

```
