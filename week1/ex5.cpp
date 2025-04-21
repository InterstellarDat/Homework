#include <iostream>
using namespace std;

// Recursive function to check if array is sorted
bool isSorted(int arr[], int n) {
    if (n <= 1) return true;        // Base case: 0 or 1 element is sorted
    if (arr[0] > arr[1]) return false; // If current element > next, not sorted
    return isSorted(arr + 1, n - 1); // Recursive call for rest of array
}

int main() {
    int n;
    cin >> n;                       // Read array size
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];              // Read array elements
    }
    if (isSorted(arr, n)) {
        cout << "The array is sorted.\n";
    } else {
        cout << "The array is NOT sorted.\n";
    }
    return 0;
}
