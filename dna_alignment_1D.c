#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 40000

// Macro for 1D array indexing: dp[i][j] becomes DP(i, j)
#define DP(i, j) dp[(i) * (n+1) + (j)]

// Allocate contiguous 1D array for DP table
int *alloc_dp(int m, int n) {
    return (int*)malloc((m + 1) * (n + 1) * sizeof(int));
}

// Initialize base cases for DP table
void init_table(int *dp, int m, int n, int gap) {
    DP(0, 0) = 0;
    
    // First column: gaps in sequence B
    for (int i = 1; i <= m; i++) {
        DP(i, 0) = DP(i-1, 0) + gap;
    }
    
    // First row: gaps in sequence A
    for (int j = 1; j <= n; j++) {
        DP(0, j) = DP(0, j-1) + gap;
    }
}

void fill_table(int *dp, const char *A, const char *B, int m, int n, 
                int match, int mismatch, int gap) {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int diag = DP(i-1, j-1) + ((A[i-1] == B[j-1]) ? match : mismatch);
            int up = DP(i-1, j) + gap;
            int left = DP(i, j-1) + gap;
            int best = diag;
            if (up > best) best = up;
            if (left > best) best = left;
            DP(i, j) = best;
        }
    }
}

// Generate random DNA sequence
void random_dna(char *S, int len) {
    const char bases[4] = {'A', 'C', 'G', 'T'};
    for (int i = 0; i < len; i++) {
        S[i] = bases[rand() % 4];
    }
    S[len] = '\0';
}

int main() {
    srand(time(NULL));
    
    // Allocate sequences on heap (too large for stack)
    char *A = (char*)malloc(MAX_LEN + 1);
    char *B = (char*)malloc(MAX_LEN + 1);
    
    if (!A || !B) {
        fprintf(stderr, "Failed to allocate memory for sequences\n");
        return 1;
    }
    
    // Generate random DNA sequences
    random_dna(A, MAX_LEN);
    random_dna(B, MAX_LEN);
    
    int m = strlen(A);
    int n = strlen(B);
    
    int *dp = alloc_dp(m, n);
    
    if (!dp) {
        fprintf(stderr, "Failed to allocate DP table\n");
        free(A);
        free(B);
        return 1;
    }
    
    // Scoring parameters
    int match = 1;
    int mismatch = -1;
    int gap = -2;
    
    printf("Allocating %dx%d DP table...\n", MAX_LEN, MAX_LEN);
    
    // Time the alignment
    clock_t start = clock();
    init_table(dp, m, n, gap);
    fill_table(dp, A, B, m, n, match, mismatch, gap);
    clock_t end = clock();
    
    printf("Final score: %d\n", DP(m, n));
    printf("Runtime for 1D: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    // Cleanup
    free(dp);
    free(A);
    free(B);
    
    return 0;
}