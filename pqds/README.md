# Priority Queues and Disjoint Sets

# 1. Priority Queues
## Definition
Priority Queue is a generalization of a queue where each element is assigned a priority
and elements come out in order by priority. Supports the following operations:

1. Insert(prio)
    - adds new element with priority 'prio'
2. ExtractMax()
    - extracts an element with maximum priority

- Usage:
    - Scheduling jobs and process them one by one in order of decreasing priority.
    - While the current job is being processed, new jobs may arrive.

## Implementation
- Naive Implementations:

| Data Structure        | Insert        | ExtractMax    |
| :-------------        | :----------:  | :----------:  |
| Unsorted Array/List   | O(1)          | O(n)          |
| Sorted Array/List     | O(n)          | O(1)          |

- Used Implementation:

| Data Structure        | Insert        | ExtractMax    |
| :-------------        | :----------:  | :----------:  |
| Binary Heap           | O(log n)      | O(log n)      |

### Binary max-heap
1. It is a binary tree (each node has zero, one or two children), where the value of
   each node is **at least** the values of its children.
2. Take any edge of this tree, the value of its top end is at least the value of
   its bottom end.
3. Definition of height here is *number of edges on the longest path from the root
   to a leaf*.
4. **Invariant**: heap property is violated on at most one edge
5. A binary tree is **complete** if all its levels are filled except possibly the last
   one, which is filled from left to right.
    - First Advantage: 
        - Lemma: A complete binary tree with **n** nodes has height at most **O(logn)**.
    - Second advantage
        - Stored as an array.
    - Cost: Keep Binary Tree complete.
        - Insert(): insert an element as a leaf in the leftmost vacant position in the last
            level and let it sift up.
        - ExtractMax(): to extract the maximum value, replace the root by the last leaf
            and let it sift down.
6. This implementation is:
    - fast: O(logn)
    - space efficient: array used to store data
    - easy to implement

## API Complexity
|                       | Complexity    |
| :-------------        | :----------:  |
| GetMax()              | O(1)          |
| Insert(p)             | O(tree height)|
| ExtractMax()          | O(tree height)|
| ChangePriority(prio)  | O(tree height)|
| SiftUp()              | O(1)          |
| SiftDown()            | O(1)          |
| Remove(elem)          | O(tree height)|

## Snippets
- *size*: actual size of our heap
- *maxSize*: size of the array and at the same time, the maximum number of nodes in our
    heap.

```python
def Parent(i):
    return [i/2]
    # 0 based: [i -1/2]
```

```python
def LeftChild(i):
    return 2*i
    # 0 based: 2*i +1
```

```python
def RightChild(i):
    return 2*i + 1
    # 0 based: 2*i +2
```

```python
def SiftUp(i):
    while i > 1 and H[Parent(i)] < H[i]:
        swap H[Parent(i)] and H[i]
        i <- Parent(i)
```

```python
def SiftDown(i):
    maxIndex <- i
    l <- LeftChild(i)
    if l <= size and H[l] > H[maxIndex]:
        maxIndex <- l

    r <- RightChild(i)
    if r <= size and H[r] > H[maxIndex]:
        maxIndex <- r

    if i != maxIndex:
        swap H[i] and H[maxIndex]
        SiftDown(maxIndex)
```

```python
def Insert(p):
    if size = maxSize:
        return ERROR

    size <- size + 1
    H[size] <- p
    SiftUp(size)
```

```python
def ExtractMax(p):
    result <- H[1]
    H[1] <- H[size]]
    size <- size - 1
    SiftDown(1)
    return result
```

```python
def Remove(i):
    H[i] <- inf
    SiftUp(1)
    ExtractMax()
```

```python
def ChangePriority(i, p):
    oldp <- H[i]
    H[i] <- p
    if p > oldp:
        SiftUp(i)
    else:
        SiftDown(i)
```

## Heap Sort
The resulting algorithm is comparison-based and is a sorting algorithm based on the
implementation of priority queues through binary max-heap trees. 

- Its running time will be of **O(logn)**, hence asymptotically optimal!
- Natural generalization of selection sort: instead of simply scanning the rest of the
  array to find the maximum value, use a smart data structure.
- Disadvantage: Not in place, uses additional space to store the priority queue.
- Solution: In-place heap sorting algorithm:
    - For this, we will first turn a given array into a heap by permuting its elements.


```python
def BuildHeap(A[1..n]):
    size <- n
    for i from [n/2] downto 1:
        SiftDown(i)
# O(nlogn)
# actually at most O(2n) with extra analysis
```

```python
def HeapSort(A[1..n]):
    BuildHeap(A)
    repeat (n- 1) times:
        swap A[1] and A[size]
        size <- size - 1
        SiftDown(1)
```

Heap Sort still underperforms other sorting algorithms even with the proof of linear
`BuildHeap`. However this may be useful for `Partial sorting`.

## Partial Sorting
- Input:
    - An array A[1..n], an integer `1 < k < n`.
- Output:
    - The last k elements of a sorted version of A.

```python
def PartialSorting(A[1..n], k):
    BuildHeap(A)
    for i from 1 to k:
        ExtractMax()
```

Running Time: O(n + k*logn) = O(n) for `k <= n/logn`, which is better than solving this same
problem naively.

## Extra Remarks

### Binary min-heap
1. It is a binary tree (each node has zero, one or two children), where the value of
   each node is **at most** the values of its children.
2. Implemented similarly to max-heap.
3. Useful for extracting nodes with the minimum priority!

### d-ary heap
1. Heap nodes on all levels except for possibly the last one have exactly d children.
2. Height of such tree is about logn base d.
3. The running time of SiftUp is O(logn base d)
3. The running time of SiftDown is O(dlogn base d): on each level, we find the largest
   value among d children.

# 2. Disjoint Sets
## Definition
Supports the following operations:
- MakeSet(x)
    - creates a singleton set {x}
- Find(x)
    - returns ID of the set containing x
    - if x and y lie in the same set, then Find(x) = Find(y)
    - otherwise Find(x) != Find(y)
- Union(x,y)
    - merges two sets containing x and y

## Implementation
- Naive Implementations:
    - Array
        - Use the smallest element of a set as its ID
        - objects are integers
        - use the array smallest[1...n]:
            - smallest[i] stores the smallest element that the set i belongs to
        - Current bottleneck is the `Union(i, j)` method
        - What basic DS allows for efficient merging? 
            - Answer: Linked Lists

    - Linked List
        - Pros:
            - Running time of Union is O(1)
            - Well-defined ID
        - Cons:
            - Running time of Find is O(n) as we need to traverse the entire list to find
                its tail
            - Union(x, y) works in time O(1) **only** if we can get the tail of the list x and
                head of the list y in constant time!
        - This brings us eventually to the conclusion that tree's are better DS for this
            implementation than linked lists are, since LL grow longer and longer and add
            complexity to the runtime.

- Used Implementations:
    - Trees
        1. With Union by Rank Heuristic:
            - When merging two trees together, the goal is to hang the shorter one under the root
              of the taller one. This way we keep the running time lower. To quickly find the height
              a tree, we will keep the height of each subtree in an array rank[1..n]: rank[i] is the 
              height of the subtree whose roots is i. 
            - Hanging a shorter tree under a taller one is called a union by rank heuristic!
            - Important Property: 
                - for any node i, ranke[i] is equal to the height of the tree rooted at i
            - Lemma: the height of any tree in the forest is at most log(n) with base 2!
            - Follows from the following:
                - Lemma: Any tree of height k in the forest has at least 2^k nodes.
        2. With Path Compression Heuristic:
            - Restructures tree as a heuristic that keeps the tree height even smaller. All
                nodes are directly connected to roots, except the leaves.
            - The iterated logarithm of n, log*n, is the number of times the logarithm
                function needs to be applied to n before the result is less or equal than 1.
                For any practical value of the log star function, its result will be at most
                5.
            - Result:
                - Lemma: Assume that initially the data structure is empty. We make sequence
                    of m operations including n calls to MakeSet. Then the total running time
                    is O(mlog*n). Then the amortizewd time of a single operation is O(log*n). 
                    Even though the log start function is not bounded, for all practical values we can 
                    evaluate, log start of n is at most 5. Constant time!

## Snippets
- Array Implementation
```python
def MakeSet(i):
    smallest[i] <- i
```
- Tree Implementation
```python
def MakeSet(i):
    parent[i] <- i
    rank[i] <- 0
    # Running Time: O(1)
```

- Array Implementation
```python
def Find(i):
    return smallest[i]
```
- Tree Implementation
```python
def Find(i):
    while i != parent[i]:
        i <- parent[i]
    return i
    # Running Time: O(tree height) = O(logn)
```

- Tree with Path Compression Implementation
```python
def Find(i):
    while i != parent[i]:
        i <- Find(parent[i])
    return parent[i]
    # Running Time: O(tree height) = O(log*n)
```

- Array Implementation
```python
def Union(i, j):
    i_id <- Find(i)
    j_id <- Find(j)
    if i_id == j_id:
        return
    
    m <- min(i_id, j_id)
    for k from 1 to n:
        if smallest[k] in {i_id, j_id}:
            smallest[k] <- m
    # Running time O(n)
    # Here is the largest bottleneck
```

- Tree Implementation
```python
def Union(i, j):
    i_id <- Find(i)
    j_id <- Find(j)
    if i_id == j_id:
        return
    
    if rank[i_id] > rank[j_id]:
        parent[j_id] <- i_id
    else:
        parent[i_id] <- j_id
        if rank[i_id] = rank[j_id]:
            rank[j_id] <- rank[j_id] + 1
    # Running Time: O(tree height) = O(logn)
```

```python
def Preprocess(maze):
    for each cell c in maze:
        MakeSet(c)

    for each cell c in maze:
        for each neighbor n of c:
            Union(c, n)
```

```python
def isReachable(A, B):
    return Find(A) == Find(B)
```

```python
def isReachable(A, B):
    return Find(A) == Find(B)
```
