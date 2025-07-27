/*
ENCAPSULATION
=============

THEORY:
-------
Encapsulation is the bundling of data and the methods that operate on that data 
within a single unit (class). It hides the internal state of an object and 
requires all interaction to be performed through an object's methods.

Key Concepts:
1. Data Hiding: Private data members are hidden from outside world
2. Bundling: Data and methods that operate on data are bundled together
3. Access Control: Controlled access through public methods
4. Information Hiding: Implementation details are hidden from users

BENEFITS:
---------
1. Readability: Code is more organized and easier to understand
2. Security: Data cannot be accessed or modified directly from outside
3. Control: Access to data is controlled through methods
4. Maintenance: Changes to implementation don't affect external code
5. Reusability: Encapsulated code can be reused easily

ACCESS SPECIFIERS:
------------------
1. Private: Accessible only within the class (default for class members)
2. Protected: Accessible within the class and derived classes
3. Public: Accessible from anywhere
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Example 1: Basic Encapsulation - Bank Account
class BankAccount {
private:
    // Private data members (encapsulated data)
    string accountNumber;
    string accountHolder;
    double balance;
    string password;
    vector<string> transactionHistory;
    
public:
    // Public constructor
    BankAccount(string accNum, string holder, string pwd, double initialBalance = 0.0) {
        accountNumber = accNum;
        accountHolder = holder;
        password = pwd;
        balance = initialBalance;
        addTransaction("Account opened with balance: $" + to_string(initialBalance));
    }
    
    // Public methods to access private data (controlled access)
    bool deposit(double amount, string pwd) {
        if(authenticate(pwd) && amount > 0) {
            balance += amount;
            addTransaction("Deposit: +$" + to_string(amount));
            return true;
        }
        return false;
    }
    
    bool withdraw(double amount, string pwd) {
        if(authenticate(pwd) && amount > 0 && amount <= balance) {
            balance -= amount;
            addTransaction("Withdrawal: -$" + to_string(amount));
            return true;
        }
        return false;
    }
    
    double getBalance(string pwd) {
        if(authenticate(pwd)) {
            return balance;
        }
        return -1; // Error indicator
    }
    
    string getAccountInfo(string pwd) {
        if(authenticate(pwd)) {
            return "Account: " + accountNumber + ", Holder: " + accountHolder;
        }
        return "Access denied";
    }
    
    void displayTransactionHistory(string pwd) {
        if(authenticate(pwd)) {
            cout << "Transaction History for " << accountNumber << ":" << endl;
            for(const string& transaction : transactionHistory) {
                cout << "- " << transaction << endl;
            }
        } else {
            cout << "Access denied" << endl;
        }
    }
    
private:
    // Private helper methods (implementation details hidden)
    bool authenticate(string pwd) {
        return password == pwd;
    }
    
    void addTransaction(string transaction) {
        transactionHistory.push_back(transaction);
    }
};

// Example 2: Student Grade Management
class StudentGrade {
private:
    string studentId;
    string name;
    vector<double> grades;
    double average;
    
public:
    StudentGrade(string id, string studentName) {
        studentId = id;
        name = studentName;
        average = 0.0;
    }
    
    void addGrade(double grade) {
        if(grade >= 0 && grade <= 100) {
            grades.push_back(grade);
            calculateAverage();
        }
    }
    
    double getAverage() {
        return average;
    }
    
    string getGrade() {
        if(average >= 90) return "A";
        else if(average >= 80) return "B";
        else if(average >= 70) return "C";
        else if(average >= 60) return "D";
        else return "F";
    }
    
    void displayInfo() {
        cout << "Student ID: " << studentId << endl;
        cout << "Name: " << name << endl;
        cout << "Average: " << average << endl;
        cout << "Grade: " << getGrade() << endl;
    }
    
private:
    void calculateAverage() {
        if(grades.empty()) {
            average = 0.0;
            return;
        }
        
        double sum = 0;
        for(double grade : grades) {
            sum += grade;
        }
        average = sum / grades.size();
    }
};

// Example 3: Temperature Converter with Validation
class TemperatureConverter {
private:
    double celsius;
    double fahrenheit;
    double kelvin;
    
public:
    TemperatureConverter() {
        celsius = 0.0;
        fahrenheit = 32.0;
        kelvin = 273.15;
    }
    
    void setCelsius(double temp) {
        if(temp >= -273.15) {  // Absolute zero check
            celsius = temp;
            updateAllTemperatures();
        }
    }
    
    void setFahrenheit(double temp) {
        if(temp >= -459.67) {  // Absolute zero in Fahrenheit
            fahrenheit = temp;
            celsius = (temp - 32) * 5.0 / 9.0;
            updateAllTemperatures();
        }
    }
    
    double getCelsius() { return celsius; }
    double getFahrenheit() { return fahrenheit; }
    double getKelvin() { return kelvin; }
    
    void displayAll() {
        cout << "Temperature in different units:" << endl;
        cout << "Celsius: " << celsius << "°C" << endl;
        cout << "Fahrenheit: " << fahrenheit << "°F" << endl;
        cout << "Kelvin: " << kelvin << "K" << endl;
    }
    
private:
    void updateAllTemperatures() {
        fahrenheit = celsius * 9.0 / 5.0 + 32;
        kelvin = celsius + 273.15;
    }
};

// DRY RUN PROBLEMS
void dryRunProblems() {
    cout << "\n=== DRY RUN PROBLEMS ===" << endl;
    
    // Problem 1: Bank Account Operations
    cout << "Problem 1: Bank Account Operations" << endl;
    BankAccount acc("12345", "John Doe", "password123", 1000);
    cout << "Initial balance: $" << acc.getBalance("password123") << endl;
    acc.deposit(500, "password123");
    acc.withdraw(200, "password123");
    cout << "Final balance: $" << acc.getBalance("password123") << endl;
    
    // Problem 2: Student Grade Calculation
    cout << "\nProblem 2: Student Grade Calculation" << endl;
    StudentGrade student("S001", "Alice");
    student.addGrade(85);
    student.addGrade(92);
    student.addGrade(78);
    student.displayInfo();
    
    // Problem 3: Temperature Conversion
    cout << "\nProblem 3: Temperature Conversion" << endl;
    TemperatureConverter temp;
    temp.setCelsius(25);
    temp.displayAll();
}

// PRACTICE QUESTIONS
void practiceQuestions() {
    cout << "\n=== PRACTICE QUESTIONS ===" << endl;
    
    cout << "1. Create a 'Library' class that encapsulates books and borrowing functionality" << endl;
    cout << "2. Create a 'Employee' class with salary, benefits, and performance tracking" << endl;
    cout << "3. Create a 'Inventory' class for managing product stock and sales" << endl;
    cout << "4. Create a 'Time' class with validation for hours, minutes, seconds" << endl;
    cout << "5. Create a 'Calculator' class that stores calculation history" << endl;
}

int main() {
    cout << "=== ENCAPSULATION DEMONSTRATION ===" << endl;
    
    // Example 1: Bank Account
    cout << "\n1. Bank Account Encapsulation:" << endl;
    BankAccount account("123456789", "John Doe", "secret123", 1000);
    cout << account.getAccountInfo("secret123") << endl;
    account.deposit(500, "secret123");
    account.withdraw(200, "secret123");
    cout << "Balance: $" << account.getBalance("secret123") << endl;
    account.displayTransactionHistory("secret123");
    
    // Example 2: Student Grade
    cout << "\n2. Student Grade Encapsulation:" << endl;
    StudentGrade student("S001", "Alice Johnson");
    student.addGrade(85);
    student.addGrade(92);
    student.addGrade(78);
    student.displayInfo();
    
    // Example 3: Temperature Converter
    cout << "\n3. Temperature Converter Encapsulation:" << endl;
    TemperatureConverter temp;
    temp.setCelsius(25);
    temp.displayAll();
    
    dryRunProblems();
    practiceQuestions();
    
    return 0;
}

/*
OUTPUT:
=======
=== ENCAPSULATION DEMONSTRATION ===

1. Bank Account Encapsulation:
Account: 123456789, Holder: John Doe
Balance: $1300
Transaction History for 123456789:
- Account opened with balance: $1000
- Deposit: +$500
- Withdrawal: -$200

2. Student Grade Encapsulation:
Student ID: S001
Name: Alice Johnson
Average: 85
Grade: B

3. Temperature Converter Encapsulation:
Temperature in different units:
Celsius: 25°C
Fahrenheit: 77°F
Kelvin: 298.15K

=== DRY RUN PROBLEMS ===
Problem 1: Bank Account Operations
Initial balance: $1000
Final balance: $1300

Problem 2: Student Grade Calculation
Student ID: S001
Name: Alice
Average: 85
Grade: B

Problem 3: Temperature Conversion
Temperature in different units:
Celsius: 25°C
Fahrenheit: 77°F
Kelvin: 298.15K

=== PRACTICE QUESTIONS ===
1. Create a 'Library' class that encapsulates books and borrowing functionality
2. Create a 'Employee' class with salary, benefits, and performance tracking
3. Create a 'Inventory' class for managing product stock and sales
4. Create a 'Time' class with validation for hours, minutes, seconds
5. Create a 'Calculator' class that stores calculation history
*/ 