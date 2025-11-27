# Assignment 3

## Project Description

This project compares two DNA sequences using dynamic programming. The program builds a DP table and evaluates alignment scores using match, mismatch, and gap penalties. Both C and Python implementations are included. The Python version prints each step of the DP process. The C version includes testing functions and DP table printing.

## Task Allocation

### Massimo

- Wrote the Python implementation.
- Added detailed step-by-step DP table printing.
- Helped explain DP logic and scoring choices.

### Vinh Nguyen

- Wrote the C implementation.
- Added initialization, fill, and print functions.
- Prepared the automated test suite for multiple DNA examples.

### Bao Nguyen

- Wrote pseudocode.
- Analyzed DP operations and alignment principles.
- Reviewed correctness and documentation.

## Pseudocode

```
function align(A, B):
    create dp table sized (len(A)+1) x (len(B)+1)

    for i from 1 to len(A):
        dp[i][0] = dp[i-1][0] + gap

    for j from 1 to len(B):
        dp[0][j] = dp[0][j-1] + gap

    for i from 1 to len(A):
        for j from 1 to len(B):
            diag = dp[i-1][j-1] + match_or_mismatch
            up = dp[i-1][j] + gap
            left = dp[i][j-1] + gap
            dp[i][j] = max(diag, up, left)

    return dp[len(A)][len(B)]
```

## Time Complexity

Dynamic programming computes each subproblem once. The DP table has (m + 1) rows and (n + 1) columns, where m is the length of the first sequence and n is the length of the second sequence.

For each cell dp[i][j], the algorithm performs constant-time work:

- one comparison between A[i−1] and B[j−1]
- three score calculations (diagonal, up, left)
- one max comparison to select the best value

Because each of the m × n cells performs O(1) work, the total time is:

Time = O(m × n)

### Breakdown by function

- `init_table`: O(m + n)
- `fill_table`: O(m × n)
- `print_table`: O(m × n)

The dominant term is the fill step, which defines the final time complexity.

### Comparison to the naive approach

A naive recursive alignment must explore three branches at every step:

- match or mismatch
- delete
- insert

This produces an exponential worst case:

Time = O(3^(m + n))

Dynamic programming removes repeated work by storing results in the DP table. This improvement reduces the time from exponential to quadratic.

Therefore, the final time complexity of the implemented algorithm is:

O(m × n)

Dynamic programming prevents exponential recomputation seen in naive recursion.

## Project Structure

```
assignment3/
│
├── dna_alignment.c
├── dna_alignment.py
└── README.md
```

## How to Run

### Python

```
python3 dna_alignment.py
```

### C

```
gcc dna_alignment.c -o dna_alignment
./dna_alignment
```

## Requirements

### Python

```
python>=3.8
```

No external libraries required.

### C

Any C99-compatible compiler.

## Bibliography

**Kellis, M.** (2005). _Sequence Alignment_. Lecture 5, **6.096 Algorithms for Computational Biology**, Massachusetts Institute of Technology. Retrieved from https://ocw.mit.edu/courses/6-096-algorithms-for-computational-biology-spring-2005/01f55f348ea1e95f7015bd1b40586012_lecture5.pdf

**Annotation:**  
This lecture explains biological sequence alignment using dynamic programming. It covers scoring matrices, gap penalties, global and local alignment, and includes pseudocode relevant to this assignment.

This README was generated with the help of ChatGPT 5.
