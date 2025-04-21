#include <iostream>
using namespace std;

// Recursive function to solve Towers of Hanoi
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {                   // Base case: only one disk to move
        cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl;
        return;
    }
    // Move n-1 disks from source to auxiliary rod
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    // Move the nth disk from source to target rod
    cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
    // Move n-1 disks from auxiliary to target rod
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n;
    cin >> n;                       // Read number of disks
    towerOfHanoi(n, 'A', 'C', 'B'); // Solve with rods A (source), C (target), B (auxiliary)
    return 0;
}
