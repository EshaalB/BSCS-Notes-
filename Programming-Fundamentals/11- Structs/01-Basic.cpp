/*
Structures in C++ - Basic Concepts
==================================

Structures (structs) are user-defined data types that group related data together.
They allow you to create custom data types that can hold multiple values of different types.

Key Concepts:
1. Structure Definition
2. Structure Variables
3. Accessing Members
4. Nested Structures
5. Arrays of Structures
6. Structures as Function Parameters
*/

#include <iostream>
#include <string>
using namespace std;

// ========================================
// 1. BASIC STRUCTURE DEFINITION
// ========================================
struct Person {
    string name;    // Member variable
    int age;        // Member variable
    string city;    // Member variable
};

// ========================================
// 2. STRUCTURE WITH DIFFERENT DATA TYPES
// ========================================
struct Student {
    int rollNo;
    string name;
    float gpa;
    char grade;
    bool isActive;
};

// ========================================
// 3. NESTED STRUCTURE
// ========================================
struct Address {
    string street;
    string city;
    string state;
    int zipCode;
};

struct Employee {
    int id;
    string name;
    Address address;  // Nested structure
    double salary;
};

// ========================================
// 4. STRUCTURE WITH ARRAYS
// ========================================
struct Course {
    string name;
    int credits;
    int marks[5];  // Array as member
};

int main() {
    cout << "=== STRUCTURES BASICS ===\n\n";

    // ========================================
    // 1. CREATING AND USING STRUCTURE VARIABLES
    // ========================================
    cout << "1. Basic Structure Usage:\n";
    
    // Create a Person structure variable
    Person person1;
    
    // Assign values to members using dot operator
    person1.name = "John Doe";
    person1.age = 25;
    person1.city = "New York";
    
    // Access and display members
    cout << "   Name: " << person1.name << endl;
    cout << "   Age: " << person1.age << endl;
    cout << "   City: " << person1.city << endl;
    
    cout << endl;

    // ========================================
    // 2. INITIALIZING STRUCTURES
    // ========================================
    cout << "2. Structure Initialization:\n";
    
    // Method 1: Initialize during declaration
    Person person2 = {"Jane Smith", 30, "Los Angeles"};
    
    // Method 2: Create and assign later
    Student student1;
    student1.rollNo = 101;
    student1.name = "Alice Johnson";
    student1.gpa = 3.8;
    student1.grade = 'A';
    student1.isActive = true;
    
    cout << "   Student: " << student1.name << " (Roll: " << student1.rollNo << ")" << endl;
    cout << "   GPA: " << student1.gpa << ", Grade: " << student1.grade << endl;
    
    cout << endl;

    // ========================================
    // 3. NESTED STRUCTURE USAGE
    // ========================================
    cout << "3. Nested Structure:\n";
    
    Employee emp1;
    emp1.id = 1001;
    emp1.name = "Bob Wilson";
    emp1.address.street = "123 Main St";
    emp1.address.city = "Chicago";
    emp1.address.state = "IL";
    emp1.address.zipCode = 60601;
    emp1.salary = 75000.0;
    
    cout << "   Employee: " << emp1.name << " (ID: " << emp1.id << ")" << endl;
    cout << "   Address: " << emp1.address.street << ", " << emp1.address.city << endl;
    cout << "   Salary: $" << emp1.salary << endl;
    
    cout << endl;

    // ========================================
    // 4. ARRAY OF STRUCTURES
    // ========================================
    cout << "4. Array of Structures:\n";
    
    Person people[3] = {
        {"Tom", 28, "Boston"},
        {"Sarah", 32, "Miami"},
        {"Mike", 24, "Seattle"}
    };
    
    cout << "   People List:\n";
    for (int i = 0; i < 3; i++) {
        cout << "   " << (i+1) << ". " << people[i].name 
             << " (" << people[i].age << " years, " << people[i].city << ")" << endl;
    }
    
    cout << endl;

    // ========================================
    // 5. STRUCTURE WITH ARRAY MEMBER
    // ========================================
    cout << "5. Structure with Array Member:\n";
    
    Course course1;
    course1.name = "Programming";
    course1.credits = 3;
    
    // Assign values to array member
    course1.marks[0] = 85;
    course1.marks[1] = 90;
    course1.marks[2] = 88;
    course1.marks[3] = 92;
    course1.marks[4] = 87;
    
    cout << "   Course: " << course1.name << " (" << course1.credits << " credits)" << endl;
    cout << "   Marks: ";
    for (int i = 0; i < 5; i++) {
        cout << course1.marks[i];
        if (i < 4) cout << ", ";
    }
    cout << endl;
    
    cout << endl;

    // ========================================
    // 6. COPYING STRUCTURES
    // ========================================
    cout << "6. Structure Assignment:\n";
    
    Person original = {"David", 35, "Denver"};
    Person copy = original;  // Copy all members
    
    cout << "   Original: " << original.name << " from " << original.city << endl;
    cout << "   Copy: " << copy.name << " from " << copy.city << endl;
    
    // Modify copy
    copy.city = "Phoenix";
    cout << "   After modification - Copy: " << copy.name << " from " << copy.city << endl;
    cout << "   Original unchanged: " << original.name << " from " << original.city << endl;

    return 0;
}

/*
SUMMARY OF KEY CONCEPTS:
========================

1. Structure Definition:
   - Use 'struct' keyword followed by structure name
   - Define member variables inside curly braces
   - End with semicolon

2. Creating Structure Variables:
   - struct_name variable_name;
   - Access members using dot operator (.)

3. Member Access:
   - variable.member_name
   - For nested structures: outer.inner.member

4. Initialization:
   - During declaration: struct_name var = {val1, val2, ...};
   - After declaration: var.member = value;

5. Arrays of Structures:
   - struct_name array_name[size];
   - Access: array_name[index].member

6. Structure Assignment:
   - Direct assignment copies all members
   - Changes to copy don't affect original

7. Common Use Cases:
   - Grouping related data
   - Creating custom data types
   - Organizing complex information
   - Building larger data structures
*/ 