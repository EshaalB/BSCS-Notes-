/*
Algorithms in C++ - Basic Concepts
==================================

Algorithms are step-by-step procedures for solving problems.
This file covers fundamental sorting and searching algorithms.

Key Concepts:
1. Sorting Algorithms (Bubble, Selection, Insertion, Merge)
2. Searching Algorithms (Linear, Binary)
3. Kadane's Algorithm (Maximum Subarray Sum)
4. Algorithm Analysis (Time Complexity)
*/

#include <iostream>
#include <algorithm>
using namespace std;

// ========================================
// 1. BUBBLE SORT
// ========================================
/*
Bubble Sort:
- Compare adjacent elements and swap if they are in wrong order
- After each pass, largest element "bubbles" to the end
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Stable: Yes
*/
void bubbleSort(int arr[], int n) {
    cout << "Bubble Sort Process:" << endl;
    
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // Print current state
        cout << "Pass " << (i + 1) << ": ";
        for (int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
        
        // If no swapping occurred, array is sorted
        if (!swapped) {
            cout << "Array is sorted! No more passes needed." << endl;
            break;
        }
    }
}

// ========================================
// 2. SELECTION SORT
// ========================================
/*
Selection Sort:
- Find minimum element and place it at beginning
- Repeat for remaining elements
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Stable: No
*/
void selectionSort(int arr[], int n) {
    cout << "Selection Sort Process:" << endl;
    
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        // Find minimum element in unsorted part
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap minimum element with first element
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
        
        // Print current state
        cout << "Pass " << (i + 1) << ": ";
        for (int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }
        cout << " (Swapped " << arr[i] << " to position " << i << ")" << endl;
    }
}

// ========================================
// 3. INSERTION SORT
// ========================================
/*
Insertion Sort:
- Build final array one element at a time
- Take element and insert it into sorted portion
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Stable: Yes
*/
void insertionSort(int arr[], int n) {
    cout << "Insertion Sort Process:" << endl;
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        
        // Print current state
        cout << "Pass " << i << ": ";
        for (int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }
        cout << " (Inserted " << key << ")" << endl;
    }
}

// ========================================
// 4. MERGE SORT
// ========================================
/*
Merge Sort:
- Divide array into two halves
- Recursively sort the two halves
- Merge the sorted halves
- Time Complexity: O(n log n)
- Space Complexity: O(n)
- Stable: Yes
*/

// Function to merge two subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int L[n1], R[n2];
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
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

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// ========================================
// 5. LINEAR SEARCH
// ========================================
/*
Linear Search:
- Check each element one by one
- Return index if found, -1 if not found
- Time Complexity: O(n)
- Space Complexity: O(1)
*/
int linearSearch(int arr[], int n, int target) {
    cout << "Linear Search for " << target << ":" << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "Checking position " << i << " (value: " << arr[i] << ")";
        
        if (arr[i] == target) {
            cout << " - Found!" << endl;
            return i;
        }
        cout << " - Not found" << endl;
    }
    
    cout << "Element not found in array" << endl;
    return -1;
}

// ========================================
// 6. BINARY SEARCH
// ========================================
/*
Binary Search:
- Works only on sorted arrays
- Compare target with middle element
- Eliminate half of remaining elements
- Time Complexity: O(log n)
- Space Complexity: O(1)
*/
int binarySearch(int arr[], int n, int target) {
    cout << "Binary Search for " << target << ":" << endl;
    
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        cout << "Checking range [" << left << ", " << right << "] ";
        cout << "middle = " << mid << " (value: " << arr[mid] << ")";
        
        if (arr[mid] == target) {
            cout << " - Found!" << endl;
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
            cout << " - Target is in right half" << endl;
        } else {
            right = mid - 1;
            cout << " - Target is in left half" << endl;
        }
    }
    
    cout << "Element not found in array" << endl;
    return -1;
}

// ========================================
// 7. KADANE'S ALGORITHM
// ========================================
/*
Kadane's Algorithm:
- Find maximum sum of contiguous subarray
- Keep track of current sum and maximum sum
- Time Complexity: O(n)
- Space Complexity: O(1)
*/
int kadanesAlgorithm(int arr[], int n) {
    cout << "Kadane's Algorithm - Finding maximum subarray sum:" << endl;
    
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];
    int start = 0, end = 0, tempStart = 0;
    
    cout << "Initial: maxSoFar = " << maxSoFar << ", maxEndingHere = " << maxEndingHere << endl;
    
    for (int i = 1; i < n; i++) {
        // Either extend previous subarray or start new one
        if (arr[i] > maxEndingHere + arr[i]) {
            maxEndingHere = arr[i];
            tempStart = i;
        } else {
            maxEndingHere = maxEndingHere + arr[i];
        }
        
        // Update maximum if current sum is greater
        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            start = tempStart;
            end = i;
        }
        
        cout << "i=" << i << ": arr[" << i << "]=" << arr[i] 
             << ", maxEndingHere=" << maxEndingHere 
             << ", maxSoFar=" << maxSoFar << endl;
    }
    
    cout << "Maximum subarray sum: " << maxSoFar << endl;
    cout << "Subarray: [";
    for (int i = start; i <= end; i++) {
        cout << arr[i];
        if (i < end) cout << ", ";
    }
    cout << "]" << endl;
    
    return maxSoFar;
}

// ========================================
// UTILITY FUNCTIONS
// ========================================

void printArray(int arr[], int n, string message = "") {
    if (!message.empty()) {
        cout << message << ": ";
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main() {
    cout << "=== ALGORITHMS BASICS ===\n\n";
    
    int original[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(original) / sizeof(original[0]);
    int arr[n];
    
    cout << "Original array: ";
    printArray(original, n);
    cout << endl;
    
    // ========================================
    // 1. BUBBLE SORT DEMONSTRATION
    // ========================================
    cout << "1. BUBBLE SORT" << endl;
    cout << "==============" << endl;
    copyArray(original, arr, n);
    bubbleSort(arr, n);
    printArray(arr, n, "Sorted array");
    cout << endl;
    
    // ========================================
    // 2. SELECTION SORT DEMONSTRATION
    // ========================================
    cout << "2. SELECTION SORT" << endl;
    cout << "=================" << endl;
    copyArray(original, arr, n);
    selectionSort(arr, n);
    printArray(arr, n, "Sorted array");
    cout << endl;
    
    // ========================================
    // 3. INSERTION SORT DEMONSTRATION
    // ========================================
    cout << "3. INSERTION SORT" << endl;
    cout << "=================" << endl;
    copyArray(original, arr, n);
    insertionSort(arr, n);
    printArray(arr, n, "Sorted array");
    cout << endl;
    
    // ========================================
    // 4. MERGE SORT DEMONSTRATION
    // ========================================
    cout << "4. MERGE SORT" << endl;
    cout << "=============" << endl;
    copyArray(original, arr, n);
    cout << "Merge Sort Process (recursive):" << endl;
    mergeSort(arr, 0, n - 1);
    printArray(arr, n, "Sorted array");
    cout << endl;
    
    // ========================================
    // 5. LINEAR SEARCH DEMONSTRATION
    // ========================================
    cout << "5. LINEAR SEARCH" << endl;
    cout << "================" << endl;
    int target = 22;
    int result = linearSearch(original, n, target);
    cout << "Result: Element " << target << " found at index " << result << endl;
    cout << endl;
    
    // ========================================
    // 6. BINARY SEARCH DEMONSTRATION
    // ========================================
    cout << "6. BINARY SEARCH" << endl;
    cout << "================" << endl;
    // First sort the array for binary search
    copyArray(original, arr, n);
    sort(arr, arr + n);  // Using STL sort for demonstration
    printArray(arr, n, "Sorted array for binary search");
    
    target = 25;
    result = binarySearch(arr, n, target);
    cout << "Result: Element " << target << " found at index " << result << endl;
    cout << endl;
    
    // ========================================
    // 7. KADANE'S ALGORITHM DEMONSTRATION
    // ========================================
    cout << "7. KADANE'S ALGORITHM" << endl;
    cout << "=====================" << endl;
    int kadaneArray[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int kadaneN = sizeof(kadaneArray) / sizeof(kadaneArray[0]);
    printArray(kadaneArray, kadaneN, "Array for Kadane's algorithm");
    int maxSum = kadanesAlgorithm(kadaneArray, kadaneN);
    cout << endl;
    
    // ========================================
    // ALGORITHM COMPARISON
    // ========================================
    cout << "ALGORITHM COMPARISON" << endl;
    cout << "===================" << endl;
    cout << "Sorting Algorithms:" << endl;
    cout << "- Bubble Sort:    O(n²) time, O(1) space, Stable" << endl;
    cout << "- Selection Sort: O(n²) time, O(1) space, Not Stable" << endl;
    cout << "- Insertion Sort: O(n²) time, O(1) space, Stable" << endl;
    cout << "- Merge Sort:     O(n log n) time, O(n) space, Stable" << endl;
    cout << endl;
    cout << "Searching Algorithms:" << endl;
    cout << "- Linear Search:  O(n) time, O(1) space" << endl;
    cout << "- Binary Search:  O(log n) time, O(1) space (requires sorted array)" << endl;
    cout << endl;
    cout << "Special Algorithms:" << endl;
    cout << "- Kadane's:       O(n) time, O(1) space (maximum subarray sum)" << endl;

    return 0;
}

/*
SUMMARY OF KEY CONCEPTS:
========================

1. Sorting Algorithms:
   - Bubble Sort: Simple but inefficient, good for small arrays
   - Selection Sort: Simple, performs well on small arrays
   - Insertion Sort: Efficient for small arrays, adaptive
   - Merge Sort: Efficient, stable, good for large arrays

2. Searching Algorithms:
   - Linear Search: Simple, works on any array
   - Binary Search: Fast, requires sorted array

3. Algorithm Analysis:
   - Time Complexity: How runtime grows with input size
   - Space Complexity: How memory usage grows with input size
   - Stable: Maintains relative order of equal elements

4. When to Use Each Algorithm:
   - Small arrays (< 50): Insertion Sort
   - Large arrays: Merge Sort
   - Unsorted search: Linear Search
   - Sorted search: Binary Search
   - Maximum subarray: Kadane's Algorithm

5. Key Principles:
   - Choose algorithm based on problem requirements
   - Consider time and space complexity
   - Understand algorithm behavior before implementation
*/ 