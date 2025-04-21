#include <iostream>
#include <string>
using namespace std;

// Recursive function to generate binary strings
void generateBinaryStrings(int n, string str) {
    if (str.length() == static_cast<size_t>(n)) { // Base case: string length equals n
        cout << str << endl;                      // Print the binary string
        return;
    }
    // Append '0' and recurse
    generateBinaryStrings(n, str + "0");
    // Append '1' and recurse
    generateBinaryStrings(n, str + "1");
}

int main() {
    int n;
    cin >> n;                       // Read input
    generateBinaryStrings(n, "");   // Start with empty string
    return 0;
}
