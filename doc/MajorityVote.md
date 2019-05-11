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
\begin{alignedat}{2}
\boldsymbol{const}\space n:& Nat; \newline
a:& \boldsymbol{array}\space [0,1,...,n) of\space Candidate; \newline
\boldsymbol{var}\space p:& Candidate.
\end{alignedat}
$$

The postcondition of the first repetition is that every candidate other than $p$ does not hold a majority:
$$
Q: (\forall q: q \neq p \Rightarrow \# \{i|a[i] = q\} \leq \frac{1}{2} \cdot n)
$$
In order to establish this postcondition, it is natural to inspect the elements of array $a$ one by one, and to introduce a loop variable
$$
\boldsymbol{var} \space k: Nat.
$$
We know define 
$$
votes(k,q) = \#\{i|i < k \land a[i] = q\}
$$
Then we have
$$
Q\equiv (\forall q: q \neq p \Rightarrow 2 \cdot votes(n,q) \leq \cdot n)
$$
This suggests the generalization
$$
P: (\forall q: q \neq p \Rightarrow 2 \cdot votes(k,q) \leq k)
$$
It is clear that $Q$ follows from $P \land k=n$. On the other hand, $P$ holds trivially for $k=0$. When $P$ holds and testing yields $a[k] = p$, we can increment $k$ and sharpen the majority estimates since the values $votes(k,q)$ remain unchanged for $q \neq p$. We therefore introduce a variable $s$ to indicate the sharpening:
$$
\boldsymbol{var} \space s: Int.
$$
The sharpening is expected in the proposed invariant
$$
J0: s \geq 0 \space \land \space k \leq n \space \land \space (\forall q: p \neq q \Rightarrow s + 2 \cdot votes(k,q) \leq k)
$$
We now choose $B: k \neq n$ as guard of the repetition to be developed. It is easy to verify that $[J0 \space \land \space \neg B \Rightarrow Q]$.

> In the following analysis, we use the terms incrementation and decrementation to mean incrementation and decrementation with 1.

1. When $J0 \land k \neq n$ holds and $a[k] = p$, then $J0$ is preserved when $s$ and $k$ are incremented.
2. When $J0 \land k \neq n$ holds and $s > 0$(and $a[k] \neq p$), then $J0$ is preserved when $k$ is incremented and $s$ is decremented.
3. When $J0 \land k \neq n$ holds and $a[k] \neq p$ and $s = 0$, however, we seem to have to switch to a different favourite candidate, i.e., to modify $p$.

Preservation of $J0$ under modification of $p$ requires an upperbound for the number of votes for the old value of $p$. It is the intention that the number of such votes increases with $s$ and $k$. In this way, we come to the additional invariant
$$
J1: \space 2 \cdot votes(k,p) \leq s + k.
$$
1. When $J1 \land k < n$ holds(and $a[k] = p$), then $J1$ is preserved when $s$ and $k$ are incremented. 
2. When $J1 \land k < n$ holds and $a[k] \neq p$ and $s > 0$, then $J1$ is preserved when $k$ is incremented and $s$ is decremented.

For the remaining case, we observe that $J0 \land J1 \land s = 0$ is equivalent to
$$
s = 0 \land k \leq n \land (\forall q: 2 \cdot votes(k, q) \leq k).
$$
It is therefore preserved under arbitrary assignments to $p$, in particular under the assignment $p = a[k]$. In that way the troublesome remaining case can be avoided. We thus get the loop body
$$
\begin{alignedat}{1}
S:\space\space& \boldsymbol{if} \space\space s = 0 \space\space \boldsymbol{then} \space\space p = a[k] \space\space \boldsymbol{end}; \\ \newline
&\{J0 \land J1 \land B \land (s > 0 \lor a[k] = p)\} \\ \newline
&\boldsymbol{if} \space\space p = a[k] \space\space \boldsymbol{then} \space\space s = s+1 \\ \newline
&\boldsymbol{else} \space\space s = s-1 \space\space \boldsymbol{end}; \\ \newline
&k = k+1
\end{alignedat}
$$
The arguments given above show that $S$ satisfies the Hoare triple
$$
\{J0 \land J1 \land B\} \space\space S \space\space \{J0 \land J1\}
$$
The variant function $vf = n - k$ remains nonnegative because of $J0$. It clearly decreases under command $S$. This proves that postcondition $Q$ is established by
$$
\begin{alignedat}{1}
    &k = 0; s = 0; \\ \newline
    &\boldsymbol{while} \space\space k \neq n \space\space \boldsymbol{do} \space\space S \space\space \boldsymbol{end}. \\ \newline
\end{alignedat}
$$
*Remark* If the problem terminates with the final value $s=0$, clearly no candidate holds a majority. If $s > \frac{1}{2} \cdot n$ in the postcondition, then $p$ holds a majority. To prove this, however, we need the additional (but obvious) invariant $s \leq votes(k,p)$.

## Related Problems
[Leetcode 169 Majority Element](https://leetcode.com/problems/majority-element/)
> Given an array of size n, find the majority element. The majority element is the element that appears **more than** ⌊ n/2 ⌋ times.
>
> *You may assume that the array is non-empty and the majority element always exist in the array.*
>
> Example 1:
>
> > Input: [3,2,3]
> > Output: 3
> 
> Example 2:
>
> > Input: [2,2,1,1,1,2,2]
> > Output: 2

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