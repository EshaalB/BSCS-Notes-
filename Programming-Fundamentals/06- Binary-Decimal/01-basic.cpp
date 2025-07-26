#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    cout << "BINARY-DECIMAL CONVERSION METHODS" << endl;
    cout << "=================================" << endl;
    
    int choice;
    cout << "\nChoose conversion type (1-6): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. Binary to Decimal
        cout << "\n=== 1. BINARY TO DECIMAL ===" << endl;
        cout << "Method 1: Using Modulo and Division" << endl;
        
        int binaryNum;
        cout << "Enter a binary number: ";
        cin >> binaryNum;
        
        int decimal = 0;
        int power = 0;
        int temp = binaryNum;
        
        // Extract each digit using modulo and division with loop
        while (temp > 0) {
            int digit = temp % 10;
            if (digit == 1) {
                decimal += pow(2, power);
            }
            temp = temp / 10;
            power++;
        }
        
        cout << "Binary: " << binaryNum << " = Decimal: " << decimal << endl;
        
        cout << "\nMethod 2: Using Bitwise Operators" << endl;
        int decimal2 = 0;
        int position = 0;
        int temp2 = binaryNum;
        
        // Using bitwise operations with loop
        while (temp2 > 0) {
            if (temp2 & 1) {
                decimal2 += pow(2, position);
            }
            temp2 = temp2 >> 1;
            position++;
        }
        
        cout << "Binary: " << binaryNum << " = Decimal: " << decimal2 << endl;
    }
    
    else if (choice == 2) {
        // 2. Decimal to Binary
        cout << "\n=== 2. DECIMAL TO BINARY ===" << endl;
        cout << "Method 1: Using Division by 2" << endl;
        
        int decimalNum;
        cout << "Enter a decimal number: ";
        cin >> decimalNum;
        
        int binary = 0;
        int place = 1;
        int temp = decimalNum;
        
        // Convert using division by 2 method with loop
        while (temp > 0) {
            int remainder = temp % 2;
            binary = remainder * place + binary;
            temp = temp / 2;
            place = place * 10;
        }
        
        cout << "Decimal: " << decimalNum << " = Binary: " << binary << endl;
        
        cout << "\nMethod 2: Using Bitwise Operations" << endl;
        int binary2 = 0;
        int position = 0;
        int temp2 = decimalNum;
        
        // Using bitwise operations with loop
        while (temp2 > 0) {
            if (temp2 & 1) {
                binary2 += pow(10, position);
            }
            temp2 = temp2 >> 1;
            position++;
        }
        
        cout << "Decimal: " << decimalNum << " = Binary: " << binary2 << endl;
    }
    
    else if (choice == 3) {
        // 3. Binary to Octal
        cout << "\n=== 3. BINARY TO OCTAL ===" << endl;
        
        int binaryNum;
        cout << "Enter a binary number: ";
        cin >> binaryNum;
        
        // First convert to decimal, then to octal
        int decimal = 0;
        int temp = binaryNum;
        int power = 0;
        
        // Convert binary to decimal using loop
        while (temp > 0) {
            int digit = temp % 10;
            if (digit == 1) {
                decimal += pow(2, power);
            }
            temp = temp / 10;
            power++;
        }
        
        // Convert decimal to octal using loop
        int octal = 0;
        int place = 1;
        int temp2 = decimal;
        
        while (temp2 > 0) {
            int remainder = temp2 % 8;
            octal = remainder * place + octal;
            temp2 = temp2 / 8;
            place = place * 10;
        }
        
        cout << "Binary: " << binaryNum << " = Decimal: " << decimal << " = Octal: " << octal << endl;
    }
    
    else if (choice == 4) {
        // 4. Octal to Binary
        cout << "\n=== 4. OCTAL TO BINARY ===" << endl;
        
        int octalNum;
        cout << "Enter an octal number: ";
        cin >> octalNum;
        
        // First convert to decimal, then to binary
        int decimal = 0;
        int temp = octalNum;
        int power = 0;
        
        // Convert octal to decimal using loop
        while (temp > 0) {
            int digit = temp % 10;
            decimal += digit * pow(8, power);
            temp = temp / 10;
            power++;
        }
        
        // Convert decimal to binary using loop
        int binary = 0;
        int place = 1;
        int temp2 = decimal;
        
        while (temp2 > 0) {
            int remainder = temp2 % 2;
            binary = remainder * place + binary;
            temp2 = temp2 / 2;
            place = place * 10;
        }
        
        cout << "Octal: " << octalNum << " = Decimal: " << decimal << " = Binary: " << binary << endl;
    }
    
    else if (choice == 5) {
        // 5. Binary to Hexadecimal
        cout << "\n=== 5. BINARY TO HEXADECIMAL ===" << endl;
        
        int binaryNum;
        cout << "Enter a binary number: ";
        cin >> binaryNum;
        
        // Convert to decimal first
        int decimal = 0;
        int temp = binaryNum;
        int power = 0;
        
        // Convert binary to decimal using loop
        while (temp > 0) {
            int digit = temp % 10;
            if (digit == 1) {
                decimal += pow(2, power);
            }
            temp = temp / 10;
            power++;
        }
        
        // Convert decimal to hexadecimal using loop
        string hex = "";
        int temp2 = decimal;
        
        while (temp2 > 0) {
            int remainder = temp2 % 16;
            if (remainder < 10) {
                hex = char(remainder + '0') + hex;
            } else {
                hex = char(remainder - 10 + 'A') + hex;
            }
            temp2 = temp2 / 16;
        }
        
        cout << "Binary: " << binaryNum << " = Decimal: " << decimal << endl;
        cout << "Hexadecimal: " << hex << endl;
    }
    
    else if (choice == 6) {
        // 6. Hexadecimal to Binary
        cout << "\n=== 6. HEXADECIMAL TO BINARY ===" << endl;
        
        string hexNum;
        cout << "Enter a hexadecimal number: ";
        cin >> hexNum;
        
        // Convert to decimal first
        int decimal = 0;
        int power = 0;
        
        // Process each character using loop
        for (int i = hexNum.length() - 1; i >= 0; i--) {
            char digit = hexNum[i];
            int value;
            
            if (digit >= '0' && digit <= '9') {
                value = digit - '0';
            } else {
                switch (digit) {
                    case 'A': case 'a': value = 10; break;
                    case 'B': case 'b': value = 11; break;
                    case 'C': case 'c': value = 12; break;
                    case 'D': case 'd': value = 13; break;
                    case 'E': case 'e': value = 14; break;
                    case 'F': case 'f': value = 15; break;
                    default: value = 0; break;
                }
            }
            decimal += value * pow(16, power);
            power++;
        }
        
        // Convert decimal to binary using loop
        int binary = 0;
        int place = 1;
        int temp = decimal;
        
        while (temp > 0) {
            int remainder = temp % 2;
            binary = remainder * place + binary;
            temp = temp / 2;
            place = place * 10;
        }
        
        cout << "Hexadecimal: " << hexNum << " = Decimal: " << decimal << endl;
        cout << "Binary: " << binary << endl;
    }
    
    else {
        cout << "Invalid choice! Please enter 1-6." << endl;
    }
    
    // Switch case for conversion methods summary
    cout << "\n\n=== CONVERSION METHODS SUMMARY ===" << endl;
    cout << "Choose method type (1-3): ";
    int methodChoice;
    cin >> methodChoice;
    
    switch (methodChoice) {
        case 1:
            cout << "\n1. ARITHMETIC METHODS:" << endl;
            cout << "   - Modulo and Division" << endl;
            cout << "   - Powers of base (2, 8, 16)" << endl;
            cout << "   - Place value system" << endl;
            break;
            
        case 2:
            cout << "\n2. BITWISE METHODS:" << endl;
            cout << "   - AND operator (&)" << endl;
            cout << "   - Right shift (>>)" << endl;
            cout << "   - Left shift (<<)" << endl;
            break;
            
        case 3:
            cout << "\n3. CONVERSION FLOW:" << endl;
            cout << "   Binary ↔ Decimal: Direct conversion" << endl;
            cout << "   Binary ↔ Octal: Via decimal" << endl;
            cout << "   Binary ↔ Hex: Via decimal" << endl;
            cout << "   Octal ↔ Hex: Via decimal" << endl;
            break;
            
        default:
            cout << "Invalid method choice!" << endl;
    }
    
    return 0;
}