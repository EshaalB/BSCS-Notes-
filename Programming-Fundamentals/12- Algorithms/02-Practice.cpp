/*
ALGORITHMS PRACTICE QUESTIONS
=============================

This file contains various practice problems using algorithms:
- Sorting problems (custom sorting, frequency sort)
- Searching problems (multiple occurrences, closest element)
- Array manipulation (remove duplicates, find missing number)
- String algorithms (anagram check, palindrome)
- Mathematical algorithms (prime factorization, GCD/LCM)
- Pattern matching (substring search, pattern printing)
- Optimization problems (minimum operations, maximum profit)
- Data structure algorithms (stack operations, queue operations)
- Graph-like problems (adjacency matrix, path finding)
- Advanced algorithms (two pointers, sliding window)
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

// ========================================
// HELPER FUNCTIONS
// ========================================

// Function to print array
void printArray(int arr[], int n, string message = "") {
    if (!message.empty()) {
        cout << message << ": ";
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to check if number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to calculate GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// ========================================
// SORTING ALGORITHMS
// ========================================

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// 3. Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
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
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ========================================
// SEARCHING ALGORITHMS
// ========================================

// 1. Linear Search
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// 2. Binary Search
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// 3. Find all occurrences
vector<int> findAllOccurrences(int arr[], int n, int target) {
    vector<int> positions;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            positions.push_back(i);
        }
    }
    return positions;
}

// 4. Find closest element
int findClosest(int arr[], int n, int target) {
    int closest = arr[0];
    int minDiff = abs(arr[0] - target);
    
    for (int i = 1; i < n; i++) {
        int diff = abs(arr[i] - target);
        if (diff < minDiff) {
            minDiff = diff;
            closest = arr[i];
        }
    }
    return closest;
}

// ========================================
// ARRAY MANIPULATION ALGORITHMS
// ========================================

// 1. Remove duplicates
int removeDuplicates(int arr[], int n) {
    if (n == 0 || n == 1) return n;
    
    int j = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[n - 1];
    return j;
}

// 2. Find missing number in 1 to n
int findMissingNumber(int arr[], int n) {
    int expectedSum = (n + 1) * (n + 2) / 2;
    int actualSum = 0;
    
    for (int i = 0; i < n; i++) {
        actualSum += arr[i];
    }
    
    return expectedSum - actualSum;
}

// 3. Find first non-repeating element
int findFirstNonRepeating(int arr[], int n) {
    map<int, int> count;
    
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    
    for (int i = 0; i < n; i++) {
        if (count[arr[i]] == 1) {
            return arr[i];
        }
    }
    return -1;
}

// ========================================
// STRING ALGORITHMS
// ========================================

// 1. Check if strings are anagrams
bool areAnagrams(string str1, string str2) {
    if (str1.length() != str2.length()) return false;
    
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    
    return str1 == str2;
}

// 2. Check if string is palindrome
bool isPalindrome(string str) {
    int left = 0, right = str.length() - 1;
    
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// 3. Find longest palindrome substring
string longestPalindrome(string str) {
    int n = str.length();
    int maxLength = 1;
    int start = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            bool isPal = true;
            
            for (int k = 0; k < (j - i + 1) / 2; k++) {
                if (str[i + k] != str[j - k]) {
                    isPal = false;
                    break;
                }
            }
            
            if (isPal && (j - i + 1) > maxLength) {
                start = i;
                maxLength = j - i + 1;
            }
        }
    }
    
    return str.substr(start, maxLength);
}

// ========================================
// MATHEMATICAL ALGORITHMS
// ========================================

// 1. Prime factorization
vector<int> primeFactorization(int n) {
    vector<int> factors;
    
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    
    if (n > 1) {
        factors.push_back(n);
    }
    
    return factors;
}

// 2. Find all prime numbers up to n (Sieve of Eratosthenes)
vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;
    
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// ========================================
// PATTERN MATCHING ALGORITHMS
// ========================================

// 1. Substring search (naive)
int substringSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            return i;
        }
    }
    return -1;
}

// 2. Print pattern (pyramid)
void printPyramid(int n) {
    for (int i = 1; i <= n; i++) {
        // Print spaces
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // Print stars
        for (int j = 1; j <= 2 * i - 1; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

// ========================================
// OPTIMIZATION ALGORITHMS
// ========================================

// 1. Kadane's Algorithm (Maximum subarray sum)
int kadanesAlgorithm(int arr[], int n) {
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];
    
    for (int i = 1; i < n; i++) {
        maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    
    return maxSoFar;
}

// 2. Find minimum operations to make array equal
int minOperationsToEqual(int arr[], int n) {
    int minElement = arr[0];
    for (int i = 1; i < n; i++) {
        minElement = min(minElement, arr[i]);
    }
    
    int operations = 0;
    for (int i = 0; i < n; i++) {
        operations += arr[i] - minElement;
    }
    
    return operations;
}

// ========================================
// DATA STRUCTURE ALGORITHMS
// ========================================

// 1. Stack operations (using array)
class Stack {
private:
    int arr[100];
    int top;
    
public:
    Stack() {
        top = -1;
    }
    
    void push(int value) {
        if (top < 99) {
            arr[++top] = value;
        }
    }
    
    int pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return -1;
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    int peek() {
        if (top >= 0) {
            return arr[top];
        }
        return -1;
    }
};

// 2. Queue operations (using array)
class Queue {
private:
    int arr[100];
    int front, rear;
    
public:
    Queue() {
        front = rear = -1;
    }
    
    void enqueue(int value) {
        if (rear < 99) {
            if (front == -1) front = 0;
            arr[++rear] = value;
        }
    }
    
    int dequeue() {
        if (front != -1 && front <= rear) {
            return arr[front++];
        }
        return -1;
    }
    
    bool isEmpty() {
        return front == -1 || front > rear;
    }
    
    int peek() {
        if (front != -1 && front <= rear) {
            return arr[front];
        }
        return -1;
    }
};

// ========================================
// GRAPH-LIKE ALGORITHMS
// ========================================

// 1. Adjacency matrix operations
void createAdjacencyMatrix(int matrix[][10], int vertices) {
    cout << "Enter adjacency matrix (" << vertices << "x" << vertices << "):" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cin >> matrix[i][j];
        }
    }
}

void printAdjacencyMatrix(int matrix[][10], int vertices) {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// 2. Find degree of vertices
void findDegrees(int matrix[][10], int vertices) {
    cout << "Degrees of vertices:" << endl;
    for (int i = 0; i < vertices; i++) {
        int degree = 0;
        for (int j = 0; j < vertices; j++) {
            degree += matrix[i][j];
        }
        cout << "Vertex " << i << ": " << degree << endl;
    }
}

// ========================================
// ADVANCED ALGORITHMS
// ========================================

// 1. Two pointers technique
pair<int, int> findPairWithSum(int arr[], int n, int target) {
    sort(arr, arr + n);
    
    int left = 0, right = n - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            return make_pair(arr[left], arr[right]);
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return make_pair(-1, -1);
}

// 2. Sliding window technique
int maxSumSubarrayOfSizeK(int arr[], int n, int k) {
    if (k > n) return -1;
    
    int maxSum = 0;
    for (int i = 0; i < k; i++) {
        maxSum += arr[i];
    }
    
    int windowSum = maxSum;
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}

int main() {
    cout << "ALGORITHMS PRACTICE QUESTIONS" << endl;
    cout << "=============================" << endl;

    int choice;
    cout << "\nChoose a practice question (1-20): ";
    cin >> choice;

    if (choice == 1) {
        // 1. Custom Sorting (sort by frequency, then by value)
        cout << "\n=== 1. Custom Sorting (Frequency Sort) ===" << endl;
        
        int arr[] = {2, 3, 2, 4, 5, 12, 2, 3, 3, 3, 12};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        printArray(arr, n, "Original array");
        
        // Count frequencies
        map<int, int> freq;
        for (int i = 0; i < n; i++) {
            freq[arr[i]]++;
        }
        
        // Sort by frequency (descending), then by value (ascending)
        sort(arr, arr + n, [&freq](int a, int b) {
            if (freq[a] != freq[b]) {
                return freq[a] > freq[b];
            }
            return a < b;
        });
        
        printArray(arr, n, "Sorted by frequency");
    }
    
    else if (choice == 2) {
        // 2. Find all occurrences of an element
        cout << "\n=== 2. Find All Occurrences ===" << endl;
        
        int arr[] = {1, 2, 3, 2, 4, 2, 5, 2};
        int n = sizeof(arr) / sizeof(arr[0]);
        int target = 2;
        
        printArray(arr, n, "Array");
        cout << "Searching for: " << target << endl;
        
        vector<int> positions = findAllOccurrences(arr, n, target);
        
        if (positions.empty()) {
            cout << "Element not found" << endl;
        } else {
            cout << "Found at positions: ";
            for (int pos : positions) {
                cout << pos << " ";
            }
            cout << endl;
            cout << "Total occurrences: " << positions.size() << endl;
        }
    }
    
    else if (choice == 3) {
        // 3. Find closest element
        cout << "\n=== 3. Find Closest Element ===" << endl;
        
        int arr[] = {1, 3, 6, 7, 9, 12, 15, 18};
        int n = sizeof(arr) / sizeof(arr[0]);
        int target = 8;
        
        printArray(arr, n, "Sorted array");
        cout << "Target: " << target << endl;
        
        int closest = findClosest(arr, n, target);
        cout << "Closest element: " << closest << endl;
    }
    
    else if (choice == 4) {
        // 4. Remove duplicates from sorted array
        cout << "\n=== 4. Remove Duplicates ===" << endl;
        
        int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 5, 5};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        printArray(arr, n, "Original array");
        
        int newSize = removeDuplicates(arr, n);
        
        cout << "Array after removing duplicates: ";
        for (int i = 0; i < newSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "New size: " << newSize << endl;
    }
    
    else if (choice == 5) {
        // 5. Find missing number
        cout << "\n=== 5. Find Missing Number ===" << endl;
        
        int arr[] = {1, 2, 4, 6, 3, 7, 8};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        printArray(arr, n, "Array (missing one number from 1 to " << (n + 1) << ")");
        
        int missing = findMissingNumber(arr, n);
        cout << "Missing number: " << missing << endl;
    }
    
    else if (choice == 6) {
        // 6. Find first non-repeating element
        cout << "\n=== 6. First Non-Repeating Element ===" << endl;
        
        int arr[] = {9, 4, 9, 6, 7, 4};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        printArray(arr, n, "Array");
        
        int result = findFirstNonRepeating(arr, n);
        if (result != -1) {
            cout << "First non-repeating element: " << result << endl;
        } else {
            cout << "No non-repeating element found" << endl;
        }
    }
    
    else if (choice == 7) {
        // 7. Check if strings are anagrams
        cout << "\n=== 7. Anagram Check ===" << endl;
        
        string str1, str2;
        cout << "Enter first string: ";
        cin >> str1;
        cout << "Enter second string: ";
        cin >> str2;
        
        if (areAnagrams(str1, str2)) {
            cout << "The strings are anagrams" << endl;
        } else {
            cout << "The strings are not anagrams" << endl;
        }
    }
    
    else if (choice == 8) {
        // 8. Find longest palindrome substring
        cout << "\n=== 8. Longest Palindrome Substring ===" << endl;
        
        string str;
        cout << "Enter a string: ";
        cin >> str;
        
        string longest = longestPalindrome(str);
        cout << "Longest palindrome substring: " << longest << endl;
        cout << "Length: " << longest.length() << endl;
    }
    
    else if (choice == 9) {
        // 9. Prime factorization
        cout << "\n=== 9. Prime Factorization ===" << endl;
        
        int n;
        cout << "Enter a number: ";
        cin >> n;
        
        vector<int> factors = primeFactorization(n);
        
        cout << "Prime factors of " << n << ": ";
        for (int factor : factors) {
            cout << factor << " ";
        }
        cout << endl;
    }
    
    else if (choice == 10) {
        // 10. Sieve of Eratosthenes
        cout << "\n=== 10. Sieve of Eratosthenes ===" << endl;
        
        int n;
        cout << "Enter upper limit: ";
        cin >> n;
        
        vector<int> primes = sieveOfEratosthenes(n);
        
        cout << "Prime numbers up to " << n << ": ";
        for (int prime : primes) {
            cout << prime << " ";
        }
        cout << endl;
        cout << "Count: " << primes.size() << endl;
    }
    
    else if (choice == 11) {
        // 11. Substring search
        cout << "\n=== 11. Substring Search ===" << endl;
        
        string text, pattern;
        cout << "Enter text: ";
        cin >> text;
        cout << "Enter pattern: ";
        cin >> pattern;
        
        int position = substringSearch(text, pattern);
        
        if (position != -1) {
            cout << "Pattern found at position: " << position << endl;
        } else {
            cout << "Pattern not found" << endl;
        }
    }
    
    else if (choice == 12) {
        // 12. Print pyramid pattern
        cout << "\n=== 12. Pyramid Pattern ===" << endl;
        
        int n;
        cout << "Enter number of rows: ";
        cin >> n;
        
        printPyramid(n);
    }
    
    else if (choice == 13) {
        // 13. Kadane's Algorithm
        cout << "\n=== 13. Kadane's Algorithm ===" << endl;
        
        int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        printArray(arr, n, "Array");
        
        int maxSum = kadanesAlgorithm(arr, n);
        cout << "Maximum subarray sum: " << maxSum << endl;
    }
    
    else if (choice == 14) {
        // 14. Minimum operations to make array equal
        cout << "\n=== 14. Minimum Operations to Make Array Equal ===" << endl;
        
        int arr[] = {1, 2, 3, 4, 5};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        printArray(arr, n, "Array");
        
        int operations = minOperationsToEqual(arr, n);
        cout << "Minimum operations needed: " << operations << endl;
    }
    
    else if (choice == 15) {
        // 15. Stack operations
        cout << "\n=== 15. Stack Operations ===" << endl;
        
        Stack stack;
        
        stack.push(10);
        stack.push(20);
        stack.push(30);
        
        cout << "Stack operations:" << endl;
        cout << "Pushed: 10, 20, 30" << endl;
        cout << "Top element: " << stack.peek() << endl;
        cout << "Popped: " << stack.pop() << endl;
        cout << "New top: " << stack.peek() << endl;
        cout << "Is empty: " << (stack.isEmpty() ? "Yes" : "No") << endl;
    }
    
    else if (choice == 16) {
        // 16. Queue operations
        cout << "\n=== 16. Queue Operations ===" << endl;
        
        Queue queue;
        
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        
        cout << "Queue operations:" << endl;
        cout << "Enqueued: 10, 20, 30" << endl;
        cout << "Front element: " << queue.peek() << endl;
        cout << "Dequeued: " << queue.dequeue() << endl;
        cout << "New front: " << queue.peek() << endl;
        cout << "Is empty: " << (queue.isEmpty() ? "Yes" : "No") << endl;
    }
    
    else if (choice == 17) {
        // 17. Adjacency matrix operations
        cout << "\n=== 17. Adjacency Matrix Operations ===" << endl;
        
        int vertices;
        cout << "Enter number of vertices: ";
        cin >> vertices;
        
        int matrix[10][10];
        createAdjacencyMatrix(matrix, vertices);
        printAdjacencyMatrix(matrix, vertices);
        findDegrees(matrix, vertices);
    }
    
    else if (choice == 18) {
        // 18. Two pointers technique
        cout << "\n=== 18. Two Pointers Technique ===" << endl;
        
        int arr[] = {1, 4, 45, 6, 10, 8};
        int n = sizeof(arr) / sizeof(arr[0]);
        int target = 16;
        
        printArray(arr, n, "Array");
        cout << "Target sum: " << target << endl;
        
        pair<int, int> result = findPairWithSum(arr, n, target);
        
        if (result.first != -1) {
            cout << "Pair found: " << result.first << " + " << result.second << " = " << target << endl;
        } else {
            cout << "No pair found" << endl;
        }
    }
    
    else if (choice == 19) {
        // 19. Sliding window technique
        cout << "\n=== 19. Sliding Window Technique ===" << endl;
        
        int arr[] = {1, 4, 2, 10, 2, 3, 1, 0, 20};
        int n = sizeof(arr) / sizeof(arr[0]);
        int k = 4;
        
        printArray(arr, n, "Array");
        cout << "Window size: " << k << endl;
        
        int maxSum = maxSumSubarrayOfSizeK(arr, n, k);
        cout << "Maximum sum of subarray of size " << k << ": " << maxSum << endl;
    }
    
    else if (choice == 20) {
        // 20. Algorithm comparison
        cout << "\n=== 20. Algorithm Comparison ===" << endl;
        
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        int n = sizeof(arr) / sizeof(arr[0]);
        int temp[n];
        
        cout << "Original array: ";
        printArray(arr, n);
        
        // Compare different sorting algorithms
        cout << "\nSorting Algorithm Comparison:" << endl;
        
        // Bubble Sort
        copy(arr, arr + n, temp);
        bubbleSort(temp, n);
        cout << "Bubble Sort: ";
        printArray(temp, n);
        
        // Selection Sort
        copy(arr, arr + n, temp);
        selectionSort(temp, n);
        cout << "Selection Sort: ";
        printArray(temp, n);
        
        // Insertion Sort
        copy(arr, arr + n, temp);
        insertionSort(temp, n);
        cout << "Insertion Sort: ";
        printArray(temp, n);
        
        // Merge Sort
        copy(arr, arr + n, temp);
        mergeSort(temp, 0, n - 1);
        cout << "Merge Sort: ";
        printArray(temp, n);
    }
    
    else {
        cout << "Invalid choice! Please select 1-20." << endl;
    }

    return 0;
} 