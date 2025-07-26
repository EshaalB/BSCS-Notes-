/*
STRUCTURES PRACTICE QUESTIONS
=============================

This file contains various practice problems using structures:
- Student management system
- Library book management
- Employee payroll system
- Point and Rectangle calculations
- Complex number operations
- Time and Date operations
- Bank account management
- Product inventory system
- Contact management
- Grade book system
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// ========================================
// STRUCTURE DEFINITIONS
// ========================================

struct Student {
    int rollNo;
    string name;
    string course;
    float marks[5];
    float average;
    char grade;
};

struct Book {
    int id;
    string title;
    string author;
    string category;
    bool isAvailable;
    double price;
};

struct Employee {
    int id;
    string name;
    string department;
    double salary;
    int experience;
    string designation;
};

struct Point {
    double x, y;
};

struct Rectangle {
    Point topLeft;
    Point bottomRight;
};

struct Complex {
    double real, imaginary;
};

struct Time {
    int hours, minutes, seconds;
};

struct Date {
    int day, month, year;
};

struct BankAccount {
    string accountNumber;
    string holderName;
    double balance;
    string accountType;
    bool isActive;
};

struct Product {
    int id;
    string name;
    string category;
    double price;
    int stock;
    double rating;
};

struct Contact {
    string name;
    string phone;
    string email;
    string address;
    string group;
};

// ========================================
// HELPER FUNCTIONS
// ========================================

// Function to calculate student average and grade
void calculateStudentStats(Student& student) {
    float sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += student.marks[i];
    }
    student.average = sum / 5.0;
    
    if (student.average >= 90) student.grade = 'A';
    else if (student.average >= 80) student.grade = 'B';
    else if (student.average >= 70) student.grade = 'C';
    else if (student.average >= 60) student.grade = 'D';
    else student.grade = 'F';
}

// Function to calculate distance between two points
double calculateDistance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Function to calculate rectangle area
double calculateArea(Rectangle rect) {
    double width = abs(rect.bottomRight.x - rect.topLeft.x);
    double height = abs(rect.bottomRight.y - rect.topLeft.y);
    return width * height;
}

// Function to add complex numbers
Complex addComplex(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}

// Function to multiply complex numbers
Complex multiplyComplex(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
    result.imaginary = c1.real * c2.imaginary + c1.imaginary * c2.real;
    return result;
}

// Function to add time
Time addTime(Time t1, Time t2) {
    Time result;
    result.seconds = t1.seconds + t2.seconds;
    result.minutes = t1.minutes + t2.minutes;
    result.hours = t1.hours + t2.hours;
    
    if (result.seconds >= 60) {
        result.minutes += result.seconds / 60;
        result.seconds %= 60;
    }
    if (result.minutes >= 60) {
        result.hours += result.minutes / 60;
        result.minutes %= 60;
    }
    
    return result;
}

// Function to check if date is valid
bool isValidDate(Date date) {
    if (date.year < 1900 || date.year > 2100) return false;
    if (date.month < 1 || date.month > 12) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Check for leap year
    if (date.month == 2 && date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    
    return date.day >= 1 && date.day <= daysInMonth[date.month - 1];
}

int main() {
    cout << "STRUCTURES PRACTICE QUESTIONS" << endl;
    cout << "=============================" << endl;

    int choice;
    cout << "\nChoose a practice question (1-10): ";
    cin >> choice;

    if (choice == 1) {
        // 1. Student Management System
        cout << "\n=== 1. Student Management System ===" << endl;
        
        Student students[3];
        
        // Input student data
        for (int i = 0; i < 3; i++) {
            cout << "\nEnter details for Student " << (i+1) << ":" << endl;
            cout << "Roll No: ";
            cin >> students[i].rollNo;
            cin.ignore();
            cout << "Name: ";
            getline(cin, students[i].name);
            cout << "Course: ";
            getline(cin, students[i].course);
            
            cout << "Enter 5 subject marks:" << endl;
            for (int j = 0; j < 5; j++) {
                cout << "Subject " << (j+1) << ": ";
                cin >> students[i].marks[j];
            }
            
            calculateStudentStats(students[i]);
        }
        
        // Display results
        cout << "\nStudent Report:" << endl;
        cout << setw(10) << "Roll No" << setw(20) << "Name" << setw(15) << "Course" 
             << setw(10) << "Average" << setw(8) << "Grade" << endl;
        cout << string(65, '-') << endl;
        
        for (int i = 0; i < 3; i++) {
            cout << setw(10) << students[i].rollNo 
                 << setw(20) << students[i].name 
                 << setw(15) << students[i].course
                 << setw(10) << fixed << setprecision(2) << students[i].average
                 << setw(8) << students[i].grade << endl;
        }
    }
    
    else if (choice == 2) {
        // 2. Library Book Management
        cout << "\n=== 2. Library Book Management ===" << endl;
        
        Book books[5] = {
            {1, "The Great Gatsby", "F. Scott Fitzgerald", "Fiction", true, 15.99},
            {2, "To Kill a Mockingbird", "Harper Lee", "Fiction", true, 12.99},
            {3, "1984", "George Orwell", "Fiction", false, 10.99},
            {4, "Pride and Prejudice", "Jane Austen", "Fiction", true, 9.99},
            {5, "The Hobbit", "J.R.R. Tolkien", "Fantasy", true, 18.99}
        };
        
        cout << "Available Books:" << endl;
        cout << setw(5) << "ID" << setw(25) << "Title" << setw(20) << "Author" 
             << setw(12) << "Category" << setw(10) << "Price" << endl;
        cout << string(75, '-') << endl;
        
        for (int i = 0; i < 5; i++) {
            if (books[i].isAvailable) {
                cout << setw(5) << books[i].id 
                     << setw(25) << books[i].title 
                     << setw(20) << books[i].author
                     << setw(12) << books[i].category
                     << setw(10) << fixed << setprecision(2) << books[i].price << endl;
            }
        }
        
        // Search by category
        string searchCategory;
        cout << "\nEnter category to search: ";
        cin.ignore();
        getline(cin, searchCategory);
        
        cout << "\nBooks in category '" << searchCategory << "':" << endl;
        for (int i = 0; i < 5; i++) {
            if (books[i].category == searchCategory) {
                cout << "- " << books[i].title << " by " << books[i].author << endl;
            }
        }
    }
    
    else if (choice == 3) {
        // 3. Employee Payroll System
        cout << "\n=== 3. Employee Payroll System ===" << endl;
        
        Employee employees[4] = {
            {1001, "John Smith", "Engineering", 75000, 5, "Senior Developer"},
            {1002, "Sarah Johnson", "Marketing", 65000, 3, "Marketing Manager"},
            {1003, "Mike Wilson", "Sales", 55000, 2, "Sales Representative"},
            {1004, "Lisa Brown", "HR", 60000, 4, "HR Specialist"}
        };
        
        cout << "Employee Payroll Report:" << endl;
        cout << setw(8) << "ID" << setw(15) << "Name" << setw(15) << "Department" 
             << setw(15) << "Designation" << setw(10) << "Salary" << endl;
        cout << string(65, '-') << endl;
        
        double totalSalary = 0;
        for (int i = 0; i < 4; i++) {
            cout << setw(8) << employees[i].id 
                 << setw(15) << employees[i].name 
                 << setw(15) << employees[i].department
                 << setw(15) << employees[i].designation
                 << setw(10) << fixed << setprecision(2) << employees[i].salary << endl;
            totalSalary += employees[i].salary;
        }
        
        cout << string(65, '-') << endl;
        cout << "Total Payroll: $" << fixed << setprecision(2) << totalSalary << endl;
        cout << "Average Salary: $" << fixed << setprecision(2) << totalSalary / 4 << endl;
    }
    
    else if (choice == 4) {
        // 4. Point and Rectangle Calculations
        cout << "\n=== 4. Point and Rectangle Calculations ===" << endl;
        
        Point p1, p2;
        cout << "Enter coordinates for Point 1 (x y): ";
        cin >> p1.x >> p1.y;
        cout << "Enter coordinates for Point 2 (x y): ";
        cin >> p2.x >> p2.y;
        
        cout << "Distance between points: " << fixed << setprecision(2) 
             << calculateDistance(p1, p2) << endl;
        
        Rectangle rect;
        rect.topLeft = p1;
        rect.bottomRight = p2;
        
        cout << "Rectangle area: " << fixed << setprecision(2) 
             << calculateArea(rect) << endl;
    }
    
    else if (choice == 5) {
        // 5. Complex Number Operations
        cout << "\n=== 5. Complex Number Operations ===" << endl;
        
        Complex c1, c2;
        cout << "Enter first complex number (real imaginary): ";
        cin >> c1.real >> c1.imaginary;
        cout << "Enter second complex number (real imaginary): ";
        cin >> c2.real >> c2.imaginary;
        
        Complex sum = addComplex(c1, c2);
        Complex product = multiplyComplex(c1, c2);
        
        cout << "Sum: " << sum.real << " + " << sum.imaginary << "i" << endl;
        cout << "Product: " << product.real << " + " << product.imaginary << "i" << endl;
    }
    
    else if (choice == 6) {
        // 6. Time and Date Operations
        cout << "\n=== 6. Time and Date Operations ===" << endl;
        
        Time t1, t2;
        cout << "Enter first time (hours minutes seconds): ";
        cin >> t1.hours >> t1.minutes >> t1.seconds;
        cout << "Enter second time (hours minutes seconds): ";
        cin >> t2.hours >> t2.minutes >> t2.seconds;
        
        Time total = addTime(t1, t2);
        cout << "Total time: " << total.hours << ":" << total.minutes << ":" << total.seconds << endl;
        
        Date date;
        cout << "\nEnter date (day month year): ";
        cin >> date.day >> date.month >> date.year;
        
        if (isValidDate(date)) {
            cout << "Valid date: " << date.day << "/" << date.month << "/" << date.year << endl;
        } else {
            cout << "Invalid date!" << endl;
        }
    }
    
    else if (choice == 7) {
        // 7. Bank Account Management
        cout << "\n=== 7. Bank Account Management ===" << endl;
        
        BankAccount accounts[3] = {
            {"ACC001", "John Doe", 5000.0, "Savings", true},
            {"ACC002", "Jane Smith", 12000.0, "Checking", true},
            {"ACC003", "Bob Wilson", 2500.0, "Savings", false}
        };
        
        cout << "Active Bank Accounts:" << endl;
        cout << setw(10) << "Account" << setw(15) << "Holder" << setw(12) << "Type" 
             << setw(12) << "Balance" << endl;
        cout << string(55, '-') << endl;
        
        double totalBalance = 0;
        int activeCount = 0;
        
        for (int i = 0; i < 3; i++) {
            if (accounts[i].isActive) {
                cout << setw(10) << accounts[i].accountNumber 
                     << setw(15) << accounts[i].holderName
                     << setw(12) << accounts[i].accountType
                     << setw(12) << fixed << setprecision(2) << accounts[i].balance << endl;
                totalBalance += accounts[i].balance;
                activeCount++;
            }
        }
        
        cout << string(55, '-') << endl;
        cout << "Total Balance: $" << fixed << setprecision(2) << totalBalance << endl;
        cout << "Active Accounts: " << activeCount << endl;
    }
    
    else if (choice == 8) {
        // 8. Product Inventory System
        cout << "\n=== 8. Product Inventory System ===" << endl;
        
        Product products[5] = {
            {1, "Laptop", "Electronics", 999.99, 10, 4.5},
            {2, "Smartphone", "Electronics", 699.99, 25, 4.3},
            {3, "Book", "Education", 29.99, 100, 4.7},
            {4, "Headphones", "Electronics", 89.99, 50, 4.2},
            {5, "Notebook", "Stationery", 5.99, 200, 4.0}
        };
        
        cout << "Product Inventory:" << endl;
        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Category" 
             << setw(10) << "Price" << setw(8) << "Stock" << setw(8) << "Rating" << endl;
        cout << string(65, '-') << endl;
        
        for (int i = 0; i < 5; i++) {
            cout << setw(5) << products[i].id 
                 << setw(15) << products[i].name 
                 << setw(15) << products[i].category
                 << setw(10) << fixed << setprecision(2) << products[i].price
                 << setw(8) << products[i].stock
                 << setw(8) << fixed << setprecision(1) << products[i].rating << endl;
        }
        
        // Find low stock items
        cout << "\nLow Stock Items (stock < 20):" << endl;
        for (int i = 0; i < 5; i++) {
            if (products[i].stock < 20) {
                cout << "- " << products[i].name << " (Stock: " << products[i].stock << ")" << endl;
            }
        }
    }
    
    else if (choice == 9) {
        // 9. Contact Management
        cout << "\n=== 9. Contact Management ===" << endl;
        
        Contact contacts[4] = {
            {"John Doe", "555-0101", "john@email.com", "123 Main St", "Family"},
            {"Jane Smith", "555-0102", "jane@email.com", "456 Oak Ave", "Work"},
            {"Bob Wilson", "555-0103", "bob@email.com", "789 Pine Rd", "Friends"},
            {"Alice Brown", "555-0104", "alice@email.com", "321 Elm St", "Work"}
        };
        
        cout << "Contact List:" << endl;
        cout << setw(15) << "Name" << setw(12) << "Phone" << setw(20) << "Email" 
             << setw(15) << "Group" << endl;
        cout << string(65, '-') << endl;
        
        for (int i = 0; i < 4; i++) {
            cout << setw(15) << contacts[i].name 
                 << setw(12) << contacts[i].phone 
                 << setw(20) << contacts[i].email
                 << setw(15) << contacts[i].group << endl;
        }
        
        // Search by group
        string searchGroup;
        cout << "\nEnter group to search: ";
        cin.ignore();
        getline(cin, searchGroup);
        
        cout << "\nContacts in group '" << searchGroup << "':" << endl;
        for (int i = 0; i < 4; i++) {
            if (contacts[i].group == searchGroup) {
                cout << "- " << contacts[i].name << " (" << contacts[i].phone << ")" << endl;
            }
        }
    }
    
    else if (choice == 10) {
        // 10. Grade Book System
        cout << "\n=== 10. Grade Book System ===" << endl;
        
        Student gradeBook[3];
        
        // Input data
        for (int i = 0; i < 3; i++) {
            cout << "\nStudent " << (i+1) << ":" << endl;
            cout << "Name: ";
            cin.ignore();
            getline(cin, gradeBook[i].name);
            cout << "Roll No: ";
            cin >> gradeBook[i].rollNo;
            
            cout << "Enter marks for 5 subjects:" << endl;
            for (int j = 0; j < 5; j++) {
                cout << "Subject " << (j+1) << ": ";
                cin >> gradeBook[i].marks[j];
            }
            
            calculateStudentStats(gradeBook[i]);
        }
        
        // Calculate class statistics
        float classAverage = 0;
        int aCount = 0, bCount = 0, cCount = 0, dCount = 0, fCount = 0;
        
        for (int i = 0; i < 3; i++) {
            classAverage += gradeBook[i].average;
            switch (gradeBook[i].grade) {
                case 'A': aCount++; break;
                case 'B': bCount++; break;
                case 'C': cCount++; break;
                case 'D': dCount++; break;
                case 'F': fCount++; break;
            }
        }
        classAverage /= 3;
        
        cout << "\nClass Statistics:" << endl;
        cout << "Class Average: " << fixed << setprecision(2) << classAverage << endl;
        cout << "Grade Distribution:" << endl;
        cout << "A: " << aCount << " students" << endl;
        cout << "B: " << bCount << " students" << endl;
        cout << "C: " << cCount << " students" << endl;
        cout << "D: " << dCount << " students" << endl;
        cout << "F: " << fCount << " students" << endl;
    }
    
    else {
        cout << "Invalid choice! Please select 1-10." << endl;
    }

    return 0;
} 