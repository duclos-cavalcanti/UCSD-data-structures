# Priority Queues and Disjoint Sets

## Definition

## Implementation

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
