/*
FUNCTIONS PRACTICE QUESTIONS
============================

This file contains various practice problems using functions:
- GCD
- Prime number check
- Reduce function
- Sub total
- Concatenate
- Character frequency
- Character delete
- Character add
- Spiral pattern (using nested loops only)
- Diamond pattern
- Hour glass pattern with sleep
*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

// Function to calculate GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to reduce array by given factor
void reduceArray(int arr[], int size, int factor) {
    for (int i = 0; i < size; i++) {
        arr[i] /= factor;
    }
}

// Function to calculate subtotal
int subTotal(int arr[], int size, int start, int end) {
    int sum = 0;
    for (int i = start; i <= end && i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Function to concatenate two strings
string concatenate(string str1, string str2) {
    return str1 + str2;
}

// Function to count character frequency
int charFrequency(string str, char ch) {
    int count = 0;
    for (char c : str) {
        if (c == ch) {
            count++;
        }
    }
    return count;
}

// Function to delete character from string
string charDelete(string str, char ch) {
    string result = "";
    for (char c : str) {
        if (c != ch) {
            result += c;
        }
    }
    return result;
}

// Function to add character to string at specific position
string charAdd(string str, char ch, int position) {
    if (position < 0 || position > str.length()) {
        return str; // Invalid position
    }
    
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        if (i == position) {
            result += ch;
        }
        result += str[i];
    }
    
    if (position == str.length()) {
        result += ch;
    }
    
    return result;
}

// Function to print spiral pattern
void printSpiral(int size) {
    int arr[size][size];
    int num = 1;
    int top = 0, bottom = size - 1, left = 0, right = size - 1;
    
    while (top <= bottom && left <= right) {
        // Fill top row
        for (int i = left; i <= right; i++) {
            arr[top][i] = num++;
        }
        top++;
        
        // Fill right column
        for (int i = top; i <= bottom; i++) {
            arr[i][right] = num++;
        }
        right--;
        
        // Fill bottom row
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                arr[bottom][i] = num++;
            }
            bottom--;
        }
        
        // Fill left column
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                arr[i][left] = num++;
            }
            left++;
        }
    }
    
    // Print the spiral
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function to print diamond pattern
void printDiamond(int size) {
    // Upper half
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size - i; j++) {
            cout << " ";
        }
        for (int k = 1; k <= 2 * i - 1; k++) {
            cout << "*";
        }
        cout << endl;
    }
    
    // Lower half
    for (int i = size - 1; i >= 1; i--) {
        for (int j = 1; j <= size - i; j++) {
            cout << " ";
        }
        for (int k = 1; k <= 2 * i - 1; k++) {
            cout << "*";
        }
        cout << endl;
    }
}

// Function to print hourglass pattern with sleep
void printHourglassWithSleep(int size) {
    // Upper half
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            cout << " ";
        }
        for (int k = 0; k < 2 * (size - i) - 1; k++) {
            cout << "*";
        }
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    // Lower half
    for (int i = size - 2; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            cout << " ";
        }
        for (int k = 0; k < 2 * (size - i) - 1; k++) {
            cout << "*";
        }
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    cout << "FUNCTIONS PRACTICE QUESTIONS" << endl;
    cout << "============================" << endl;
    
    int choice;
    
    cout << "\nChoose a practice question (1-15): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. GCD
        cout << "\n=== 1. GCD (Greatest Common Divisor) ===" << endl;
        int a, b;
        cout << "Enter two numbers: ";
        cin >> a >> b;
        
        cout << "GCD of " << a << " and " << b << " is: " << gcd(a, b) << endl;
    }
    
    else if (choice == 2) {
        // 2. Prime Number Check
        cout << "\n=== 2. Prime Number Check ===" << endl;
        int num;
        cout << "Enter a number: ";
        cin >> num;
        
        if (isPrime(num)) {
            cout << num << " is a prime number." << endl;
        } else {
            cout << num << " is not a prime number." << endl;
        }
    }
    
    else if (choice == 3) {
        // 3. Reduce Array
        cout << "\n=== 3. Reduce Array ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int factor;
        cout << "Enter reduction factor: ";
        cin >> factor;
        
        cout << "Original array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        
        reduceArray(arr, size, factor);
        
        cout << "\nReduced array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    else if (choice == 4) {
        // 4. Sub Total
        cout << "\n=== 4. Sub Total ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int start, end;
        cout << "Enter start index: ";
        cin >> start;
        cout << "Enter end index: ";
        cin >> end;
        
        int subtotal = subTotal(arr, size, start, end);
        cout << "Subtotal from index " << start << " to " << end << ": " << subtotal << endl;
    }
    
    else if (choice == 5) {
        // 5. Concatenate Strings
        cout << "\n=== 5. Concatenate Strings ===" << endl;
        string str1, str2;
        cout << "Enter first string: ";
        cin.ignore();
        getline(cin, str1);
        cout << "Enter second string: ";
        getline(cin, str2);
        
        string result = concatenate(str1, str2);
        cout << "Concatenated string: " << result << endl;
    }
    
    else if (choice == 6) {
        // 6. Character Frequency
        cout << "\n=== 6. Character Frequency ===" << endl;
        string str;
        char ch;
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        cout << "Enter character to count: ";
        cin >> ch;
        
        int frequency = charFrequency(str, ch);
        cout << "Frequency of '" << ch << "' in the string: " << frequency << endl;
    }
    
    else if (choice == 7) {
        // 7. Character Delete
        cout << "\n=== 7. Character Delete ===" << endl;
        string str;
        char ch;
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        cout << "Enter character to delete: ";
        cin >> ch;
        
        string result = charDelete(str, ch);
        cout << "Original string: " << str << endl;
        cout << "String after deletion: " << result << endl;
    }
    
    else if (choice == 8) {
        // 8. Character Add
        cout << "\n=== 8. Character Add ===" << endl;
        string str;
        char ch;
        int position;
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        cout << "Enter character to add: ";
        cin >> ch;
        cout << "Enter position to add: ";
        cin >> position;
        
        string result = charAdd(str, ch, position);
        cout << "Original string: " << str << endl;
        cout << "String after addition: " << result << endl;
    }
    
    else if (choice == 9) {
        // 9. Spiral Pattern
        cout << "\n=== 9. Spiral Pattern ===" << endl;
        int size;
        cout << "Enter size of spiral (odd number recommended): ";
        cin >> size;
        
        printSpiral(size);
    }
    
    else if (choice == 10) {
        // 10. Diamond Pattern
        cout << "\n=== 10. Diamond Pattern ===" << endl;
        int size;
        cout << "Enter size of diamond: ";
        cin >> size;
        
        printDiamond(size);
    }
    
    else if (choice == 11) {
        // 11. Hourglass Pattern with Sleep
        cout << "\n=== 11. Hourglass Pattern with Sleep ===" << endl;
        int size;
        cout << "Enter size of hourglass: ";
        cin >> size;
        
        cout << "Creating hourglass pattern with 500ms delay..." << endl;
        printHourglassWithSleep(size);
    }
    
    else if (choice == 12) {
        // 12. Multiple GCD
        cout << "\n=== 12. Multiple GCD ===" << endl;
        int size;
        cout << "Enter number of elements: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " numbers: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int result = arr[0];
        for (int i = 1; i < size; i++) {
            result = gcd(result, arr[i]);
        }
        
        cout << "GCD of all numbers: " << result << endl;
    }
    
    else if (choice == 13) {
        // 13. Prime Numbers in Range
        cout << "\n=== 13. Prime Numbers in Range ===" << endl;
        int start, end;
        cout << "Enter start of range: ";
        cin >> start;
        cout << "Enter end of range: ";
        cin >> end;
        
        cout << "Prime numbers in range " << start << " to " << end << ": ";
        for (int i = start; i <= end; i++) {
            if (isPrime(i)) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    
    else if (choice == 14) {
        // 14. String Manipulation Functions
        cout << "\n=== 14. String Manipulation Functions ===" << endl;
        string str = "Hello World";
        cout << "Original string: " << str << endl;
        
        // Test all string functions
        cout << "Frequency of 'l': " << charFrequency(str, 'l') << endl;
        cout << "After deleting 'o': " << charDelete(str, 'o') << endl;
        cout << "After adding 'X' at position 5: " << charAdd(str, 'X', 5) << endl;
        cout << "Concatenated with '!!!': " << concatenate(str, "!!!") << endl;
    }
    
    else if (choice == 15) {
        // 15. Array Operations with Functions
        cout << "\n=== 15. Array Operations with Functions ===" << endl;
        int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        int size = 10;
        
        cout << "Original array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        cout << "Subtotal from index 2 to 6: " << subTotal(arr, size, 2, 6) << endl;
        
        reduceArray(arr, size, 2);
        cout << "Array after reducing by factor 2: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    else {
        cout << "Invalid choice! Please enter 1-15." << endl;
    }
    
    return 0;
}
