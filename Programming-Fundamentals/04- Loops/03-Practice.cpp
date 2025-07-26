/*
LOOPS PRACTICE QUESTIONS
========================

This file contains various practice problems using loops:
- Print table
- Print even/odd from loop
- Reverse numbers
- Swapping (3 methods)
- Check vowel
- Fibonacci series
- Leap year
- Prime numbers from 1-100
- Sum of digits
- Palindrome
- Armstrong number
- HCF
- LCM
- Patterns (various types)
*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

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

// Function to check if a number is Armstrong
bool isArmstrong(int n) {
    int original = n;
    int sum = 0;
    int digits = 0;
    
    // Count digits
    int temp = n;
    while (temp != 0) {
        digits++;
        temp /= 10;
    }
    
    // Calculate sum of powers
    while (n != 0) {
        int digit = n % 10;
        sum += pow(digit, digits);
        n /= 10;
    }
    
    return sum == original;
}

// Function to calculate HCF
int hcf(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate LCM
int lcm(int a, int b) {
    return (a * b) / hcf(a, b);
}

int main() {
    cout << "LOOPS PRACTICE QUESTIONS" << endl;
    cout << "========================" << endl;
    
    int choice;
    
    cout << "\nChoose a practice question (1-20): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. Print Table
        cout << "\n=== 1. Print Table ===" << endl;
        int num;
        cout << "Enter a number to print its table: ";
        cin >> num;
        
        cout << "Table of " << num << ":" << endl;
        for (int i = 1; i <= 10; i++) {
            cout << num << " x " << i << " = " << num * i << endl;
        }
    }
    
    else if (choice == 2) {
        // 2. Print Even/Odd from Loop
        cout << "\n=== 2. Print Even/Odd from Loop ===" << endl;
        int start, end;
        cout << "Enter start number: ";
        cin >> start;
        cout << "Enter end number: ";
        cin >> end;
        
        cout << "Even numbers: ";
        for (int i = start; i <= end; i++) {
            if (i % 2 == 0) {
                cout << i << " ";
            }
        }
        
        cout << "\nOdd numbers: ";
        for (int i = start; i <= end; i++) {
            if (i % 2 != 0) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    
    else if (choice == 3) {
        // 3. Reverse Number
        cout << "\n=== 3. Reverse Number ===" << endl;
        int num;
        cout << "Enter a number: ";
        cin >> num;
        
        int reversed = 0;
        int original = num;
        
        while (num != 0) {
            int digit = num % 10;
            reversed = reversed * 10 + digit;
            num /= 10;
        }
        
        cout << "Original: " << original << endl;
        cout << "Reversed: " << reversed << endl;
    }
    
    else if (choice == 4) {
        // 4. Swapping (3 Methods)
        cout << "\n=== 4. Swapping (3 Methods) ===" << endl;
        int a, b;
        cout << "Enter two numbers: ";
        cin >> a >> b;
        
        cout << "Before swapping: a = " << a << ", b = " << b << endl;
        
        // Method 1: Using temporary variable
        int temp = a;
        a = b;
        b = temp;
        cout << "Method 1 (temp): a = " << a << ", b = " << b << endl;
        
        // Method 2: Using arithmetic
        a = a + b;
        b = a - b;
        a = a - b;
        cout << "Method 2 (arithmetic): a = " << a << ", b = " << b << endl;
        
        // Method 3: Using XOR
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
        cout << "Method 3 (XOR): a = " << a << ", b = " << b << endl;
    }
    
    else if (choice == 5) {
        // 5. Check Vowel
        cout << "\n=== 5. Check Vowel ===" << endl;
        char ch;
        cout << "Enter a character: ";
        cin >> ch;
        
        // Convert to lowercase for easier checking
        ch = tolower(ch);
        
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            cout << "The character is a vowel." << endl;
        } else {
            cout << "The character is a consonant." << endl;
        }
    }
    
    else if (choice == 6) {
        // 6. Fibonacci Series
        cout << "\n=== 6. Fibonacci Series ===" << endl;
        int n;
        cout << "Enter number of terms: ";
        cin >> n;
        
        int first = 0, second = 1;
        cout << "Fibonacci Series: ";
        
        for (int i = 1; i <= n; i++) {
            cout << first << " ";
            int next = first + second;
            first = second;
            second = next;
        }
        cout << endl;
    }
    
    else if (choice == 7) {
        // 7. Leap Year
        cout << "\n=== 7. Leap Year ===" << endl;
        int year;
        cout << "Enter a year: ";
        cin >> year;
        
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            cout << year << " is a leap year." << endl;
        } else {
            cout << year << " is not a leap year." << endl;
        }
    }
    
    else if (choice == 8) {
        // 8. Prime Numbers from 1-100
        cout << "\n=== 8. Prime Numbers from 1-100 ===" << endl;
        cout << "Prime numbers between 1 and 100: ";
        
        for (int i = 1; i <= 100; i++) {
            if (isPrime(i)) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    
    else if (choice == 9) {
        // 9. Sum of Digits
        cout << "\n=== 9. Sum of Digits ===" << endl;
        int num;
        cout << "Enter a number: ";
        cin >> num;
        
        int sum = 0;
        int original = num;
        
        while (num != 0) {
            sum += num % 10;
            num /= 10;
        }
        
        cout << "Sum of digits of " << original << " is: " << sum << endl;
    }
    
    else if (choice == 10) {
        // 10. Palindrome Number
        cout << "\n=== 10. Palindrome Number ===" << endl;
        int num;
        cout << "Enter a number: ";
        cin >> num;
        
        int reversed = 0;
        int original = num;
        
        while (num != 0) {
            int digit = num % 10;
            reversed = reversed * 10 + digit;
            num /= 10;
        }
        
        if (original == reversed) {
            cout << original << " is a palindrome." << endl;
        } else {
            cout << original << " is not a palindrome." << endl;
        }
    }
    
    else if (choice == 11) {
        // 11. Armstrong Number
        cout << "\n=== 11. Armstrong Number ===" << endl;
        int num;
        cout << "Enter a number: ";
        cin >> num;
        
        if (isArmstrong(num)) {
            cout << num << " is an Armstrong number." << endl;
        } else {
            cout << num << " is not an Armstrong number." << endl;
        }
    }
    
    else if (choice == 12) {
        // 12. HCF
        cout << "\n=== 12. HCF (Highest Common Factor) ===" << endl;
        int a, b;
        cout << "Enter two numbers: ";
        cin >> a >> b;
        
        cout << "HCF of " << a << " and " << b << " is: " << hcf(a, b) << endl;
    }
    
    else if (choice == 13) {
        // 13. LCM
        cout << "\n=== 13. LCM (Least Common Multiple) ===" << endl;
        int a, b;
        cout << "Enter two numbers: ";
        cin >> a >> b;
        
        cout << "LCM of " << a << " and " << b << " is: " << lcm(a, b) << endl;
    }
    
    else if (choice == 14) {
        // 14. Left Triangle Pattern
        cout << "\n=== 14. Left Triangle Pattern ===" << endl;
        int rows;
        cout << "Enter number of rows: ";
        cin >> rows;
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= i; j++) {
                cout << "* ";
            }
            cout << endl;
        }
    }
    
    else if (choice == 15) {
        // 15. Right Triangle Pattern
        cout << "\n=== 15. Right Triangle Pattern ===" << endl;
        int rows;
        cout << "Enter number of rows: ";
        cin >> rows;
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= rows - i; j++) {
                cout << "  ";
            }
            for (int k = 1; k <= i; k++) {
                cout << "* ";
            }
            cout << endl;
        }
    }
    
    else if (choice == 16) {
        // 16. Centered Triangle Pattern
        cout << "\n=== 16. Centered Triangle Pattern ===" << endl;
        int rows;
        cout << "Enter number of rows: ";
        cin >> rows;
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= rows - i; j++) {
                cout << " ";
            }
            for (int k = 1; k <= 2 * i - 1; k++) {
                cout << "*";
            }
            cout << endl;
        }
    }
    
    else if (choice == 17) {
        // 17. Reverse Triangle with Spaces
        cout << "\n=== 17. Reverse Triangle with Spaces ===" << endl;
        int rows;
        cout << "Enter number of rows: ";
        cin >> rows;
        
        for (int i = rows; i >= 1; i--) {
            for (int j = 1; j <= rows - i; j++) {
                cout << " ";
            }
            for (int k = 1; k <= 2 * i - 1; k++) {
                cout << "*";
            }
            cout << endl;
        }
    }
    
    else if (choice == 18) {
        // 18. Sideways Triangle Pattern
        cout << "\n=== 18. Sideways Triangle Pattern ===" << endl;
        int rows;
        cout << "Enter number of rows: ";
        cin >> rows;
        
        // Upper half
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= i; j++) {
                cout << "* ";
            }
            cout << endl;
        }
        
        // Lower half
        for (int i = rows - 1; i >= 1; i--) {
            for (int j = 1; j <= i; j++) {
                cout << "* ";
            }
            cout << endl;
        }
    }
    
    else if (choice == 19) {
        // 19. Square Pattern
        cout << "\n=== 19. Square Pattern ===" << endl;
        int size;
        cout << "Enter size of square: ";
        cin >> size;
        
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                cout << "* ";
            }
            cout << endl;
        }
    }
    
    else if (choice == 20) {
        // 20. Hollow Square Pattern
        cout << "\n=== 20. Hollow Square Pattern ===" << endl;
        int size;
        cout << "Enter size of square: ";
        cin >> size;
        
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                if (i == 1 || i == size || j == 1 || j == size) {
                    cout << "* ";
                } else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    }
    
    else {
        cout << "Invalid choice! Please enter 1-20." << endl;
    }
    
    return 0;
}
