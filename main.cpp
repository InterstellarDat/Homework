#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "DataGenerator.cpp"

using namespace std;
using namespace std::chrono;

// Selection Sort
void selectionSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            HoanVi(arr[i], arr[min_idx]);
        }
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && ++comparisons && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Shell Sort
void shellSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparisons++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                } else {
                    break;
                }
            }
            if (j != i) {
                arr[j] = temp;
            }
        }
    }
}

// Bubble Sort
void bubbleSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                HoanVi(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Heap Sort
void heapify(vector<int>& arr, int n, int i, long long& comparisons) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n) {
        comparisons++;
        if (arr[left] > arr[largest])
            largest = left;
    }
    if (right < n) {
        comparisons++;
        if (arr[right] > arr[largest])
            largest = right;
    }
    if (largest != i) {
        HoanVi(arr[i], arr[largest]);
        heapify(arr, n, largest, comparisons);
    }
}

void heapSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons);
    }
    for (int i = n - 1; i > 0; i--) {
        HoanVi(arr[0], arr[i]);
        heapify(arr, i, 0, comparisons);
    }
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right, long long& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right, long long& comparisons) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, comparisons);
    mergeSort(arr, mid + 1, right, comparisons);
    merge(arr, left, mid, right, comparisons);
}

// Quick Sort
int partition(vector<int>& arr, int low, int high, long long& comparisons) {
    int mid = low + (high - low) / 2;
    comparisons++;
    if (arr[mid] < arr[low])
        HoanVi(arr[mid], arr[low]);
    comparisons++;
    if (arr[high] < arr[low])
        HoanVi(arr[high], arr[low]);
    comparisons++;
    if (arr[mid] < arr[high])
        HoanVi(arr[mid], arr[high]);
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            HoanVi(arr[i], arr[j]);
        }
    }
    HoanVi(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high, long long& comparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons);
        quickSort(arr, low, pi - 1, comparisons);
        quickSort(arr, pi + 1, high, comparisons);
    }
}

// Radix Sort
int getMax(vector<int>& arr) {
    int max = arr[0];
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(vector<int>& arr, int exp, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int m = getMax(arr);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, exp, comparisons);
}

// Counting Sort
void countingSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    int range = max - min + 1;
    vector<int> count(range, 0), output(n);
    for (int i = 0; i < n; i++)
        count[arr[i] - min]++;
    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Binary Insertion Sort
void binaryInsertionSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0;
        int right = i;
        while (left < right) {
            int mid = left + (right - left) / 2;
            comparisons++;
            if (key >= arr[mid]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        for (int j = i; j > left; j--)
            arr[j] = arr[j - 1];
        arr[left] = key;
    }
}

// Shaker Sort
void shakerSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    int n = arr.size();
    int upperBound = n - 1;
    int lowerBound = 0;
    bool swapped;
    do {
        swapped = false;
        for (int i = lowerBound; i < upperBound; ++i) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                HoanVi(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        upperBound--;
        for (int i = upperBound; i > lowerBound; --i) {
            comparisons++;
            if (arr[i - 1] > arr[i]) {
                HoanVi(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        lowerBound++;
    } while (swapped);
}

// Flash Sort
void flashSort(vector<int>& arr, long long& comparisons) {
    comparisons = 0;
    if (arr.size() <= 1) return;
    int n = arr.size();
    int m = static_cast<int>(0.45 * n);
    vector<int> l(m, 0);
    int max = 0, min = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > arr[max]) max = i;
    }
    if (min == arr[max]) return;
    double c1 = static_cast<double>(m - 1) / (arr[max] - min);
    for (int j = 0; j < n; ++j) {
        ++l[static_cast<int>(c1 * (arr[j] - min))];
    }
    for (int p = 1; p < m; ++p) {
        l[p] += l[p - 1];
    }
    HoanVi(arr[max], arr[0]);
    int move = 0, t, flash;
    int j = 0;
    int k = m - 1;
    while (move < n - 1) {
        while (j > (l[k] - 1)) {
            ++j;
            k = static_cast<int>(c1 * (arr[j] - min));
        }
        if (k < 0) break;
        flash = arr[j];
        while (j != l[k]) {
            k = static_cast<int>(c1 * (flash - min));
            t = --l[k];
            HoanVi(arr[t], arr[j]);
            flash = arr[j];
            ++move;
        }
    }
    for (j = 1; j < n; ++j) {
        int hold = arr[j];
        int i = j - 1;
        while (i >= 0) {
            comparisons++;
            if (arr[i] <= hold) break;
            arr[i + 1] = arr[i];
            --i;
        }
        arr[i + 1] = hold;
    }
}

// Helper function to apply the sorting algorithm
void applySort(vector<int>& arr, const string& algorithm, long long& comparisons) {
    if (algorithm == "selection-sort") {
        selectionSort(arr, comparisons);
    } else if (algorithm == "insertion-sort") {
        insertionSort(arr, comparisons);
    } else if (algorithm == "shell-sort") {
        shellSort(arr, comparisons);
    } else if (algorithm == "bubble-sort") {
        bubbleSort(arr, comparisons);
    } else if (algorithm == "heap-sort") {
        heapSort(arr, comparisons);
    } else if (algorithm == "merge-sort") {
        mergeSort(arr, 0, arr.size() - 1, comparisons);
    } else if (algorithm == "quick-sort") {
        quickSort(arr, 0, arr.size() - 1, comparisons);
    } else if (algorithm == "radix-sort") {
        radixSort(arr, comparisons);
    } else if (algorithm == "counting-sort") {
        countingSort(arr, comparisons);
    } else if (algorithm == "binary-insertion-sort") {
        binaryInsertionSort(arr, comparisons);
    } else if (algorithm == "shaker-sort") {
        shakerSort(arr, comparisons);
    } else if (algorithm == "flash-sort") {
        flashSort(arr, comparisons);
    } else {
        cerr << "Invalid algorithm: " << algorithm << endl;
        exit(1);
    }
}

// Function to read data from a file
vector<int> readInputFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening input file: " << filename << endl;
        exit(1);
    }
    int size;
    file >> size;
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        if (!(file >> data[i])) {
            cerr << "Error reading data from file: " << filename << endl;
            file.close();
            exit(1);
        }
    }
    file.close();
    return data;
}

// Function to write sorted data to output file
void writeFile(const vector<int>& data, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening output file: " << filename << endl;
        exit(1);
    }
    file << data.size() << "\n";
    for (size_t i = 0; i < data.size(); i++) {
        file << data[i];
        if (i < data.size() - 1) file << " ";
    }
    file << "\n";
    file.close();
}

// Function to measure execution time
template<typename Func, typename... Args>
double measureTime(Func func, Args&&... args) {
    auto start = high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto stop = high_resolution_clock::now();
    return duration<double, milli>(stop - start).count();
}

int main(int argc, char* argv[]) {
    // Handle test mode: ./main.exe -r
    if (argc == 2 && string(argv[1]) == "-r") {
        // Define data orders, sizes, and algorithms
        const vector<string> dataOrders = {"sorted", "nearly_sorted", "reverse_sorted", "randomized"};
        const vector<int> dataTypes = {1, 3, 2, 0}; // Corresponds to DataGenerator.cpp
        const vector<int> sizes = {10000, 30000, 50000, 100000};
        const vector<string> algorithms = {
            "selection-sort", "insertion-sort", "bubble-sort", "shaker-sort",
            "shell-sort", "heap-sort", "merge-sort", "quick-sort",
            "counting-sort", "radix-sort", "flash-sort"
        };

        // Initialize CSV files for each data order (time and comparisons)
        vector<ofstream> timeFiles(4);
        vector<ofstream> compFiles(4);
        for (size_t i = 0; i < 4; ++i) {
            timeFiles[i].open(dataOrders[i] + "_time.csv");
            compFiles[i].open(dataOrders[i] + "_comp.csv");
            if (!timeFiles[i].is_open() || !compFiles[i].is_open()) {
                cerr << "Error opening CSV file for " << dataOrders[i] << endl;
                return 1;
            }
            // Write header row
            timeFiles[i] << "Size";
            compFiles[i] << "Size";
            for (const string& algo : algorithms) {
                timeFiles[i] << "," << algo;
                compFiles[i] << "," << algo;
            }
            timeFiles[i] << "\n";
            compFiles[i] << "\n";
        }

        cout << "Report Test Mode\n";
        cout << "Generating 8 CSV files for graphs...\n";

        // Iterate over data orders
        for (size_t i = 0; i < dataOrders.size(); ++i) {
            // For each size, collect data for all algorithms
            for (int size : sizes) {
                timeFiles[i] << size;
                compFiles[i] << size;
                for (const string& algo : algorithms) {
                    // Create array with DataGenerator
                    vector<int> arr(size);
                    GenerateData(arr.data(), size, dataTypes[i]);

                    // Sort and measure
                    long long comparisons = 0;
                    double time_taken = measureTime([&]() { applySort(arr, algo, comparisons); });

                    // Write to CSV (comma-separated)
                    timeFiles[i] << "," << time_taken;
                    compFiles[i] << "," << comparisons;

                    // Optional console output for progress
                    cout << "Data Order: " << dataOrders[i] 
                         << ", Size: " << size 
                         << ", Algorithm: " << algo 
                         << ", Time: " << time_taken << " ms"
                         << ", Comp: " << comparisons << "\n";
                }
                timeFiles[i] << "\n";
                compFiles[i] << "\n";
            }
        }

        // Close all files
        for (size_t i = 0; i < 4; ++i) {
            timeFiles[i].close();
            compFiles[i].close();
        }

        cout << "----------------\n";
        cout << "Generated CSV files: sorted_time.csv, sorted_comp.csv, nearly_sorted_time.csv, nearly_sorted_comp.csv, "
             << "reverse_sorted_time.csv, reverse_sorted_comp.csv, randomized_time.csv, randomized_comp.csv\n";

        return 0;
    }    

    // Expect command: ./main.exe -a algorithm -i input.txt -o output.txt
    if (argc != 7 || string(argv[1]) != "-a" || string(argv[3]) != "-i" || string(argv[5]) != "-o") {
        cerr << "Usage: " << argv[0] << " -a algorithm -i input_file -o output_file" << endl;
        return 1;
    }

    string algorithm = argv[2];
    string inputFile = argv[4];
    string outputFile = argv[6];

    // Read input data
    vector<int> arr = readInputFile(inputFile);

    // Apply sorting algorithm and measure time
    long long comparisons = 0;
    double time_taken = measureTime([&]() { applySort(arr, algorithm, comparisons); });

    // Print running time and comparisons
    cout << "Algorithm: " << algorithm << "\n";
    cout << "Running time: " << time_taken << " milliseconds\n";
    cout << "Comparisons: " << comparisons << "\n";

    // Write sorted data to output file
    writeFile(arr, outputFile);

    return 0;
}
