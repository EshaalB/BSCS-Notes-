/*
CONSTRUCTORS AND DESTRUCTORS
============================

THEORY:
-------
CONSTRUCTORS:
- Special member functions with same name as class
- Automatically called when object is created
- Used to initialize data members
- No return type (not even void)
- Can be overloaded

TYPES OF CONSTRUCTORS:
1. Default Constructor: No parameters, automatically provided if no constructor defined
2. Parameterized Constructor: Takes parameters to initialize with specific values
3. Copy Constructor: Initializes object using another object of same class

DESTRUCTORS:
- Special member function with same name as class but with ~ prefix
- Automatically called when object goes out of scope
- Used to clean up resources (memory deallocation)
- No parameters, no return type
- Cannot be overloaded (only one destructor per class)
- Last object created is first destroyed (LIFO - Last In, First Out)

IMPORTANT POINTS:
- If no default constructor and parameterized constructor exists, default constructor won't be provided
- Copy constructor takes reference to object (pass by value can cause infinite recursion)
- Use const reference in copy constructor to prevent modification
- Destructor can be virtual (important for inheritance)
- Destructor cannot be static, const, or have parameters
*/

#include <iostream>
#include <string>
using namespace std;

// Example 1: Basic Constructors and Destructor
class Student {
private:
    string name;
    int rollNo;
    float gpa;
    
public:
    // Default Constructor
    Student() {
        cout << "Default constructor called" << endl;
        name = "Unknown";
        rollNo = 0;
        gpa = 0.0;
    }
    
    // Parameterized Constructor
    Student(string n, int r, float g) {
        cout << "Parameterized constructor called" << endl;
        name = n;
        rollNo = r;
        gpa = g;
    }
    
    // Copy Constructor
    Student(const Student &other) {
        cout << "Copy constructor called" << endl;
        name = other.name;
        rollNo = other.rollNo;
        gpa = other.gpa;
    }
    
    // Destructor
    ~Student() {
        cout << "Destructor called for " << name << endl;
    }
    
    void display() {
        cout << "Name: " << name << ", Roll No: " << rollNo << ", GPA: " << gpa << endl;
    }
};

// Example 2: Constructor Overloading
class Rectangle {
private:
    double length;
    double width;
    
public:
    // Default constructor
    Rectangle() {
        cout << "Default Rectangle constructor" << endl;
        length = 0;
        width = 0;
    }
    
    // Single parameter constructor (square)
    Rectangle(double side) {
        cout << "Square Rectangle constructor" << endl;
        length = width = side;
    }
    
    // Two parameter constructor
    Rectangle(double l, double w) {
        cout << "Two parameter Rectangle constructor" << endl;
        length = l;
        width = w;
    }
    
    // Copy constructor
    Rectangle(const Rectangle &other) {
        cout << "Rectangle copy constructor" << endl;
        length = other.length;
        width = other.width;
    }
    
    ~Rectangle() {
        cout << "Rectangle destructor" << endl;
    }
    
    double getArea() {
        return length * width;
    }
    
    void display() {
        cout << "Length: " << length << ", Width: " << width << ", Area: " << getArea() << endl;
    }
};

// Example 3: Deep Copy vs Shallow Copy
class DeepCopy {
private:
    int *data;
    
public:
    DeepCopy(int value) {
        data = new int(value);
        cout << "DeepCopy constructor: " << *data << endl;
    }
    
    // Deep copy constructor (correct)
    DeepCopy(const DeepCopy &other) {
        cout << "DeepCopy copy constructor" << endl;
        data = new int(*other.data);  // Allocate new memory
    }
    
    ~DeepCopy() {
        cout << "DeepCopy destructor: " << *data << endl;
        delete data;
    }
    
    void setData(int value) { *data = value; }
    int getData() { return *data; }
};

// Example 4: Static Members
class Counter {
private:
    static int count;  // Static member variable
    int id;
    
public:
    Counter() {
        count++;
        id = count;
        cout << "Counter " << id << " created. Total: " << count << endl;
    }
    
    ~Counter() {
        count--;
        cout << "Counter " << id << " destroyed. Total: " << count << endl;
    }
    
    static int getCount() {  // Static member function
        return count;
    }
    
    int getId() { return id; }
};

// Initialize static member
int Counter::count = 0;

// Example 5: This Pointer Usage
class ThisDemo {
private:
    int value;
    
public:
    ThisDemo(int value) {
        // Using this pointer to distinguish between local and member variable
        this->value = value;
        cout << "Constructor: value = " << this->value << endl;
    }
    
    ThisDemo& setValue(int value) {
        this->value = value;
        cout << "setValue: value = " << this->value << endl;
        return *this;  // Return reference for method chaining
    }
    
    ThisDemo& increment() {
        this->value++;
        cout << "increment: value = " << this->value << endl;
        return *this;
    }
    
    int getValue() { return value; }
    
    ~ThisDemo() {
        cout << "Destructor: value = " << value << endl;
    }
};

// DRY RUN PROBLEMS
void dryRunProblems() {
    cout << "\n=== DRY RUN PROBLEMS ===" << endl;
    
    // Problem 1: Constructor and Destructor Order
    cout << "Problem 1: Constructor/Destructor Order" << endl;
    {
        Student s1("Alice", 101, 3.8);
        Student s2 = s1;  // Copy constructor
        s1.display();
        s2.display();
    }  // Destructors called here in reverse order
    
    // Problem 2: Constructor Overloading
    cout << "\nProblem 2: Constructor Overloading" << endl;
    Rectangle r1;        // Default
    Rectangle r2(5);     // Square
    Rectangle r3(4, 6);  // Rectangle
    Rectangle r4 = r3;   // Copy
    
    // Problem 3: Deep vs Shallow Copy
    cout << "\nProblem 3: Deep vs Shallow Copy" << endl;
    {
        DeepCopy dc1(42);
        DeepCopy dc2 = dc1;  // Deep copy
        dc2.setData(100);
        cout << "dc1: " << dc1.getData() << ", dc2: " << dc2.getData() << endl;
    }
    
    // Problem 4: Static Members
    cout << "\nProblem 4: Static Members" << endl;
    cout << "Initial count: " << Counter::getCount() << endl;
    {
        Counter c1, c2, c3;
        cout << "Count after creating 3 objects: " << Counter::getCount() << endl;
    }
    cout << "Count after destruction: " << Counter::getCount() << endl;
    
    // Problem 5: This Pointer
    cout << "\nProblem 5: This Pointer" << endl;
    ThisDemo td(10);
    td.setValue(20).increment().increment();  // Method chaining
    cout << "Final value: " << td.getValue() << endl;
}

// PRACTICE QUESTIONS
void practiceQuestions() {
    cout << "\n=== PRACTICE QUESTIONS ===" << endl;
    
    cout << "1. Create a class 'BankAccount' with constructors and destructor" << endl;
    cout << "2. Create a class 'Array' with dynamic memory allocation and proper copy constructor" << endl;
    cout << "3. Create a class 'String' with char pointer and deep copy implementation" << endl;
    cout << "4. Create a class 'Matrix' with 2D array and copy constructor" << endl;
    cout << "5. Create a class 'LinkedList' with proper memory management" << endl;
}

int main() {
    cout << "=== CONSTRUCTORS AND DESTRUCTORS DEMONSTRATION ===" << endl;
    
    // Example 1: Basic Constructors and Destructor
    cout << "\n1. Student Class:" << endl;
    {
        Student s1("Alice", 101, 3.8);
        Student s2 = s1;  // Copy constructor
        s1.display();
        s2.display();
    }  // Destructors called here
    
    // Example 2: Constructor Overloading
    cout << "\n2. Rectangle Class:" << endl;
    Rectangle r1;        // Default
    Rectangle r2(5);     // Square
    Rectangle r3(4, 6);  // Rectangle
    Rectangle r4 = r3;   // Copy
    
    // Example 3: Deep vs Shallow Copy
    cout << "\n3. Deep vs Shallow Copy:" << endl;
    {
        DeepCopy dc1(42);
        DeepCopy dc2 = dc1;  // Deep copy
        dc2.setData(100);
        cout << "dc1: " << dc1.getData() << ", dc2: " << dc2.getData() << endl;
    }
    
    // Example 4: Static Members
    cout << "\n4. Static Members:" << endl;
    cout << "Initial count: " << Counter::getCount() << endl;
    {
        Counter c1, c2, c3;
        cout << "Count after creating 3 objects: " << Counter::getCount() << endl;
    }
    cout << "Count after destruction: " << Counter::getCount() << endl;
    
    // Example 5: This Pointer
    cout << "\n5. This Pointer:" << endl;
    ThisDemo td(10);
    td.setValue(20).increment().increment();  // Method chaining
    cout << "Final value: " << td.getValue() << endl;
    
    dryRunProblems();
    practiceQuestions();
    
    return 0;
}

/*
OUTPUT:
=======
=== CONSTRUCTORS AND DESTRUCTORS DEMONSTRATION ===

1. Student Class:
Parameterized constructor called
Copy constructor called
Name: Alice, Roll No: 101, GPA: 3.8
Name: Alice, Roll No: 101, GPA: 3.8
Destructor called for Alice
Destructor called for Alice

2. Rectangle Class:
Default Rectangle constructor
Square Rectangle constructor
Two parameter Rectangle constructor
Rectangle copy constructor

3. Deep vs Shallow Copy:
DeepCopy constructor: 42
DeepCopy copy constructor
dc1: 42, dc2: 100
DeepCopy destructor: 100
DeepCopy destructor: 42

4. Static Members:
Initial count: 0
Counter 1 created. Total: 1
Counter 2 created. Total: 2
Counter 3 created. Total: 3
Count after creating 3 objects: 3
Counter 3 destroyed. Total: 2
Counter 2 destroyed. Total: 1
Counter 1 destroyed. Total: 0
Count after destruction: 0

5. This Pointer:
Constructor: value = 10
setValue: value = 20
increment: value = 21
increment: value = 22
Final value: 22
Destructor: value = 22

=== DRY RUN PROBLEMS ===
Problem 1: Constructor/Destructor Order
Parameterized constructor called
Copy constructor called
Name: Alice, Roll No: 101, GPA: 3.8
Name: Alice, Roll No: 101, GPA: 3.8
Destructor called for Alice
Destructor called for Alice

Problem 2: Constructor Overloading
Default Rectangle constructor
Square Rectangle constructor
Two parameter Rectangle constructor
Rectangle copy constructor

Problem 3: Deep vs Shallow Copy
DeepCopy constructor: 42
DeepCopy copy constructor
dc1: 42, dc2: 100
DeepCopy destructor: 100
DeepCopy destructor: 42

Problem 4: Static Members
Initial count: 0
Counter 1 created. Total: 1
Counter 2 created. Total: 2
Counter 3 created. Total: 3
Count after creating 3 objects: 3
Counter 3 destroyed. Total: 2
Counter 2 destroyed. Total: 1
Counter 1 destroyed. Total: 0
Count after destruction: 0

Problem 5: This Pointer
Constructor: value = 10
setValue: value = 20
increment: value = 21
increment: value = 22
Final value: 22
Destructor: value = 22

=== PRACTICE QUESTIONS ===
1. Create a class 'BankAccount' with constructors and destructor
2. Create a class 'Array' with dynamic memory allocation and proper copy constructor
3. Create a class 'String' with char pointer and deep copy implementation
4. Create a class 'Matrix' with 2D array and copy constructor
5. Create a class 'LinkedList' with proper memory management
*/ 