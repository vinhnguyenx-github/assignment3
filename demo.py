import time
import random

def random_dna(length):
    bases = ["A", "C", "G", "T"]
    return "".join(random.choice(bases) for _ in range(length))

def dna_alignment_demo(A, B, match=1, mismatch=-1, gap=-2):
    m, n = len(A), len(B)

    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # Base cases
    for i in range(1, m + 1):
        dp[i][0] = dp[i - 1][0] + gap
    for j in range(1, n + 1):
        dp[0][j] = dp[0][j - 1] + gap

    # Fill DP table
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if A[i - 1] == B[j - 1]:
                score_diag = dp[i - 1][j - 1] + match
            else:
                score_diag = dp[i - 1][j - 1] + mismatch

            score_up = dp[i - 1][j] + gap
            score_left = dp[i][j - 1] + gap

            dp[i][j] = max(score_diag, score_up, score_left)

    print("Sequence A:", A)
    print("Sequence B:", B)

    # Print a 50×50 subsection of the DP table
    limit = 50
    for i in range(min(m+1, limit)):
        print(dp[i][:limit])

    print(f"\nFinal alignment score: {dp[m][n]}")

# Use short sequences for printing version
A = random_dna(30)
B = random_dna(30)

start = time.time()
dna_alignment_demo(A, B)
end = time.time()

print(f"Runtime: {end - start} seconds")

print("\n=== Test with AAGC vs AGT ===")
start = time.time()
dna_alignment_demo("AAGC", "AGT")
end = time.time()
print(f"Runtime: {end - start} seconds")