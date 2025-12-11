import time
import random
import numpy as np

def random_dna(length):
    bases = ["A", "C", "G", "T"]
    return "".join(random.choice(bases) for _ in range(length))

def dna_alignment_numpy(A, B, match=1, mismatch=-1, gap=-2):
    m, n = len(A), len(B)

    dp = np.zeros((m + 1, n + 1), dtype=np.int32)

    # base cases
    dp[1:, 0] = np.arange(1, m + 1, dtype=np.int32) * gap
    dp[0, 1:] = np.arange(1, n + 1, dtype=np.int32) * gap

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if A[i - 1] == B[j - 1]:
                score_diag = dp[i - 1, j - 1] + match
            else:
                score_diag = dp[i - 1, j - 1] + mismatch

            score_up = dp[i - 1, j] + gap
            score_left = dp[i, j - 1] + gap

            dp[i, j] = max(score_diag, score_up, score_left)

    print(f"Final alignment score: {dp[m, n]}")
    return dp[m, n]

A = random_dna(10000)
B = random_dna(10000)

start = time.time()
score = dna_alignment_numpy(A, B)
end = time.time()

print(f"Runtime: {end - start} seconds")