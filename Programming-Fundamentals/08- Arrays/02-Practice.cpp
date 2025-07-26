/*
ARRAYS PRACTICE QUESTIONS
=========================

This file contains various practice problems using arrays:
- Perfect number
- Max element of array
- Reverse array
- Mean, mode, median
- Equilibrium index
- Copy array
- Even/odd array
- Palindrome array
- Merge array
- Delete array
- Insert array
- Remove duplicates
- Rotate array (different cases)
- Check palindrome in char array
- Largest word
- Length of string
- Longest palindrome
- String compression
- Saddle points of 2D array
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// Function to check if a number is perfect
bool isPerfect(int n) {
    if (n <= 1) return false;
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    return sum == n;
}

// Function to find maximum element
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to reverse array
void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        swap(arr[i], arr[size - 1 - i]);
    }
}

// Function to calculate mean
double calculateMean(int arr[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

// Function to calculate median
double calculateMedian(int arr[], int size) {
    // Create a copy to sort
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    sort(temp, temp + size);
    
    if (size % 2 == 0) {
        return (temp[size/2 - 1] + temp[size/2]) / 2.0;
    } else {
        return temp[size/2];
    }
}

// Function to calculate mode
int calculateMode(int arr[], int size) {
    int maxCount = 0, mode = arr[0];
    
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mode = arr[i];
        }
    }
    return mode;
}

// Function to find equilibrium index
int findEquilibriumIndex(int arr[], int size) {
    int totalSum = 0;
    for (int i = 0; i < size; i++) {
        totalSum += arr[i];
    }
    
    int leftSum = 0;
    for (int i = 0; i < size; i++) {
        totalSum -= arr[i];
        if (leftSum == totalSum) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}

// Function to check if array is palindrome
bool isPalindromeArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        if (arr[i] != arr[size - 1 - i]) {
            return false;
        }
    }
    return true;
}

// Function to remove duplicates
int removeDuplicates(int arr[], int size) {
    if (size <= 1) return size;
    
    int j = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

// Function to rotate array left
void rotateLeft(int arr[], int size, int positions) {
    positions = positions % size;
    for (int i = 0; i < positions; i++) {
        int temp = arr[0];
        for (int j = 0; j < size - 1; j++) {
            arr[j] = arr[j + 1];
        }
        arr[size - 1] = temp;
    }
}

// Function to rotate array right
void rotateRight(int arr[], int size, int positions) {
    positions = positions % size;
    for (int i = 0; i < positions; i++) {
        int temp = arr[size - 1];
        for (int j = size - 1; j > 0; j--) {
            arr[j] = arr[j - 1];
        }
        arr[0] = temp;
    }
}

// Function to check if character array is palindrome
bool isPalindromeCharArray(char arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        if (arr[i] != arr[size - 1 - i]) {
            return false;
        }
    }
    return true;
}

// Function to find largest word in string
string findLargestWord(string str) {
    string largest = "";
    string current = "";
    
    for (char c : str) {
        if (c == ' ' || c == '\0') {
            if (current.length() > largest.length()) {
                largest = current;
            }
            current = "";
        } else {
            current += c;
        }
    }
    
    if (current.length() > largest.length()) {
        largest = current;
    }
    
    return largest;
}

// Function to compress string
string compressString(string str) {
    if (str.empty()) return str;
    
    string result = "";
    char current = str[0];
    int count = 1;
    
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == current) {
            count++;
        } else {
            result += current;
            if (count > 1) {
                result += to_string(count);
            }
            current = str[i];
            count = 1;
        }
    }
    
    result += current;
    if (count > 1) {
        result += to_string(count);
    }
    
    return result;
}

int main() {
    cout << "ARRAYS PRACTICE QUESTIONS" << endl;
    cout << "=========================" << endl;
    
    int choice;
    
    cout << "\nChoose a practice question (1-25): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. Perfect Number
        cout << "\n=== 1. Perfect Number ===" << endl;
        int num;
        cout << "Enter a number: ";
        cin >> num;
        
        if (isPerfect(num)) {
            cout << num << " is a perfect number." << endl;
        } else {
            cout << num << " is not a perfect number." << endl;
        }
    }
    
    else if (choice == 2) {
        // 2. Max Element of Array
        cout << "\n=== 2. Max Element of Array ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        cout << "Maximum element: " << findMax(arr, size) << endl;
    }
    
    else if (choice == 3) {
        // 3. Reverse Array
        cout << "\n=== 3. Reverse Array ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        cout << "Original array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        
        reverseArray(arr, size);
        
        cout << "\nReversed array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    else if (choice == 4) {
        // 4. Mean, Mode, Median
        cout << "\n=== 4. Mean, Mode, Median ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        cout << "Mean: " << calculateMean(arr, size) << endl;
        cout << "Median: " << calculateMedian(arr, size) << endl;
        cout << "Mode: " << calculateMode(arr, size) << endl;
    }
    
    else if (choice == 5) {
        // 5. Equilibrium Index
        cout << "\n=== 5. Equilibrium Index ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int eqIndex = findEquilibriumIndex(arr, size);
        if (eqIndex != -1) {
            cout << "Equilibrium index: " << eqIndex << endl;
        } else {
            cout << "No equilibrium index found." << endl;
        }
    }
    
    else if (choice == 6) {
        // 6. Copy Array
        cout << "\n=== 6. Copy Array ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int original[size], copy[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> original[i];
        }
        
        // Copy array
        for (int i = 0; i < size; i++) {
            copy[i] = original[i];
        }
        
        cout << "Original array: ";
        for (int i = 0; i < size; i++) {
            cout << original[i] << " ";
        }
        
        cout << "\nCopied array: ";
        for (int i = 0; i < size; i++) {
            cout << copy[i] << " ";
        }
        cout << endl;
    }
    
    else if (choice == 7) {
        // 7. Even/Odd Array
        cout << "\n=== 7. Even/Odd Array ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        cout << "Even numbers: ";
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 == 0) {
                cout << arr[i] << " ";
            }
        }
        
        cout << "\nOdd numbers: ";
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 != 0) {
                cout << arr[i] << " ";
            }
        }
        cout << endl;
    }
    
    else if (choice == 8) {
        // 8. Palindrome Array
        cout << "\n=== 8. Palindrome Array ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        if (isPalindromeArray(arr, size)) {
            cout << "Array is palindrome." << endl;
        } else {
            cout << "Array is not palindrome." << endl;
        }
    }
    
    else if (choice == 9) {
        // 9. Merge Array
        cout << "\n=== 9. Merge Array ===" << endl;
        int size1, size2;
        cout << "Enter size of first array: ";
        cin >> size1;
        cout << "Enter size of second array: ";
        cin >> size2;
        
        int arr1[size1], arr2[size2], merged[size1 + size2];
        
        cout << "Enter " << size1 << " elements for first array: ";
        for (int i = 0; i < size1; i++) {
            cin >> arr1[i];
        }
        
        cout << "Enter " << size2 << " elements for second array: ";
        for (int i = 0; i < size2; i++) {
            cin >> arr2[i];
        }
        
        // Merge arrays
        for (int i = 0; i < size1; i++) {
            merged[i] = arr1[i];
        }
        for (int i = 0; i < size2; i++) {
            merged[size1 + i] = arr2[i];
        }
        
        cout << "Merged array: ";
        for (int i = 0; i < size1 + size2; i++) {
            cout << merged[i] << " ";
        }
        cout << endl;
    }
    
    else if (choice == 10) {
        // 10. Delete Array Element
        cout << "\n=== 10. Delete Array Element ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int position;
        cout << "Enter position to delete (0-" << size-1 << "): ";
        cin >> position;
        
        if (position >= 0 && position < size) {
            for (int i = position; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
            
            cout << "Array after deletion: ";
            for (int i = 0; i < size; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        } else {
            cout << "Invalid position!" << endl;
        }
    }
    
    else if (choice == 11) {
        // 11. Insert Array Element
        cout << "\n=== 11. Insert Array Element ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size + 1]; // Extra space for insertion
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int element, position;
        cout << "Enter element to insert: ";
        cin >> element;
        cout << "Enter position to insert (0-" << size << "): ";
        cin >> position;
        
        if (position >= 0 && position <= size) {
            for (int i = size; i > position; i--) {
                arr[i] = arr[i - 1];
            }
            arr[position] = element;
            size++;
            
            cout << "Array after insertion: ";
            for (int i = 0; i < size; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        } else {
            cout << "Invalid position!" << endl;
        }
    }
    
    else if (choice == 12) {
        // 12. Remove Duplicates
        cout << "\n=== 12. Remove Duplicates ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements (sorted): ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int newSize = removeDuplicates(arr, size);
        
        cout << "Array after removing duplicates: ";
        for (int i = 0; i < newSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    else if (choice == 13) {
        // 13. Rotate Array Left
        cout << "\n=== 13. Rotate Array Left ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int positions;
        cout << "Enter number of positions to rotate left: ";
        cin >> positions;
        
        cout << "Original array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        
        rotateLeft(arr, size, positions);
        
        cout << "\nArray after left rotation: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    else if (choice == 14) {
        // 14. Rotate Array Right
        cout << "\n=== 14. Rotate Array Right ===" << endl;
        int size;
        cout << "Enter array size: ";
        cin >> size;
        
        int arr[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        int positions;
        cout << "Enter number of positions to rotate right: ";
        cin >> positions;
        
        cout << "Original array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        
        rotateRight(arr, size, positions);
        
        cout << "\nArray after right rotation: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    else if (choice == 15) {
        // 15. Check Palindrome in Char Array
        cout << "\n=== 15. Check Palindrome in Char Array ===" << endl;
        int size;
        cout << "Enter string length: ";
        cin >> size;
        
        char arr[size];
        cout << "Enter " << size << " characters: ";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
        
        if (isPalindromeCharArray(arr, size)) {
            cout << "Character array is palindrome." << endl;
        } else {
            cout << "Character array is not palindrome." << endl;
        }
    }
    
    else if (choice == 16) {
        // 16. Largest Word
        cout << "\n=== 16. Largest Word ===" << endl;
        string str;
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        
        string largest = findLargestWord(str);
        cout << "Largest word: " << largest << endl;
        cout << "Length: " << largest.length() << endl;
    }
    
    else if (choice == 17) {
        // 17. Length of String
        cout << "\n=== 17. Length of String ===" << endl;
        string str;
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        
        cout << "String: " << str << endl;
        cout << "Length: " << str.length() << endl;
    }
    
    else if (choice == 18) {
        // 18. Longest Palindrome
        cout << "\n=== 18. Longest Palindrome ===" << endl;
        string str;
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        
        int maxLength = 1;
        int start = 0;
        
        for (int i = 0; i < str.length(); i++) {
            for (int j = i; j < str.length(); j++) {
                bool isPalindrome = true;
                for (int k = 0; k < (j - i + 1) / 2; k++) {
                    if (str[i + k] != str[j - k]) {
                        isPalindrome = false;
                        break;
                    }
                }
                if (isPalindrome && (j - i + 1) > maxLength) {
                    start = i;
                    maxLength = j - i + 1;
                }
            }
        }
        
        cout << "Longest palindrome: " << str.substr(start, maxLength) << endl;
        cout << "Length: " << maxLength << endl;
    }
    
    else if (choice == 19) {
        // 19. String Compression
        cout << "\n=== 19. String Compression ===" << endl;
        string str;
        cout << "Enter a string: ";
        cin.ignore();
        getline(cin, str);
        
        string compressed = compressString(str);
        cout << "Original string: " << str << endl;
        cout << "Compressed string: " << compressed << endl;
    }
    
    else if (choice == 20) {
        // 20. Saddle Points of 2D Array
        cout << "\n=== 20. Saddle Points of 2D Array ===" << endl;
        int rows, cols;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;
        
        int arr[rows][cols];
        cout << "Enter " << rows * cols << " elements:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> arr[i][j];
            }
        }
        
        cout << "Saddle points:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool isSaddle = true;
                
                // Check if it's minimum in its row
                for (int k = 0; k < cols; k++) {
                    if (arr[i][k] < arr[i][j]) {
                        isSaddle = false;
                        break;
                    }
                }
                
                // Check if it's maximum in its column
                if (isSaddle) {
                    for (int k = 0; k < rows; k++) {
                        if (arr[k][j] > arr[i][j]) {
                            isSaddle = false;
                            break;
                        }
                    }
                }
                
                if (isSaddle) {
                    cout << "Saddle point at (" << i << "," << j << "): " << arr[i][j] << endl;
                }
            }
        }
    }
    
    else {
        cout << "Invalid choice! Please enter 1-20." << endl;
    }
    
    return 0;
}
