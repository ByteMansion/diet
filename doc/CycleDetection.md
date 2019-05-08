# Cycle Detection

In computer science, **cycle detection** or **cycle finding** is a algorithmic problem of finding a cycle in a sequence of iterated function values.

For any function $f$ that maps a finite set $S$ to itself, and any initial value $x_0$ in $S$, the sequence if iterated function values
$$x_0, x_1 = f(x_0), x_2 = f(x_1), ..., x_i = f(x_{i-1}), ...$$
must eventually use the same value twice: there must be some pair of distinct indices $i$ and $j$ such that $x_i = x_j$. Once this happens, the sequence must continue periodically, by repeading the same sequence of values from $x_i$ to $x_{j-1}$. Cycle detection is the problem of finding $i$ and $j$, given $f$ and $x_0$.

Several algorithms for finding cycles quickly and with little memory are known. **Floyd's tortoise and the hare algorithm moves two pointers at different speeds through the sequence of values until they both point to equal values.** Alternatively, **Brent's algorithm is based on the idea of exponential search.** Both Floyd's and Brent's algorithms use only a constant number of memory cells, and take a number of function evaluations that is proportional to the distance from the start of the sequence to the first repetion. Several other algorithms trade off larger amounts of memory for fewer function evaluations.

The applications of cycle detection include testing the quality of pseudorandom number generators and cryptographic hash functions, computational number theory algorithms, detection of infinite loops in computer programs and periodic configurations in cellular automata, and the automated shape analysis of linked list data structures.

