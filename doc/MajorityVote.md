# Boyer-Moore Majority Vote Algorithm
## Problem
If you have a non-sorted list of integers, you want to know if there is a value that is the majority element(# of this value is more than or equal to half length of the list). If so, how to find the value as efficiently as possible with as little as extra space? (If we have enough extra space, linear time complexity is possible and can be implemented easily.) If not, you need to know that there is no majority element.

In the data [stream model](https://en.wikipedia.org/wiki/Streaming_algorithm), the **frequent elements problem** is to output a set of elements that constitute more than some fixed fraction of the stream. A special case is the **majority problem**, which is to determine whether or not any value constitutes a majority of the stream.

## Intro and Definition
The majority vote problem is to determine in any given sequence of votes whether there is a candidate with more votes than all the others, and if so, to determine this candidate. The Boyer-Moore majority vote algorithm solves the problem in time linear in the length of the sequence and constant memory.

It does so in two repetitions. The first repetition eliminates all candidates but one. The second repetition verifies whether or not the remaining candidate holds a majority. Given the postcondition of the first repetition, it is easy to implement the second repetition, and to verify its correctness.

## Proof$^{[2]}$
Compared to the second repetition, the first one is more interesting.
We model the input sequence of votes by an array $a$, and the candidate to be chosen by a variable $p$, according to the following daclaration.

$$
\begin{align}
\bold{const}\space n: Nat; \\
a: \bold{array}\space [0,1,...,n) of\space Candidate;\\
var\space p: Candidate.
\end{align}
$$

## Related Problem
[Leetcode 229 Majority Element II](https://leetcode.com/problems/majority-element-ii/)

> Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
> Note: The algorithm should run in linear time and in O(1) space.
> 
> Example 1:
> >Input: [3,2,3]
> >
> >Output: [3]
> 
> Example 2:
> >
> >Input: [1,1,1,3,3,2,2,2]
> >
> >Output: [1,2]

## Reference
1. [Boyer-Moore Majority Vote Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm)

2. [Boyer-Moore algorithm - Paper](http://www.cs.rug.nl/~wim/pub/whh348.pdf)

3. [Majority Voting Algorithm - Blog](https://gregable.com/2013/10/majority-vote-algorithm-find-majority.html)