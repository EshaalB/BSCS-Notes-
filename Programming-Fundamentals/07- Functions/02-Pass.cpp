#include <iostream>
using namespace std;

// Global variables
int globalVar = 100;
int globalCounter = 0;

// PASS BY VALUE - Creates a copy
int passByValue(int x) {
    int localVar = 20;
    globalCounter++;
    cout << "  Inside passByValue:" << endl;
    cout << "    x = " << x << " (copy of original)" << endl;
    cout << "    localVar = " << localVar << endl;
    cout << "    globalVar = " << globalVar << endl;
    cout << "    globalCounter = " << globalCounter << endl;
    
    x = x + globalVar + localVar;  // Modify the copy
    cout << "    After calculation: x = " << x << endl;
    cout << "    (Original variable unchanged)" << endl;
    return x;
}

// PASS BY REFERENCE - Uses original directly
void passByReference(int &x) {
    int localVar = 30;
    globalCounter++;
    cout << "  Inside passByReference:" << endl;
    cout << "    x = " << x << " (original variable)" << endl;
    cout << "    localVar = " << localVar << endl;
    cout << "    globalVar = " << globalVar << endl;
    cout << "    globalCounter = " << globalCounter << endl;
    
    x = x + globalVar + localVar;  // Modify the original
    cout << "    After calculation: x = " << x << endl;
    cout << "    (Original variable changed!)" << endl;
}

int main() {
    cout << "DRY RUN: PARAMETER PASSING DEMONSTRATION" << endl;
    cout << "=======================================" << endl;
    
    int choice;
    cout << "\nChoose dry run scenario (1-3): ";
    cin >> choice;
    
    if (choice == 1) {
        // Scenario 1: Basic demonstration
        cout << "\n=== SCENARIO 1: BASIC DEMONSTRATION ===" << endl;
        
        int x = 15, y = 25, z = 35;
        cout << "Initial values:" << endl;
        cout << "  x = " << x << ", y = " << y << ", z = " << z << endl;
        cout << "  globalVar = " << globalVar << ", globalCounter = " << globalCounter << endl;
        
        cout << "\nStep 1: y = y + local variable" << endl;
        int localVar = 10;
        y = y + localVar;
        cout << "  y = " << y << " (25 + 10 = 35)" << endl;
        
        cout << "\nStep 2: x - passByValue(y, x)" << endl;
        int result1 = passByValue(y);
        cout << "  result1 = " << result1 << endl;
        cout << "  x = " << x << " (unchanged)" << endl;
        cout << "  y = " << y << " (unchanged)" << endl;
        
        cout << "\nStep 3: passByReference(x)" << endl;
        passByReference(x);
        cout << "  x = " << x << " (changed!)" << endl;
        
        cout << "\nFinal values:" << endl;
        cout << "  x = " << x << ", y = " << y << ", z = " << z << endl;
        cout << "  globalCounter = " << globalCounter << endl;
    }
    
    else if (choice == 2) {
        // Scenario 2: Complex calculation
        cout << "\n=== SCENARIO 2: COMPLEX CALCULATION ===" << endl;
        
        int localVar = 20, b = 6;
        cout << "Initial values:" << endl;
        cout << "  localVar = " << localVar << ", b = " << b << endl;
        cout << "  globalVar = " << globalVar << ", globalCounter = " << globalCounter << endl;
        
        cout << "\nStep 1: localVar + globalVar + b" << endl;
        int temp = localVar + globalVar + b;
        cout << "  temp = " << temp << " (20 + 100 + 6 = 126)" << endl;
        
        cout << "\nStep 2: int result = passByValue(localVar, b)" << endl;
        int result = passByValue(localVar);
        cout << "  result = " << result << endl;
        cout << "  localVar = " << localVar << " (unchanged)" << endl;
        cout << "  b = " << b << " (unchanged)" << endl;
        
        cout << "\nStep 3: passByReference(b)" << endl;
        passByReference(b);
        cout << "  b = " << b << " (changed!)" << endl;
        
        cout << "\nStep 4: variable << b << localVar" << endl;
        cout << "  Output: " << b << " " << localVar << endl;
        
        cout << "\nStep 5: result << result" << endl;
        cout << "  Output: " << result << endl;
        
        cout << "\nFinal values:" << endl;
        cout << "  localVar = " << localVar << ", b = " << b << endl;
        cout << "  result = " << result << endl;
        cout << "  globalCounter = " << globalCounter << endl;
    }
    
    else if (choice == 3) {
        // Scenario 3: Multiple function calls
        cout << "\n=== SCENARIO 3: MULTIPLE FUNCTION CALLS ===" << endl;
        
        int a = 5, b = 10, c = 15;
        cout << "Initial values:" << endl;
        cout << "  a = " << a << ", b = " << b << ", c = " << c << endl;
        cout << "  globalVar = " << globalVar << ", globalCounter = " << globalCounter << endl;
        
        cout << "\nStep 1: a + globalVar + c" << endl;
        int sum1 = a + globalVar + c;
        cout << "  sum1 = " << sum1 << " (5 + 100 + 15 = 120)" << endl;
        
        cout << "\nStep 2: b = b + local variable" << endl;
        int localVar = 8;
        b = b + localVar;
        cout << "  b = " << b << " (10 + 8 = 18)" << endl;
        
        cout << "\nStep 3: a - passByValue(b, a)" << endl;
        int result1 = passByValue(b);
        int diff1 = a - result1;
        cout << "  result1 = " << result1 << endl;
        cout << "  a - result1 = " << diff1 << endl;
        cout << "  a = " << a << " (unchanged)" << endl;
        cout << "  b = " << b << " (unchanged)" << endl;
        
        cout << "\nStep 4: passByReference(c)" << endl;
        passByReference(c);
        cout << "  c = " << c << " (changed!)" << endl;
        
        cout << "\nStep 5: passByReference(a)" << endl;
        passByReference(a);
        cout << "  a = " << a << " (changed!)" << endl;
        
        cout << "\nStep 6: variable << b << localVar" << endl;
        cout << "  Output: " << b << " " << localVar << endl;
        
        cout << "\nStep 7: result << result1" << endl;
        cout << "  Output: " << result1 << endl;
        
        cout << "\nFinal values:" << endl;
        cout << "  a = " << a << ", b = " << b << ", c = " << c << endl;
        cout << "  globalCounter = " << globalCounter << endl;
    }
    
    else {
        cout << "Invalid choice! Please enter 1-3." << endl;
    }
    
    // Switch case for explanation
    cout << "\n\n=== DRY RUN EXPLANATION ===" << endl;
    cout << "Choose explanation (1-3): ";
    int explanationChoice;
    cin >> explanationChoice;
    
    switch (explanationChoice) {
        case 1:
            cout << "\n1. VARIABLE SCOPE:" << endl;
            cout << "   Global variables: Accessible everywhere" << endl;
            cout << "   Local variables: Only in their function" << endl;
            cout << "   Parameters: Copy (value) or reference" << endl;
            break;
            
        case 2:
            cout << "\n2. FUNCTION BEHAVIOR:" << endl;
            cout << "   passByValue: Creates copy, original unchanged" << endl;
            cout << "   passByReference: Uses original, can modify it" << endl;
            cout << "   Return values: New values created by function" << endl;
            break;
            
        case 3:
            cout << "\n3. MEMORY TRACKING:" << endl;
            cout << "   globalCounter: Tracks function calls" << endl;
            cout << "   Variable values: Change based on passing method" << endl;
            cout << "   Output: Shows final state of all variables" << endl;
            break;
            
        default:
            cout << "Invalid explanation choice!" << endl;
    }
    
    return 0;
}