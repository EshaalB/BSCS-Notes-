/*
POLYMORPHISM
============

THEORY:
-------
Polymorphism means "many forms" - the ability to represent a message in different ways.
It allows objects of different classes to be treated as objects of a common base class.

Key Concepts:
1. Same Interface: Different classes can have methods with the same name
2. Different Implementation: Each class implements the method differently
3. Runtime Binding: The correct method is called at runtime based on object type
4. Code Reusability: Same code can work with different object types

TYPES OF POLYMORPHISM:
---------------------
1. COMPILE-TIME POLYMORPHISM (Static Binding):
   - Function Overloading: Multiple functions with same name, different parameters
   - Operator Overloading: Redefining operators for user-defined types

2. RUNTIME POLYMORPHISM (Dynamic Binding):
   - Virtual Functions: Functions that can be overridden in derived classes
   - Function Overriding: Redefining base class function in derived class

CASTING:
--------
- Upcasting: Converting derived class pointer to base class pointer
- Downcasting: Converting base class pointer to derived class pointer
- Dynamic Cast: Safe downcasting with runtime type checking

FRIEND FUNCTIONS:
-----------------
- Functions that can access private and protected members of a class
- Not member functions but declared inside the class
- Can be friend to multiple classes
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Example 1: Animal and Sounds (Runtime Polymorphism)
class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {}
    
    // Virtual function - can be overridden
    virtual void makeSound() {
        cout << name << " makes a sound" << endl;
    }
    
    // Pure virtual function - must be implemented in derived classes
    virtual void move() = 0;
    
    virtual ~Animal() {
        cout << "Animal destructor" << endl;
    }
};

class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    
    void makeSound() override {
        cout << name << " says: Woof! Woof!" << endl;
    }
    
    void move() override {
        cout << name << " runs on four legs" << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor" << endl;
    }
};

class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}
    
    void makeSound() override {
        cout << name << " says: Meow! Meow!" << endl;
    }
    
    void move() override {
        cout << name << " walks gracefully" << endl;
    }
    
    ~Cat() {
        cout << "Cat destructor" << endl;
    }
};

class Bird : public Animal {
public:
    Bird(string n) : Animal(n) {}
    
    void makeSound() override {
        cout << name << " says: Tweet! Tweet!" << endl;
    }
    
    void move() override {
        cout << name << " flies in the sky" << endl;
    }
    
    ~Bird() {
        cout << "Bird destructor" << endl;
    }
};

// Example 2: Function Overloading (Compile-time Polymorphism)
class Calculator {
public:
    // Function overloading - same name, different parameters
    int add(int a, int b) {
        cout << "Adding two integers: " << a << " + " << b << endl;
        return a + b;
    }
    
    double add(double a, double b) {
        cout << "Adding two doubles: " << a << " + " << b << endl;
        return a + b;
    }
    
    int add(int a, int b, int c) {
        cout << "Adding three integers: " << a << " + " << b << " + " << c << endl;
        return a + b + c;
    }
    
    string add(string a, string b) {
        cout << "Concatenating strings: " << a << " + " << b << endl;
        return a + b;
    }
};

// Example 3: Operator Overloading
class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Operator overloading for addition
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }
    
    // Operator overloading for subtraction
    Complex operator-(const Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }
    
    // Operator overloading for output stream
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real;
        if(c.imag >= 0) os << " + ";
        os << c.imag << "i";
        return os;
    }
    
    // Friend function to access private members
    friend Complex multiply(const Complex& a, const Complex& b);
};

// Friend function implementation
Complex multiply(const Complex& a, const Complex& b) {
    double real = a.real * b.real - a.imag * b.imag;
    double imag = a.real * b.imag + a.imag * b.real;
    return Complex(real, imag);
}

// Example 4: Virtual Functions and Runtime Polymorphism
class Shape {
protected:
    string name;
    
public:
    Shape(string n) : name(n) {}
    
    virtual double calculateArea() {
        cout << "Base class area calculation" << endl;
        return 0;
    }
    
    virtual void display() {
        cout << "Shape: " << name << endl;
    }
    
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    
    double calculateArea() override {
        return 3.14159 * radius * radius;
    }
    
    void display() override {
        cout << "Circle with radius: " << radius << endl;
        cout << "Area: " << calculateArea() << endl;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(double l, double w) : Shape("Rectangle"), length(l), width(w) {}
    
    double calculateArea() override {
        return length * width;
    }
    
    void display() override {
        cout << "Rectangle with length: " << length << ", width: " << width << endl;
        cout << "Area: " << calculateArea() << endl;
    }
};

// Example 5: Casting Examples
class Base {
public:
    virtual void show() {
        cout << "Base class show()" << endl;
    }
    
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() override {
        cout << "Derived class show()" << endl;
    }
    
    void derivedSpecific() {
        cout << "Derived specific method" << endl;
    }
};

// DRY RUN PROBLEMS
void dryRunProblems() {
    cout << "\n=== DRY RUN PROBLEMS ===" << endl;
    
    // Problem 1: Runtime Polymorphism with Animals
    cout << "Problem 1: Runtime Polymorphism with Animals" << endl;
    Animal* animals[3];
    animals[0] = new Dog("Buddy");
    animals[1] = new Cat("Whiskers");
    animals[2] = new Bird("Tweety");
    
    for(int i = 0; i < 3; i++) {
        animals[i]->makeSound();
        animals[i]->move();
    }
    
    // Cleanup
    for(int i = 0; i < 3; i++) {
        delete animals[i];
    }
    
    // Problem 2: Function Overloading
    cout << "\nProblem 2: Function Overloading" << endl;
    Calculator calc;
    cout << "Result: " << calc.add(5, 3) << endl;
    cout << "Result: " << calc.add(3.5, 2.7) << endl;
    cout << "Result: " << calc.add(1, 2, 3) << endl;
    cout << "Result: " << calc.add("Hello", " World") << endl;
    
    // Problem 3: Operator Overloading
    cout << "\nProblem 3: Operator Overloading" << endl;
    Complex c1(3, 4);
    Complex c2(1, 2);
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    Complex c5 = multiply(c1, c2);
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c3 << endl;
    cout << "c1 - c2 = " << c4 << endl;
    cout << "c1 * c2 = " << c5 << endl;
    
    // Problem 4: Virtual Functions and Casting
    cout << "\nProblem 4: Virtual Functions and Casting" << endl;
    Shape* shapes[2];
    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(4, 6);
    
    for(int i = 0; i < 2; i++) {
        shapes[i]->display();
    }
    
    // Upcasting and downcasting
    Base* basePtr = new Derived();
    basePtr->show();  // Calls Derived::show() due to virtual function
    
    // Downcasting
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if(derivedPtr) {
        derivedPtr->derivedSpecific();
    }
    
    // Cleanup
    for(int i = 0; i < 2; i++) {
        delete shapes[i];
    }
    delete basePtr;
}

// PRACTICE QUESTIONS
void practiceQuestions() {
    cout << "\n=== PRACTICE QUESTIONS ===" << endl;
    
    cout << "1. Create a 'Vehicle' hierarchy with virtual start() and stop() methods" << endl;
    cout << "2. Create a 'Employee' class with overloaded calculateSalary() methods" << endl;
    cout << "3. Create a 'String' class with overloaded operators (+, ==, <<)" << endl;
    cout << "4. Create a 'BankAccount' hierarchy with virtual withdraw() method" << endl;
    cout << "5. Create a 'MediaPlayer' hierarchy with virtual play() and pause() methods" << endl;
}

int main() {
    cout << "=== POLYMORPHISM DEMONSTRATION ===" << endl;
    
    // Example 1: Animal Polymorphism
    cout << "\n1. Animal Polymorphism (Runtime):" << endl;
    Animal* animals[3];
    animals[0] = new Dog("Buddy");
    animals[1] = new Cat("Whiskers");
    animals[2] = new Bird("Tweety");
    
    for(int i = 0; i < 3; i++) {
        animals[i]->makeSound();
        animals[i]->move();
    }
    
    // Cleanup
    for(int i = 0; i < 3; i++) {
        delete animals[i];
    }
    
    // Example 2: Function Overloading
    cout << "\n2. Function Overloading (Compile-time):" << endl;
    Calculator calc;
    cout << "Result: " << calc.add(5, 3) << endl;
    cout << "Result: " << calc.add(3.5, 2.7) << endl;
    cout << "Result: " << calc.add(1, 2, 3) << endl;
    cout << "Result: " << calc.add("Hello", " World") << endl;
    
    // Example 3: Operator Overloading
    cout << "\n3. Operator Overloading:" << endl;
    Complex c1(3, 4);
    Complex c2(1, 2);
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    Complex c5 = multiply(c1, c2);
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c3 << endl;
    cout << "c1 - c2 = " << c4 << endl;
    cout << "c1 * c2 = " << c5 << endl;
    
    // Example 4: Virtual Functions
    cout << "\n4. Virtual Functions:" << endl;
    Shape* shapes[2];
    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(4, 6);
    
    for(int i = 0; i < 2; i++) {
        shapes[i]->display();
    }
    
    // Cleanup
    for(int i = 0; i < 2; i++) {
        delete shapes[i];
    }
    
    // Example 5: Casting
    cout << "\n5. Casting Examples:" << endl;
    Base* basePtr = new Derived();
    basePtr->show();  // Calls Derived::show() due to virtual function
    
    // Downcasting
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if(derivedPtr) {
        derivedPtr->derivedSpecific();
    }
    
    delete basePtr;
    
    dryRunProblems();
    practiceQuestions();
    
    return 0;
}

/*
OUTPUT:
=======
=== POLYMORPHISM DEMONSTRATION ===

1. Animal Polymorphism (Runtime):
Buddy says: Woof! Woof!
Buddy runs on four legs
Whiskers says: Meow! Meow!
Whiskers walks gracefully
Tweety says: Tweet! Tweet!
Tweety flies in the sky
Dog destructor
Animal destructor
Cat destructor
Animal destructor
Bird destructor
Animal destructor

2. Function Overloading (Compile-time):
Adding two integers: 5 + 3
Result: 8
Adding two doubles: 3.5 + 2.7
Result: 6.2
Adding three integers: 1 + 2 + 3
Result: 6
Concatenating strings: Hello +  World
Result: Hello World

3. Operator Overloading:
c1 = 3 + 4i
c2 = 1 + 2i
c1 + c2 = 4 + 6i
c1 - c2 = 2 + 2i
c1 * c2 = -5 + 10i

4. Virtual Functions:
Circle with radius: 5
Area: 78.5398
Rectangle with length: 4, width: 6
Area: 24

5. Casting Examples:
Derived class show()
Derived specific method

=== DRY RUN PROBLEMS ===
Problem 1: Runtime Polymorphism with Animals
Buddy says: Woof! Woof!
Buddy runs on four legs
Whiskers says: Meow! Meow!
Whiskers walks gracefully
Tweety says: Tweet! Tweet!
Tweety flies in the sky
Dog destructor
Animal destructor
Cat destructor
Animal destructor
Bird destructor
Animal destructor

Problem 2: Function Overloading
Adding two integers: 5 + 3
Result: 8
Adding two doubles: 3.5 + 2.7
Result: 6.2
Adding three integers: 1 + 2 + 3
Result: 6
Concatenating strings: Hello +  World
Result: Hello World

Problem 3: Operator Overloading
c1 = 3 + 4i
c2 = 1 + 2i
c1 + c2 = 4 + 6i
c1 - c2 = 2 + 2i
c1 * c2 = -5 + 10i

Problem 4: Virtual Functions and Casting
Circle with radius: 5
Area: 78.5398
Rectangle with length: 4, width: 6
Area: 24
Derived class show()
Derived specific method

=== PRACTICE QUESTIONS ===
1. Create a 'Vehicle' hierarchy with virtual start() and stop() methods
2. Create a 'Employee' class with overloaded calculateSalary() methods
3. Create a 'String' class with overloaded operators (+, ==, <<)
4. Create a 'BankAccount' hierarchy with virtual withdraw() method
5. Create a 'MediaPlayer' hierarchy with virtual play() and pause() methods
*/ 