/*
==========================================
STUDENT MANAGEMENT SYSTEM QUESTION
==========================================

PROBLEM STATEMENT:
------------------
Create a comprehensive Student Management System with the following requirements:

1. Base Class: Person (name, age, gender)
2. Derived Class: Student (studentId, major, gpa, courses)
3. Derived Class: Teacher (teacherId, department, subjects)
4. Course Class: (courseId, name, credits, instructor)
5. Features:
   - Add/Remove students and teachers
   - Enroll students in courses
   - Calculate GPA
   - Generate reports
   - File handling for data persistence
   - Exception handling for invalid operations

IMPLEMENTATION REQUIREMENTS:
- Use inheritance hierarchy
- Implement encapsulation with proper access modifiers
- Use constructors and destructors
- Implement static members for tracking
- Use friend functions for cross-class operations
- Implement operator overloading for comparisons
- Use templates for generic operations
- Handle exceptions for invalid data
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
using namespace std;

// ==========================================
// EXCEPTION CLASSES
// ==========================================

class StudentException : public exception {
private:
    string message;
public:
    StudentException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class CourseException : public exception {
private:
    string message;
public:
    CourseException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ==========================================
// BASE CLASS: PERSON
// ==========================================

class Person {
protected:
    string name;
    int age;
    string gender;
    static int totalPersons;

public:
    Person(string n, int a, string g) : name(n), age(a), gender(g) {
        totalPersons++;
    }

    virtual ~Person() {
        totalPersons--;
    }

    // Virtual function for polymorphism
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender << endl;
    }

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }

    // Static function
    static int getTotalPersons() { return totalPersons; }

    // Operator overloading for comparison
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }

    bool operator<(const Person& other) const {
        return name < other.name;
    }

    // Friend function for cross-class operations
    friend ostream& operator<<(ostream& os, const Person& person);
};

int Person::totalPersons = 0;

ostream& operator<<(ostream& os, const Person& person) {
    os << "Person: " << person.name << " (" << person.age << ", " << person.gender << ")";
    return os;
}

// ==========================================
// COURSE CLASS
// ==========================================

class Course {
private:
    string courseId;
    string name;
    int credits;
    string instructor;
    vector<string> enrolledStudents;
    static int totalCourses;

public:
    Course(string id, string n, int c, string instr) 
        : courseId(id), name(n), credits(c), instructor(instr) {
        totalCourses++;
    }

    ~Course() {
        totalCourses--;
    }

    // Getters
    string getCourseId() const { return courseId; }
    string getName() const { return name; }
    int getCredits() const { return credits; }
    string getInstructor() const { return instructor; }

    // Enroll student in course
    void enrollStudent(string studentId) {
        if (find(enrolledStudents.begin(), enrolledStudents.end(), studentId) != enrolledStudents.end()) {
            throw CourseException("Student already enrolled in this course");
        }
        enrolledStudents.push_back(studentId);
    }

    // Remove student from course
    void removeStudent(string studentId) {
        auto it = find(enrolledStudents.begin(), enrolledStudents.end(), studentId);
        if (it == enrolledStudents.end()) {
            throw CourseException("Student not enrolled in this course");
        }
        enrolledStudents.erase(it);
    }

    // Display course information
    void display() const {
        cout << "Course ID: " << courseId << endl;
        cout << "Name: " << name << endl;
        cout << "Credits: " << credits << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Enrolled Students: " << enrolledStudents.size() << endl;
    }

    // Static function
    static int getTotalCourses() { return totalCourses; }

    // Operator overloading
    bool operator==(const Course& other) const {
        return courseId == other.courseId;
    }

    friend ostream& operator<<(ostream& os, const Course& course);
};

int Course::totalCourses = 0;

ostream& operator<<(ostream& os, const Course& course) {
    os << "Course: " << course.name << " (ID: " << course.courseId << ", Credits: " << course.credits << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: STUDENT
// ==========================================

class Student : public Person {
private:
    string studentId;
    string major;
    double gpa;
    vector<pair<string, double>> courses; // courseId, grade
    static int totalStudents;

public:
    Student(string n, int a, string g, string id, string m) 
        : Person(n, a, g), studentId(id), major(m), gpa(0.0) {
        totalStudents++;
    }

    ~Student() {
        totalStudents--;
    }

    // Getters
    string getStudentId() const { return studentId; }
    string getMajor() const { return major; }
    double getGpa() const { return gpa; }

    // Add course with grade
    void addCourse(string courseId, double grade) {
        if (grade < 0.0 || grade > 4.0) {
            throw StudentException("Invalid grade. Must be between 0.0 and 4.0");
        }
        
        // Check if course already exists
        for (auto& course : courses) {
            if (course.first == courseId) {
                course.second = grade; // Update existing grade
                calculateGPA();
                return;
            }
        }
        
        courses.push_back({courseId, grade});
        calculateGPA();
    }

    // Remove course
    void removeCourse(string courseId) {
        auto it = find_if(courses.begin(), courses.end(),
            [courseId](const pair<string, double>& course) {
                return course.first == courseId;
            });
        
        if (it != courses.end()) {
            courses.erase(it);
            calculateGPA();
        } else {
            throw StudentException("Course not found for this student");
        }
    }

    // Calculate GPA
    void calculateGPA() {
        if (courses.empty()) {
            gpa = 0.0;
            return;
        }

        double totalPoints = 0.0;
        int totalCredits = 0;

        for (const auto& course : courses) {
            totalPoints += course.second;
            totalCredits++;
        }

        gpa = totalPoints / totalCredits;
    }

    // Override display function
    void display() const override {
        Person::display();
        cout << "Student ID: " << studentId << endl;
        cout << "Major: " << major << endl;
        cout << "GPA: " << fixed << setprecision(2) << gpa << endl;
        cout << "Courses: ";
        for (const auto& course : courses) {
            cout << course.first << "(" << course.second << ") ";
        }
        cout << endl;
    }

    // Static function
    static int getTotalStudents() { return totalStudents; }

    // Operator overloading
    bool operator>(const Student& other) const {
        return gpa > other.gpa;
    }

    friend ostream& operator<<(ostream& os, const Student& student);
};

int Student::totalStudents = 0;

ostream& operator<<(ostream& os, const Student& student) {
    os << "Student: " << student.name << " (ID: " << student.studentId << ", GPA: " << student.gpa << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: TEACHER
// ==========================================

class Teacher : public Person {
private:
    string teacherId;
    string department;
    vector<string> subjects;
    static int totalTeachers;

public:
    Teacher(string n, int a, string g, string id, string dept) 
        : Person(n, a, g), teacherId(id), department(dept) {
        totalTeachers++;
    }

    ~Teacher() {
        totalTeachers--;
    }

    // Getters
    string getTeacherId() const { return teacherId; }
    string getDepartment() const { return department; }

    // Add subject
    void addSubject(string subject) {
        if (find(subjects.begin(), subjects.end(), subject) != subjects.end()) {
            throw StudentException("Subject already exists for this teacher");
        }
        subjects.push_back(subject);
    }

    // Remove subject
    void removeSubject(string subject) {
        auto it = find(subjects.begin(), subjects.end(), subject);
        if (it != subjects.end()) {
            subjects.erase(it);
        } else {
            throw StudentException("Subject not found for this teacher");
        }
    }

    // Override display function
    void display() const override {
        Person::display();
        cout << "Teacher ID: " << teacherId << endl;
        cout << "Department: " << department << endl;
        cout << "Subjects: ";
        for (const auto& subject : subjects) {
            cout << subject << " ";
        }
        cout << endl;
    }

    // Static function
    static int getTotalTeachers() { return totalTeachers; }

    friend ostream& operator<<(ostream& os, const Teacher& teacher);
};

int Teacher::totalTeachers = 0;

ostream& operator<<(ostream& os, const Teacher& teacher) {
    os << "Teacher: " << teacher.name << " (ID: " << teacher.teacherId << ", Dept: " << teacher.department << ")";
    return os;
}

// ==========================================
// TEMPLATE CLASS FOR GENERIC OPERATIONS
// ==========================================

template<typename T>
class DataManager {
private:
    vector<T*> items;

public:
    void addItem(T* item) {
        items.push_back(item);
    }

    void removeItem(T* item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    T* findItem(string id) {
        for (auto item : items) {
            // This requires items to have getId() method
            // For demonstration, we'll use a simple approach
            if (typeid(*item) == typeid(Student)) {
                Student* student = dynamic_cast<Student*>(item);
                if (student && student->getStudentId() == id) return item;
            } else if (typeid(*item) == typeid(Teacher)) {
                Teacher* teacher = dynamic_cast<Teacher*>(item);
                if (teacher && teacher->getTeacherId() == id) return item;
            }
        }
        return nullptr;
    }

    void displayAll() {
        for (auto item : items) {
            item->display();
            cout << "------------------------" << endl;
        }
    }

    int getCount() const { return items.size(); }
};

// ==========================================
// STUDENT MANAGEMENT SYSTEM CLASS
// ==========================================

class StudentManagementSystem {
private:
    DataManager<Person> personManager;
    vector<Course*> courses;
    string dataFile;

public:
    StudentManagementSystem(string filename = "student_data.txt") : dataFile(filename) {}

    ~StudentManagementSystem() {
        // Clean up memory
        for (auto course : courses) {
            delete course;
        }
    }

    // Add student
    void addStudent(string name, int age, string gender, string studentId, string major) {
        try {
            Student* student = new Student(name, age, gender, studentId, major);
            personManager.addItem(student);
            cout << "Student added successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error adding student: " << e.what() << endl;
        }
    }

    // Add teacher
    void addTeacher(string name, int age, string gender, string teacherId, string department) {
        try {
            Teacher* teacher = new Teacher(name, age, gender, teacherId, department);
            personManager.addItem(teacher);
            cout << "Teacher added successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error adding teacher: " << e.what() << endl;
        }
    }

    // Add course
    void addCourse(string courseId, string name, int credits, string instructor) {
        try {
            Course* course = new Course(courseId, name, credits, instructor);
            courses.push_back(course);
            cout << "Course added successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error adding course: " << e.what() << endl;
        }
    }

    // Enroll student in course
    void enrollStudentInCourse(string studentId, string courseId, double grade) {
        try {
            Student* student = dynamic_cast<Student*>(personManager.findItem(studentId));
            if (!student) {
                throw StudentException("Student not found");
            }

            Course* course = nullptr;
            for (auto c : courses) {
                if (c->getCourseId() == courseId) {
                    course = c;
                    break;
                }
            }

            if (!course) {
                throw CourseException("Course not found");
            }

            course->enrollStudent(studentId);
            student->addCourse(courseId, grade);
            cout << "Student enrolled successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error enrolling student: " << e.what() << endl;
        }
    }

    // Generate report
    void generateReport() {
        cout << "\n=== STUDENT MANAGEMENT SYSTEM REPORT ===" << endl;
        cout << "Total Persons: " << Person::getTotalPersons() << endl;
        cout << "Total Students: " << Student::getTotalStudents() << endl;
        cout << "Total Teachers: " << Teacher::getTotalTeachers() << endl;
        cout << "Total Courses: " << Course::getTotalCourses() << endl;
        cout << "\nAll Persons:" << endl;
        personManager.displayAll();
        cout << "\nAll Courses:" << endl;
        for (auto course : courses) {
            course->display();
            cout << "------------------------" << endl;
        }
    }

    // Save data to file
    void saveToFile() {
        ofstream file(dataFile);
        if (file.is_open()) {
            file << "Student Management System Data" << endl;
            file << "==============================" << endl;
            file.close();
            cout << "Data saved to " << dataFile << endl;
        } else {
            cout << "Error saving data to file" << endl;
        }
    }
};

// ==========================================
// DEMONSTRATION FUNCTION
// ==========================================

void demonstrateStudentManagement() {
    cout << "STUDENT MANAGEMENT SYSTEM DEMONSTRATION" << endl;
    cout << "=======================================" << endl;

    StudentManagementSystem sms;

    // Add students
    sms.addStudent("Alice Johnson", 20, "Female", "S001", "Computer Science");
    sms.addStudent("Bob Smith", 22, "Male", "S002", "Mathematics");
    sms.addStudent("Carol Davis", 21, "Female", "S003", "Physics");

    // Add teachers
    sms.addTeacher("Dr. Wilson", 45, "Male", "T001", "Computer Science");
    sms.addTeacher("Prof. Brown", 38, "Female", "T002", "Mathematics");

    // Add courses
    sms.addCourse("CS101", "Introduction to Programming", 3, "Dr. Wilson");
    sms.addCourse("MATH201", "Calculus II", 4, "Prof. Brown");
    sms.addCourse("PHYS101", "Physics I", 4, "Dr. Wilson");

    // Enroll students in courses
    sms.enrollStudentInCourse("S001", "CS101", 3.8);
    sms.enrollStudentInCourse("S001", "MATH201", 3.5);
    sms.enrollStudentInCourse("S002", "MATH201", 4.0);
    sms.enrollStudentInCourse("S003", "PHYS101", 3.2);

    // Generate report
    sms.generateReport();

    // Save data
    sms.saveToFile();
}

// ==========================================
// TRICKY DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class A {
    static int count;
public:
    A() { count++; cout << "A" << count; }
    ~A() { count--; cout << "~A" << count; }
};
int A::count = 0;
int main() {
    A a1, a2;
    { A a3; }
    return 0;
}
Answer: A1A2A3~A2~A1~A0

Problem 2: What will be the output?
class Base {
public:
    virtual void show() { cout << "Base"; }
    ~Base() { cout << "~Base"; }
};
class Derived : public Base {
public:
    void show() { cout << "Derived"; }
    ~Derived() { cout << "~Derived"; }
};
int main() {
    Base* ptr = new Derived();
    ptr->show();
    delete ptr;
    return 0;
}
Answer: Derived~Derived~Base

Problem 3: What will be the output?
class MagicBox {
    int data;
public:
    MagicBox(int x) : data(x) {}
    MagicBox operator+(const MagicBox& other) {
        return MagicBox(data + other.data + 1);
    }
    friend ostream& operator<<(ostream& os, const MagicBox& box) {
        return os << "Box(" << box.data << ")";
    }
};
int main() {
    MagicBox a(5), b(3);
    cout << a + b;
    return 0;
}
Answer: Box(9)
*/

/*
==========================================
PRACTICE DRY RUNS - STUDENT MANAGEMENT
==========================================

Practice Problem 1: Simple Person Class
---------------------------------------
Create a simple Person class with:
- name (string)
- age (int)
- display() method
- constructor and destructor

Practice Problem 2: Basic Inheritance
-------------------------------------
Create a Student class that inherits from Person:
- Add studentId (string)
- Add major (string)
- Override display() method

Practice Problem 3: Static Members
---------------------------------
Add static counter to track total students created.
Create static method to get total count.

Practice Problem 4: Operator Overloading
---------------------------------------
Overload == operator to compare students by studentId.
Overload << operator for output.

Practice Problem 5: Exception Handling
-------------------------------------
Create custom exception for invalid student data.
Throw exception when age < 0 or studentId is empty.

Practice Problem 6: Template Function
------------------------------------
Create template function to find student by any field.
Use with different data types.

Practice Problem 7: Friend Function
----------------------------------
Create friend function to calculate average age of students.
Access private members of Student class.

Practice Problem 8: Virtual Functions
------------------------------------
Create base class with virtual display().
Create derived classes with different display implementations.

Practice Problem 9: File Handling
--------------------------------
Save student data to file and load from file.
Handle file exceptions.

Practice Problem 10: Vector Operations
-------------------------------------
Store multiple students in vector.
Implement add, remove, search, and display all operations.
*/

// ==========================================
// PRACTICE SOLUTIONS
// ==========================================

// Practice 1: Simple Person Class
class SimplePerson {
private:
    string name;
    int age;
public:
    SimplePerson(string n, int a) : name(n), age(a) {
        cout << "Person created: " << name << endl;
    }
    ~SimplePerson() {
        cout << "Person destroyed: " << name << endl;
    }
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// Practice 2: Basic Inheritance
class SimpleStudent : public SimplePerson {
private:
    string studentId;
    string major;
public:
    SimpleStudent(string n, int a, string id, string m) 
        : SimplePerson(n, a), studentId(id), major(m) {}
    
    void display() const override {
        cout << "Student - Name: " << getName() << ", ID: " << studentId 
             << ", Major: " << major << endl;
    }
    
    string getName() const { return name; } // This would need to be protected in base
};

// Practice 3: Static Members
class StudentCounter {
private:
    string name;
    static int totalStudents;
public:
    StudentCounter(string n) : name(n) {
        totalStudents++;
    }
    ~StudentCounter() {
        totalStudents--;
    }
    static int getTotal() { return totalStudents; }
};
int StudentCounter::totalStudents = 0;

// Practice 4: Operator Overloading
class StudentOp {
private:
    string studentId;
    string name;
public:
    StudentOp(string id, string n) : studentId(id), name(n) {}
    
    bool operator==(const StudentOp& other) const {
        return studentId == other.studentId;
    }
    
    friend ostream& operator<<(ostream& os, const StudentOp& s) {
        os << "Student[" << s.studentId << ": " << s.name << "]";
        return os;
    }
    
    string getId() const { return studentId; }
    string getName() const { return name; }
};

// Practice 5: Exception Handling
class StudentException : public exception {
private:
    string message;
public:
    StudentException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class StudentValid {
private:
    string studentId;
    int age;
public:
    StudentValid(string id, int a) {
        if (a < 0) throw StudentException("Age cannot be negative");
        if (id.empty()) throw StudentException("Student ID cannot be empty");
        studentId = id;
        age = a;
    }
};

// Practice 6: Template Function
template<typename T>
T* findStudent(vector<T*>& students, string field, string value) {
    for (auto student : students) {
        if (student->getId() == value || student->getName() == value) {
            return student;
        }
    }
    return nullptr;
}

// Practice 7: Friend Function
class StudentFriend {
private:
    string name;
    int age;
    static vector<StudentFriend*> allStudents;
public:
    StudentFriend(string n, int a) : name(n), age(a) {
        allStudents.push_back(this);
    }
    
    friend double calculateAverageAge() {
        if (allStudents.empty()) return 0.0;
        int total = 0;
        for (auto student : allStudents) {
            total += student->age;
        }
        return static_cast<double>(total) / allStudents.size();
    }
    
    string getName() const { return name; }
    int getAge() const { return age; }
};
vector<StudentFriend*> StudentFriend::allStudents;

// Practice 8: Virtual Functions
class VirtualPerson {
protected:
    string name;
public:
    VirtualPerson(string n) : name(n) {}
    virtual void display() const {
        cout << "Person: " << name << endl;
    }
    virtual ~VirtualPerson() {}
};

class VirtualStudent : public VirtualPerson {
private:
    string major;
public:
    VirtualStudent(string n, string m) : VirtualPerson(n), major(m) {}
    void display() const override {
        cout << "Student: " << name << " (Major: " << major << ")" << endl;
    }
};

class VirtualTeacher : public VirtualPerson {
private:
    string department;
public:
    VirtualTeacher(string n, string d) : VirtualPerson(n), department(d) {}
    void display() const override {
        cout << "Teacher: " << name << " (Dept: " << department << ")" << endl;
    }
};

// Practice 9: File Handling
class FileStudent {
private:
    string name;
    string studentId;
public:
    FileStudent(string n, string id) : name(n), studentId(id) {}
    
    void saveToFile(ofstream& file) {
        file << name << "," << studentId << endl;
    }
    
    static FileStudent* loadFromFile(ifstream& file) {
        string line;
        if (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string name = line.substr(0, pos);
                string id = line.substr(pos + 1);
                return new FileStudent(name, id);
            }
        }
        return nullptr;
    }
    
    void display() const {
        cout << "FileStudent: " << name << " (" << studentId << ")" << endl;
    }
};

// Practice 10: Vector Operations
class VectorStudent {
private:
    string name;
    string studentId;
public:
    VectorStudent(string n, string id) : name(n), studentId(id) {}
    
    string getName() const { return name; }
    string getId() const { return studentId; }
    
    void display() const {
        cout << "VectorStudent: " << name << " (" << studentId << ")" << endl;
    }
};

class StudentManager {
private:
    vector<VectorStudent*> students;
public:
    void addStudent(VectorStudent* student) {
        students.push_back(student);
    }
    
    void removeStudent(string studentId) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if ((*it)->getId() == studentId) {
                delete *it;
                students.erase(it);
                break;
            }
        }
    }
    
    VectorStudent* findStudent(string studentId) {
        for (auto student : students) {
            if (student->getId() == studentId) {
                return student;
            }
        }
        return nullptr;
    }
    
    void displayAll() {
        for (auto student : students) {
            student->display();
        }
    }
    
    ~StudentManager() {
        for (auto student : students) {
            delete student;
        }
    }
};

// ==========================================
// PRACTICE DEMONSTRATION
// ==========================================

void demonstratePracticeProblems() {
    cout << "\n=== PRACTICE PROBLEMS DEMONSTRATION ===\n";
    
    // Practice 1: Simple Person
    cout << "\n1. Simple Person Class:";
    SimplePerson p1("Alice", 20);
    p1.display();
    
    // Practice 2: Basic Inheritance
    cout << "\n2. Basic Inheritance:";
    SimpleStudent s1("Bob", 19, "S001", "Computer Science");
    s1.display();
    
    // Practice 3: Static Members
    cout << "\n3. Static Members:";
    StudentCounter sc1("Charlie");
    StudentCounter sc2("David");
    cout << "Total students: " << StudentCounter::getTotal() << endl;
    
    // Practice 4: Operator Overloading
    cout << "\n4. Operator Overloading:";
    StudentOp so1("S001", "Eve");
    StudentOp so2("S001", "Frank");
    StudentOp so3("S002", "Grace");
    cout << "so1: " << so1 << endl;
    cout << "so1 == so2: " << (so1 == so2) << endl;
    cout << "so1 == so3: " << (so1 == so3) << endl;
    
    // Practice 5: Exception Handling
    cout << "\n5. Exception Handling:";
    try {
        StudentValid sv1("S001", 20);
        cout << "Valid student created" << endl;
        // StudentValid sv2("", 20); // This would throw exception
    } catch (const StudentException& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
    // Practice 6: Template Function
    cout << "\n6. Template Function:";
    vector<StudentOp*> students = {new StudentOp("S001", "Alice"), new StudentOp("S002", "Bob")};
    StudentOp* found = findStudent(students, "name", "Alice");
    if (found) cout << "Found: " << *found << endl;
    
    // Practice 7: Friend Function
    cout << "\n7. Friend Function:";
    StudentFriend sf1("Alice", 20);
    StudentFriend sf2("Bob", 22);
    cout << "Average age: " << calculateAverageAge() << endl;
    
    // Practice 8: Virtual Functions
    cout << "\n8. Virtual Functions:";
    VirtualPerson* vp1 = new VirtualStudent("Charlie", "Math");
    VirtualPerson* vp2 = new VirtualTeacher("David", "Physics");
    vp1->display();
    vp2->display();
    delete vp1;
    delete vp2;
    
    // Practice 9: File Handling
    cout << "\n9. File Handling:";
    ofstream outFile("practice_students.txt");
    FileStudent fs1("Eve", "S001");
    FileStudent fs2("Frank", "S002");
    fs1.saveToFile(outFile);
    fs2.saveToFile(outFile);
    outFile.close();
    
    ifstream inFile("practice_students.txt");
    FileStudent* loaded1 = FileStudent::loadFromFile(inFile);
    FileStudent* loaded2 = FileStudent::loadFromFile(inFile);
    if (loaded1) loaded1->display();
    if (loaded2) loaded2->display();
    inFile.close();
    delete loaded1;
    delete loaded2;
    
    // Practice 10: Vector Operations
    cout << "\n10. Vector Operations:";
    StudentManager manager;
    manager.addStudent(new VectorStudent("Grace", "S001"));
    manager.addStudent(new VectorStudent("Henry", "S002"));
    manager.displayAll();
    VectorStudent* found_student = manager.findStudent("S001");
    if (found_student) found_student->display();
    
    // Cleanup
    for (auto student : students) {
        delete student;
    }
}

int main() {
    demonstrateStudentManagement();
    return 0;
} 