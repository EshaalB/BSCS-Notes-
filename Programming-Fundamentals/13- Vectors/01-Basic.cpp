/*
Vectors in C++ - Basic Concepts
===============================

Vectors are dynamic arrays that can grow and shrink in size.
They are part of the Standard Template Library (STL) in C++.

Key Concepts:
1. Vector Declaration and Initialization
2. Adding and Removing Elements
3. Accessing Elements
4. Vector Size and Capacity
5. Iterating Through Vectors
6. Vector Operations and Methods
7. 2D Vectors (Vector of Vectors)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    cout << "=== VECTORS BASICS ===\n\n";

    // ========================================
    // 1. VECTOR DECLARATION AND INITIALIZATION
    // ========================================
    cout << "1. Vector Declaration and Initialization:\n";
    
    // Empty vector
    vector<int> vec1;
    cout << "   Empty vector created\n";
    
    // Vector with initial size
    vector<int> vec2(5);  // 5 elements, all initialized to 0
    cout << "   Vector with size 5: ";
    for (int i = 0; i < vec2.size(); i++) {
        cout << vec2[i] << " ";
    }
    cout << endl;
    
    // Vector with initial size and value
    vector<int> vec3(4, 10);  // 4 elements, all initialized to 10
    cout << "   Vector with size 4, value 10: ";
    for (int i = 0; i < vec3.size(); i++) {
        cout << vec3[i] << " ";
    }
    cout << endl;
    
    // Vector initialized with values
    vector<int> vec4 = {1, 2, 3, 4, 5};
    cout << "   Vector with initial values: ";
    for (int i = 0; i < vec4.size(); i++) {
        cout << vec4[i] << " ";
    }
    cout << endl;
    
    // Vector from another vector
    vector<int> vec5(vec4.begin(), vec4.end());
    cout << "   Vector copied from another: ";
    for (int i = 0; i < vec5.size(); i++) {
        cout << vec5[i] << " ";
    }
    cout << endl;
    
    cout << endl;

    // ========================================
    // 2. ADDING AND REMOVING ELEMENTS
    // ========================================
    cout << "2. Adding and Removing Elements:\n";
    
    vector<int> numbers;
    
    // Adding elements at the end
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    cout << "   After push_back: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Adding element at specific position
    numbers.insert(numbers.begin() + 1, 15);  // Insert 15 at index 1
    cout << "   After insert at index 1: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Removing last element
    numbers.pop_back();
    cout << "   After pop_back: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Removing element at specific position
    numbers.erase(numbers.begin() + 1);  // Remove element at index 1
    cout << "   After erase at index 1: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << endl;

    // ========================================
    // 3. ACCESSING ELEMENTS
    // ========================================
    cout << "3. Accessing Elements:\n";
    
    vector<int> data = {100, 200, 300, 400, 500};
    
    // Using index operator []
    cout << "   First element (data[0]): " << data[0] << endl;
    cout << "   Last element (data[4]): " << data[4] << endl;
    
    // Using at() method (with bounds checking)
    cout << "   Element at index 2 (data.at(2)): " << data.at(2) << endl;
    
    // Using front() and back() methods
    cout << "   First element (data.front()): " << data.front() << endl;
    cout << "   Last element (data.back()): " << data.back() << endl;
    
    // Safe access with bounds checking
    try {
        cout << "   Trying to access data.at(10): ";
        cout << data.at(10) << endl;
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << endl;

    // ========================================
    // 4. VECTOR SIZE AND CAPACITY
    // ========================================
    cout << "4. Vector Size and Capacity:\n";
    
    vector<int> capacityDemo;
    
    cout << "   Initial size: " << capacityDemo.size() << endl;
    cout << "   Initial capacity: " << capacityDemo.capacity() << endl;
    
    // Add elements and observe capacity changes
    for (int i = 1; i <= 10; i++) {
        capacityDemo.push_back(i);
        cout << "   After adding " << i << ": size=" << capacityDemo.size() 
             << ", capacity=" << capacityDemo.capacity() << endl;
    }
    
    // Check if vector is empty
    cout << "   Is vector empty? " << (capacityDemo.empty() ? "Yes" : "No") << endl;
    
    // Reserve capacity
    vector<int> reserved;
    reserved.reserve(20);
    cout << "   After reserve(20): size=" << reserved.size() 
         << ", capacity=" << reserved.capacity() << endl;
    
    cout << endl;

    // ========================================
    // 5. ITERATING THROUGH VECTORS
    // ========================================
    cout << "5. Iterating Through Vectors:\n";
    
    vector<int> iterate = {1, 2, 3, 4, 5};
    
    // Method 1: Using index
    cout << "   Method 1 (index): ";
    for (int i = 0; i < iterate.size(); i++) {
        cout << iterate[i] << " ";
    }
    cout << endl;
    
    // Method 2: Using range-based for loop
    cout << "   Method 2 (range-based): ";
    for (int num : iterate) {
        cout << num << " ";
    }
    cout << endl;
    
    // Method 3: Using iterators
    cout << "   Method 3 (iterators): ";
    for (vector<int>::iterator it = iterate.begin(); it != iterate.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Method 4: Using auto keyword
    cout << "   Method 4 (auto): ";
    for (auto it = iterate.begin(); it != iterate.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Method 5: Reverse iteration
    cout << "   Method 5 (reverse): ";
    for (auto it = iterate.rbegin(); it != iterate.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << endl;

    // ========================================
    // 6. VECTOR OPERATIONS AND METHODS
    // ========================================
    cout << "6. Vector Operations and Methods:\n";
    
    vector<int> vecA = {1, 2, 3};
    vector<int> vecB = {4, 5, 6};
    
    cout << "   Vector A: ";
    for (int num : vecA) cout << num << " ";
    cout << endl;
    
    cout << "   Vector B: ";
    for (int num : vecB) cout << num << " ";
    cout << endl;
    
    // Assignment
    vecA = vecB;
    cout << "   After A = B: ";
    for (int num : vecA) cout << num << " ";
    cout << endl;
    
    // Comparison
    vector<int> vecC = {4, 5, 6};
    cout << "   A == C? " << (vecA == vecC ? "Yes" : "No") << endl;
    cout << "   A < C? " << (vecA < vecC ? "Yes" : "No") << endl;
    
    // Resize
    vecA.resize(5, 100);  // Resize to 5, fill new elements with 100
    cout << "   After resize(5, 100): ";
    for (int num : vecA) cout << num << " ";
    cout << endl;
    
    // Clear
    vecA.clear();
    cout << "   After clear: size=" << vecA.size() << endl;
    
    // Swap
    vector<int> vecX = {1, 2, 3};
    vector<int> vecY = {4, 5, 6};
    cout << "   Before swap - X: ";
    for (int num : vecX) cout << num << " ";
    cout << ", Y: ";
    for (int num : vecY) cout << num << " ";
    cout << endl;
    
    vecX.swap(vecY);
    cout << "   After swap - X: ";
    for (int num : vecX) cout << num << " ";
    cout << ", Y: ";
    for (int num : vecY) cout << num << " ";
    cout << endl;
    
    cout << endl;

    // ========================================
    // 7. 2D VECTORS (VECTOR OF VECTORS)
    // ========================================
    cout << "7. 2D Vectors (Vector of Vectors):\n";
    
    // Method 1: Initialize with size
    vector<vector<int>> matrix1(3, vector<int>(4, 0));  // 3x4 matrix filled with 0
    cout << "   3x4 matrix filled with 0:" << endl;
    for (int i = 0; i < matrix1.size(); i++) {
        cout << "   ";
        for (int j = 0; j < matrix1[i].size(); j++) {
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }
    
    // Method 2: Initialize with values
    vector<vector<int>> matrix2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "   3x3 matrix with values:" << endl;
    for (int i = 0; i < matrix2.size(); i++) {
        cout << "   ";
        for (int j = 0; j < matrix2[i].size(); j++) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }
    
    // Method 3: Dynamic 2D vector
    vector<vector<int>> matrix3;
    for (int i = 0; i < 3; i++) {
        vector<int> row;
        for (int j = 0; j < 3; j++) {
            row.push_back(i * 3 + j + 1);
        }
        matrix3.push_back(row);
    }
    cout << "   Dynamic 3x3 matrix:" << endl;
    for (int i = 0; i < matrix3.size(); i++) {
        cout << "   ";
        for (int j = 0; j < matrix3[i].size(); j++) {
            cout << matrix3[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl;

    // ========================================
    // 8. PRACTICAL EXAMPLES
    // ========================================
    cout << "8. Practical Examples:\n";
    
    // Example 1: Finding maximum and minimum
    vector<int> scores = {85, 92, 78, 96, 88, 91};
    cout << "   Scores: ";
    for (int score : scores) cout << score << " ";
    cout << endl;
    
    auto maxScore = max_element(scores.begin(), scores.end());
    auto minScore = min_element(scores.begin(), scores.end());
    cout << "   Maximum score: " << *maxScore << endl;
    cout << "   Minimum score: " << *minScore << endl;
    
    // Example 2: Sorting
    vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    cout << "   Unsorted: ";
    for (int num : unsorted) cout << num << " ";
    cout << endl;
    
    sort(unsorted.begin(), unsorted.end());
    cout << "   Sorted: ";
    for (int num : unsorted) cout << num << " ";
    cout << endl;
    
    // Example 3: Finding element
    vector<string> names = {"Alice", "Bob", "Charlie", "David", "Eve"};
    cout << "   Names: ";
    for (string name : names) cout << name << " ";
    cout << endl;
    
    auto it = find(names.begin(), names.end(), "Charlie");
    if (it != names.end()) {
        cout << "   Found 'Charlie' at position: " << (it - names.begin()) << endl;
    } else {
        cout << "   'Charlie' not found" << endl;
    }
    
    // Example 4: Counting elements
    vector<int> numbers2 = {1, 2, 2, 3, 2, 4, 2, 5};
    cout << "   Numbers: ";
    for (int num : numbers2) cout << num << " ";
    cout << endl;
    
    int count2 = count(numbers2.begin(), numbers2.end(), 2);
    cout << "   Count of 2: " << count2 << endl;

    return 0;
}

/*
SUMMARY OF KEY CONCEPTS:
========================

1. Vector Declaration:
   - vector<type> name;                    // Empty vector
   - vector<type> name(size);              // Vector with size
   - vector<type> name(size, value);       // Vector with size and value
   - vector<type> name = {val1, val2, ...}; // Vector with initial values

2. Adding Elements:
   - push_back(value)                      // Add at end
   - insert(position, value)               // Add at specific position
   - emplace_back(value)                   // Add at end (more efficient)

3. Removing Elements:
   - pop_back()                            // Remove from end
   - erase(position)                       // Remove at specific position
   - clear()                               // Remove all elements

4. Accessing Elements:
   - vector[index]                         // Direct access
   - vector.at(index)                      // Safe access with bounds checking
   - vector.front()                        // First element
   - vector.back()                         // Last element

5. Size and Capacity:
   - size()                                // Number of elements
   - capacity()                            // Total allocated space
   - empty()                               // Check if empty
   - reserve(size)                         // Reserve capacity

6. Iteration Methods:
   - Index-based loop                      // for (int i = 0; i < vec.size(); i++)
   - Range-based loop                      // for (int num : vec)
   - Iterator-based loop                   // for (auto it = vec.begin(); it != vec.end(); ++it)

7. Common Operations:
   - Assignment (=)                        // Copy vector
   - Comparison (==, !=, <, >, <=, >=)     // Compare vectors
   - Swap                                  // Exchange contents
   - Resize                                // Change size

8. 2D Vectors:
   - vector<vector<type>> name;            // Declaration
   - Access: name[row][column]             // Access element
   - Dynamic sizing                        // Each row can have different size

9. STL Algorithms:
   - sort(vec.begin(), vec.end())          // Sort vector
   - find(vec.begin(), vec.end(), value)   // Find element
   - count(vec.begin(), vec.end(), value)  // Count occurrences
   - max_element(vec.begin(), vec.end())   // Find maximum
   - min_element(vec.begin(), vec.end())   // Find minimum

10. Best Practices:
    - Use reserve() when you know the size
    - Use at() for bounds checking in debug
    - Use range-based for loops when possible
    - Consider using emplace_back() instead of push_back()
    - Use clear() to free memory when done
*/ 