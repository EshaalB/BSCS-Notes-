#include <iostream>
using namespace std;

int main() {
    cout << "BASIC TYPES OF LOOPS IN C++" << endl;
    cout << "===========================" << endl;
    
    int choice;
    cout << "\nChoose a loop type to learn about (1-3): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. For Loop
        cout << "\n=== 1. FOR LOOP ===" << endl;
        cout << "Syntax: for(initialization; condition; increment/decrement)" << endl;
        cout << "Example: for(int i = 1; i <= 5; i++)" << endl;
        cout << "\nCharacteristics:" << endl;
        cout << "- Used when you know the number of iterations" << endl;
        cout << "- Has initialization, condition, and increment/decrement" << endl;
        cout << "- Executes a fixed number of times" << endl;
        cout << "- Good for counting and array traversal" << endl;
        
        cout << "\nDemo: Counting from 1 to 5 (without actual loop):" << endl;
        int i = 1;
        if (i <= 5) {
            cout << "i = " << i << endl;
            i++;
        }
        if (i <= 5) {
            cout << "i = " << i << endl;
            i++;
        }
        if (i <= 5) {
            cout << "i = " << i << endl;
            i++;
        }
        if (i <= 5) {
            cout << "i = " << i << endl;
            i++;
        }
        if (i <= 5) {
            cout << "i = " << i << endl;
            i++;
        }
        cout << "Loop completed!" << endl;
    }
    
    else if (choice == 2) {
        // 2. While Loop
        cout << "\n=== 2. WHILE LOOP ===" << endl;
        cout << "Syntax: while(condition)" << endl;
        cout << "Example: while(count < 10)" << endl;
        cout << "\nCharacteristics:" << endl;
        cout << "- Used when you don't know the number of iterations" << endl;
        cout << "- Condition is checked before execution" << endl;
        cout << "- May not execute at all (if condition is false initially)" << endl;
        cout << "- Good for user input validation and unknown iterations" << endl;
        
        cout << "\nDemo: Countdown from 3 (without actual loop):" << endl;
        int count = 3;
        if (count > 0) {
            cout << "Countdown: " << count << endl;
            count--;
        }
        if (count > 0) {
            cout << "Countdown: " << count << endl;
            count--;
        }
        if (count > 0) {
            cout << "Countdown: " << count << endl;
            count--;
        }
        cout << "Blast off!" << endl;
    }
    
    else if (choice == 3) {
        // 3. Do-While Loop
        cout << "\n=== 3. DO-WHILE LOOP ===" << endl;
        cout << "Syntax: do { statements } while(condition);" << endl;
        cout << "Example: do { cout << 'Hello'; } while(count < 3);" << endl;
        cout << "\nCharacteristics:" << endl;
        cout << "- Executes at least once" << endl;
        cout << "- Condition is checked after execution" << endl;
        cout << "- Always executes the body at least once" << endl;
        cout << "- Good for menu-driven programs and input validation" << endl;
        
        cout << "\nDemo: Menu system (without actual loop):" << endl;
        int menuChoice = 1;
        cout << "Menu Option " << menuChoice << " executed" << endl;
        menuChoice++;
        
        if (menuChoice <= 3) {
            cout << "Menu Option " << menuChoice << " executed" << endl;
            menuChoice++;
        }
        if (menuChoice <= 3) {
            cout << "Menu Option " << menuChoice << " executed" << endl;
            menuChoice++;
        }
        cout << "Menu system completed!" << endl;
    }
    
    else {
        cout << "Invalid choice! Please enter 1-3." << endl;
    }
    
    // Switch case example for loop comparison
    cout << "\n\n=== LOOP COMPARISON USING SWITCH ===" << endl;
    cout << "Choose comparison aspect (1-4): ";
    int comparisonChoice;
    cin >> comparisonChoice;
    
    switch (comparisonChoice) {
        case 1:
            cout << "\n1. WHEN TO USE EACH LOOP:" << endl;
            cout << "   For Loop: Known iterations, counting, arrays" << endl;
            cout << "   While Loop: Unknown iterations, input validation" << endl;
            cout << "   Do-While: Menu systems, guaranteed execution" << endl;
            break;
            
        case 2:
            cout << "\n2. CONDITION CHECKING:" << endl;
            cout << "   For Loop: Before execution" << endl;
            cout << "   While Loop: Before execution" << endl;
            cout << "   Do-While: After execution" << endl;
            break;
            
        case 3:
            cout << "\n3. MINIMUM EXECUTIONS:" << endl;
            cout << "   For Loop: 0 times (if condition false initially)" << endl;
            cout << "   While Loop: 0 times (if condition false initially)" << endl;
            cout << "   Do-While: 1 time (always executes at least once)" << endl;
            break;
            
        case 4:
            cout << "\n4. COMMON USE CASES:" << endl;
            cout << "   For Loop: for(int i = 0; i < n; i++)" << endl;
            cout << "   While Loop: while(userInput != 'q')" << endl;
            cout << "   Do-While: do { showMenu(); } while(choice != 0);" << endl;
            break;
            
        default:
            cout << "Invalid comparison choice!" << endl;
    }
    
    return 0;
}


 