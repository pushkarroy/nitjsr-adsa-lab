#include <stdio.h>
#include <string.h>

#define ALPHABET 256

void badCharTable(char pattern[], int m, int badChar[]) {
	int i;
    for ( i = 0; i < ALPHABET; i++)
        badChar[i] = -1;
    for ( i = 0; i < m; i++)
        badChar[(unsigned char)pattern[i]] = i;
}

void boyerMoore(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int badChar[ALPHABET];
    badCharTable(pattern, m, badChar);

    int s = 0;  // shift
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else {
            int shift = j - badChar[text[s + j]];
            if (shift < 1) shift = 1;
            s += shift;
        }
    }
}

int main() {
    char text[200], pattern[200];
    printf("Enter text: ");
    gets(text);
    printf("Enter pattern: ");
    gets(pattern);

    boyerMoore(text, pattern);
    return 0;
}

