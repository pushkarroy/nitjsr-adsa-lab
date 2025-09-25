#include <stdio.h>
#include <stdbool.h>

#define N 8   // You can change N (e.g., 4, 8)

int board[N][N];

// Function to print the chessboard
void printSolution() {
	int i,j;
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

// Check if a queen can be placed on board[row][col]
bool isSafe(int row, int col) {
    int i, j;

    // Check this column on upper rows
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper-left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper-right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Solve N-Queens using backtracking
bool solveNQUtil(int row) {
    // Base case: If all queens are placed
    if (row == N) {
        printSolution();
        return true; // To print all solutions, do not return here
    }

    bool res = false;
    int col;
    for ( col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;

            // Recur to place rest of the queens
            res = solveNQUtil(row + 1) || res;

            // BACKTRACK
            board[row][col] = 0;
        }
    }

    return res;
}

// Main function
int main() {
    // Initialize board
    int i,j;
    for ( i = 0; i < N; i++)
        for ( j = 0; j < N; j++)
            board[i][j] = 0;

    if (!solveNQUtil(0)) {
        printf("Solution does not exist\n");
    }

    return 0;
}

