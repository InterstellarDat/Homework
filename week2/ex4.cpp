#include <iostream>
using namespace std;

int shipWithinDays(int weights[], int n, int days) {
    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        left = max(left, weights[i]); // Min capacity: max weight
        right += weights[i];          // Max capacity: sum of weights
    }
    while (left < right) {
        int mid = left + (right - left) / 2;
        int currDays = 1, currWeight = 0;
        for (int i = 0; i < n; i++) {
            if (currWeight + weights[i] > mid) {
                currDays++;
                currWeight = weights[i];
            } else {
                currWeight += weights[i];
            }
        }
        if (currDays > days) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int main() {
    int n, days;
    cin >> n;
    int weights[n];
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    cin >> days;
    cout << shipWithinDays(weights, n, days) << endl;
    return 0;
}
