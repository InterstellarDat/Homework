#include <iostream>
using namespace std;

// Recursive function to compute factorial
int factorial(int n) {
    if (n == 0) return 1;           // Base case: 0! = 1
    return n * factorial(n - 1);    // Recursive case: n! = n * (n-1)!
}

int main() {
    int n;
    cin >> n;                       // Read input
    cout << factorial(n) << endl;   // Output result
    return 0;
}
