# Problems

### Karatsuba multiplication
Regular implementation of the $O(n^{\log_{2} 3})$ Karatsuba multiplication algorithm.
- Need to reduce the number copies, i.e `memcpy` calls, if possible

### Merge sort
Two implementations are in the file [msort.c](src/msort.c) and [merge_sort.c](src/merge_sort.c).
First one is the typical and more readable implementation of the algorithm. Second one is compiled into a static library, that mimics the quick-sort `qsort` implementation in C, using `void` pointers to specify the array and a comparison function `compar`.
```c
void msort(void *_Nonnull base,
        const size_t nel,
        const size_t width,
        int (*_Nonnull compar)(const void *_Nonnull, const void *_Nonnull))
```

### Array inversions
Piggyback of merge sort to count the number of inversion on an array. The C implementation uses a `struct` to group the array pointer and inversion counter. 

### Strassen matrix multiplication
Piggyback of merge sort to count the number of inversion on an array. The C implementation uses a `struct` to group the array pointer and inversion counter.

## Optional batch (weeks 2)

-   You are given as input an unsorted array of n distinct numbers, where $n$ is a power of $2$. Give an algorithm that identifies the second-largest number in the array, and that uses at most $n + \log_{2}(n) - 2$ comparisons.

-   You are a given a _unimodal_ array of n distinct elements, meaning that its entries are in increasing order up until its maximum element, after which its elements are in decreasing order. Give an algorithm to compute the maximum element that runs in $O(\log n)$ time.

-   You are given a sorted (from smallest to largest) array `A` of $n$ distinct integers which can be positive, negative, or zero. You want to decide whether or not there is an index `i` such that `A[i] = i`. Design the fastest algorithm that you can for solving this problem.

-   You are given an $n$ by $n$ grid of distinct numbers. A number is a local minimum if it is smaller than all of its neighbors. (A neighbor of a number is one immediately above, below, to the left, or the right. Most numbers have four neighbors; numbers on the side have three; the four corners have two.) Use the divide-and-conquer algorithm design paradigm to compute a local minimum with only $O(n)$ comparisons between pairs of numbers. (**Note:** since there are $n^2$ numbers in the input, you cannot afford to look at all of them. **Hint:** Think about what types of recurrences would give you the desired upper bound.)
