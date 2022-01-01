# Hashing

Applications:
- Hashing
- Filesystems
- Digital Hashing
- Programming Languages: C++, Ruby, Python (Dict)
    - Keywords: for, if while, int
        - These keywords need to be quickly obtained by the parser/compiler. Done so with
            hashing.

# Hashing
## Example Problem
1. Phone number problem. 

How to connect phone number to name and number to name?

Solution:
- Direct Addressing (Scheme)
    - Phone Numbers are converted to actual numbers.
    - Arrays will have at each cell number corresponding to the converted cell phone
        number, the entry to the person's name.
    - This results into a constant time access to these values.

## Hash Functions
- Definition:
    - For any set of objects S and any integer m > 0, a function h:S -> {0, 1, ... m -1} is called a hash function.
    - This means it maps a set of objects to a set of integers.
    - m is called the cardinality of hash function h.
- Possible Properties:
    - Should be fast to compute
    - Different values for different objects
    - Direct addressing with O(m) memory
    - Want small cardinality => small memory usage
    - Impossible to have all different values if number of objects |S| is more than m.
        - when h(o1) == h(o2) and o1 != o2, this is a collision!
- Desirable Properties:
    - Should be fast to compute
    - Small probability of collision
    - Small enough cardinality m
- Good Hash Functions
    - Deterministic
    - Fast to compute
    - Distribute keys well into different cells
    - Few collisions
- Lemma: if the number of possible keys is big (|S| >> m), for any hash function h there is a bad input resulting in many collisions. 
- Universal Family of Hash Functions
    - let U be the universe, the set of all possible keys
    - Let a set of hash functions H where all containing hash functions h have cardinality m
    - We can call H a universal family if for any two keys x, y element of U, where x is different than y, the probability of collision is:
        - `P[h(x) == h(y)] <= 1/m`
    - This means that a collistion for any fixed pair of different keys happens no more than 1 / m of all hash functions.
    - Hashing Integers:
        - Lemma: Hp = { h(x) = ((ax + b)mod p)mod m }
            - for all a: `1 <= a <= p-1`
            - for all b: `0 <= b <= p-1`
            - for a prime number p, which has to be larger than the maximum value of used keys!
    - Hashing Strings
        - Polynomial Hashing
        - `Pp = { hp(S) = Sum from i to |S| -1 of (S[i] * x*i)* mod p }`
        - `1 <= x <= p -1`
        - fixed prime number p
        - The concept here is to hash strings into an integer value that may be as big as p
        - Then Rehash the resulting value from the string hash using the integer hashing mentioned above
        - That way we can obtain a usable cardinality m that reduces our memory consumption and maintains the resources more optimal
        - `hm(S) = ha,b(hx(S))mod m`
        - Probability of collision is at most 1/m + L/p, L being the size of the string
        - Choosing p  > mL, we can then have a collision probability of O(1/m), which is needed to be a universal family
        - Running time will be c = O(1 + n/m) = O(1 + alpha), when choosing p > mL
        - PolyHash running time runs in O(|S|)
        - By bounding length of strings to constant L, computing h(S) takes O(L) = O(1)

- Randomization
    - All hash functions in H are deterministic
    - The random nature comes from the random selection of which hash function h to choose
    - Then a fixed h is used throughout the algorithm

## Implementation
1. Naive Implementations:
- Arrays
    - Using arrays to store all the phone numbers.
    - Memory consumption is `O(|U|)`, where U is the set of all phone numbers. There are a lot of empty space!

- Linked List
    - Lets store only known phone numbers
    - Put pairs (Phone number, Name) into a doubly linked list
    - Too slow, have to scan entire list

- Dynamic arrays
    - dynamic array sorted by phone numbers
    - dynamic is needed since we don't know the number of contacts beforehand
    - use binary search to look up phone number since it is sorted
    - to insert we have to find first the appropriate cell to insert (O(logn)), then move all the other elements to the right, which makes inserting O(n).

Until now the tradeoffs between Arrays x LL x Dynamic Arrays is of speed and memory.
Arrays are constant time access and read, however use too much memory. The other way
around for the other DS, therefore simple list-based and array-based approaches are too
slow.

- Solution: Hashing / Hash Functions

2. Actual Implementation with Hash Functions:
- Terminology: Map from set S of objects to set V of values is a data structure with methods HasKey(obj), Get(obj), Set(obj, value), where obj is an element of S and value is an element of V.

    1. Chaining Technique (can also be seen as a technique to implement a Hash Table)
        - Map phone numbers to integers in an array through a hash function h of cardinality m
        - Collisions are solved by having doubly linked lists on every array cell/entry, these are usually called chains
        - Basically a combination of hash function, direct addressing with doubly linked lists! 
        - An array of chains with size m.
        - Lemma: let c be the length of the longest chain in Chains. Then the running time of HasKey, Get, Set is O(c + 1).
        - Lemma: let n be the number of different objects currently in the map and m be the cardinality of the hash function. Then the memory consumption for chaining is O(m + n).

    2. Hash Tables (Sets)
        - Sets are data structures with methods: Add(obj), Remove(obj) and Find(obj)
        - Can be implemented using chaining, making Set equivalent to a map from S to V = {true}.
        - Or directly just store objects instead of pairs (object, value) in the chains.  Basically the same as above without the pair notion.
        - Finally we can define Hash Tables as a implementation of a set or a Map using hashing.
        - Hash Tables Implementations in Languages:
            - C++ unordered_set(Set implementation) and unordered_map(Map Implementation)
            - Python set(Set Implementation) and dict(Map Implementation)
        - The Load factor of a Hash Table:
            - is the ratio alpha = n / m, which is the ration between the number of objects stored to the size of the hash table.
            - It is important because if it is very small,
              then we can be sure that a lot of the cells of the hash table are empty and so, we're wasting space.  And if it is bigger than one,
              then we can be sure that there is at least one collision.  And if it is big, then we can be sure that there are a lot of collisions
              and the longest chain length is too long and the operations will be too slow.  So we want to keep the load factor in some medium range.
        - Lemma: If h is chosen randomly from a universal family, the average length of the longest chain c is O(1 + alpha), where alpha is the load factor.
        - Corollary: If h is from a universal family, operations with hash table run on average in time O(1 + alpha)
        - Load factor actually determined the speed in which operations are run!
        - Choosing size of Hash Table:
            - control amount of memory used with m
            - ideally load factor between 0.5 and 1
            - use O(m) = O(n/alpha) = O(n) memory to store keys
            - operations run then in time O(1 + alpha) = O(1) on average
        - Dynamic Hash Tables
            - are needed when we can't possibly know how many objects may be stored
            - resize the hash table when alpha becomes too large? No, breaks the hashing system.
            - Choose new hash function and rehash all the objects to a new hash table with new size!

Example Application 1:
Design a data structure to store your contacts. Should support the following operations.

- Add and Delete contacts
- Call person by name
- Determine who is calling given their phone number.

Steps:
1. We need two Maps
    - phone number -> name
    - name -> phone number
2. Implement these Maps as hash tables
    - Important question: how to choose Hash functions?
        - Last three digits? If many phone numbers end with the same digits we will have a lot of collisions
        - Random value? helps with uniform distribution of keys, but we cannot find our keys again
        - Solution:
            - Universal Family of hash functions!!!
    - Define maximum length L of a phone number
    - convert phone numbers to integers from 0 to 10^L - 1
    - choose prime number p > 10^L
    - choose hash table size m
    - choose random hash function from universal family Hp

Example Application 2:
String Hashing.
- `|S|` is the length of a string
- Given a string, compute hash value from the characters of the string, which is an array of characters
- We should use all characters in the hash function to reduce collisions
- Convert each character to integer through the ASCII encoding or Unicode
- Choose big prime number p
- Use Polynomial Hashing

Example Application 3:
Searching for Substrings:
- Given a text T and a string P, find all occurrences of P in T
- Can be used to find genes within genome
- Rabin Karp's Algorithm
    - if h(P) != h(S), then definitely P != S
    - if h(P) == h(S), call AreEqual(P, S)
    - uses polynomial hash family Pp with prime p
    - the probability Pr[h(P) = h(S)] of collision is at most |P|/p, which can be made small by choosing very large prime p.
    - we may have false alarms! Same hashes but different strings. Probability of false alarms = `(|T| - |P| + 1)*P/p`, which can be made small by selecting `p >> |T||P|`
    - Running Time without AreEqual: O(|T||P|), Still??
    - AreEqual itself is O(|P|)
    - Optimization:
        - Using properties of the Polynomial Hashing, the `Recurrence Equation` can be deduced
        - Therefore x^|P| can be computed and saved
        - Given this new equation, H[i] can be computed in O(1) given H[i + 1] and x^|P|
        - Using Precomputation and the Recurrence Equation, Rabin Karps Algorithm can be greatly improved. The idea is that we use the recurrence equation to precompute all hashes of substrings T of length equal to of P.
        - Then proceed the same way as the original
        - Precomputation:
            - PolyHash is called once: O(|P|)
            - x^|P| is computed in O(|P|)
            - All values of H are computed in O(|T| - |P|)
            - Total precomputation time: O(|T| + |P|)
        - Now final Optimized Rabin Karp:
            - h(P) is computed O(|P|)
            - PrecomputeHashes in O(|T| + |P|)
            - Total time spent in AreEqual is O(q|P|) on average (for large enough p), where q is the number of occurrences of P in T.
            - Total running time on average: O(|T| + (q + 1)|P|), much faster than O(|T||P|)!!
            - Usually q is small!!

## API Complexity
| API (Array)                | Complexity    |
| :-------------             | :----------:  |
| GetName(phoneNumber)       | O(1)          |
| SetName(phoneNumber, name) | O(1)          |

| API (Linked List)          | Complexity    |
| :-------------             | :----------:  |
| insert(phoneNumber, name)  | O(1)          |
| getName(phoneNumber, name) | O(n)          |

| API (Dynamic Array)        | Complexity    |
| :-------------             | :----------:  |
| insert(phoneNumber, name)  | O(n)          |
| getName(phoneNumber)       | O(logn)          |

| API (Chaining Technique/Hash Tables)   | Complexity    |
| :-------------                         | :----------:  |
| HasKey(obj)                            | O(c + 1)      |
| Get(obj)                               | O(c + 1)      |
| Set(obj, value)                        | O(c + 1)      |

## Snippets
- Array
```python
def GetName(phoneNumber):
    index <- convertToInt(phoneNumber)
    return phoneBookArray[index]
```

```python
def GetName(phoneNumber):
    index <- convertToInt(phoneNumber)
    phoneBookArray[index] <- name
```
- Chaining Scheme
```python
def HasKey(obj):
    chain <- Chains[hash(obj)]
    for (key, value) in chain:
        if key == obj:
            return true
    return false
```

```python
def Get(obj):
    chain <- Chains[hash(obj)]
    for (key, value) in chain:
        if key == obj:
            return value
    return N/A
```

```python
def Set(obj, value):
    chain <- Chains[hash(obj)]
    for pair in chain:
        if pair.key == obj:
            pair.value = value;
            return
    chain.Append((obj, value))
```

- Sets with Chaining
```python
def Find(obj):
    chain <- Chains[hash(obj)]
    for key in chain:
        if key == obj:
            return true
    return false
```

```python
def Add(obj):
    chain <- Chains[hash(obj)]
    for key in chain:
        if key == obj:
            return
    chain.Append(obj)
```

```python
def Remove(obj):
    if not Find(obj):
        return
    chain <- Chains[hash(obj)]
    chain.Erase(obj)
```

```python
def Rehash(T):
    loadFactor <- T.numberOfKeys/T.size
    if loadFactor > 0.9
    create Tnow of size 2 x T.size
    choose hnew with cardinality Tnew * size
    for each obj in T:
        insert object in Tnew using hnew
    T <- Tnew
    h <- hnew
    # this is O(n), however the amortized running time of each operation with the hash
    # table is still O(1) since rehashing is rare
```

- String hashing

```python
# string S, prime number p and parameter/number x
def PolyHash(S, p, x)):
    hash <- 0
    for i from |S| - 1 downto 0:
        hash <- (hash * x + S[i]) mod p
    return hash
```

- Substring searching
```python
def AreEqual(S1, S2)):
    if |S1| != |S2|:
        return False
    for i from 0 to |S1| - 1:
        if S1[i] != S2[i]:
            return False
    return True
```

```python
def FindSubstringNaive(T, P)):
    positions <- empty list
    for i from |T| - |P|:
        if AreEqual(T[i..i + |P| -1], P):
            positions.Append(i)
    return positions
    # O(|T|*|P|)
```

```python
def RabinKarp(T, P)):
    p <- big_prime
    x <- random(1, p -1)
    positions <- empty list
    pHash <- PolyHash(P, p, x)

    for i from 0 to |T| - |P|:
        tHash <- PolyHash(T[i..i + |P| -1], p, x)
        if pHash != tHash
            continue

        if AreEqual(T[i..i +  |P| - 1], P)
            positions.Append(i)
    return positions
```

```python
def PrecomputeHashes(T, |P|, p, x):
    H <- array of length |T| - |P| + 1
    S <- T[|T| - |P|..|T| - 1]
    H[|T| - |P|] <- PolyHash(S, p ,x)
    y <- 1
    for i from 1 to |P|:
        y <- (y*x) mod p
    for i from |T| - |P| - 1 downto 0:
        H[i] <- (xH[i + 1] + T[i] - yT[i + |P|])mod p 
    return H
    # O(|P| + |P| + |T| - |P|) = O(|T| + |P|), much faster!
```
```python
def RabinKarpFinal(T, P)):
    p <- big_prime
    x <- random(1, p -1)
    positions <- empty list
    pHash <- PolyHash(P, p, x)
    H <- PrecomputeHashes(T, |P|, p , x)

    for i from 0 to |T| - |P|:
        if pHash != H[i]
            continue

        if AreEqual(T[i..i +  |P| - 1], P)
            positions.Append(i)
    return positions
    # O(|T| + (q + 1)|P|)
```
