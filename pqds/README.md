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
    - First Advantage: A complete binary tree with **n** nodes has height at most **O(logn)**.
    - Second advantage: Store as an array.
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
