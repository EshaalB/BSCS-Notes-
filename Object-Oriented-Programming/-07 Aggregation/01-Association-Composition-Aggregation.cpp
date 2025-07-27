/*
==========================================
ASSOCIATION, COMPOSITION & AGGREGATION IN C++
==========================================

THEORY:
--------
These are different types of relationships between classes in OOP:

1. ASSOCIATION: A general relationship between objects (uses-a relationship)
   - Objects can exist independently
   - Weak coupling between classes
   - Example: Student uses Library

2. COMPOSITION: Strong ownership relationship (has-a relationship)
   - Part object cannot exist without the whole
   - Strong coupling, lifecycle dependency
   - When whole is destroyed, parts are destroyed
   - Example: House has Rooms (rooms don't exist without house)

3. AGGREGATION: Weak ownership relationship (has-a relationship)
   - Part object can exist independently
   - Weak coupling, no lifecycle dependency
   - Parts can exist even if whole is destroyed
   - Example: University has Students (students exist even if university closes)

Key Differences:
- Composition: "owns" (strong relationship)
- Aggregation: "has" (weak relationship)  
- Association: "uses" (no ownership)
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ==========================================
// ASSOCIATION EXAMPLES
// ==========================================

// Association: Student uses Library
class Library {
private:
    string name;
    vector<string> books;
    
public:
    Library(string n) : name(n) {
        books = {"Book1", "Book2", "Book3"};
    }
    
    bool borrowBook(string bookName) {
        for(auto& book : books) {
            if(book == bookName) {
                cout << "Book '" << bookName << "' borrowed from " << name << endl;
                return true;
            }
        }
        cout << "Book '" << bookName << "' not found in " << name << endl;
        return false;
    }
    
    void returnBook(string bookName) {
        cout << "Book '" << bookName << "' returned to " << name << endl;
    }
};

class Student {
private:
    string name;
    int studentId;
    
public:
    Student(string n, int id) : name(n), studentId(id) {}
    
    void study(Library& lib, string bookName) {
        cout << name << " is studying from " << bookName << endl;
        lib.borrowBook(bookName);
    }
    
    void returnBookToLibrary(Library& lib, string bookName) {
        lib.returnBook(bookName);
    }
    
    void display() {
        cout << "Student: " << name << " (ID: " << studentId << ")" << endl;
    }
};

// Association: Driver uses Car
class Car {
private:
    string model;
    string licensePlate;
    
public:
    Car(string m, string lp) : model(m), licensePlate(lp) {}
    
    void start() {
        cout << model << " (" << licensePlate << ") is starting" << endl;
    }
    
    void stop() {
        cout << model << " (" << licensePlate << ") is stopping" << endl;
    }
    
    string getModel() { return model; }
    string getLicensePlate() { return licensePlate; }
};

class Driver {
private:
    string name;
    string licenseNumber;
    
public:
    Driver(string n, string ln) : name(n), licenseNumber(ln) {}
    
    void drive(Car& car) {
        cout << name << " is driving " << car.getModel() << endl;
        car.start();
    }
    
    void park(Car& car) {
        cout << name << " is parking " << car.getModel() << endl;
        car.stop();
    }
    
    void display() {
        cout << "Driver: " << name << " (License: " << licenseNumber << ")" << endl;
    }
};

// ==========================================
// COMPOSITION EXAMPLES
// ==========================================

// Composition: House owns Rooms (rooms don't exist without house)
class Room {
private:
    string name;
    int area;
    
public:
    Room(string n, int a) : name(n), area(a) {
        cout << "Room '" << name << "' created" << endl;
    }
    
    ~Room() {
        cout << "Room '" << name << "' destroyed" << endl;
    }
    
    void display() {
        cout << "Room: " << name << " (Area: " << area << " sq ft)" << endl;
    }
    
    string getName() { return name; }
};

class House {
private:
    string address;
    vector<Room*> rooms;  // Composition: House owns rooms
    
public:
    House(string addr) : address(addr) {
        cout << "House at " << address << " created" << endl;
    }
    
    ~House() {
        cout << "House at " << address << " destroyed" << endl;
        // Clean up rooms (composition - rooms are destroyed with house)
        for(auto room : rooms) {
            delete room;
        }
    }
    
    void addRoom(string roomName, int area) {
        rooms.push_back(new Room(roomName, area));
    }
    
    void displayRooms() {
        cout << "House at " << address << " has rooms:" << endl;
        for(auto room : rooms) {
            room->display();
        }
    }
};

// Composition: Computer owns CPU, RAM, etc.
class CPU {
private:
    string model;
    double speed;
    
public:
    CPU(string m, double s) : model(m), speed(s) {
        cout << "CPU " << model << " created" << endl;
    }
    
    ~CPU() {
        cout << "CPU " << model << " destroyed" << endl;
    }
    
    void process() {
        cout << "CPU " << model << " processing at " << speed << " GHz" << endl;
    }
};

class RAM {
private:
    int capacity;
    string type;
    
public:
    RAM(int cap, string t) : capacity(cap), type(t) {
        cout << "RAM " << capacity << "GB " << type << " created" << endl;
    }
    
    ~RAM() {
        cout << "RAM " << capacity << "GB " << type << " destroyed" << endl;
    }
    
    void store() {
        cout << "RAM storing data in " << capacity << "GB " << type << " memory" << endl;
    }
};

class Computer {
private:
    string brand;
    CPU* cpu;      // Composition: Computer owns CPU
    RAM* ram;      // Composition: Computer owns RAM
    
public:
    Computer(string b, string cpuModel, double cpuSpeed, int ramCap, string ramType) 
        : brand(b) {
        cout << "Computer " << brand << " created" << endl;
        cpu = new CPU(cpuModel, cpuSpeed);
        ram = new RAM(ramCap, ramType);
    }
    
    ~Computer() {
        cout << "Computer " << brand << " destroyed" << endl;
        delete cpu;  // CPU destroyed with computer
        delete ram;  // RAM destroyed with computer
    }
    
    void run() {
        cout << "Computer " << brand << " is running" << endl;
        cpu->process();
        ram->store();
    }
};

// ==========================================
// AGGREGATION EXAMPLES
// ==========================================

// Aggregation: University has Students (students can exist without university)
class StudentInfo {
private:
    string name;
    int studentId;
    string major;
    
public:
    StudentInfo(string n, int id, string m) : name(n), studentId(id), major(m) {
        cout << "Student " << name << " created" << endl;
    }
    
    ~StudentInfo() {
        cout << "Student " << name << " destroyed" << endl;
    }
    
    void study() {
        cout << name << " is studying " << major << endl;
    }
    
    void display() {
        cout << "Student: " << name << " (ID: " << studentId << ", Major: " << major << ")" << endl;
    }
    
    string getName() { return name; }
};

class University {
private:
    string name;
    vector<StudentInfo*> students;  // Aggregation: University has students
    
public:
    University(string n) : name(n) {
        cout << "University " << name << " created" << endl;
    }
    
    ~University() {
        cout << "University " << name << " destroyed" << endl;
        // Note: Students are NOT deleted (aggregation - they can exist independently)
        cout << "Note: Students still exist independently" << endl;
    }
    
    void enrollStudent(StudentInfo* student) {
        students.push_back(student);
        cout << "Student " << student->getName() << " enrolled in " << name << endl;
    }
    
    void displayStudents() {
        cout << "University " << name << " has students:" << endl;
        for(auto student : students) {
            student->display();
        }
    }
    
    void closeUniversity() {
        cout << "University " << name << " is closing" << endl;
        students.clear();  // Remove references but don't delete students
    }
};

// Aggregation: Department has Employees
class Employee {
private:
    string name;
    int employeeId;
    string position;
    
public:
    Employee(string n, int id, string pos) : name(n), employeeId(id), position(pos) {
        cout << "Employee " << name << " created" << endl;
    }
    
    ~Employee() {
        cout << "Employee " << name << " destroyed" << endl;
    }
    
    void work() {
        cout << name << " is working as " << position << endl;
    }
    
    void display() {
        cout << "Employee: " << name << " (ID: " << employeeId << ", Position: " << position << ")" << endl;
    }
    
    string getName() { return name; }
};

class Department {
private:
    string name;
    vector<Employee*> employees;  // Aggregation: Department has employees
    
public:
    Department(string n) : name(n) {
        cout << "Department " << name << " created" << endl;
    }
    
    ~Department() {
        cout << "Department " << name << " destroyed" << endl;
        // Employees are not deleted (they can work elsewhere)
    }
    
    void hireEmployee(Employee* emp) {
        employees.push_back(emp);
        cout << "Employee " << emp->getName() << " hired in " << name << endl;
    }
    
    void displayEmployees() {
        cout << "Department " << name << " has employees:" << endl;
        for(auto emp : employees) {
            emp->display();
        }
    }
    
    void layoffEmployee(string empName) {
        for(auto it = employees.begin(); it != employees.end(); ++it) {
            if((*it)->getName() == empName) {
                cout << "Employee " << empName << " laid off from " << name << endl;
                employees.erase(it);
                break;
            }
        }
    }
};

// ==========================================
// DEMONSTRATION FUNCTIONS
// ==========================================

void demonstrateAssociation() {
    cout << "\n=== ASSOCIATION EXAMPLES ===" << endl;
    
    // Student uses Library
    Library library("Central Library");
    Student student("Alice", 12345);
    student.study(library, "Book1");
    student.returnBookToLibrary(library, "Book1");
    
    // Driver uses Car
    Car car("Toyota Camry", "ABC123");
    Driver driver("Bob", "DL123456");
    driver.drive(car);
    driver.park(car);
}

void demonstrateComposition() {
    cout << "\n=== COMPOSITION EXAMPLES ===" << endl;
    
    // House owns Rooms
    {
        House house("123 Main St");
        house.addRoom("Living Room", 200);
        house.addRoom("Bedroom", 150);
        house.addRoom("Kitchen", 100);
        house.displayRooms();
        // When house goes out of scope, rooms are automatically destroyed
    }
    
    // Computer owns CPU and RAM
    {
        Computer computer("Dell", "Intel i7", 3.2, 16, "DDR4");
        computer.run();
        // When computer goes out of scope, CPU and RAM are automatically destroyed
    }
}

void demonstrateAggregation() {
    cout << "\n=== AGGREGATION EXAMPLES ===" << endl;
    
    // University has Students
    StudentInfo* student1 = new StudentInfo("Charlie", 11111, "Computer Science");
    StudentInfo* student2 = new StudentInfo("Diana", 22222, "Mathematics");
    
    {
        University university("Tech University");
        university.enrollStudent(student1);
        university.enrollStudent(student2);
        university.displayStudents();
        university.closeUniversity();
        // University destroyed, but students still exist
    }
    
    // Students still exist independently
    student1->study();
    student2->study();
    
    // Department has Employees
    Employee* emp1 = new Employee("Eve", 33333, "Manager");
    Employee* emp2 = new Employee("Frank", 44444, "Developer");
    
    {
        Department dept("IT Department");
        dept.hireEmployee(emp1);
        dept.hireEmployee(emp2);
        dept.displayEmployees();
        dept.layoffEmployee("Eve");
        // Department destroyed, but employees still exist
    }
    
    // Employees still exist independently
    emp1->work();
    emp2->work();
    
    // Clean up
    delete student1;
    delete student2;
    delete emp1;
    delete emp2;
}

// ==========================================
// PRACTICE QUESTIONS SOLUTIONS
// ==========================================

// Solution 1: Library Management System
class Book {
private:
    string title, author, isbn;
    bool isAvailable;
    
public:
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}
    
    bool borrow() {
        if(isAvailable) {
            isAvailable = false;
            cout << "Book '" << title << "' borrowed" << endl;
            return true;
        }
        cout << "Book '" << title << "' is not available" << endl;
        return false;
    }
    
    void returnBook() {
        isAvailable = true;
        cout << "Book '" << title << "' returned" << endl;
    }
    
    string getTitle() { return title; }
    bool getAvailability() { return isAvailable; }
};

class LibraryMember {
private:
    string name;
    int memberId;
    vector<Book*> borrowedBooks;  // Association: Member uses Books
    
public:
    LibraryMember(string n, int id) : name(n), memberId(id) {}
    
    void borrowBook(Book* book) {
        if(book->borrow()) {
            borrowedBooks.push_back(book);
        }
    }
    
    void returnBook(Book* book) {
        book->returnBook();
        // Remove from borrowed books
        for(auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if(*it == book) {
                borrowedBooks.erase(it);
                break;
            }
        }
    }
    
    void displayBorrowedBooks() {
        cout << name << "'s borrowed books:" << endl;
        for(auto book : borrowedBooks) {
            cout << "- " << book->getTitle() << endl;
        }
    }
};

// Solution 2: Car Manufacturing System
class Engine {
private:
    string type;
    int horsepower;
    
public:
    Engine(string t, int hp) : type(t), horsepower(hp) {
        cout << "Engine " << type << " created" << endl;
    }
    
    ~Engine() {
        cout << "Engine " << type << " destroyed" << endl;
    }
    
    void start() {
        cout << "Engine " << type << " starting with " << horsepower << " HP" << endl;
    }
};

class Wheel {
private:
    string brand;
    int size;
    
public:
    Wheel(string b, int s) : brand(b), size(s) {
        cout << "Wheel " << brand << " size " << size << " created" << endl;
    }
    
    ~Wheel() {
        cout << "Wheel " << brand << " size " << size << " destroyed" << endl;
    }
    
    void rotate() {
        cout << "Wheel " << brand << " rotating" << endl;
    }
};

class Car {
private:
    string model;
    Engine* engine;        // Composition: Car owns Engine
    vector<Wheel*> wheels; // Composition: Car owns Wheels
    
public:
    Car(string m, string engineType, int hp, string wheelBrand, int wheelSize) 
        : model(m) {
        cout << "Car " << model << " created" << endl;
        engine = new Engine(engineType, hp);
        
        // Create 4 wheels
        for(int i = 0; i < 4; i++) {
            wheels.push_back(new Wheel(wheelBrand, wheelSize));
        }
    }
    
    ~Car() {
        cout << "Car " << model << " destroyed" << endl;
        delete engine;
        for(auto wheel : wheels) {
            delete wheel;
        }
    }
    
    void drive() {
        cout << "Car " << model << " is driving" << endl;
        engine->start();
        for(auto wheel : wheels) {
            wheel->rotate();
        }
    }
};

// Solution 3: School Management System
class Teacher {
private:
    string name;
    string subject;
    
public:
    Teacher(string n, string s) : name(n), subject(s) {
        cout << "Teacher " << name << " created" << endl;
    }
    
    ~Teacher() {
        cout << "Teacher " << name << " destroyed" << endl;
    }
    
    void teach() {
        cout << name << " is teaching " << subject << endl;
    }
    
    string getName() { return name; }
};

class School {
private:
    string name;
    vector<Teacher*> teachers;  // Aggregation: School has Teachers
    
public:
    School(string n) : name(n) {
        cout << "School " << name << " created" << endl;
    }
    
    ~School() {
        cout << "School " << name << " destroyed" << endl;
        // Teachers are not deleted (they can teach elsewhere)
    }
    
    void hireTeacher(Teacher* teacher) {
        teachers.push_back(teacher);
        cout << "Teacher " << teacher->getName() << " hired at " << name << endl;
    }
    
    void displayTeachers() {
        cout << "School " << name << " has teachers:" << endl;
        for(auto teacher : teachers) {
            teacher->teach();
        }
    }
};

// ==========================================
// DEMONSTRATE SOLUTIONS
// ==========================================

void demonstrateSolutions() {
    cout << "\n=== SOLUTION 1: LIBRARY MANAGEMENT ===" << endl;
    Book* book1 = new Book("C++ Programming", "John Doe", "123");
    Book* book2 = new Book("Data Structures", "Jane Smith", "456");
    
    LibraryMember member("Alice", 1001);
    member.borrowBook(book1);
    member.borrowBook(book2);
    member.displayBorrowedBooks();
    member.returnBook(book1);
    
    delete book1;
    delete book2;
    
    cout << "\n=== SOLUTION 2: CAR MANUFACTURING ===" << endl;
    {
        Car car("Toyota", "V6", 300, "Michelin", 17);
        car.drive();
        // Car and its components are destroyed when going out of scope
    }
    
    cout << "\n=== SOLUTION 3: SCHOOL MANAGEMENT ===" << endl;
    Teacher* teacher1 = new Teacher("Mr. Johnson", "Mathematics");
    Teacher* teacher2 = new Teacher("Ms. Davis", "English");
    
    {
        School school("High School");
        school.hireTeacher(teacher1);
        school.hireTeacher(teacher2);
        school.displayTeachers();
        // School destroyed, but teachers still exist
    }
    
    // Teachers still exist independently
    teacher1->teach();
    teacher2->teach();
    
    delete teacher1;
    delete teacher2;
}

// ==========================================
// DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class Part { public: Part() { cout << "Part created"; } ~Part() { cout << "Part destroyed"; } };
class Whole { private: Part* part; public: Whole() { part = new Part(); } ~Whole() { delete part; } };
int main() { Whole w; return 0; }
Answer: Part created Part destroyed

Problem 2: What will be the output?
class Student { public: Student() { cout << "Student created"; } ~Student() { cout << "Student destroyed"; } };
class University { private: vector<Student*> students; public: ~University() { cout << "University destroyed"; } };
int main() { Student* s = new Student(); University u; return 0; }
Answer: Student created University destroyed Student destroyed

Problem 3: What will be the output?
class Tool { public: void use() { cout << "Tool used"; } };
class Worker { public: void work(Tool& t) { t.use(); } };
int main() { Tool tool; Worker worker; worker.work(tool); return 0; }
Answer: Tool used
*/

// ==========================================
// PRACTICE QUESTIONS
// ==========================================

/*
1. Create a library management system:
   - Association: LibraryMember uses Book
   - Include methods for borrowing and returning books

2. Implement a car manufacturing system:
   - Composition: Car owns Engine and Wheels
   - Include methods for starting car and rotating wheels

3. Create a school management system:
   - Aggregation: School has Teachers
   - Include methods for hiring teachers and displaying staff

4. Implement a restaurant system:
   - Association: Customer uses Menu
   - Composition: Restaurant owns Kitchen
   - Aggregation: Restaurant has Waiters

5. Create a hospital management system:
   - Association: Doctor uses MedicalEquipment
   - Composition: Hospital owns OperatingRoom
   - Aggregation: Hospital has Nurses
*/

int main() {
    cout << "ASSOCIATION, COMPOSITION & AGGREGATION IN C++" << endl;
    cout << "=============================================" << endl;
    
    demonstrateAssociation();
    demonstrateComposition();
    demonstrateAggregation();
    demonstrateSolutions();
    
    return 0;
} 