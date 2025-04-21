#include <iostream>
using namespace std;

// Recursive function to compute nth Fibonacci number
int fibonacci(int n) {
    if (n == 0) return 0;           // Base case: F(0) = 0
    if (n == 1) return 1;           // Base case: F(1) = 1
    return fibonacci(n - 1) + fibonacci(n - 2); // Recursive case
}

// Helper function to print Fibonacci series up to n terms
void printFibonacci(int n, int i = 0) {
    if (i >= n) return;             // Base case: stop when i reaches n
    cout << fibonacci(i) << " ";    // Print current Fibonacci number
    printFibonacci(n, i + 1);       // Recursive call for next number
}

int main() {
    int n;
    cin >> n;                       // Read input
    printFibonacci(n);              // Print series
    cout << endl;
    return 0;
}
