import time

def dna_alignment(A, B, match=1, mismatch=-1, gap=-2):
    m, n = len(A), len(B)

    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(1, m + 1):
        dp[i][0] = dp[i - 1][0] + gap
    for j in range(1, n + 1):
        dp[0][j] = dp[0][j - 1] + gap

    print("Initial DP table:")
    for row in dp:
        print(row)
    print()

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if A[i - 1] == B[j - 1]:
                score_diag = dp[i - 1][j - 1] + match
            else:
                score_diag = dp[i - 1][j - 1] + mismatch

            score_up = dp[i - 1][j] + gap
            score_left = dp[i][j - 1] + gap

            best = max(score_diag, score_up, score_left)
            dp[i][j] = best

            print(f"Comparing A[{i-1}] = '{A[i-1]}' with B[{j-1}] = '{B[j-1]}'")
            print(f"  diag (match/mismatch): {score_diag}")
            print(f"  up   (gap):            {score_up}")
            print(f"  left (gap):            {score_left}")
            print(f"  → best score chosen:   {best}")
            print("DP table now:")
            for row in dp:
                print(row)
            print()

    print("Final DP table:")
    for row in dp:
        print(row)

    print(f"\nFinal alignment score: {dp[m][n]}")


start = time.time()
dna_alignment("AAAA", "GGGG")
end = time.time()
print(f"Runtime: {end - start} seconds")