#include <iostream>
using namespace std;

int sentinelLinearSearch(int a[], int n, int k) {
    int last = a[n - 1]; // Store last element
    a[n - 1] = k;        // Place sentinel
    int i = 0;
    while (a[i] != k) {
        i++;
    }
    a[n - 1] = last;     // Restore original last element
    if (i < n - 1 || last == k) {
        return i;
    }
    return -1;
}

int main() {
    int n, k;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> k;
    cout << sentinelLinearSearch(a, n, k) << endl;
    return 0;
}
