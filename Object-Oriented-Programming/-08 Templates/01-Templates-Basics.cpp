/*
==========================================
TEMPLATES IN C++
==========================================

THEORY:
--------
Templates allow writing generic code that works with different data types.
Types: Function Templates, Class Templates
Benefits: Code reusability, type safety, compile-time polymorphism
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ==========================================
// FUNCTION TEMPLATES
// ==========================================

template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T1, typename T2>
void display(T1 value1, T2 value2) {
    cout << "Value1: " << value1 << ", Value2: " << value2 << endl;
}

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
T minimum(T arr[], int size) {
    T min = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] < min) min = arr[i];
    }
    return min;
}

template<typename T>
void bubbleSort(T arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template<typename T>
void printArray(T arr[], int size) {
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ==========================================
// CLASS TEMPLATES
// ==========================================

template<typename T>
class Calculator {
private:
    T value1, value2;
    
public:
    Calculator(T v1, T v2) : value1(v1), value2(v2) {}
    
    T add() { return value1 + value2; }
    T subtract() { return value1 - value2; }
    T multiply() { return value1 * value2; }
    T divide() { 
        if(value2 != 0) return value1 / value2;
        cout << "Error: Division by zero!" << endl;
        return 0;
    }
    
    void display() {
        cout << "Values: " << value1 << ", " << value2 << endl;
    }
};

template<typename T>
class Stack {
private:
    vector<T> elements;
    int top;
    
public:
    Stack() : top(-1) {}
    
    void push(T element) {
        elements.push_back(element);
        top++;
        cout << "Pushed: " << element << endl;
    }
    
    T pop() {
        if(isEmpty()) {
            cout << "Stack is empty!" << endl;
            return T();
        }
        T element = elements[top];
        elements.pop_back();
        top--;
        cout << "Popped: " << element << endl;
        return element;
    }
    
    T peek() {
        if(isEmpty()) {
            cout << "Stack is empty!" << endl;
            return T();
        }
        return elements[top];
    }
    
    bool isEmpty() { return top == -1; }
    int size() { return top + 1; }
    
    void display() {
        cout << "Stack: ";
        for(int i = 0; i <= top; i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
    
public:
    Pair(T1 f, T2 s) : first(f), second(s) {}
    
    T1 getFirst() { return first; }
    T2 getSecond() { return second; }
    
    void display() {
        cout << "(" << first << ", " << second << ")" << endl;
    }
};

template<typename T>
class Array {
private:
    T* data;
    int size;
    
public:
    Array(int s) : size(s) {
        data = new T[size];
    }
    
    ~Array() { delete[] data; }
    
    T& operator[](int index) {
        if(index >= 0 && index < size) return data[index];
        cout << "Index out of bounds!" << endl;
        return data[0];
    }
    
    void display() {
        cout << "Array: ";
        for(int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
    int getSize() { return size; }
};

// ==========================================
// TEMPLATE SPECIALIZATION
// ==========================================

template<>
class Calculator<string> {
private:
    string value1, value2;
    
public:
    Calculator(string v1, string v2) : value1(v1), value2(v2) {}
    
    string add() { return value1 + value2; }
    string multiply() { 
        string result = "";
        for(char c : value2) result += value1;
        return result;
    }
    
    void display() {
        cout << "Strings: " << value1 << ", " << value2 << endl;
    }
};

// ==========================================
// NON-TYPE TEMPLATE PARAMETERS
// ==========================================

template<typename T, int size>
class FixedArray {
private:
    T data[size];
    
public:
    void setElement(int index, T value) {
        if(index >= 0 && index < size) data[index] = value;
    }
    
    T getElement(int index) {
        if(index >= 0 && index < size) return data[index];
        return T();
    }
    
    void display() {
        cout << "Fixed Array (" << size << "): ";
        for(int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// ==========================================
// DEMONSTRATION FUNCTIONS
// ==========================================

void demonstrateFunctionTemplates() {
    cout << "\n=== FUNCTION TEMPLATES ===" << endl;
    
    int a = 10, b = 20;
    cout << "Max of " << a << " and " << b << ": " << maximum(a, b) << endl;
    
    double x = 3.14, y = 2.71;
    cout << "Max of " << x << " and " << y << ": " << maximum(x, y) << endl;
    
    string s1 = "Hello", s2 = "World";
    cout << "Max of " << s1 << " and " << s2 << ": " << maximum(s1, s2) << endl;
    
    display(42, "Hello");
    display(3.14, true);
    
    int intArr[] = {5, 2, 8, 1, 9};
    cout << "Min in array: " << minimum(intArr, 5) << endl;
    
    cout << "Before sort: ";
    printArray(intArr, 5);
    bubbleSort(intArr, 5);
    cout << "After sort: ";
    printArray(intArr, 5);
}

void demonstrateClassTemplates() {
    cout << "\n=== CLASS TEMPLATES ===" << endl;
    
    Calculator<int> intCalc(10, 3);
    Calculator<double> doubleCalc(10.5, 2.5);
    Calculator<string> stringCalc("Hello", "World");
    
    cout << "Integer Calculator:" << endl;
    intCalc.display();
    cout << "Add: " << intCalc.add() << ", Multiply: " << intCalc.multiply() << endl;
    
    cout << "\nDouble Calculator:" << endl;
    doubleCalc.display();
    cout << "Add: " << doubleCalc.add() << ", Divide: " << doubleCalc.divide() << endl;
    
    cout << "\nString Calculator:" << endl;
    stringCalc.display();
    cout << "Add: " << stringCalc.add() << ", Multiply: " << stringCalc.multiply() << endl;
    
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    intStack.pop();
    intStack.display();
    
    Pair<int, string> pair1(1, "One");
    Pair<double, char> pair2(3.14, 'A');
    pair1.display();
    pair2.display();
    
    Array<int> intArray(5);
    for(int i = 0; i < 5; i++) {
        intArray[i] = i * 10;
    }
    intArray.display();
}

void demonstrateTemplateSpecialization() {
    cout << "\n=== TEMPLATE SPECIALIZATION ===" << endl;
    
    FixedArray<int, 5> intFixedArray;
    FixedArray<double, 3> doubleFixedArray;
    
    for(int i = 0; i < 5; i++) {
        intFixedArray.setElement(i, i * 2);
    }
    
    for(int i = 0; i < 3; i++) {
        doubleFixedArray.setElement(i, i * 1.5);
    }
    
    intFixedArray.display();
    doubleFixedArray.display();
}

// ==========================================
// PRACTICE QUESTIONS SOLUTIONS
// ==========================================

template<typename T>
class Vector {
private:
    T* data;
    int capacity;
    int size;
    
public:
    Vector() : data(nullptr), capacity(0), size(0) {}
    
    ~Vector() { delete[] data; }
    
    void push_back(T element) {
        if(size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for(int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = element;
    }
    
    T& operator[](int index) {
        if(index >= 0 && index < size) return data[index];
        cout << "Index out of bounds!" << endl;
        return data[0];
    }
    
    int getSize() { return size; }
    
    void display() {
        cout << "Vector: ";
        for(int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

template<typename T>
class Queue {
private:
    vector<T> elements;
    
public:
    void enqueue(T element) {
        elements.push_back(element);
        cout << "Enqueued: " << element << endl;
    }
    
    T dequeue() {
        if(isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        T element = elements.front();
        elements.erase(elements.begin());
        cout << "Dequeued: " << element << endl;
        return element;
    }
    
    bool isEmpty() { return elements.empty(); }
    int size() { return elements.size(); }
    
    void display() {
        cout << "Queue: ";
        for(auto element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }
};

void demonstrateSolutions() {
    cout << "\n=== SOLUTION 1: GENERIC VECTOR ===" << endl;
    Vector<int> intVector;
    for(int i = 0; i < 5; i++) {
        intVector.push_back(i * 10);
    }
    intVector.display();
    
    Vector<string> stringVector;
    stringVector.push_back("Hello");
    stringVector.push_back("World");
    stringVector.push_back("C++");
    stringVector.display();
    
    cout << "\n=== SOLUTION 2: GENERIC QUEUE ===" << endl;
    Queue<int> intQueue;
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);
    intQueue.display();
    intQueue.dequeue();
    intQueue.display();
}

// ==========================================
// DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
template<typename T>
T max(T a, T b) { return (a > b) ? a : b; }
int main() { cout << max(10, 20) << " " << max(3.14, 2.71); return 0; }
Answer: 20 3.14

Problem 2: What will be the output?
template<typename T>
class Box { T data; public: Box(T d) : data(d) {} T get() { return data; } };
int main() { Box<int> b(42); cout << b.get(); return 0; }
Answer: 42

Problem 3: What will be the output?
template<typename T>
T add(T a, T b) { return a + b; }
int main() { cout << add(5, 3) << " " << add(2.5, 3.5); return 0; }
Answer: 8 6
*/

// ==========================================
// PRACTICE QUESTIONS
// ==========================================

/*
1. Create a generic Vector class:
   - Implement push_back, operator[], getSize methods
   - Support dynamic resizing
   - Work with any data type

2. Implement a generic Queue class:
   - Include enqueue, dequeue, front, isEmpty methods
   - Use vector as underlying container
   - Support any data type

3. Create a generic Matrix class:
   - Support 2D matrix operations
   - Include setElement, getElement, display methods
   - Work with numeric types

4. Implement a generic LinkedList class:
   - Include insert, delete, search, display methods
   - Support any data type
   - Use template nodes

5. Create a generic BinaryTree class:
   - Include insert, search, display methods
   - Support any comparable data type
   - Implement inorder traversal
*/

int main() {
    cout << "TEMPLATES IN C++" << endl;
    cout << "================" << endl;
    
    demonstrateFunctionTemplates();
    demonstrateClassTemplates();
    demonstrateTemplateSpecialization();
    demonstrateSolutions();
    
    return 0;
} 