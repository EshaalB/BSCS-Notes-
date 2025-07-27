/*
==========================================
EXCEPTION HANDLING IN C++
==========================================

THEORY:
--------
Exception handling is a mechanism to handle runtime errors gracefully.
Components: try, catch, throw, finally (not in C++)

Types of Exceptions:
1. Standard Exceptions: runtime_error, logic_error, invalid_argument, etc.
2. Custom Exceptions: User-defined exception classes
3. Built-in Exceptions: Division by zero, array out of bounds, etc.

Benefits:
- Graceful error handling
- Program doesn't crash
- Better user experience
- Debugging information
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

// ==========================================
// BASIC EXCEPTION HANDLING
// ==========================================

// Function that may throw an exception
int divide(int a, int b) {
    if(b == 0) {
        throw runtime_error("Division by zero!");
    }
    return a / b;
}

// Function with multiple exception types
double calculateSquareRoot(double x) {
    if(x < 0) {
        throw invalid_argument("Cannot calculate square root of negative number");
    }
    if(x == 0) {
        throw logic_error("Square root of zero is zero");
    }
    return sqrt(x);
}

// Function with array bounds checking
int getArrayElement(int arr[], int size, int index) {
    if(index < 0 || index >= size) {
        throw out_of_range("Array index out of bounds");
    }
    return arr[index];
}

// ==========================================
// CUSTOM EXCEPTION CLASSES
// ==========================================

// Custom exception for age validation
class AgeException : public exception {
private:
    string message;
    
public:
    AgeException(string msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Custom exception for bank operations
class BankException : public exception {
private:
    string message;
    double amount;
    
public:
    BankException(string msg, double amt = 0.0) : message(msg), amount(amt) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
    
    double getAmount() const { return amount; }
};

// Custom exception for file operations
class FileException : public exception {
private:
    string filename;
    string operation;
    
public:
    FileException(string file, string op) : filename(file), operation(op) {}
    
    const char* what() const noexcept override {
        string msg = "File operation failed: " + operation + " on " + filename;
        return msg.c_str();
    }
    
    string getFilename() const { return filename; }
    string getOperation() const { return operation; }
};

// ==========================================
// FUNCTIONS WITH CUSTOM EXCEPTIONS
// ==========================================

// Age validation function
void validateAge(int age) {
    if(age < 0) {
        throw AgeException("Age cannot be negative");
    }
    if(age > 150) {
        throw AgeException("Age cannot be greater than 150");
    }
    if(age < 18) {
        throw AgeException("Must be at least 18 years old");
    }
    cout << "Age " << age << " is valid" << endl;
}

// Bank account operations
class BankAccount {
private:
    string accountNumber;
    double balance;
    
public:
    BankAccount(string acc, double bal) : accountNumber(acc), balance(bal) {}
    
    void deposit(double amount) {
        if(amount <= 0) {
            throw BankException("Deposit amount must be positive", amount);
        }
        balance += amount;
        cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
    }
    
    void withdraw(double amount) {
        if(amount <= 0) {
            throw BankException("Withdrawal amount must be positive", amount);
        }
        if(amount > balance) {
            throw BankException("Insufficient funds", amount);
        }
        balance -= amount;
        cout << "Withdrawn $" << amount << ". New balance: $" << balance << endl;
    }
    
    double getBalance() { return balance; }
    string getAccountNumber() { return accountNumber; }
};

// File operations simulation
class FileManager {
public:
    void openFile(string filename) {
        if(filename.empty()) {
            throw FileException(filename, "open");
        }
        if(filename.find(".txt") == string::npos) {
            throw FileException(filename, "open - invalid file type");
        }
        cout << "File " << filename << " opened successfully" << endl;
    }
    
    void readFile(string filename) {
        if(filename == "nonexistent.txt") {
            throw FileException(filename, "read - file not found");
        }
        cout << "Reading file " << filename << endl;
    }
    
    void writeFile(string filename) {
        if(filename == "readonly.txt") {
            throw FileException(filename, "write - file is read-only");
        }
        cout << "Writing to file " << filename << endl;
    }
};

// ==========================================
// EXCEPTION HANDLING EXAMPLES
// ==========================================

void demonstrateBasicExceptions() {
    cout << "\n=== BASIC EXCEPTION HANDLING ===" << endl;
    
    // Division by zero
    try {
        int result = divide(10, 0);
        cout << "Result: " << result << endl;
    } catch(const runtime_error& e) {
        cout << "Caught runtime error: " << e.what() << endl;
    }
    
    // Successful division
    try {
        int result = divide(10, 2);
        cout << "Result: " << result << endl;
    } catch(const runtime_error& e) {
        cout << "Caught runtime error: " << e.what() << endl;
    }
    
    // Square root calculation
    try {
        double result = calculateSquareRoot(-4);
        cout << "Square root: " << result << endl;
    } catch(const invalid_argument& e) {
        cout << "Caught invalid argument: " << e.what() << endl;
    } catch(const logic_error& e) {
        cout << "Caught logic error: " << e.what() << endl;
    }
    
    // Array access
    int arr[] = {1, 2, 3, 4, 5};
    try {
        int element = getArrayElement(arr, 5, 10);
        cout << "Element: " << element << endl;
    } catch(const out_of_range& e) {
        cout << "Caught out of range: " << e.what() << endl;
    }
}

void demonstrateCustomExceptions() {
    cout << "\n=== CUSTOM EXCEPTION HANDLING ===" << endl;
    
    // Age validation
    try {
        validateAge(-5);
    } catch(const AgeException& e) {
        cout << "Age error: " << e.what() << endl;
    }
    
    try {
        validateAge(200);
    } catch(const AgeException& e) {
        cout << "Age error: " << e.what() << endl;
    }
    
    try {
        validateAge(16);
    } catch(const AgeException& e) {
        cout << "Age error: " << e.what() << endl;
    }
    
    try {
        validateAge(25);
    } catch(const AgeException& e) {
        cout << "Age error: " << e.what() << endl;
    }
    
    // Bank operations
    BankAccount account("12345", 1000.0);
    
    try {
        account.deposit(-100);
    } catch(const BankException& e) {
        cout << "Bank error: " << e.what() << " (Amount: $" << e.getAmount() << ")" << endl;
    }
    
    try {
        account.withdraw(2000);
    } catch(const BankException& e) {
        cout << "Bank error: " << e.what() << " (Amount: $" << e.getAmount() << ")" << endl;
    }
    
    try {
        account.deposit(500);
        account.withdraw(200);
    } catch(const BankException& e) {
        cout << "Bank error: " << e.what() << endl;
    }
    
    // File operations
    FileManager fileManager;
    
    try {
        fileManager.openFile("");
    } catch(const FileException& e) {
        cout << "File error: " << e.what() << endl;
    }
    
    try {
        fileManager.openFile("document.pdf");
    } catch(const FileException& e) {
        cout << "File error: " << e.what() << endl;
    }
    
    try {
        fileManager.readFile("nonexistent.txt");
    } catch(const FileException& e) {
        cout << "File error: " << e.what() << endl;
    }
    
    try {
        fileManager.writeFile("readonly.txt");
    } catch(const FileException& e) {
        cout << "File error: " << e.what() << endl;
    }
}

// ==========================================
// EXCEPTION HANDLING WITH MULTIPLE CATCH BLOCKS
// ==========================================

void demonstrateMultipleCatchBlocks() {
    cout << "\n=== MULTIPLE CATCH BLOCKS ===" << endl;
    
    try {
        // This will throw different types of exceptions
        int choice = 2; // Change this to test different exceptions
        
        switch(choice) {
            case 1:
                divide(10, 0);
                break;
            case 2:
                calculateSquareRoot(-4);
                break;
            case 3:
                int arr[] = {1, 2, 3};
                getArrayElement(arr, 3, 10);
                break;
            case 4:
                validateAge(-5);
                break;
            default:
                cout << "No exception thrown" << endl;
        }
    } catch(const runtime_error& e) {
        cout << "Runtime error: " << e.what() << endl;
    } catch(const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    } catch(const out_of_range& e) {
        cout << "Out of range: " << e.what() << endl;
    } catch(const AgeException& e) {
        cout << "Age exception: " << e.what() << endl;
    } catch(const exception& e) {
        cout << "Generic exception: " << e.what() << endl;
    } catch(...) {
        cout << "Unknown exception caught" << endl;
    }
}

// ==========================================
// EXCEPTION HANDLING IN CLASSES
// ==========================================

class Student {
private:
    string name;
    int age;
    vector<double> grades;
    
public:
    Student(string n, int a) : name(n), age(a) {
        validateAge(age);
    }
    
    void addGrade(double grade) {
        if(grade < 0 || grade > 100) {
            throw invalid_argument("Grade must be between 0 and 100");
        }
        grades.push_back(grade);
        cout << "Grade " << grade << " added for " << name << endl;
    }
    
    double getAverage() {
        if(grades.empty()) {
            throw runtime_error("No grades available");
        }
        
        double sum = 0;
        for(double grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
    
    void displayInfo() {
        cout << "Student: " << name << ", Age: " << age << endl;
        cout << "Grades: ";
        for(double grade : grades) {
            cout << grade << " ";
        }
        cout << endl;
        
        try {
            double avg = getAverage();
            cout << "Average: " << avg << endl;
        } catch(const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
};

void demonstrateClassExceptions() {
    cout << "\n=== EXCEPTION HANDLING IN CLASSES ===" << endl;
    
    try {
        Student student1("Alice", 16); // Will throw AgeException
    } catch(const AgeException& e) {
        cout << "Student creation failed: " << e.what() << endl;
    }
    
    try {
        Student student2("Bob", 20);
        student2.addGrade(85);
        student2.addGrade(92);
        student2.addGrade(78);
        student2.displayInfo();
        
        student2.addGrade(150); // Will throw invalid_argument
    } catch(const invalid_argument& e) {
        cout << "Grade error: " << e.what() << endl;
    } catch(const AgeException& e) {
        cout << "Age error: " << e.what() << endl;
    }
    
    try {
        Student student3("Charlie", 22);
        student3.getAverage(); // Will throw runtime_error
    } catch(const runtime_error& e) {
        cout << "Average error: " << e.what() << endl;
    }
}

// ==========================================
// PRACTICE QUESTIONS SOLUTIONS
// ==========================================

// Solution 1: Calculator with Exception Handling
class Calculator {
public:
    double add(double a, double b) { return a + b; }
    
    double subtract(double a, double b) { return a - b; }
    
    double multiply(double a, double b) { return a * b; }
    
    double divide(double a, double b) {
        if(b == 0) {
            throw runtime_error("Division by zero");
        }
        return a / b;
    }
    
    double power(double base, double exponent) {
        if(base == 0 && exponent <= 0) {
            throw invalid_argument("Invalid power operation");
        }
        return pow(base, exponent);
    }
    
    double squareRoot(double x) {
        if(x < 0) {
            throw invalid_argument("Cannot calculate square root of negative number");
        }
        return sqrt(x);
    }
};

// Solution 2: Array Manager with Exception Handling
class ArrayManager {
private:
    vector<int> data;
    
public:
    void addElement(int element) {
        data.push_back(element);
    }
    
    int getElement(int index) {
        if(index < 0 || index >= data.size()) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    void setElement(int index, int value) {
        if(index < 0 || index >= data.size()) {
            throw out_of_range("Index out of bounds");
        }
        data[index] = value;
    }
    
    int getSize() { return data.size(); }
    
    void display() {
        cout << "Array: ";
        for(int element : data) {
            cout << element << " ";
        }
        cout << endl;
    }
};

// Solution 3: String Processor with Exception Handling
class StringProcessor {
public:
    string reverse(string str) {
        if(str.empty()) {
            throw invalid_argument("Cannot reverse empty string");
        }
        reverse(str.begin(), str.end());
        return str;
    }
    
    string substring(string str, int start, int length) {
        if(start < 0 || start >= str.length()) {
            throw out_of_range("Start index out of bounds");
        }
        if(start + length > str.length()) {
            throw out_of_range("Substring length exceeds string bounds");
        }
        return str.substr(start, length);
    }
    
    int findCharacter(string str, char ch) {
        size_t pos = str.find(ch);
        if(pos == string::npos) {
            throw runtime_error("Character not found");
        }
        return pos;
    }
    
    string toUpperCase(string str) {
        if(str.empty()) {
            throw invalid_argument("Cannot process empty string");
        }
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
};

// ==========================================
// DEMONSTRATE SOLUTIONS
// ==========================================

void demonstrateSolutions() {
    cout << "\n=== SOLUTION 1: CALCULATOR ===" << endl;
    Calculator calc;
    
    try {
        cout << "10 / 2 = " << calc.divide(10, 2) << endl;
        cout << "10 / 0 = " << calc.divide(10, 0) << endl;
    } catch(const runtime_error& e) {
        cout << "Calculator error: " << e.what() << endl;
    }
    
    try {
        cout << "sqrt(16) = " << calc.squareRoot(16) << endl;
        cout << "sqrt(-4) = " << calc.squareRoot(-4) << endl;
    } catch(const invalid_argument& e) {
        cout << "Calculator error: " << e.what() << endl;
    }
    
    cout << "\n=== SOLUTION 2: ARRAY MANAGER ===" << endl;
    ArrayManager arrManager;
    
    for(int i = 0; i < 5; i++) {
        arrManager.addElement(i * 10);
    }
    arrManager.display();
    
    try {
        cout << "Element at index 2: " << arrManager.getElement(2) << endl;
        cout << "Element at index 10: " << arrManager.getElement(10) << endl;
    } catch(const out_of_range& e) {
        cout << "Array error: " << e.what() << endl;
    }
    
    cout << "\n=== SOLUTION 3: STRING PROCESSOR ===" << endl;
    StringProcessor strProc;
    
    try {
        cout << "Reverse of 'Hello': " << strProc.reverse("Hello") << endl;
        cout << "Reverse of '': " << strProc.reverse("") << endl;
    } catch(const invalid_argument& e) {
        cout << "String error: " << e.what() << endl;
    }
    
    try {
        cout << "Substring of 'Hello World': " << strProc.substring("Hello World", 0, 5) << endl;
        cout << "Substring of 'Hello World': " << strProc.substring("Hello World", 0, 20) << endl;
    } catch(const out_of_range& e) {
        cout << "String error: " << e.what() << endl;
    }
}

// ==========================================
// DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
try { throw runtime_error("Error"); }
catch(runtime_error& e) { cout << e.what(); }
Answer: Error

Problem 2: What will be the output?
try { int x = 10/0; }
catch(exception& e) { cout << "Exception"; }
Answer: Exception

Problem 3: What will be the output?
try { throw 42; }
catch(int x) { cout << x; }
Answer: 42
*/

// ==========================================
// PRACTICE QUESTIONS
// ==========================================

/*
1. Create a Calculator class with exception handling:
   - Include add, subtract, multiply, divide methods
   - Handle division by zero
   - Handle invalid mathematical operations

2. Implement an Array Manager with exception handling:
   - Include add, get, set, display methods
   - Handle array bounds checking
   - Handle invalid operations

3. Create a String Processor with exception handling:
   - Include reverse, substring, find methods
   - Handle empty strings and invalid indices
   - Handle character not found scenarios

4. Implement a File Handler with exception handling:
   - Include open, read, write, close methods
   - Handle file not found, permission denied
   - Handle invalid file operations

5. Create a Database Connector with exception handling:
   - Include connect, query, disconnect methods
   - Handle connection failures, query errors
   - Handle timeout and authentication issues
*/

int main() {
    cout << "EXCEPTION HANDLING IN C++" << endl;
    cout << "=========================" << endl;
    
    demonstrateBasicExceptions();
    demonstrateCustomExceptions();
    demonstrateMultipleCatchBlocks();
    demonstrateClassExceptions();
    demonstrateSolutions();
    
    return 0;
} 