#include <stdio.h>
#include <string.h>

#define MAX 20   // max size for dp table

void init_table(int dp[MAX][MAX], int m, int n, int gap) {
    dp[0][0] = 0;

    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i - 1][0] + gap;
    }

    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] + gap;
    }
}

void fill_table(int dp[MAX][MAX], char A[], char B[], int match, int mismatch, int gap) {
    int m = strlen(A);
    int n = strlen(B);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            int score_diag = dp[i - 1][j - 1] + 
                (A[i - 1] == B[j - 1] ? match : mismatch);

            int score_up = dp[i - 1][j] + gap;
            int score_left = dp[i][j - 1] + gap;

            int best = score_diag;
            if (score_up > best) best = score_up;
            if (score_left > best) best = score_left;

            dp[i][j] = best;
        }
    }
}

void print_table(int dp[MAX][MAX], int m, int n) {
    printf("DP table:\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%3d ", dp[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char A[] = "AAGC";
    char B[] = "AGT";

    int match = 1;
    int mismatch = -1;
    int gap = -2;

    int m = strlen(A);
    int n = strlen(B);

    int dp[MAX][MAX];

    init_table(dp, m, n, gap);
    fill_table(dp, A, B, match, mismatch, gap);
    print_table(dp, m, n);

    printf("\nFinal score: %d\n", dp[m][n]);

    return 0;
}