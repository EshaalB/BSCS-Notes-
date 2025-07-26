/*
Standard Template Library (STL) - Basics
========================================

STL is a powerful library in C++ that provides:
1. Containers (data structures)
2. Iterators (ways to traverse containers)
3. Algorithms (common operations on containers)

Key Components:
- Sequence Containers: vector, list, deque, array
- Associative Containers: set, map, multiset, multimap
- Unordered Containers: unordered_set, unordered_map
- Container Adapters: stack, queue, priority_queue
- Iterators: input, output, forward, bidirectional, random access
- Algorithms: sorting, searching, modifying, etc.
*/

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    cout << "=== STL BASICS ===\n\n";

    // ========================================
    // 1. SEQUENCE CONTAINERS
    // ========================================
    cout << "1. SEQUENCE CONTAINERS:\n";
    cout << "======================\n\n";

    // Vector (Dynamic Array)
    cout << "a) Vector (Dynamic Array):\n";
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "   Vector: ";
    for (int num : vec) cout << num << " ";
    cout << endl;
    cout << "   Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
    vec.push_back(6);
    cout << "   After push_back(6): ";
    for (int num : vec) cout << num << " ";
    cout << endl << endl;

    // List (Doubly Linked List)
    cout << "b) List (Doubly Linked List):\n";
    list<int> lst = {1, 2, 3, 4, 5};
    cout << "   List: ";
    for (int num : lst) cout << num << " ";
    cout << endl;
    lst.push_front(0);
    lst.push_back(6);
    cout << "   After push_front(0) and push_back(6): ";
    for (int num : lst) cout << num << " ";
    cout << endl << endl;

    // Deque (Double-ended Queue)
    cout << "c) Deque (Double-ended Queue):\n";
    deque<int> dq = {1, 2, 3, 4, 5};
    cout << "   Deque: ";
    for (int num : dq) cout << num << " ";
    cout << endl;
    dq.push_front(0);
    dq.push_back(6);
    cout << "   After push_front(0) and push_back(6): ";
    for (int num : dq) cout << num << " ";
    cout << endl << endl;

    // Array (Fixed-size Array)
    cout << "d) Array (Fixed-size Array):\n";
    array<int, 5> arr = {1, 2, 3, 4, 5};
    cout << "   Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    cout << "   Size: " << arr.size() << endl;
    cout << "   First element: " << arr.front() << endl;
    cout << "   Last element: " << arr.back() << endl << endl;

    // ========================================
    // 2. ASSOCIATIVE CONTAINERS
    // ========================================
    cout << "2. ASSOCIATIVE CONTAINERS:\n";
    cout << "==========================\n\n";

    // Set (Unique elements, sorted)
    cout << "a) Set (Unique elements, sorted):\n";
    set<int> st = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "   Set: ";
    for (int num : st) cout << num << " ";
    cout << endl;
    st.insert(7);
    cout << "   After insert(7): ";
    for (int num : st) cout << num << " ";
    cout << endl << endl;

    // Multiset (Multiple elements allowed, sorted)
    cout << "b) Multiset (Multiple elements allowed, sorted):\n";
    multiset<int> mst = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "   Multiset: ";
    for (int num : mst) cout << num << " ";
    cout << endl;
    mst.insert(1);
    cout << "   After insert(1): ";
    for (int num : mst) cout << num << " ";
    cout << endl << endl;

    // Map (Key-value pairs, sorted by key)
    cout << "c) Map (Key-value pairs, sorted by key):\n";
    map<string, int> mp;
    mp["apple"] = 5;
    mp["banana"] = 3;
    mp["cherry"] = 8;
    cout << "   Map:" << endl;
    for (const auto& pair : mp) {
        cout << "     " << pair.first << ": " << pair.second << endl;
    }
    cout << endl;

    // Multimap (Multiple values per key, sorted)
    cout << "d) Multimap (Multiple values per key, sorted):\n";
    multimap<string, int> mmp;
    mmp.insert({"apple", 5});
    mmp.insert({"apple", 3});
    mmp.insert({"banana", 2});
    cout << "   Multimap:" << endl;
    for (const auto& pair : mmp) {
        cout << "     " << pair.first << ": " << pair.second << endl;
    }
    cout << endl;

    // ========================================
    // 3. UNORDERED CONTAINERS
    // ========================================
    cout << "3. UNORDERED CONTAINERS:\n";
    cout << "========================\n\n";

    // Unordered Set
    cout << "a) Unordered Set:\n";
    unordered_set<int> ust = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "   Unordered Set: ";
    for (int num : ust) cout << num << " ";
    cout << endl << endl;

    // Unordered Map
    cout << "b) Unordered Map:\n";
    unordered_map<string, int> ump;
    ump["apple"] = 5;
    ump["banana"] = 3;
    ump["cherry"] = 8;
    cout << "   Unordered Map:" << endl;
    for (const auto& pair : ump) {
        cout << "     " << pair.first << ": " << pair.second << endl;
    }
    cout << endl;

    // ========================================
    // 4. CONTAINER ADAPTERS
    // ========================================
    cout << "4. CONTAINER ADAPTERS:\n";
    cout << "======================\n\n";

    // Stack (LIFO)
    cout << "a) Stack (LIFO - Last In, First Out):\n";
    stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    cout << "   Stack operations:" << endl;
    cout << "     Push: 1, 2, 3" << endl;
    cout << "     Top: " << stk.top() << endl;
    stk.pop();
    cout << "     After pop, Top: " << stk.top() << endl;
    cout << "     Size: " << stk.size() << endl << endl;

    // Queue (FIFO)
    cout << "b) Queue (FIFO - First In, First Out):\n";
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "   Queue operations:" << endl;
    cout << "     Push: 1, 2, 3" << endl;
    cout << "     Front: " << q.front() << endl;
    cout << "     Back: " << q.back() << endl;
    q.pop();
    cout << "     After pop, Front: " << q.front() << endl << endl;

    // Priority Queue (Heap)
    cout << "c) Priority Queue (Max Heap by default):\n";
    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(2);
    cout << "   Priority Queue operations:" << endl;
    cout << "     Push: 3, 1, 4, 2" << endl;
    cout << "     Top (max): " << pq.top() << endl;
    pq.pop();
    cout << "     After pop, Top: " << pq.top() << endl << endl;

    // ========================================
    // 5. ITERATORS
    // ========================================
    cout << "5. ITERATORS:\n";
    cout << "=============\n\n";

    vector<int> iterVec = {10, 20, 30, 40, 50};
    
    // Different types of iterators
    cout << "Vector: ";
    for (int num : iterVec) cout << num << " ";
    cout << endl;

    // Forward iteration
    cout << "   Forward iteration: ";
    for (auto it = iterVec.begin(); it != iterVec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Reverse iteration
    cout << "   Reverse iteration: ";
    for (auto it = iterVec.rbegin(); it != iterVec.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Const iteration
    cout << "   Const iteration: ";
    for (auto it = iterVec.cbegin(); it != iterVec.cend(); ++it) {
        cout << *it << " ";
    }
    cout << endl << endl;

    // ========================================
    // 6. ALGORITHMS
    // ========================================
    cout << "6. ALGORITHMS:\n";
    cout << "==============\n\n";

    vector<int> algoVec = {64, 34, 25, 12, 22, 11, 90};
    cout << "Original vector: ";
    for (int num : algoVec) cout << num << " ";
    cout << endl;

    // Sorting
    sort(algoVec.begin(), algoVec.end());
    cout << "After sort: ";
    for (int num : algoVec) cout << num << " ";
    cout << endl;

    // Reverse
    reverse(algoVec.begin(), algoVec.end());
    cout << "After reverse: ";
    for (int num : algoVec) cout << num << " ";
    cout << endl;

    // Find
    auto findIt = find(algoVec.begin(), algoVec.end(), 25);
    if (findIt != algoVec.end()) {
        cout << "Found 25 at position: " << (findIt - algoVec.begin()) << endl;
    }

    // Count
    int count25 = count(algoVec.begin(), algoVec.end(), 25);
    cout << "Count of 25: " << count25 << endl;

    // Max and Min
    auto maxIt = max_element(algoVec.begin(), algoVec.end());
    auto minIt = min_element(algoVec.begin(), algoVec.end());
    cout << "Max element: " << *maxIt << endl;
    cout << "Min element: " << *minIt << endl;

    // Binary search (requires sorted container)
    sort(algoVec.begin(), algoVec.end());
    bool found = binary_search(algoVec.begin(), algoVec.end(), 25);
    cout << "Binary search for 25: " << (found ? "Found" : "Not found") << endl;

    // Transform
    vector<int> transformVec = {1, 2, 3, 4, 5};
    vector<int> result(transformVec.size());
    transform(transformVec.begin(), transformVec.end(), result.begin(), 
             [](int x) { return x * 2; });
    cout << "Transform (multiply by 2): ";
    for (int num : result) cout << num << " ";
    cout << endl << endl;

    // ========================================
    // 7. PRACTICAL EXAMPLES
    // ========================================
    cout << "7. PRACTICAL EXAMPLES:\n";
    cout << "======================\n\n";

    // Example 1: Student grades with map
    cout << "Example 1: Student Grades:\n";
    map<string, vector<int>> studentGrades;
    studentGrades["Alice"] = {85, 92, 78};
    studentGrades["Bob"] = {90, 88, 95};
    studentGrades["Charlie"] = {75, 82, 88};

    for (const auto& student : studentGrades) {
        cout << "   " << student.first << ": ";
        for (int grade : student.second) {
            cout << grade << " ";
        }
        double avg = 0;
        for (int grade : student.second) avg += grade;
        avg /= student.second.size();
        cout << "(Avg: " << avg << ")" << endl;
    }
    cout << endl;

    // Example 2: Word frequency counter
    cout << "Example 2: Word Frequency Counter:\n";
    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    map<string, int> wordCount;
    
    for (const string& word : words) {
        wordCount[word]++;
    }
    
    for (const auto& pair : wordCount) {
        cout << "   " << pair.first << ": " << pair.second << " times" << endl;
    }
    cout << endl;

    // Example 3: Priority queue for task scheduling
    cout << "Example 3: Task Scheduling (Priority Queue):\n";
    priority_queue<pair<int, string>> tasks;
    tasks.push({3, "Low priority task"});
    tasks.push({1, "High priority task"});
    tasks.push({2, "Medium priority task"});

    cout << "   Processing tasks in priority order:" << endl;
    while (!tasks.empty()) {
        cout << "     Priority " << tasks.top().first << ": " << tasks.top().second << endl;
        tasks.pop();
    }

    return 0;
}

/*
SUMMARY OF STL COMPONENTS:
==========================

1. SEQUENCE CONTAINERS:
   - vector: Dynamic array, random access, fast insertion/deletion at end
   - list: Doubly linked list, fast insertion/deletion anywhere
   - deque: Double-ended queue, fast insertion/deletion at both ends
   - array: Fixed-size array, compile-time size

2. ASSOCIATIVE CONTAINERS:
   - set: Unique elements, sorted, logarithmic operations
   - multiset: Multiple elements allowed, sorted, logarithmic operations
   - map: Key-value pairs, sorted by key, logarithmic operations
   - multimap: Multiple values per key, sorted by key, logarithmic operations

3. UNORDERED CONTAINERS:
   - unordered_set: Unique elements, hash-based, average O(1) operations
   - unordered_map: Key-value pairs, hash-based, average O(1) operations

4. CONTAINER ADAPTERS:
   - stack: LIFO (Last In, First Out)
   - queue: FIFO (First In, First Out)
   - priority_queue: Priority-based (heap)

5. ITERATORS:
   - begin()/end(): Forward iteration
   - rbegin()/rend(): Reverse iteration
   - cbegin()/cend(): Const iteration

6. COMMON ALGORITHMS:
   - sort(): Sort elements
   - find(): Find element
   - count(): Count occurrences
   - reverse(): Reverse order
   - transform(): Apply function to elements
   - binary_search(): Search in sorted container
   - max_element()/min_element(): Find max/min

7. BEST PRACTICES:
   - Choose container based on usage patterns
   - Use const iterators when possible
   - Reserve capacity for vectors when size is known
   - Use algorithms instead of manual loops
   - Consider performance characteristics
*/ 