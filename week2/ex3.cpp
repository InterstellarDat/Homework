#include <iostream>
using namespace std;

int findMin(int nums[], int n) {
    int low = 0, high = n - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] > nums[high]) {
            low = mid + 1; // Min is in right half
        } else {
            high = mid;    // Min is in left half or at mid
        }
    }
    return nums[low];
}

int main() {
    int n;
    cin >> n;
    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << findMin(nums, n) << endl;
    return 0;
}
