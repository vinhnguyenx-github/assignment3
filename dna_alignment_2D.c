#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 60000

// allocate 2D DP array safely
int **alloc_dp_2D(int m, int n) {
    int **dp = malloc((m + 1) * sizeof(int *));
    if (!dp) return NULL;

    for (int i = 0; i <= m; i++) {
        dp[i] = malloc((n + 1) * sizeof(int));
        if (!dp[i]) {
            // free previous rows
            for (int k = 0; k < i; k++) free(dp[k]);
            free(dp);
            return NULL;
        }
    }
    return dp;
}

void free_dp_2D(int **dp, int m) {
    for (int i = 0; i <= m; i++) free(dp[i]);
    free(dp);
}

void random_dna(char *S, int len) {
    static const char bases[4] = {'A','C','G','T'};
    for (int i = 0; i < len; i++)
        S[i] = bases[rand() % 4];
    S[len] = '\0';
}

void init_table(int **dp, int m, int n, int gap) {
    dp[0][0] = 0;
    for (int i = 1; i <= m; i++) dp[i][0] = dp[i-1][0] + gap;
    for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j-1] + gap;
}

void fill_table(int **dp, char *A, char *B, int m, int n,
                int match, int mismatch, int gap)
{
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int diag = dp[i-1][j-1] + (A[i-1] == B[j-1] ? match : mismatch);
            int up   = dp[i-1][j] + gap;
            int left = dp[i][j-1] + gap;

            int best = diag;
            if (up > best) best = up;
            if (left > best) best = left;

            dp[i][j] = best;
        }
    }
}

int main() {
    srand(time(NULL));

    char *A = malloc(MAX_LEN + 1);
    char *B = malloc(MAX_LEN + 1);

    random_dna(A, MAX_LEN);
    random_dna(B, MAX_LEN);

    printf("Allocating %dx%d DP table...\n", MAX_LEN, MAX_LEN);

    int **dp = alloc_dp_2D(MAX_LEN, MAX_LEN);
    if (!dp) {
        printf("Failed to allocate DP table (not enough RAM)\n");
        return 1;
    }

    int match = 1, mismatch = -1, gap = -2;

    clock_t start = clock();
    init_table(dp, MAX_LEN, MAX_LEN, gap);
    fill_table(dp, A, B, MAX_LEN, MAX_LEN, match, mismatch, gap);
    clock_t end = clock();

    printf("Final score: %d\n", dp[MAX_LEN][MAX_LEN]);
    printf("Runtime for 2D: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free_dp_2D(dp, MAX_LEN);
    free(A);
    free(B);
    return 0;
}