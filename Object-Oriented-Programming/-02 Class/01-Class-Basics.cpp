/*
CLASS BASICS
============

THEORY:
-------
A class is a user-defined data type that contains data members (variables) and 
member functions (methods) that can be accessed by creating instances (objects).

Key Concepts:
1. Class: Blueprint/template for creating objects
2. Object: Instance of a class
3. Data Members: Variables that store data
4. Member Functions: Functions that operate on the data
5. Access Modifiers: Control visibility of members (public, private, protected)

SIZE OF OBJECTS:
----------------
- Size of object = sum of sizes of all data members
- If class is empty, size = 1 byte (minimum size for object existence)
- Memory alignment may affect actual size

ACCESS MODIFIERS:
-----------------
1. Public: Accessible from anywhere
2. Private: Accessible only within the class (default)
3. Protected: Accessible within class and derived classes

MEMBER FUNCTIONS:
-----------------
Two ways to define:
1. Inside class definition (inline)
2. Outside class using scope resolution operator (::)

ACCESSORS & MUTATORS:
---------------------
- Accessors (Getters): Return values of private members
- Mutators (Setters): Set values of private members
*/

#include <iostream>
#include <string>
using namespace std;

// Example 1: Basic Class Structure
class Student {
private:
    string name;
    int rollNo;
    float gpa;
    
public:
    // Constructor
    Student() {
        name = "Unknown";
        rollNo = 0;
        gpa = 0.0;
    }
    
    // Member function inside class
    void display() {
        cout << "Name: " << name << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "GPA: " << gpa << endl;
    }
    
    // Accessors (Getters)
    string getName() { return name; }
    int getRollNo() { return rollNo; }
    float getGpa() { return gpa; }
    
    // Mutators (Setters)
    void setName(string n) { name = n; }
    void setRollNo(int r) { rollNo = r; }
    void setGpa(float g) { gpa = g; }
};

// Example 2: Class with Member Functions Outside
class Rectangle {
private:
    double length;
    double width;
    
public:
    // Constructor
    Rectangle(double l = 0, double w = 0);
    
    // Member functions declared inside, defined outside
    void setDimensions(double l, double w);
    double getArea();
    double getPerimeter();
    void display();
};

// Constructor definition outside class
Rectangle::Rectangle(double l, double w) {
    length = l;
    width = w;
}

// Member function definitions outside class
void Rectangle::setDimensions(double l, double w) {
    length = l;
    width = w;
}

double Rectangle::getArea() {
    return length * width;
}

double Rectangle::getPerimeter() {
    return 2 * (length + width);
}

void Rectangle::display() {
    cout << "Length: " << length << ", Width: " << width << endl;
    cout << "Area: " << getArea() << endl;
    cout << "Perimeter: " << getPerimeter() << endl;
}

// Example 3: Class with Different Access Modifiers
class BankAccount {
private:
    string accountNumber;
    double balance;
    
protected:
    string accountType;
    
public:
    string customerName;
    
    BankAccount(string name, string accNum, string type) {
        customerName = name;
        accountNumber = accNum;
        accountType = type;
        balance = 0.0;
    }
    
    void deposit(double amount) {
        if(amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        }
    }
    
    bool withdraw(double amount) {
        if(amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
            return true;
        }
        cout << "Insufficient funds!" << endl;
        return false;
    }
    
    double getBalance() {
        return balance;
    }
    
    void displayInfo() {
        cout << "Customer: " << customerName << endl;
        cout << "Account: " << accountNumber << endl;
        cout << "Type: " << accountType << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// Example 4: Demonstrating Object Size
class EmptyClass {
    // Empty class
};

class SizeDemo {
private:
    char c;     // 1 byte
    int i;      // 4 bytes
    double d;   // 8 bytes
};

class SizeDemo2 {
private:
    int i;      // 4 bytes
    char c;     // 1 byte
    double d;   // 8 bytes
};

// Example 5: This Pointer Usage
class ThisPointerDemo {
private:
    int value;
    
public:
    ThisPointerDemo(int value) {
        // Using this pointer to distinguish between local and member variable
        this->value = value;
    }
    
    ThisPointerDemo& setValue(int value) {
        this->value = value;
        return *this;  // Return reference to current object
    }
    
    int getValue() {
        return value;
    }
    
    void display() {
        cout << "Value: " << this->value << endl;
    }
};

// DRY RUN PROBLEMS
void dryRunProblems() {
    cout << "\n=== DRY RUN PROBLEMS ===" << endl;
    
    // Problem 1: What will be the output?
    cout << "Problem 1:" << endl;
    Student s1;
    s1.setName("Alice");
    s1.setRollNo(101);
    s1.setGpa(3.8);
    cout << "Student: " << s1.getName() << ", GPA: " << s1.getGpa() << endl;
    
    // Problem 2: What will be the output?
    cout << "\nProblem 2:" << endl;
    Rectangle r1(5, 3);
    cout << "Area: " << r1.getArea() << endl;
    cout << "Perimeter: " << r1.getPerimeter() << endl;
    
    // Problem 3: What will be the output?
    cout << "\nProblem 3:" << endl;
    BankAccount acc("John", "12345", "Savings");
    acc.deposit(1000);
    acc.withdraw(300);
    cout << "Final balance: $" << acc.getBalance() << endl;
    
    // Problem 4: Object sizes
    cout << "\nProblem 4:" << endl;
    cout << "Size of EmptyClass: " << sizeof(EmptyClass) << " bytes" << endl;
    cout << "Size of SizeDemo: " << sizeof(SizeDemo) << " bytes" << endl;
    cout << "Size of SizeDemo2: " << sizeof(SizeDemo2) << " bytes" << endl;
}

// PRACTICE QUESTIONS
void practiceQuestions() {
    cout << "\n=== PRACTICE QUESTIONS ===" << endl;
    
    cout << "1. Create a class 'Circle' with radius as data member and functions to calculate area and circumference" << endl;
    cout << "2. Create a class 'Book' with title, author, price as data members and appropriate getters/setters" << endl;
    cout << "3. Create a class 'Employee' with name, id, salary and functions to calculate bonus and display info" << endl;
    cout << "4. Create a class 'Time' with hours, minutes, seconds and functions to add time and display" << endl;
    cout << "5. Create a class 'Complex' with real and imaginary parts and functions for arithmetic operations" << endl;
}

// Solutions to Practice Questions

// Solution 1: Circle Class
class Circle {
private:
    double radius;
    
public:
    Circle(double r = 0) : radius(r) {}
    
    void setRadius(double r) { radius = r; }
    double getRadius() { return radius; }
    
    double getArea() {
        return 3.14159 * radius * radius;
    }
    
    double getCircumference() {
        return 2 * 3.14159 * radius;
    }
    
    void display() {
        cout << "Circle - Radius: " << radius << endl;
        cout << "Area: " << getArea() << endl;
        cout << "Circumference: " << getCircumference() << endl;
    }
};

// Solution 2: Book Class
class Book {
private:
    string title;
    string author;
    double price;
    
public:
    Book(string t = "", string a = "", double p = 0.0) {
        title = t;
        author = a;
        price = p;
    }
    
    // Getters
    string getTitle() { return title; }
    string getAuthor() { return author; }
    double getPrice() { return price; }
    
    // Setters
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setPrice(double p) { price = p; }
    
    void display() {
        cout << "Book: " << title << " by " << author << endl;
        cout << "Price: $" << price << endl;
    }
};

// Solution 3: Employee Class
class Employee {
private:
    string name;
    int id;
    double salary;
    
public:
    Employee(string n = "", int i = 0, double s = 0.0) {
        name = n;
        id = i;
        salary = s;
    }
    
    void setName(string n) { name = n; }
    void setId(int i) { id = i; }
    void setSalary(double s) { salary = s; }
    
    string getName() { return name; }
    int getId() { return id; }
    double getSalary() { return salary; }
    
    double calculateBonus(double percentage = 10.0) {
        return salary * (percentage / 100.0);
    }
    
    void displayInfo() {
        cout << "Employee: " << name << " (ID: " << id << ")" << endl;
        cout << "Salary: $" << salary << endl;
        cout << "Bonus: $" << calculateBonus() << endl;
    }
};

// Solution 4: Time Class
class Time {
private:
    int hours;
    int minutes;
    int seconds;
    
public:
    Time(int h = 0, int m = 0, int s = 0) {
        hours = h;
        minutes = m;
        seconds = s;
        normalize();
    }
    
    void setTime(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
        normalize();
    }
    
    void addTime(Time t) {
        hours += t.hours;
        minutes += t.minutes;
        seconds += t.seconds;
        normalize();
    }
    
    void normalize() {
        minutes += seconds / 60;
        seconds %= 60;
        hours += minutes / 60;
        minutes %= 60;
        hours %= 24;
    }
    
    void display() {
        printf("%02d:%02d:%02d\n", hours, minutes, seconds);
    }
};

// Solution 5: Complex Class
class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) {
        real = r;
        imag = i;
    }
    
    void setComplex(double r, double i) {
        real = r;
        imag = i;
    }
    
    Complex add(Complex c) {
        return Complex(real + c.real, imag + c.imag);
    }
    
    Complex subtract(Complex c) {
        return Complex(real - c.real, imag - c.imag);
    }
    
    Complex multiply(Complex c) {
        double r = real * c.real - imag * c.imag;
        double i = real * c.imag + imag * c.real;
        return Complex(r, i);
    }
    
    void display() {
        cout << real;
        if(imag >= 0) cout << " + ";
        cout << imag << "i" << endl;
    }
};

void demonstrateSolutions() {
    cout << "\n=== SOLUTIONS DEMONSTRATION ===" << endl;
    
    // Solution 1: Circle
    cout << "1. Circle Class:" << endl;
    Circle c1(5);
    c1.display();
    
    // Solution 2: Book
    cout << "\n2. Book Class:" << endl;
    Book b1("The Great Gatsby", "F. Scott Fitzgerald", 15.99);
    b1.display();
    
    // Solution 3: Employee
    cout << "\n3. Employee Class:" << endl;
    Employee e1("John Doe", 1001, 50000);
    e1.displayInfo();
    
    // Solution 4: Time
    cout << "\n4. Time Class:" << endl;
    Time t1(10, 30, 45);
    Time t2(2, 15, 20);
    cout << "Time 1: ";
    t1.display();
    cout << "Time 2: ";
    t2.display();
    t1.addTime(t2);
    cout << "After adding: ";
    t1.display();
    
    // Solution 5: Complex
    cout << "\n5. Complex Class:" << endl;
    Complex comp1(3, 4);
    Complex comp2(1, 2);
    cout << "Complex 1: ";
    comp1.display();
    cout << "Complex 2: ";
    comp2.display();
    Complex sum = comp1.add(comp2);
    cout << "Sum: ";
    sum.display();
}

int main() {
    cout << "=== CLASS BASICS DEMONSTRATION ===" << endl;
    
    // Example 1: Basic Class
    cout << "\n1. Student Class:" << endl;
    Student student1;
    student1.setName("Alice Johnson");
    student1.setRollNo(101);
    student1.setGpa(3.8);
    student1.display();
    
    // Example 2: Rectangle Class
    cout << "\n2. Rectangle Class:" << endl;
    Rectangle rect(5, 3);
    rect.display();
    
    // Example 3: Bank Account Class
    cout << "\n3. Bank Account Class:" << endl;
    BankAccount account("John Smith", "123456789", "Savings");
    account.deposit(1000);
    account.withdraw(300);
    account.displayInfo();
    
    // Example 4: Object Sizes
    cout << "\n4. Object Sizes:" << endl;
    cout << "Size of EmptyClass: " << sizeof(EmptyClass) << " bytes" << endl;
    cout << "Size of SizeDemo: " << sizeof(SizeDemo) << " bytes" << endl;
    cout << "Size of SizeDemo2: " << sizeof(SizeDemo2) << " bytes" << endl;
    
    // Example 5: This Pointer
    cout << "\n5. This Pointer Demo:" << endl;
    ThisPointerDemo obj(42);
    obj.setValue(100).setValue(200);  // Method chaining
    obj.display();
    
    dryRunProblems();
    practiceQuestions();
    demonstrateSolutions();
    
    return 0;
}

/*
OUTPUT:
=======
=== CLASS BASICS DEMONSTRATION ===

1. Student Class:
Name: Alice Johnson
Roll No: 101
GPA: 3.8

2. Rectangle Class:
Length: 5, Width: 3
Area: 15
Perimeter: 16

3. Bank Account Class:
Deposited: $1000
Withdrawn: $300
Customer: John Smith
Account: 123456789
Type: Savings
Balance: $700

4. Object Sizes:
Size of EmptyClass: 1 bytes
Size of SizeDemo: 16 bytes
Size of SizeDemo2: 16 bytes

5. This Pointer Demo:
Value: 200

=== DRY RUN PROBLEMS ===
Problem 1:
Student: Alice, GPA: 3.8

Problem 2:
Area: 15
Perimeter: 16

Problem 3:
Deposited: $1000
Withdrawn: $300
Final balance: $700

Problem 4:
Size of EmptyClass: 1 bytes
Size of SizeDemo: 16 bytes
Size of SizeDemo2: 16 bytes

=== PRACTICE QUESTIONS ===
1. Create a class 'Circle' with radius as data member and functions to calculate area and circumference
2. Create a class 'Book' with title, author, price as data members and appropriate getters/setters
3. Create a class 'Employee' with name, id, salary and functions to calculate bonus and display info
4. Create a class 'Time' with hours, minutes, seconds and functions to add time and display
5. Create a class 'Complex' with real and imaginary parts and functions for arithmetic operations

=== SOLUTIONS DEMONSTRATION ===
1. Circle Class:
Circle - Radius: 5
Area: 78.5398
Circumference: 31.4159

2. Book Class:
Book: The Great Gatsby by F. Scott Fitzgerald
Price: $15.99

3. Employee Class:
Employee: John Doe (ID: 1001)
Salary: $50000
Bonus: $5000

4. Time Class:
Time 1: 10:30:45
Time 2: 02:15:20
After adding: 12:46:05

5. Complex Class:
Complex 1: 3 + 4i
Complex 2: 1 + 2i
Sum: 4 + 6i
*/ 