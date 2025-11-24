#include <stdio.h>
#include <string.h>

#define BASE 256
#define MOD 101   // A prime number for hash

void rabinKarp(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int i, j;
    int p_hash = 0;     // hash for pattern
    int t_hash = 0;     // hash for text
    int h = 1;

    // h = (BASE^(m-1)) % MOD
    for (i = 0; i < m - 1; i++)
        h = (h * BASE) % MOD;

    // Initial hash of pattern and first window
    for (i = 0; i < m; i++) {
        p_hash = (BASE * p_hash + pattern[i]) % MOD;
        t_hash = (BASE * t_hash + text[i]) % MOD;
    }

    for (i = 0; i <= n - m; i++) {

        // If hash matches check characters
        if (p_hash == t_hash) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m) {
                printf("Pattern found at index %d\n", i);
            }
        }

        // Calculate hash for next window
        if (i < n - m) {
            t_hash = (BASE * (t_hash - text[i] * h) + text[i + 1 + m - 1]) % MOD;

            if (t_hash < 0)
                t_hash += MOD;
        }
    }
}

int main() {
    char text[200], pattern[200];

    printf("Enter text: ");
    gets(text);

    printf("Enter pattern: ");
    gets(pattern);

    rabinKarp(text, pattern);

    return 0;
}

