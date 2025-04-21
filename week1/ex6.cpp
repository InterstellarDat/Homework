#include <iostream>
using namespace std;

const int MAX_N = 10; // Maximum board size (adjustable)
int board[MAX_N][MAX_N] = {0}; // Chessboard initialized to 0 (no queens)
int solutions = 0; // Counter for valid solutions

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int row, int col, int n) {
    // Check column above current row
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) return false; // Queen in same column
    }
    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false; // Queen on left diagonal
    }
    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) return false; // Queen on right diagonal
    }
    return true; // Safe to place queen
}

// Recursive function to solve N-Queens problem
void solveNQueens(int row, int n) {
    if (row == n) { // Base case: all queens placed successfully
        solutions++; // Increment solution count
        return;
    }
    // Try placing queen in each column of current row
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, n)) { // Check if position is safe
            board[row][col] = 1;   // Place queen
            solveNQueens(row + 1, n); // Recur for next row
            board[row][col] = 0;   // Backtrack: remove queen
        }
    }
}

int main() {
    int n;
    cin >> n; // Read board size N
    if (n > MAX_N || n < 1) {
        cout << "Invalid board size. Must be between 1 and " << MAX_N << endl;
        return 1;
    }
    solveNQueens(0, n); // Start solving from row 0
    cout << "Number of solutions: " << solutions << endl; // Output total solutions
    return 0;
}
