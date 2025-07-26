#include <iostream>
using namespace std;

int main() {
    cout << "C++ OPERATOR PRECEDENCE (HIGHEST TO LOWEST)" << endl;
    cout << "===========================================" << endl;
    
    int choice;
    cout << "\nChoose precedence level to learn (1-15): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. Postfix and Prefix (Highest Priority)
        cout << "\n=== 1. POSTFIX AND PREFIX OPERATORS ===" << endl;
        cout << "Priority: HIGHEST (Level 1)" << endl;
        cout << "Operators: ++, -- (postfix), ++, -- (prefix)" << endl;
        cout << "Associativity: Left to Right (postfix), Right to Left (prefix)" << endl;
        
        int a = 5, b = 3;
        cout << "\nExample: a = " << a << ", b = " << b << endl;
        
        if (a++ > 3) {
            cout << "a++ > 3 is true (a is " << a << " after increment)" << endl;
        } else {
            cout << "a++ > 3 is false" << endl;
        }
        
        if (++b < 5) {
            cout << "++b < 5 is true (b is " << b << " after increment)" << endl;
        } else {
            cout << "++b < 5 is false" << endl;
        }
    }
    
    else if (choice == 2) {
        // 2. Unary Operators
        cout << "\n=== 2. UNARY OPERATORS ===" << endl;
        cout << "Priority: Level 2" << endl;
        cout << "Operators: +, -, !, ~, (type), *, &, sizeof" << endl;
        cout << "Associativity: Right to Left" << endl;
        
        int x = 10, y = -5;
        cout << "\nExample: x = " << x << ", y = " << y << endl;
        
        if (!(x > 0)) {
            cout << "!(x > 0) is true" << endl;
        } else {
            cout << "!(x > 0) is false" << endl;
        }
        
        if (-y > 0) {
            cout << "-y > 0 is true (y = " << y << ", -y = " << -y << ")" << endl;
        } else {
            cout << "-y > 0 is false" << endl;
        }
    }
    
    else if (choice == 3) {
        // 3. Multiplicative Operators
        cout << "\n=== 3. MULTIPLICATIVE OPERATORS ===" << endl;
        cout << "Priority: Level 3" << endl;
        cout << "Operators: *, /, %" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int a = 10, b = 3, c = 2;
        cout << "\nExample: a = " << a << ", b = " << b << ", c = " << c << endl;
        
        if (a * b / c > 10) {
            cout << "a * b / c > 10 is true (result = " << a * b / c << ")" << endl;
        } else {
            cout << "a * b / c > 10 is false" << endl;
        }
        
        if (a % b == 1) {
            cout << "a % b == 1 is true (remainder = " << a % b << ")" << endl;
        } else {
            cout << "a % b == 1 is false" << endl;
        }
    }
    
    else if (choice == 4) {
        // 4. Additive Operators
        cout << "\n=== 4. ADDITIVE OPERATORS ===" << endl;
        cout << "Priority: Level 4" << endl;
        cout << "Operators: +, -" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int x = 5, y = 3, z = 2;
        cout << "\nExample: x = " << x << ", y = " << y << ", z = " << z << endl;
        
        if (x + y - z > 5) {
            cout << "x + y - z > 5 is true (result = " << x + y - z << ")" << endl;
        } else {
            cout << "x + y - z > 5 is false" << endl;
        }
    }
    
    else if (choice == 5) {
        // 5. Shift Operators
        cout << "\n=== 5. SHIFT OPERATORS ===" << endl;
        cout << "Priority: Level 5" << endl;
        cout << "Operators: <<, >>" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int num = 8;
        cout << "\nExample: num = " << num << endl;
        
        if ((num << 1) > 10) {
            cout << "num << 1 > 10 is true (result = " << (num << 1) << ")" << endl;
        } else {
            cout << "num << 1 > 10 is false" << endl;
        }
        
        if ((num >> 1) < 5) {
            cout << "num >> 1 < 5 is true (result = " << (num >> 1) << ")" << endl;
        } else {
            cout << "num >> 1 < 5 is false" << endl;
        }
    }
    
    else if (choice == 6) {
        // 6. Relational Operators
        cout << "\n=== 6. RELATIONAL OPERATORS ===" << endl;
        cout << "Priority: Level 6" << endl;
        cout << "Operators: <, <=, >, >=" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int a = 5, b = 10, c = 5;
        cout << "\nExample: a = " << a << ", b = " << b << ", c = " << c << endl;
        
        if (a < b <= c) {
            cout << "a < b <= c is true" << endl;
        } else {
            cout << "a < b <= c is false" << endl;
        }
        
        if (a >= c) {
            cout << "a >= c is true" << endl;
        } else {
            cout << "a >= c is false" << endl;
        }
    }
    
    else if (choice == 7) {
        // 7. Equality Operators
        cout << "\n=== 7. EQUALITY OPERATORS ===" << endl;
        cout << "Priority: Level 7" << endl;
        cout << "Operators: ==, !=" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int x = 5, y = 5, z = 10;
        cout << "\nExample: x = " << x << ", y = " << y << ", z = " << z << endl;
        
        if (x == y != z) {
            cout << "x == y != z is true" << endl;
        } else {
            cout << "x == y != z is false" << endl;
        }
    }
    
    else if (choice == 8) {
        // 8. Bitwise AND
        cout << "\n=== 8. BITWISE AND ===" << endl;
        cout << "Priority: Level 8" << endl;
        cout << "Operators: &" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int a = 5, b = 3;
        cout << "\nExample: a = " << a << " (binary: 101), b = " << b << " (binary: 011)" << endl;
        
        if ((a & b) == 1) {
            cout << "a & b == 1 is true (result = " << (a & b) << ")" << endl;
        } else {
            cout << "a & b == 1 is false" << endl;
        }
    }
    
    else if (choice == 9) {
        // 9. Bitwise XOR
        cout << "\n=== 9. BITWISE XOR ===" << endl;
        cout << "Priority: Level 9" << endl;
        cout << "Operators: ^" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int x = 5, y = 3;
        cout << "\nExample: x = " << x << " (binary: 101), y = " << y << " (binary: 011)" << endl;
        
        if ((x ^ y) > 5) {
            cout << "x ^ y > 5 is true (result = " << (x ^ y) << ")" << endl;
        } else {
            cout << "x ^ y > 5 is false" << endl;
        }
    }
    
    else if (choice == 10) {
        // 10. Bitwise OR
        cout << "\n=== 10. BITWISE OR ===" << endl;
        cout << "Priority: Level 10" << endl;
        cout << "Operators: |" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int a = 5, b = 3;
        cout << "\nExample: a = " << a << " (binary: 101), b = " << b << " (binary: 011)" << endl;
        
        if ((a | b) == 7) {
            cout << "a | b == 7 is true (result = " << (a | b) << ")" << endl;
        } else {
            cout << "a | b == 7 is false" << endl;
        }
    }
    
    else if (choice == 11) {
        // 11. Logical AND
        cout << "\n=== 11. LOGICAL AND ===" << endl;
        cout << "Priority: Level 11" << endl;
        cout << "Operators: &&" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int x = 5, y = 0, z = 10;
        cout << "\nExample: x = " << x << ", y = " << y << ", z = " << z << endl;
        
        if (x && z) {
            cout << "x && z is true (both are non-zero)" << endl;
        } else {
            cout << "x && z is false" << endl;
        }
        
        if (x && y) {
            cout << "x && y is true" << endl;
        } else {
            cout << "x && y is false (y is zero)" << endl;
        }
    }
    
    else if (choice == 12) {
        // 12. Logical OR
        cout << "\n=== 12. LOGICAL OR ===" << endl;
        cout << "Priority: Level 12" << endl;
        cout << "Operators: ||" << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int a = 0, b = 5, c = 0;
        cout << "\nExample: a = " << a << ", b = " << b << ", c = " << c << endl;
        
        if (a || b) {
            cout << "a || b is true (b is non-zero)" << endl;
        } else {
            cout << "a || b is false" << endl;
        }
        
        if (a || c) {
            cout << "a || c is true" << endl;
        } else {
            cout << "a || c is false (both are zero)" << endl;
        }
    }
    
    else if (choice == 13) {
        // 13. Conditional Operator
        cout << "\n=== 13. CONDITIONAL OPERATOR ===" << endl;
        cout << "Priority: Level 13" << endl;
        cout << "Operators: ? :" << endl;
        cout << "Associativity: Right to Left" << endl;
        
        int x = 10, y = 5;
        cout << "\nExample: x = " << x << ", y = " << y << endl;
        
        int result = (x > y) ? x : y;
        cout << "result = (x > y) ? x : y = " << result << endl;
        
        if (result == x) {
            cout << "Conditional operator returned x (larger value)" << endl;
        } else {
            cout << "Conditional operator returned y" << endl;
        }
    }
    
    else if (choice == 14) {
        // 14. Assignment Operators
        cout << "\n=== 14. ASSIGNMENT OPERATORS ===" << endl;
        cout << "Priority: Level 14" << endl;
        cout << "Operators: =, +=, -=, *=, /=, %=, <<=, >>=, &=, ^=, |=" << endl;
        cout << "Associativity: Right to Left" << endl;
        
        int a = 5, b = 3;
        cout << "\nExample: a = " << a << ", b = " << b << endl;
        
        a += b;
        cout << "After a += b: a = " << a << endl;
        
        if (a == 8) {
            cout << "Assignment successful: a = " << a << endl;
        } else {
            cout << "Assignment failed" << endl;
        }
    }
    
    else if (choice == 15) {
        // 15. Comma Operator (Lowest Priority)
        cout << "\n=== 15. COMMA OPERATOR ===" << endl;
        cout << "Priority: LOWEST (Level 15)" << endl;
        cout << "Operators: ," << endl;
        cout << "Associativity: Left to Right" << endl;
        
        int x = 1, y = 2, z = 3;
        cout << "\nExample: x = " << x << ", y = " << y << ", z = " << z << endl;
        
        int result = (x++, y++, z);
        cout << "result = (x++, y++, z) = " << result << endl;
        cout << "After comma operation: x = " << x << ", y = " << y << ", z = " << z << endl;
        
        if (result == z) {
            cout << "Comma operator returned the last value (z)" << endl;
        } else {
            cout << "Comma operator did not return z" << endl;
        }
    }
    
    else {
        cout << "Invalid choice! Please enter 1-15." << endl;
    }
    
    // Switch case for operator precedence summary
    cout << "\n\n=== OPERATOR PRECEDENCE SUMMARY ===" << endl;
    cout << "Choose summary type (1-3): ";
    int summaryChoice;
    cin >> summaryChoice;
    
    switch (summaryChoice) {
        case 1:
            cout << "\n1. HIGHEST PRIORITY (1-5):" << endl;
            cout << "   1. Postfix/Prefix (++, --)" << endl;
            cout << "   2. Unary (+, -, !, ~, *, &)" << endl;
            cout << "   3. Multiplicative (*, /, %)" << endl;
            cout << "   4. Additive (+, -)" << endl;
            cout << "   5. Shift (<<, >>)" << endl;
            break;
            
        case 2:
            cout << "\n2. MEDIUM PRIORITY (6-10):" << endl;
            cout << "   6. Relational (<, <=, >, >=)" << endl;
            cout << "   7. Equality (==, !=)" << endl;
            cout << "   8. Bitwise AND (&)" << endl;
            cout << "   9. Bitwise XOR (^)" << endl;
            cout << "   10. Bitwise OR (|)" << endl;
            break;
            
        case 3:
            cout << "\n3. LOWEST PRIORITY (11-15):" << endl;
            cout << "   11. Logical AND (&&)" << endl;
            cout << "   12. Logical OR (||)" << endl;
            cout << "   13. Conditional (? :)" << endl;
            cout << "   14. Assignment (=, +=, -=, etc.)" << endl;
            cout << "   15. Comma (,)" << endl;
            break;
            
        default:
            cout << "Invalid summary choice!" << endl;
    }
    
    return 0;
}