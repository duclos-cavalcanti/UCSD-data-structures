# Priority Queues and Disjoint Sets
Static arrays are static and their sizes as well. They are defined at compile time and
cannot be modified. Semi solution would dynamically allocate new array with new intended size.

* "All problems in Computer Science can be solved by another level of indirection"

Dynamic arrays, also known as resizable arrays,
- store a pointer to a dynamically allocated array
- replace said pointer with a newly-allocation array as needed (*INDIRECTION*)

## Definition

They are a **abstract data type** with the following operations: (minimum)
- Get(i): Returns element at location i*
- Set(i, val): Sets element i to val*

## Implementation
Store:
- arr: dynamically allocated array
- capacity: size of the dynamically-allocated array
- size: number of elements currently within the array

* C++: vector
* Java: ArrayList
* Python: list (the **only** kind of array)

Space is wasted and unlike static arrays, they can be resized.

## API Complexity

|                   | Complexity    |
| :-------------    | :----------:  |
| Get(i)            | O(1)          |
| Set(i, val)       | O(1)          |
| Pushback(val)     | O(n)          |
| Remove(i)         | O(n)          |
| Size()            | O(1)          |

## Snippets

```python
def Get(i):
    if i < 0 or i >= size:
        ERROR: index out of range
    return arr[i]
```

```python
def Set(i, val):
    if i < 0 or i >= size:
        ERROR: index out of range
    arr[i] = val
```

```python
def PushBack(i, val):
    if size == capacity:
        allocate new_arr[2 x capacity]
        for i in 0 to size - 1
            new_arr[i] <- arr[i]
        free arr
        arr <- new_arr; capacity <- 2x capacity

    arr[size] <- val
    size <- size + 1
```

```python
def Remove(i):
    if i < 0 or i >= size:
        ERROR: index out of range
    for j in i to size - 2:
        arr[j] <- arr[j+1]

    size <- size - 1
```

```python
def Size():
    return size
```

# Amortized Analysis
Sometimes looking at an individual worst case and multiplying that by the number of
operations done can be an over-estimation of a worst case scenario.

- Example:
    - Dynamic Array: Only resize every so often. Many O(1) operations are followed by O(n)
      operations.

- Amortized Cost: (*Question: What's the total cost if you have to inser a bunch of items?*)
    - Given a sequence of **n** operations, the amortized cost is:
        - Cost(**n** operations) / (**n**)

- Worst Case Cost x Amortized Cost

|                   |    Cost		                                                                                                |
| -------------	    |-------------                                                                                                  |
|    WC		        |    Cost of the operation at the time of use. Like paying the price of a car at once.                          |
|    AC		        |    Cost of the operation *amortized* or spread along a time period. Like paying 100$ per month of said Car.   | 

Amortized analysis gives us a more nuanced picture of what it looks like the costs of
successive operations.

## Aggregate Method
Dynamic array: **n** calls to PushBack

Let ci = cost of i'th insertion
        
ci = 1 + x
- x = i - 1 if *i - 1* is a power of 2
- x = 0 otherwise


Amortized Cost = Sum from i to n of **ci** divided by **n** = ... = O(n) / n = O(1)

Worst Case Cost = O(n)

## Banker's Method
- Charge extra for each cheap operation.
- Save the extra charge as tokens in your data structure (conceptually).
- Use the tokens to pay for the expensive operations.

Like an amortizing loan.


Dynamic array: **n** calls to PushBack

Charge 3 for each insertion:
- 1 token is the raw cost for the insertion
- Resize Needed: To pay for moving the elements, use the token that's present
on each element that needs to move.
- Place one token on the newly inserted element and one token capacity/2 elements prior.

## Physicist's Method
Defines a *potential function* Fi(), which maps states of the data structure to integers.

Our Data Structure has within it the potential to do future work, similar to a ball taken
to larger heights will have a larger potential energy, such that if it is released this
greater potential will be converted to actual kinetic energy.

- Fi(h0) = 0
- Fi(ht) >= 0

- amortized cost of an operation t:
    - ct + Fi(ht) - Fi(ht - 1)

Choose Fi() so that:
- if ct is small, the potential increases
- if ct is large, the potential decreases by the same scale

Dynamic array: **n** calls to PushBack

Let Fi(h)= 2 x size - capacity
- Fi(h0) = 2 x 0 - 0 = 0
- Fi(hi) = 2 x size - capacity > 0

...

amortized cost of adding elements is **3**, given this potential function. This will
change if we change the potential function.

## Notes
Cannot use constant amount to resize array. We need to refactor size by a constant
multiplicative factor to accumulate enough work to pay for the pushbacks. This becomes clear with these
analysis.
