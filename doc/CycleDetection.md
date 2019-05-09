# Cycle Detection
## Intro
In computer science, **cycle detection** or **cycle finding** is a algorithmic problem of finding a cycle in a sequence of iterated function values.

For any function $f$ that maps a finite set $S$ to itself, and any initial value $x_0$ in $S$, the sequence if iterated function values
$$x_0, x_1 = f(x_0), x_2 = f(x_1), ..., x_i = f(x_{i-1}), ...$$
must eventually use the same value twice: there must be some pair of distinct indices $i$ and $j$ such that $x_i = x_j$. Once this happens, the sequence must continue periodically, by repeading the same sequence of values from $x_i$ to $x_{j-1}$. `Cycle detection is the problem of finding $i$ and $j$, given $f$ and $x_0$.`

Several algorithms for finding cycles quickly and with little memory are known. **Floyd's tortoise and the hare algorithm moves two pointers at different speeds through the sequence of values until they both point to equal values.** Alternatively, **Brent's algorithm is based on the idea of exponential search.** Both Floyd's and Brent's algorithms use only a constant number of memory cells, and take a number of function evaluations that is proportional to the distance from the start of the sequence to the first repetition. Several other algorithms trade off larger amounts of memory for fewer function evaluations.

The applications of cycle detection include testing the quality of pseudorandom number generators and cryptographic hash functions, computational number theory algorithms, detection of infinite loops in computer programs and periodic configurations in cellular automata, and the automated shape analysis of linked list data structures.

## Definition
Let $S$ be any finite set, $f$ be any function from $S$ to itself, and $x_0$ be any element of $S$. For any $i>0$, let $x_i = f(x_{i-1})$. Let $\mu$ be the smallest index such that the value $x_{\mu}$ reappears infinitely often within the sequence of values $x_i$, and let $\lambda$(the loop length) be the smallest positive integer such that $x_{\mu} = x_{\lambda + \mu}$. The cycle detection problem is the task of finding $\lambda$ and $\mu$.

One can view the same problem graph-theoretically, by constructing a functional graph (that is, a directed graph in which each vertex has a single outgoing edge) the vertices of which are the elements of $S$ and the edges of which map an element to the corresponding function value. The set of vertices reachable from starting vertex $x_0$ form a subgraph with a shape resembling the Greek letter rho($\rho$): a path of length $\mu$ from $x_0$ to a cycle of $\lambda$ vertices.

## Algorithms
If the input is given as a subroutine for calculating $f$, the cycle detection problem may be trivially solved using only $\lambda + \mu$ function applications, simply by computing the sequence of values $x_i$ and using a data structure such as a hash table to store these values and test whether each subsequent value has already been stored. However, the space complexity of this algorithm is proportional to $\lambda + \mu$, unnecessarily large. Additionally, to implement this method as pointer algorithm would require applying the equality test to each pair of values, resulting in quadratic time overall. Thus, research in this area has concentrated on two goals: using less space than this naive algorithm, and finding pointer algorithms that use fewer equality tests.

### Floyd's Tortoise and Hare
**Floyd's cycle detection algorithm** is a pointer algorithm that uses only two pointers, which move through the sequence at different speeds. It is also called "tortoise and the hare algorithm", alluding to Aesop's fable of The Tortoise and the Hare.

The key insight in the algorithm is as follows. If there is a cycle, then, for any integers $i ≥ \mu$ and $k ≥ 0$, $x_i = x_{i + k\lambda}$, where $\lambda$ is the length of the loop to be found and $\mu$ is the index of the first element of the cycle. Based on this, it can then be shown that $i=k\lambda ≥ \mu$ for some $k$ if and only if $x_i = x_{2i}$. Thus, the algorithm only needs to check for repeated values of this special form, one twice as far from the start of the sequence as the other, to find a period $v$ of a repetition that is a multiple of $\lambda$. Once $v$ is found, the algorithm retraces the sequence from its start to find the first repeated value $x_\mu$ in the sequence, using the fact that $\lambda$ divides $v$ and therefore that $x_\mu = x_{\mu + \lambda}$. Finally, once the value of $\mu$ is known it is trivial to find the length $\lambda$ of the shortest repeating cycle, by searching for the first position $\lambda + \mu$ for which $x_{\lambda+\mu} = x_\mu$.

The following Python code shows how this idea may be implemented as an algorithm.
```Python
def floyd(f, x0):
    # Main phrase of algorithm: finding a repetition x_i = s_2i.
    # The hare moves twice as quickly as the tortoise and the distance
    # between them increases by 1 at each step. Eventually they will both
    # be inside the cycle and then, at some point, the distance between them
    # will be divisible by the period λ.
    tortoise = f(x0)  # f(x0) is the element/node next to x0
    hare = f(f(x0))
    while tortoise != hare:
        tortoise = f(tortoise)
        hare = f(f(hare))
    # At this point, the tortoise position, v, which is also equal to the distance
    # between hare and tortoise, is divisible by the period λ. So hare moving in circle 
    # on step at a time, and tortoise(reset to x0) moving torwards the circle, will 
    # intersect at the beginning of the circle. Because the distance between them is 
    # constant at 2v, a multiple of λ, they will agree as soon as the tortoise reaches
    # index μ.

    # Find the position μ of the first element
    mu = 0
    tortoise = x0
    while tortoise != hare:
        tortoise = f(tortoise)
        hare = f(hare)
        mu += 1
    # Find the loop length λ
    lam = 1
    hare = f(tortoise)
    while tortoise != hare:
        hare = f(hare)
        lam += 1

    return lam, mu
```
The code only accesses the sequence by sorting and copying pointers, function evaluations, and equality tests; therefore, it qualifies as a pointer algorithm. The algorithm uses $O(\lambda + \mu)$ operations of these types, and $O(1)$ storage space.

### Brent's algorithm
*Richard P. Brent* described an alternative cycle detection algorithm that, like the tortoise and hare algorithm, requires only two pointers into the sequence. However, it is based on a different principle: searching for the smallest power of two $2^i$ that is larger than both $\lambda$ and $\mu$. For $i = 0, 1, 2, ...$, the algorithm compares $x_{2^i-1}$ with each subsequent sequence value up to the next power of two, stopping when it finds a match. It has two advantages compares to the tortoise and hare algorithm: it finds the correct length $\lambda$ of the cycle directly, rather than needing to search for it in a subsequent stage, and its steps involve only one evaluation of $f$ rather than three.

The following Python code shows how this technique works in more detail.
```Python
def brent(f, x0):
    # main phase: search successive power of two
    power = lam = 1
    tortoise = x0
    hare = f(x0)
    # When tortoise is in cycle, and the power of two is large enough,
    # the hare and tortoise will meet with λ less than the power.
    while tortoise != hare:
        if power == lam:  # time to start a new power of two
            tortoise = hare
            power *= 2
            lam = 0
        hare = f(hare)
        lam += 1

    # Find the position of the first repetition of length λ
    mu = 0
    tortoise = hare = x0
    for i in range(lam):
        hare = f(hare)
    # The distance between the tortoise and hare is λ
    # Next, the hare and the tortoise move at the same speed until they meet
    while tortoise != hare:
        tortoise = f(tortoise)
        hare = f(hare)
        mu += 1

    return lam, mu
```
Like the tortoise and hare algorithm, this is a pointer algorithm that uses $O(\lambda + \mu)$ tests and function evaluations and $O(1)$ storage space. It is not difficult to show that the number of function evaluations can never be higher than for Floyd's algorithm. Brent claims that, on average, his cycle finding algorithm runs around 36% more quickly than Floyd's algorithm and that it speeds up the Pollard rho algorithm by around 24%.

## Related Problems
[Leetcode 287](https://leetcode.com/problems/find-the-duplicate-number/)
> Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.
> 
> Example 1:
> >Input: [1,3,4,2,2]
> >
> >Output: 2
> 
> Example 2:
> >Input: [3,1,3,4,2]
> >
> >Output: 3
> 
> Note:
> 1. You **must not** modify the array (assume the array is read only).
> 2. You must use only constant, **O(1) extra space**.
> 3. Your runtime complexity should be **less than** O(n2).
> 4. There is only one duplicate number in the array, but it could be repeated more than once.