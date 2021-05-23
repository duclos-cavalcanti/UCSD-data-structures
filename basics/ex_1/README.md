# Exercise 1
## Concepts
    Stacks

## Problem Description
In this problem you will implement a feature for a text editor to find errors in the usage of brackets in the code.

Your friend is making a text editor for programmers. He is currently working on a feature that will
find errors in the usage of different types of brackets. Code can contain any brackets from the set
[]{}(), where the opening brackets are [,{, and ( and the closing brackets corresponding to them are ],}, and ).

For convenience, the text editor should not only inform the user that there is an error in the usage
of brackets, but also point to the exact place in the code with the problematic bracket. First priority
is to find the first unmatched closing bracket which either doesn’t have an opening bracket before it.

If there are no mistakes, text editor should inform the user that the usage of brackets
is correct.

Apart from the brackets, code can contain big and small latin letters, digits and punctuation marks.

More formally, all brackets in the code should be divided into pairs of matching brackets, such that in
each pair the opening bracket goes before the closing bracket, and for any two pairs of brackets either
one of them is nested inside another one.

## Summary

- Only inform user if there is an error in the usage of brackets.
    - Also point to the exact place in the code with the problematic bracket.

1. Find first unmatched closing bracket, either by not having a opening matching bracket
   before it or closes the wrong bracket.

2. If **1** doesnt occur, show/find the first unmatched opening bracket that does not
   contain a closing bracket.

3. If both **1** and **2** don't occur, inform the user of "Success".

### Input Format.
String S containing letters and brackets like ()[]{}.

### Constraints
S-Length at least 1 and at most 10 to the power of 5.

### Output Format.
If the code in S uses brackets correctly, output “Success" (without the quotes). Otherwise,
1-based index of the first unmatched closing bracket, and if there are no unmatched closing
output the 1-based index of the first unmatched opening bracket.
