# Binary Search Trees
Types of problems to solve with BST:
- Local Search
    - Closest height to you
    - word in dictionary

The Local Search Data Structure stores a number of elements each with a key coming from an
ordered set. It supports operations:
* RangeSearch(x, y): Returns all elements with keys between x and y
* NearestNeighbours(z): Returns the element with keys on either side of z.

Also having this data structure as a dynamic one would also be needed. Thus it should
support:
* Insert(x): Adds element with key x.
* Delete(x): Removes element with key x.

## Definition

## Implementation
- Naive Implementations:
    - Hash Tables
        - doesn't support range search and nearest neighbours
    - Array
        - slow during range search and nearest neighbours
    - Sorted Array
        - faster during range search and nearest neighbours
        - slow insertion and deletion
    - Sorted/Unsorted Linked List
        - slow/linear during range search and nearest neighbours
        - fast insertion and deletion

Solution: Binary Search Trees

Definition of Binary Search:
- Take middle value of list, asks if the searched element it is bigger or smaller?
- If bigger jump to the middle of the right side of the list and continue this procedure
- If smaller jump to the middle of the left side of the list and continue this procedure
- Do this until said value is found or in fact not able to be found.

Definition of Search Tree:
- Associated to the binary search is the search tree data structure, which already stores data in a binary tree such that it already conforms to a specific structure.
- The Tree contains: 
    - Root node
    - Left Subtree of smaller keys
    - Right Subtree of larger keys
- Each Node contains:
    - Key
    - Parent
    - Left Child
    - Right Child

- Important Property: 
    - X's key is larger than the key of any descendent of its left child and smaller than the key of any descendent of its right child.

## API Complexity
- Unbalanced Tree
| API                 | Complexity      |
| :-------------      | :----------:                            |
| Find()              | O(depth of tree or even as bad as n)    |

- Balanced Tree
    - Left and Right subtrees have approximately the same size
    - Perfectly balanced means:
        - Each subtree half the size of its parent
        - After log2(n) levels, subtree of size 1
        - Operations run in O(log(n)) timw
    - Balancing is hard!
        - Do Rotations!

| API                 | Complexity      |
| :-------------      | :----------:    |
| Find()              | O(logn)         |

## Snippets

```python
def Find(key, root):
    if R.key == k:
        return R
    else if R.key > k
        if R.left != NULL
            return Find(k, R.left)
        return R
    else if R.key < k)
        if R.right != NULL
            return Find(k, R.right)
        return R
```

```python
def Next(N):
    if N.Right != Null
        return LeftDescendent(N.Right)
    else
        return RightAncestor(N.Right)
```

```python
def LeftDescendent(N):
    if N.Left == NULL
        return N
    else
        return LeftDescendent(N.Left)
```

```python
def RightAncestor(N):
    if N.Key < N.Parent.Key
        return N.Parent
    else
        return RightAncestor(N.Parent)
```

```python
def RangeSearch(x, y, R):
    L <- 0
    N <- Find(x, R)
    while N.key <= y
        if N.Key >= x:
            L <- L.Append(N)
        N <- Next(N)
    return L
```

```python
def Insert(k, R):
    P <- Find(k, R)
    Add new node with key k as child of P
```

```python
def Delete(k):
    if N.Right == NULL:
        remove N
        promote N.Left (N.Left should become the child of N's Parent)
    else:
        X <- Next(N)
        Replace N by X
        promote N.right
```

```python
def RotateRight(X):
    P <- X.Parent
    Y <- X.Left
    B <- Y.Right
    Y.Parent <- P
    P.AppropriateChild <- Y
    X.Parent <- Y, Y.Right <- X
    B.Parent <- X, X.Left <- B
```

# AVL Trees
Adds new API's, modifies existing one and adds new fields to BST.

- Each Node contains:
    - Key
    - Height
    - Parent
    - Left Child
    - Right Child

- AVL Property:
    - AVL Trees maintain the following property for all Nodes N:
        - `|N.Left.Height - N.Right.Height| <= 1`
        - Ensures Balance and allows us to perform with runtime O(log(n)) time!

```python
def Height(N):
    if N is a leaf
        N.Height = 1
    else:
        N.Height = 1 + max(N.Left.Height, N.Right.Height)
```

```python
def AVLInsert(k, R):
    Insert(k, R)
    N <- Find(k, R)
    Rebalance(N)
```

```python
def Rebalance(N):
    P <- N.Parent
    if (N.Left.Height > N.Right.Height + 1):
        RebalanceRight(N)
    if (N.Right.Height > N.Left.Height + 1):
        RebalanceLeft(N)
    AdjustHeight(N)
    if P != NULL:
        Rebalance(P)
```
```python
def RebalanceRight(N):
    M <- N.Left
    if M.Right.Height > M.Left.Height:
        RotateLeft(M)
    RotateRight(N)
    AdjustHeight on affected Nodes
```

```python
def RebalanceLeft(N):
    M <- N.Right
    if M.Left.Height > M.Right.Height:
        RotateRight(M)
    RotateLeft(N)
    AdjustHeight on affected Nodes
```

```python
def AdjustHeight(N):
    N.Height <- 1 + max(N.Left.Height, N.Right.Height)
```

```python
def AVLDelete(N):
    Delete(N)
    M <- Parent of Node replacing N
    Rebalance(M)
```
# Manipulation of Binary Trees
Recombining BST may prove to be useful. Consider the following operations:
1. Merge
    - Combines two binary search trees into a single one
2. Split
    - Breaks one BST into two

## Merge
- Is general, merging two sorted lists takes O(n) time. 
- However, with the condition that two BST with roots R1 and R2, where all keys in R1;s tree are smaller than those of R2. This can be done faster.

```python
def MergeWithRoot(R1, R2, T):
    T.Left <- R1
    T.Right <- R2
    R1.Parent <- T
    R2.Parent <- T
    return T
    # Time O(1)
```

```python
def Merge(R1, R2):
    T <- Find(inf, R1)
    Delete(T)
    MergeWithRoot(R1, R2, T)
    return T
    # Time O(h)
```

```python
def AVLTreeMergeWithRoot(R1, R2, T):
    if | R1.Height - R2.Height | <= 1
        MergeWithRoot(R1, R2, T)
        T.Ht <- max(R1.Height, R2.Height) + 1
        return T
    else if R1.Height > R2.Height:
        R\' <- AVLTreeMWR(R1.Right, R2, T)
        R1.Right <- R\'
        R\'.Parent <- R1
        Rebalance(R1)
        return root
    else if R1.Height < R.Height:
    # ...


    # Time O(hmax) = O(log(n))
```

## Split
Takes in root of Tree R and a key x, will then return two separate trees, one with
`elements < x` and another with `elements > x`.

```python
def Split(R, x):
    if R == NULL:
        return (NULL, NULL)

    if x < R.key:
        (R1,R2) <- Split(R.Left, x)
        R3 <- MergeWithRoot(R2, R.Right, R)
        return (R1, R3)
    if x > R.key:
    # ...
```
# Applications
- Order Statistics
- Color Flipping
- Sorting by order, like the phrase in a sentence, storing sorted lists etc.
