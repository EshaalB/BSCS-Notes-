/*
ABSTRACTION
===========

THEORY:
-------
Abstraction is the process of hiding complex implementation details and showing 
only the essential features of an object. It focuses on what an object does 
rather than how it does it.

Key Concepts:
1. Essential Information: Show only necessary details to the user
2. Hide Complexity: Implementation details are hidden from the user
3. Interface Focus: User interacts through a simple interface
4. Reduce Complexity: Makes code easier to understand and maintain

BENEFITS:
---------
1. Simplifies complex systems
2. Reduces code complexity
3. Improves maintainability
4. Enhances reusability
5. Provides clear interfaces

ABSTRACT CLASSES:
-----------------
- Classes that cannot be instantiated directly
- Contains at least one pure virtual function
- Used as base classes for inheritance
- Provides interface without implementation
- Derived classes must implement pure virtual functions

PURE VIRTUAL FUNCTIONS:
----------------------
- Declared with = 0 at the end
- No implementation in base class
- Must be implemented in derived classes
- Makes class abstract
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Example 1: Abstract Shape Class
class Shape {
protected:
    string name;
    
public:
    Shape(string n) : name(n) {}
    
    // Pure virtual function - makes Shape abstract
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;
    
    // Virtual function with default implementation
    virtual void display() {
        cout << "Shape: " << name << endl;
    }
    
    // Virtual destructor
    virtual ~Shape() {
        cout << "Shape destructor called" << endl;
    }
};

// Concrete derived classes
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    
    double calculateArea() override {
        return 3.14159 * radius * radius;
    }
    
    double calculatePerimeter() override {
        return 2 * 3.14159 * radius;
    }
    
    void display() override {
        cout << "Circle with radius: " << radius << endl;
        cout << "Area: " << calculateArea() << endl;
        cout << "Perimeter: " << calculatePerimeter() << endl;
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
    
    double calculatePerimeter() override {
        return 2 * (length + width);
    }
    
    void display() override {
        cout << "Rectangle with length: " << length << ", width: " << width << endl;
        cout << "Area: " << calculateArea() << endl;
        cout << "Perimeter: " << calculatePerimeter() << endl;
    }
};

// Example 2: Abstract Database Interface
class Database {
public:
    virtual ~Database() {}
    
    // Pure virtual functions - interface
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool executeQuery(string query) = 0;
    virtual vector<string> getResults() = 0;
};

// Concrete implementation
class MySQLDatabase : public Database {
private:
    bool connected;
    vector<string> results;
    
public:
    MySQLDatabase() : connected(false) {}
    
    bool connect() override {
        cout << "Connecting to MySQL database..." << endl;
        connected = true;
        return true;
    }
    
    bool disconnect() override {
        cout << "Disconnecting from MySQL database..." << endl;
        connected = false;
        return true;
    }
    
    bool executeQuery(string query) override {
        if(!connected) {
            cout << "Not connected to database!" << endl;
            return false;
        }
        cout << "Executing MySQL query: " << query << endl;
        results = {"Result 1", "Result 2", "Result 3"};
        return true;
    }
    
    vector<string> getResults() override {
        return results;
    }
};

// Example 3: Abstract Vehicle Class
class Vehicle {
protected:
    string brand;
    string model;
    int year;
    
public:
    Vehicle(string b, string m, int y) : brand(b), model(m), year(y) {}
    
    virtual ~Vehicle() {}
    
    // Pure virtual functions
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void accelerate() = 0;
    
    // Virtual function with implementation
    virtual void displayInfo() {
        cout << brand << " " << model << " (" << year << ")" << endl;
    }
};

class Car : public Vehicle {
private:
    int numDoors;
    
public:
    Car(string b, string m, int y, int doors) 
        : Vehicle(b, m, y), numDoors(doors) {}
    
    void start() override {
        cout << "Car engine started" << endl;
    }
    
    void stop() override {
        cout << "Car engine stopped" << endl;
    }
    
    void accelerate() override {
        cout << "Car accelerating" << endl;
    }
    
    void displayInfo() override {
        Vehicle::displayInfo();
        cout << "Number of doors: " << numDoors << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    
public:
    Motorcycle(string b, string m, int y, bool sidecar) 
        : Vehicle(b, m, y), hasSidecar(sidecar) {}
    
    void start() override {
        cout << "Motorcycle engine started" << endl;
    }
    
    void stop() override {
        cout << "Motorcycle engine stopped" << endl;
    }
    
    void accelerate() override {
        cout << "Motorcycle accelerating" << endl;
    }
    
    void displayInfo() override {
        Vehicle::displayInfo();
        cout << "Has sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }
};

// Example 4: Abstract Payment System
class PaymentSystem {
public:
    virtual ~PaymentSystem() {}
    
    virtual bool processPayment(double amount) = 0;
    virtual string getPaymentMethod() = 0;
    virtual bool validatePayment() = 0;
};

class CreditCardPayment : public PaymentSystem {
private:
    string cardNumber;
    string cardHolder;
    
public:
    CreditCardPayment(string number, string holder) 
        : cardNumber(number), cardHolder(holder) {}
    
    bool processPayment(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
        return validatePayment();
    }
    
    string getPaymentMethod() override {
        return "Credit Card";
    }
    
    bool validatePayment() override {
        cout << "Validating credit card payment..." << endl;
        return true;
    }
};

class PayPalPayment : public PaymentSystem {
private:
    string email;
    
public:
    PayPalPayment(string userEmail) : email(userEmail) {}
    
    bool processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
        return validatePayment();
    }
    
    string getPaymentMethod() override {
        return "PayPal";
    }
    
    bool validatePayment() override {
        cout << "Validating PayPal payment..." << endl;
        return true;
    }
};

// Example 5: Using Abstraction - Shopping System
class ShoppingCart {
private:
    vector<string> items;
    PaymentSystem* paymentMethod;
    
public:
    ShoppingCart(PaymentSystem* payment) : paymentMethod(payment) {}
    
    void addItem(string item) {
        items.push_back(item);
    }
    
    void checkout(double total) {
        cout << "Items in cart: ";
        for(const string& item : items) {
            cout << item << " ";
        }
        cout << endl;
        
        cout << "Total: $" << total << endl;
        cout << "Payment method: " << paymentMethod->getPaymentMethod() << endl;
        
        if(paymentMethod->processPayment(total)) {
            cout << "Payment successful!" << endl;
        } else {
            cout << "Payment failed!" << endl;
        }
    }
};

// DRY RUN PROBLEMS
void dryRunProblems() {
    cout << "\n=== DRY RUN PROBLEMS ===" << endl;
    
    // Problem 1: Shape Calculations
    cout << "Problem 1: Shape Calculations" << endl;
    Circle circle(5);
    Rectangle rect(4, 6);
    
    circle.display();
    rect.display();
    
    // Problem 2: Database Operations
    cout << "\nProblem 2: Database Operations" << endl;
    MySQLDatabase db;
    db.connect();
    db.executeQuery("SELECT * FROM users");
    vector<string> results = db.getResults();
    for(const string& result : results) {
        cout << result << endl;
    }
    db.disconnect();
    
    // Problem 3: Vehicle Operations
    cout << "\nProblem 3: Vehicle Operations" << endl;
    Car car("Toyota", "Camry", 2020, 4);
    Motorcycle bike("Honda", "CBR", 2019, false);
    
    car.displayInfo();
    car.start();
    car.accelerate();
    car.stop();
    
    bike.displayInfo();
    bike.start();
    bike.accelerate();
    bike.stop();
    
    // Problem 4: Payment Processing
    cout << "\nProblem 4: Payment Processing" << endl;
    CreditCardPayment cc("1234-5678-9012-3456", "John Doe");
    PayPalPayment pp("john@example.com");
    
    ShoppingCart cart1(&cc);
    cart1.addItem("Laptop");
    cart1.addItem("Mouse");
    cart1.checkout(999.99);
    
    ShoppingCart cart2(&pp);
    cart2.addItem("Book");
    cart2.checkout(25.50);
}

// PRACTICE QUESTIONS
void practiceQuestions() {
    cout << "\n=== PRACTICE QUESTIONS ===" << endl;
    
    cout << "1. Create an abstract 'Animal' class with sound() and move() methods" << endl;
    cout << "2. Create an abstract 'Employee' class with calculateSalary() method" << endl;
    cout << "3. Create an abstract 'FileHandler' class for different file types" << endl;
    cout << "4. Create an abstract 'Notification' class for different notification types" << endl;
    cout << "5. Create an abstract 'Game' class with play() and getScore() methods" << endl;
}

int main() {
    cout << "=== ABSTRACTION DEMONSTRATION ===" << endl;
    
    // Example 1: Shape Abstraction
    cout << "\n1. Shape Abstraction:" << endl;
    Circle circle(5);
    Rectangle rect(4, 6);
    
    circle.display();
    rect.display();
    
    // Example 2: Database Abstraction
    cout << "\n2. Database Abstraction:" << endl;
    MySQLDatabase db;
    db.connect();
    db.executeQuery("SELECT * FROM users");
    vector<string> results = db.getResults();
    for(const string& result : results) {
        cout << result << endl;
    }
    db.disconnect();
    
    // Example 3: Vehicle Abstraction
    cout << "\n3. Vehicle Abstraction:" << endl;
    Car car("Toyota", "Camry", 2020, 4);
    Motorcycle bike("Honda", "CBR", 2019, false);
    
    car.displayInfo();
    car.start();
    car.accelerate();
    car.stop();
    
    bike.displayInfo();
    bike.start();
    bike.accelerate();
    bike.stop();
    
    // Example 4: Payment Abstraction
    cout << "\n4. Payment Abstraction:" << endl;
    CreditCardPayment cc("1234-5678-9012-3456", "John Doe");
    PayPalPayment pp("john@example.com");
    
    ShoppingCart cart1(&cc);
    cart1.addItem("Laptop");
    cart1.addItem("Mouse");
    cart1.checkout(999.99);
    
    ShoppingCart cart2(&pp);
    cart2.addItem("Book");
    cart2.checkout(25.50);
    
    dryRunProblems();
    practiceQuestions();
    
    return 0;
}

/*
OUTPUT:
=======
=== ABSTRACTION DEMONSTRATION ===

1. Shape Abstraction:
Circle with radius: 5
Area: 78.5398
Perimeter: 31.4159
Rectangle with length: 4, width: 6
Area: 24
Perimeter: 20

2. Database Abstraction:
Connecting to MySQL database...
Executing MySQL query: SELECT * FROM users
Result 1
Result 2
Result 3
Disconnecting from MySQL database...

3. Vehicle Abstraction:
Toyota Camry (2020)
Number of doors: 4
Car engine started
Car accelerating
Car engine stopped
Honda CBR (2019)
Has sidecar: No
Motorcycle engine started
Motorcycle accelerating
Motorcycle engine stopped

4. Payment Abstraction:
Items in cart: Laptop Mouse
Total: $999.99
Payment method: Credit Card
Processing credit card payment of $999.99
Validating credit card payment...
Payment successful!
Items in cart: Book
Total: $25.50
Payment method: PayPal
Processing PayPal payment of $25.50
Validating PayPal payment...
Payment successful!

=== DRY RUN PROBLEMS ===
Problem 1: Shape Calculations
Circle with radius: 5
Area: 78.5398
Perimeter: 31.4159
Rectangle with length: 4, width: 6
Area: 24
Perimeter: 20

Problem 2: Database Operations
Connecting to MySQL database...
Executing MySQL query: SELECT * FROM users
Result 1
Result 2
Result 3
Disconnecting from MySQL database...

Problem 3: Vehicle Operations
Toyota Camry (2020)
Number of doors: 4
Car engine started
Car accelerating
Car engine stopped
Honda CBR (2019)
Has sidecar: No
Motorcycle engine started
Motorcycle accelerating
Motorcycle engine stopped

Problem 4: Payment Processing
Items in cart: Laptop Mouse
Total: $999.99
Payment method: Credit Card
Processing credit card payment of $999.99
Validating credit card payment...
Payment successful!
Items in cart: Book
Total: $25.50
Payment method: PayPal
Processing PayPal payment of $25.50
Validating PayPal payment...
Payment successful!

=== PRACTICE QUESTIONS ===
1. Create an abstract 'Animal' class with sound() and move() methods
2. Create an abstract 'Employee' class with calculateSalary() method
3. Create an abstract 'FileHandler' class for different file types
4. Create an abstract 'Notification' class for different notification types
5. Create an abstract 'Game' class with play() and getScore() methods
*/ 