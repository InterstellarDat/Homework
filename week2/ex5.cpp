#include <iostream>
using namespace std;

int minSubArrayLen(int target, int nums[], int n) {
    int minLen = n + 1, currSum = 0, left = 0;
    for (int right = 0; right < n; right++) {
        currSum += nums[right];
        while (currSum >= target) {
            minLen = min(minLen, right - left + 1);
            currSum -= nums[left++];
        }
    }
    return (minLen > n) ? 0 : minLen;
}

int main() {
    int target, n;
    cin >> target >> n;
    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << minSubArrayLen(target, nums, n) << endl;
    return 0;
}
