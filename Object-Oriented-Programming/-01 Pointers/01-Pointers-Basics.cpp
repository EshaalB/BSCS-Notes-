/*
POINTERS BASICS
===============

THEORY:
-------
A pointer is a variable that stores the memory address of another variable.
It allows us to indirectly access and manipulate data stored in memory.

Key Concepts:
1. Memory Address: Every variable is stored at a specific memory location
2. Pointer Declaration: data_type *pointer_name;
3. Address Operator (&): Gets the memory address of a variable
4. Dereference Operator (*): Accesses the value stored at the address

TYPES OF POINTERS:
-----------------
1. Null Pointer: Points to nothing (nullptr or NULL)
2. Void Pointer: Can point to any data type (void *)
3. Wild Pointer: Uninitialized pointer (dangerous)
4. Dangling Pointer: Points to deallocated memory
5. Smart Pointers: Modern C++ feature for automatic memory management

EDGE CASES & ERRORS:
-------------------
1. Dereferencing null pointer (segmentation fault)
2. Dereferencing uninitialized pointer (undefined behavior)
3. Memory leaks (not deallocating dynamic memory)
4. Buffer overflow (accessing beyond allocated memory)
5. Dangling pointers (accessing freed memory)
*/

#include <iostream>
using namespace std;

// Example 1: Basic Pointer Operations
void basicPointerExample() {
    cout << "=== BASIC POINTER EXAMPLE ===" << endl;
    
    int number = 42;
    int *ptr = &number;  // ptr stores address of number
    
    cout << "Value of number: " << number << endl;
    cout << "Address of number: " << &number << endl;
    cout << "Value of ptr: " << ptr << endl;
    cout << "Value pointed by ptr: " << *ptr << endl;
    
    // Modifying value through pointer
    *ptr = 100;
    cout << "After *ptr = 100, number = " << number << endl;
}

// Example 2: Different Types of Pointers
void pointerTypesExample() {
    cout << "\n=== POINTER TYPES EXAMPLE ===" << endl;
    
    // Null pointer
    int *nullPtr = nullptr;
    cout << "Null pointer: " << nullPtr << endl;
    
    // Void pointer
    int intValue = 10;
    double doubleValue = 3.14;
    void *voidPtr;
    
    voidPtr = &intValue;
    cout << "Void pointer to int: " << *(static_cast<int*>(voidPtr)) << endl;
    
    voidPtr = &doubleValue;
    cout << "Void pointer to double: " << *(static_cast<double*>(voidPtr)) << endl;
    
    // Array pointer
    int arr[] = {1, 2, 3, 4, 5};
    int *arrPtr = arr;  // Points to first element
    
    cout << "Array elements using pointer: ";
    for(int i = 0; i < 5; i++) {
        cout << *(arrPtr + i) << " ";
    }
    cout << endl;
}

// Example 3: Pointer Arithmetic
void pointerArithmeticExample() {
    cout << "\n=== POINTER ARITHMETIC EXAMPLE ===" << endl;
    
    int numbers[] = {10, 20, 30, 40, 50};
    int *ptr = numbers;
    
    cout << "Original array: ";
    for(int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "Using pointer arithmetic:" << endl;
    cout << "*ptr = " << *ptr << endl;           // 10
    cout << "*(ptr + 1) = " << *(ptr + 1) << endl; // 20
    cout << "*(ptr + 2) = " << *(ptr + 2) << endl; // 30
    
    ptr++;  // Move to next element
    cout << "After ptr++, *ptr = " << *ptr << endl; // 20
    
    ptr += 2;  // Move 2 elements forward
    cout << "After ptr += 2, *ptr = " << *ptr << endl; // 40
}

// Example 4: Dynamic Memory Allocation
void dynamicMemoryExample() {
    cout << "\n=== DYNAMIC MEMORY EXAMPLE ===" << endl;
    
    // Allocate single integer
    int *dynamicInt = new int;
    *dynamicInt = 25;
    cout << "Dynamically allocated int: " << *dynamicInt << endl;
    
    // Allocate array
    int *dynamicArray = new int[5];
    for(int i = 0; i < 5; i++) {
        dynamicArray[i] = (i + 1) * 10;
    }
    
    cout << "Dynamically allocated array: ";
    for(int i = 0; i < 5; i++) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;
    
    // Deallocate memory (IMPORTANT!)
    delete dynamicInt;
    delete[] dynamicArray;
    cout << "Memory deallocated successfully" << endl;
}

// DRY RUN PROBLEMS
void dryRunProblems() {
    cout << "\n=== DRY RUN PROBLEMS ===" << endl;
    
    // Problem 1: What will be the output?
    cout << "Problem 1:" << endl;
    int x = 5, y = 10;
    int *p1 = &x, *p2 = &y;
    *p1 = *p2;
    cout << "x = " << x << ", y = " << y << endl;  // x = 10, y = 10
    
    // Problem 2: What will be the output?
    cout << "\nProblem 2:" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr + 2;
    cout << "*ptr = " << *ptr << endl;        // 3
    cout << "*(ptr - 1) = " << *(ptr - 1) << endl;  // 2
    cout << "*(ptr + 1) = " << *(ptr + 1) << endl;  // 4
    
    // Problem 3: What will be the output?
    cout << "\nProblem 3:" << endl;
    int a = 15, b = 25;
    int *p = &a;
    int **pp = &p;
    cout << "**pp = " << **pp << endl;  // 15
    p = &b;
    cout << "**pp = " << **pp << endl;  // 25
}

// PRACTICE QUESTIONS
void practiceQuestions() {
    cout << "\n=== PRACTICE QUESTIONS ===" << endl;
    
    cout << "1. Write a function to swap two numbers using pointers" << endl;
    cout << "2. Write a function to reverse an array using pointers" << endl;
    cout << "3. Write a function to find the maximum element in an array using pointers" << endl;
    cout << "4. Write a function to count vowels in a string using pointers" << endl;
    cout << "5. Write a function to check if a number is palindrome using pointers" << endl;
}

// Solutions to Practice Questions
void swapNumbers(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverseArray(int *arr, int size) {
    int *start = arr;
    int *end = arr + size - 1;
    
    while(start < end) {
        swapNumbers(start, end);
        start++;
        end--;
    }
}

int findMax(int *arr, int size) {
    int max = *arr;
    for(int i = 1; i < size; i++) {
        if(*(arr + i) > max) {
            max = *(arr + i);
        }
    }
    return max;
}

int countVowels(const char *str) {
    int count = 0;
    while(*str != '\0') {
        char c = tolower(*str);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        str++;
    }
    return count;
}

bool isPalindrome(int *arr, int size) {
    int *start = arr;
    int *end = arr + size - 1;
    
    while(start < end) {
        if(*start != *end) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

void demonstrateSolutions() {
    cout << "\n=== SOLUTIONS DEMONSTRATION ===" << endl;
    
    // Solution 1: Swap numbers
    int num1 = 10, num2 = 20;
    cout << "Before swap: num1 = " << num1 << ", num2 = " << num2 << endl;
    swapNumbers(&num1, &num2);
    cout << "After swap: num1 = " << num1 << ", num2 = " << num2 << endl;
    
    // Solution 2: Reverse array
    int arr[] = {1, 2, 3, 4, 5};
    cout << "\nOriginal array: ";
    for(int i = 0; i < 5; i++) cout << arr[i] << " ";
    reverseArray(arr, 5);
    cout << "\nReversed array: ";
    for(int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;
    
    // Solution 3: Find maximum
    int numbers[] = {23, 45, 12, 67, 34};
    cout << "\nMaximum element: " << findMax(numbers, 5) << endl;
    
    // Solution 4: Count vowels
    char str[] = "Hello World";
    cout << "Vowels in '" << str << "': " << countVowels(str) << endl;
    
    // Solution 5: Check palindrome
    int palArr[] = {1, 2, 3, 2, 1};
    cout << "Array is palindrome: " << (isPalindrome(palArr, 5) ? "Yes" : "No") << endl;
}

int main() {
    basicPointerExample();
    pointerTypesExample();
    pointerArithmeticExample();
    dynamicMemoryExample();
    dryRunProblems();
    practiceQuestions();
    demonstrateSolutions();
    
    return 0;
}

/*
OUTPUT:
=======
=== BASIC POINTER EXAMPLE ===
Value of number: 42
Address of number: 0x7fff5fbff8ac
Value of ptr: 0x7fff5fbff8ac
Value pointed by ptr: 42
After *ptr = 100, number = 100

=== POINTER TYPES EXAMPLE ===
Null pointer: 0
Void pointer to int: 10
Void pointer to double: 3.14
Array elements using pointer: 1 2 3 4 5

=== POINTER ARITHMETIC EXAMPLE ===
Original array: 10 20 30 40 50
Using pointer arithmetic:
*ptr = 10
*(ptr + 1) = 20
*(ptr + 2) = 30
After ptr++, *ptr = 20
After ptr += 2, *ptr = 40

=== DYNAMIC MEMORY EXAMPLE ===
Dynamically allocated int: 25
Dynamically allocated array: 10 20 30 40 50
Memory deallocated successfully

=== DRY RUN PROBLEMS ===
Problem 1:
x = 10, y = 10

Problem 2:
*ptr = 3
*(ptr - 1) = 2
*(ptr + 1) = 4

Problem 3:
**pp = 15
**pp = 25

=== PRACTICE QUESTIONS ===
1. Write a function to swap two numbers using pointers
2. Write a function to reverse an array using pointers
3. Write a function to find the maximum element in an array using pointers
4. Write a function to count vowels in a string using pointers
5. Write a function to check if a number is palindrome using pointers

=== SOLUTIONS DEMONSTRATION ===
Before swap: num1 = 10, num2 = 20
After swap: num1 = 20, num2 = 10

Original array: 1 2 3 4 5
Reversed array: 5 4 3 2 1

Maximum element: 67
Vowels in 'Hello World': 3
Array is palindrome: Yes
*/ 