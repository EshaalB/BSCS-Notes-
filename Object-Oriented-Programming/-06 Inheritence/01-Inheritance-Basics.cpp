/*
==========================================
INHERITANCE IN C++
==========================================

THEORY:
--------
Inheritance allows a class (derived) to inherit properties from another class (base).
Types: Single, Multiple, Multilevel, Hierarchical, Hybrid, Virtual.
Special cases: Diamond Problem, Object Slicing.
*/

#include <iostream>
#include <string>
using namespace std;

// ==========================================
// BASIC INHERITANCE EXAMPLES
// ==========================================

class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {}
    virtual void makeSound() { cout << name << " makes a sound." << endl; }
    virtual ~Animal() {}
};

class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {}
    void makeSound() override { cout << name << " barks: Woof!" << endl; }
    void fetch() { cout << name << " is fetching." << endl; }
};

// Multiple Inheritance
class Flying { public: void fly() { cout << "Flying!" << endl; } };
class Swimming { public: void swim() { cout << "Swimming!" << endl; } };

class Duck : public Animal, public Flying, public Swimming {
public:
    Duck(string n, int a) : Animal(n, a) {}
    void makeSound() override { cout << name << " quacks: Quack!" << endl; }
};

// Multilevel Inheritance
class Vehicle {
protected: string brand; int year;
public:
    Vehicle(string b, int y) : brand(b), year(y) {}
    void start() { cout << brand << " starting." << endl; }
};

class Car : public Vehicle {
protected: int doors;
public:
    Car(string b, int y, int d) : Vehicle(b, y), doors(d) {}
    void drive() { cout << brand << " driving." << endl; }
};

class ElectricCar : public Car {
private: int batteryCapacity;
public:
    ElectricCar(string b, int y, int d, int bc) : Car(b, y, d), batteryCapacity(bc) {}
    void charge() { cout << brand << " charging." << endl; }
};

// ==========================================
// DIAMOND PROBLEM AND VIRTUAL INHERITANCE
// ==========================================

class Person {
public: string name; Person(string n) : name(n) {}
    void display() { cout << "Person: " << name << endl; }
};

class Student : virtual public Person {
public: int studentId;
    Student(string n, int id) : Person(n), studentId(id) {}
    void study() { cout << name << " studying." << endl; }
};

class Employee : virtual public Person {
public: int employeeId;
    Employee(string n, int id) : Person(n), employeeId(id) {}
    void work() { cout << name << " working." << endl; }
};

class TeachingAssistant : public Student, public Employee {
public:
    TeachingAssistant(string n, int sid, int eid) 
        : Person(n), Student(n, sid), Employee(n, eid) {}
    void assist() { cout << name << " assisting." << endl; }
};

// ==========================================
// OBJECT SLICING EXAMPLE
// ==========================================

class Base {
public: int baseValue;
    Base(int val) : baseValue(val) {}
    virtual void display() { cout << "Base: " << baseValue << endl; }
};

class Derived : public Base {
public: int derivedValue;
    Derived(int bval, int dval) : Base(bval), derivedValue(dval) {}
    void display() override { cout << "Base: " << baseValue << ", Derived: " << derivedValue << endl; }
};

// ==========================================
// PRACTICE QUESTIONS SOLUTIONS
// ==========================================

// Library System
class Book {
protected: string title, author, isbn;
public:
    Book(string t, string a, string i) : title(t), author(a), isbn(i) {}
    virtual void display() { cout << "Book: " << title << " by " << author << endl; }
    virtual ~Book() {}
};

class FictionBook : public Book {
private: string genre;
public:
    FictionBook(string t, string a, string i, string g) : Book(t, a, i), genre(g) {}
    void display() override { cout << "Fiction: " << title << " (" << genre << ")" << endl; }
};

// Banking System
class Account {
protected: string accountNumber; double balance;
public:
    Account(string acc, double bal) : accountNumber(acc), balance(bal) {}
    virtual void deposit(double amount) { if(amount > 0) balance += amount; }
    virtual void display() { cout << "Account: " << accountNumber << ", Balance: $" << balance << endl; }
    virtual ~Account() {}
};

class SavingsAccount : public Account {
private: double interestRate;
public:
    SavingsAccount(string acc, double bal, double rate) : Account(acc, bal), interestRate(rate) {}
    void addInterest() { balance += balance * interestRate; }
    void display() override { 
        cout << "Savings: " << accountNumber << ", Balance: $" << balance << endl; 
    }
};

// ==========================================
// DEMONSTRATION FUNCTIONS
// ==========================================

void demonstrateInheritance() {
    cout << "\n=== BASIC INHERITANCE ===" << endl;
    Dog dog("Buddy", 3, "Golden");
    dog.makeSound();
    dog.fetch();
    
    Duck duck("Donald", 2);
    duck.makeSound();
    duck.fly();
    duck.swim();
    
    cout << "\n=== MULTILEVEL INHERITANCE ===" << endl;
    ElectricCar tesla("Tesla", 2023, 4, 75);
    tesla.start();
    tesla.drive();
    tesla.charge();
    
    cout << "\n=== DIAMOND PROBLEM SOLUTION ===" << endl;
    TeachingAssistant ta("Alice", 12345, 67890);
    ta.display();
    ta.study();
    ta.work();
    
    cout << "\n=== OBJECT SLICING ===" << endl;
    Derived derived(10, 20);
    Base base = derived;
    derived.display();
    base.display();
}

void demonstrateSolutions() {
    cout << "\n=== LIBRARY SYSTEM ===" << endl;
    FictionBook fiction("The Hobbit", "Tolkien", "123", "Fantasy");
    fiction.display();
    
    cout << "\n=== BANKING SYSTEM ===" << endl;
    SavingsAccount savings("SA001", 1000.0, 0.05);
    savings.deposit(500.0);
    savings.addInterest();
    savings.display();
}

// ==========================================
// DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class A { public: A() { cout << "A"; } ~A() { cout << "~A"; } };
class B : public A { public: B() { cout << "B"; } ~B() { cout << "~B"; } };
int main() { B obj; return 0; }
Answer: AB~B~A

Problem 2: What will be the output?
class Parent { public: virtual void show() { cout << "Parent"; } };
class Child : public Parent { public: void show() { cout << "Child"; } };
int main() { Parent* ptr = new Child(); ptr->show(); delete ptr; return 0; }
Answer: Child

Problem 3: What will be the output?
class X { public: int x; X(int val) : x(val) {} };
class Y : public X { public: int y; Y(int xval, int yval) : X(xval), y(yval) {} };
int main() { Y obj(10, 20); cout << obj.x << " " << obj.y; return 0; }
Answer: 10 20
*/

// ==========================================
// PRACTICE QUESTIONS
// ==========================================

/*
1. Create a class hierarchy for a library system:
   - Base: Book (title, author, ISBN)
   - Derived: FictionBook (genre), NonFictionBook (subject)

2. Implement a vehicle rental system:
   - Base: Vehicle (model, year, dailyRate)
   - Derived: Car (seats), Motorcycle (engineSize)

3. Create a university management system:
   - Base: Person (name, age)
   - Derived: Student (studentId, major), Professor (employeeId, department)

4. Implement a shape calculator:
   - Base: Shape (color)
   - Derived: Triangle (base, height), Square (side)

5. Create a banking system:
   - Base: Account (accountNumber, balance)
   - Derived: SavingsAccount (interestRate), CheckingAccount (overdraftLimit)
*/

int main() {
    cout << "INHERITANCE IN C++" << endl;
    cout << "==================" << endl;
    
    demonstrateInheritance();
    demonstrateSolutions();
    
    return 0;
} 