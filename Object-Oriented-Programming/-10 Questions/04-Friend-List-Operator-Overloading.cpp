/*
==========================================
FRIEND LIST USING FRIEND FUNCTION AND OPERATOR OVERLOADING
==========================================

PROBLEM STATEMENT:
------------------
Create a Friend List Management System with the following requirements:

1. Friend Class: (friendId, name, age, phone, email, friendshipLevel)
2. FriendList Class: (listName, friends vector, capacity)
3. Features:
   - Add/Remove friends
   - Search friends by various criteria
   - Sort friends by different attributes
   - Display friend information

IMPLEMENTATION REQUIREMENTS:
- Use friend functions for cross-class operations
- Implement extensive operator overloading including:
  * Arithmetic operators (+, -, *, /)
  * Comparison operators (==, !=, <, >, <=, >=)
  * Assignment operators (=, +=, -=)
  * Increment/Decrement operators (++, --)
  * Subscript operator []
  * Function call operator ()
  * Type conversion operators
- Use ostream and istream operators for input/output
- Implement templates for generic operations
- Use exception handling for invalid operations
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

// ==========================================
// EXCEPTION CLASSES
// ==========================================

class FriendException : public exception {
private:
    string message;
public:
    FriendException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class ListException : public exception {
private:
    string message;
public:
    ListException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ==========================================
// FRIEND CLASS
// ==========================================

class Friend {
private:
    int friendId;
    string name;
    int age;
    string phone;
    string email;
    int friendshipLevel; // 1-10 scale
    static int friendCounter;

public:
    // Constructors
    Friend() : friendId(0), name(""), age(0), phone(""), email(""), friendshipLevel(1) {
        friendCounter++;
    }

    Friend(string n, int a, string p, string e, int level = 5) 
        : name(n), age(a), phone(p), email(e), friendshipLevel(level) {
        friendCounter++;
        friendId = friendCounter;
        
        if (friendshipLevel < 1 || friendshipLevel > 10) {
            throw FriendException("Friendship level must be between 1 and 10");
        }
    }

    // Copy constructor
    Friend(const Friend& other) 
        : friendId(other.friendId), name(other.name), age(other.age), 
          phone(other.phone), email(other.email), friendshipLevel(other.friendshipLevel) {
        friendCounter++;
    }

    // Destructor
    ~Friend() {
        friendCounter--;
    }

    // Getters
    int getFriendId() const { return friendId; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
    int getFriendshipLevel() const { return friendshipLevel; }

    // Setters
    void setName(string n) { name = n; }
    void setAge(int a) { 
        if (a < 0 || a > 150) {
            throw FriendException("Invalid age");
        }
        age = a; 
    }
    void setPhone(string p) { phone = p; }
    void setEmail(string e) { email = e; }
    void setFriendshipLevel(int level) { 
        if (level < 1 || level > 10) {
            throw FriendException("Friendship level must be between 1 and 10");
        }
        friendshipLevel = level; 
    }

    // Display friend information
    void display() const {
        cout << "Friend ID: " << friendId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "Friendship Level: " << friendshipLevel << "/10" << endl;
    }

    // Static function
    static int getFriendCounter() { return friendCounter; }

    // ==========================================
    // OPERATOR OVERLOADING
    // ==========================================

    // Assignment operator
    Friend& operator=(const Friend& other) {
        if (this != &other) {
            friendId = other.friendId;
            name = other.name;
            age = other.age;
            phone = other.phone;
            email = other.email;
            friendshipLevel = other.friendshipLevel;
        }
        return *this;
    }

    // Arithmetic operators
    Friend operator+(const Friend& other) const {
        // Combine friendship levels
        int newLevel = min(10, friendshipLevel + other.friendshipLevel);
        return Friend(name + " & " + other.name, (age + other.age) / 2, 
                     phone, email, newLevel);
    }

    Friend operator-(const Friend& other) const {
        // Subtract friendship levels
        int newLevel = max(1, friendshipLevel - other.friendshipLevel);
        return Friend(name, age, phone, email, newLevel);
    }

    Friend operator*(int factor) const {
        // Multiply friendship level
        int newLevel = min(10, friendshipLevel * factor);
        return Friend(name, age, phone, email, newLevel);
    }

    Friend operator/(int divisor) const {
        if (divisor == 0) {
            throw FriendException("Division by zero");
        }
        int newLevel = max(1, friendshipLevel / divisor);
        return Friend(name, age, phone, email, newLevel);
    }

    // Compound assignment operators
    Friend& operator+=(const Friend& other) {
        friendshipLevel = min(10, friendshipLevel + other.friendshipLevel);
        return *this;
    }

    Friend& operator-=(const Friend& other) {
        friendshipLevel = max(1, friendshipLevel - other.friendshipLevel);
        return *this;
    }

    Friend& operator*=(int factor) {
        friendshipLevel = min(10, friendshipLevel * factor);
        return *this;
    }

    Friend& operator/=(int divisor) {
        if (divisor == 0) {
            throw FriendException("Division by zero");
        }
        friendshipLevel = max(1, friendshipLevel / divisor);
        return *this;
    }

    // Increment/Decrement operators
    Friend& operator++() {
        // Pre-increment
        friendshipLevel = min(10, friendshipLevel + 1);
        return *this;
    }

    Friend operator++(int) {
        // Post-increment
        Friend temp = *this;
        friendshipLevel = min(10, friendshipLevel + 1);
        return temp;
    }

    Friend& operator--() {
        // Pre-decrement
        friendshipLevel = max(1, friendshipLevel - 1);
        return *this;
    }

    Friend operator--(int) {
        // Post-decrement
        Friend temp = *this;
        friendshipLevel = max(1, friendshipLevel - 1);
        return temp;
    }

    // Comparison operators
    bool operator==(const Friend& other) const {
        return friendId == other.friendId;
    }

    bool operator!=(const Friend& other) const {
        return !(*this == other);
    }

    bool operator<(const Friend& other) const {
        return friendshipLevel < other.friendshipLevel;
    }

    bool operator>(const Friend& other) const {
        return friendshipLevel > other.friendshipLevel;
    }

    bool operator<=(const Friend& other) const {
        return friendshipLevel <= other.friendshipLevel;
    }

    bool operator>=(const Friend& other) const {
        return friendshipLevel >= other.friendshipLevel;
    }

    // Function call operator - returns friendship score
    int operator()() const {
        return friendshipLevel * 10; // Convert to percentage
    }

    // Type conversion operators
    operator string() const {
        return name + " (Level " + to_string(friendshipLevel) + ")";
    }

    operator int() const {
        return friendshipLevel;
    }

    // Friend functions for input/output
    friend ostream& operator<<(ostream& os, const Friend& f);
    friend istream& operator>>(istream& is, Friend& f);
    
    // Friend function for cross-class operations
    friend class FriendList;
};

int Friend::friendCounter = 0;

// ==========================================
// OSTREAM AND ISTREAM OPERATORS
// ==========================================

ostream& operator<<(ostream& os, const Friend& f) {
    os << "Friend[" << f.friendId << "]: " << f.name 
       << " (Age: " << f.age << ", Level: " << f.friendshipLevel << "/10)";
    return os;
}

istream& operator>>(istream& is, Friend& f) {
    cout << "Enter friend details:" << endl;
    cout << "Name: ";
    is >> f.name;
    cout << "Age: ";
    is >> f.age;
    cout << "Phone: ";
    is >> f.phone;
    cout << "Email: ";
    is >> f.email;
    cout << "Friendship Level (1-10): ";
    is >> f.friendshipLevel;
    
    if (f.friendshipLevel < 1 || f.friendshipLevel > 10) {
        throw FriendException("Friendship level must be between 1 and 10");
    }
    
    return is;
}

// ==========================================
// FRIENDLIST CLASS
// ==========================================

class FriendList {
private:
    string listName;
    vector<Friend> friends;
    int capacity;
    static int listCounter;

public:
    // Constructors
    FriendList(string name = "My Friends", int cap = 100) 
        : listName(name), capacity(cap) {
        listCounter++;
    }

    // Copy constructor
    FriendList(const FriendList& other) 
        : listName(other.listName), friends(other.friends), capacity(other.capacity) {
        listCounter++;
    }

    // Destructor
    ~FriendList() {
        listCounter--;
    }

    // Getters
    string getListName() const { return listName; }
    int getCapacity() const { return capacity; }
    int getSize() const { return friends.size(); }
    bool isEmpty() const { return friends.empty(); }
    bool isFull() const { return friends.size() >= capacity; }

    // Add friend
    void addFriend(const Friend& f) {
        if (isFull()) {
            throw ListException("Friend list is full");
        }
        friends.push_back(f);
    }

    // Remove friend by ID
    void removeFriend(int friendId) {
        auto it = find_if(friends.begin(), friends.end(),
            [friendId](const Friend& f) { return f.getFriendId() == friendId; });
        
        if (it != friends.end()) {
            friends.erase(it);
        } else {
            throw ListException("Friend not found");
        }
    }

    // Search friend by name
    Friend* findFriendByName(string name) {
        for (auto& f : friends) {
            if (f.getName() == name) {
                return &f;
            }
        }
        return nullptr;
    }

    // Search friend by ID
    Friend* findFriendById(int friendId) {
        for (auto& f : friends) {
            if (f.getFriendId() == friendId) {
                return &f;
            }
        }
        return nullptr;
    }

    // Sort friends by friendship level
    void sortByFriendshipLevel() {
        sort(friends.begin(), friends.end());
    }

    // Sort friends by name
    void sortByName() {
        sort(friends.begin(), friends.end(),
            [](const Friend& a, const Friend& b) { return a.getName() < b.getName(); });
    }

    // Sort friends by age
    void sortByAge() {
        sort(friends.begin(), friends.end(),
            [](const Friend& a, const Friend& b) { return a.getAge() < b.getAge(); });
    }

    // Display all friends
    void displayAll() const {
        cout << "\n=== " << listName << " ===" << endl;
        cout << "Total Friends: " << friends.size() << "/" << capacity << endl;
        cout << "================================" << endl;
        
        for (const auto& f : friends) {
            f.display();
            cout << "------------------------" << endl;
        }
    }

    // Calculate statistics
    void calculateStatistics() const {
        if (friends.empty()) {
            cout << "No friends in the list" << endl;
            return;
        }

        int totalLevel = 0;
        int minLevel = 10, maxLevel = 1;
        int totalAge = 0;
        int minAge = 150, maxAge = 0;

        for (const auto& f : friends) {
            totalLevel += f.getFriendshipLevel();
            minLevel = min(minLevel, f.getFriendshipLevel());
            maxLevel = max(maxLevel, f.getFriendshipLevel());
            
            totalAge += f.getAge();
            minAge = min(minAge, f.getAge());
            maxAge = max(maxAge, f.getAge());
        }

        cout << "\n=== FRIEND LIST STATISTICS ===" << endl;
        cout << "Total Friends: " << friends.size() << endl;
        cout << "Average Friendship Level: " << (double)totalLevel / friends.size() << "/10" << endl;
        cout << "Min Friendship Level: " << minLevel << "/10" << endl;
        cout << "Max Friendship Level: " << maxLevel << "/10" << endl;
        cout << "Average Age: " << (double)totalAge / friends.size() << endl;
        cout << "Age Range: " << minAge << " - " << maxAge << endl;
    }

    // Static function
    static int getListCounter() { return listCounter; }

    // ==========================================
    // OPERATOR OVERLOADING
    // ==========================================

    // Assignment operator
    FriendList& operator=(const FriendList& other) {
        if (this != &other) {
            listName = other.listName;
            friends = other.friends;
            capacity = other.capacity;
        }
        return *this;
    }

    // Addition operator - combine two friend lists
    FriendList operator+(const FriendList& other) const {
        FriendList combined(listName + " + " + other.listName, capacity + other.capacity);
        
        // Add friends from both lists
        for (const auto& f : friends) {
            combined.addFriend(f);
        }
        for (const auto& f : other.friends) {
            combined.addFriend(f);
        }
        
        return combined;
    }

    // Compound assignment operator
    FriendList& operator+=(const FriendList& other) {
        for (const auto& f : other.friends) {
            if (!isFull()) {
                addFriend(f);
            }
        }
        return *this;
    }

    // Subtraction operator - remove common friends
    FriendList operator-(const FriendList& other) const {
        FriendList result(listName + " - " + other.listName, capacity);
        
        for (const auto& f : friends) {
            bool found = false;
            for (const auto& otherF : other.friends) {
                if (f == otherF) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                result.addFriend(f);
            }
        }
        
        return result;
    }

    // Subscript operator - access friend by index
    Friend& operator[](int index) {
        if (index < 0 || index >= friends.size()) {
            throw ListException("Index out of bounds");
        }
        return friends[index];
    }

    const Friend& operator[](int index) const {
        if (index < 0 || index >= friends.size()) {
            throw ListException("Index out of bounds");
        }
        return friends[index];
    }

    // Function call operator - filter friends by criteria
    vector<Friend> operator()(function<bool(const Friend&)> predicate) const {
        vector<Friend> filtered;
        for (const auto& f : friends) {
            if (predicate(f)) {
                filtered.push_back(f);
            }
        }
        return filtered;
    }

    // Comparison operators
    bool operator==(const FriendList& other) const {
        return friends.size() == other.friends.size() && 
               listName == other.listName;
    }

    bool operator!=(const FriendList& other) const {
        return !(*this == other);
    }

    bool operator<(const FriendList& other) const {
        return friends.size() < other.friends.size();
    }

    bool operator>(const FriendList& other) const {
        return friends.size() > other.friends.size();
    }

    // Type conversion operators
    operator int() const {
        return friends.size();
    }

    operator string() const {
        return listName + " (" + to_string(friends.size()) + " friends)";
    }

    // Friend functions for input/output
    friend ostream& operator<<(ostream& os, const FriendList& fl);
    friend istream& operator>>(istream& is, FriendList& fl);
};

int FriendList::listCounter = 0;

// ==========================================
// OSTREAM AND ISTREAM OPERATORS FOR FRIENDLIST
// ==========================================

ostream& operator<<(ostream& os, const FriendList& fl) {
    os << "FriendList: " << fl.listName << " [" << fl.friends.size() << "/" << fl.capacity << " friends]";
    return os;
}

istream& operator>>(istream& is, FriendList& fl) {
    cout << "Enter friend list details:" << endl;
    cout << "List Name: ";
    is >> fl.listName;
    cout << "Capacity: ";
    is >> fl.capacity;
    return is;
}

// ==========================================
// TEMPLATE CLASS FOR GENERIC OPERATIONS
// ==========================================

template<typename T>
class FriendManager {
private:
    vector<T> items;

public:
    void addItem(const T& item) {
        items.push_back(item);
    }

    void removeItem(const T& item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    void displayAll() {
        for (const auto& item : items) {
            cout << item << endl;
        }
    }

    int getCount() const { return items.size(); }
};

// ==========================================
// FRIEND LIST MANAGEMENT SYSTEM CLASS
// ==========================================

class FriendListManagementSystem {
private:
    vector<FriendList> lists;
    string dataFile;

public:
    FriendListManagementSystem(string filename = "friends_data.txt") : dataFile(filename) {}

    ~FriendListManagementSystem() {
        cout << "Friend List Management System shutting down..." << endl;
    }

    // Create friend list
    void createList(string name, int capacity) {
        try {
            FriendList newList(name, capacity);
            lists.push_back(newList);
            cout << "Friend list '" << name << "' created successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error creating friend list: " << e.what() << endl;
        }
    }

    // Add friend to list
    void addFriendToList(string listName, const Friend& f) {
        try {
            for (auto& list : lists) {
                if (list.getListName() == listName) {
                    list.addFriend(f);
                    cout << "Friend added to list '" << listName << "' successfully!" << endl;
                    return;
                }
            }
            throw ListException("List not found: " + listName);
        } catch (const exception& e) {
            cout << "Error adding friend: " << e.what() << endl;
        }
    }

    // Remove friend from list
    void removeFriendFromList(string listName, int friendId) {
        try {
            for (auto& list : lists) {
                if (list.getListName() == listName) {
                    list.removeFriend(friendId);
                    cout << "Friend removed from list '" << listName << "' successfully!" << endl;
                    return;
                }
            }
            throw ListException("List not found: " + listName);
        } catch (const exception& e) {
            cout << "Error removing friend: " << e.what() << endl;
        }
    }

    // Search friend in all lists
    void searchFriend(string name) {
        cout << "\nSearching for friend: " << name << endl;
        cout << "================================" << endl;
        
        bool found = false;
        for (auto& list : lists) {
            Friend* f = list.findFriendByName(name);
            if (f) {
                cout << "Found in list: " << list.getListName() << endl;
                f->display();
                found = true;
            }
        }
        
        if (!found) {
            cout << "Friend not found in any list" << endl;
        }
    }

    // Generate system report
    void generateReport() {
        cout << "\n=== FRIEND LIST MANAGEMENT SYSTEM REPORT ===" << endl;
        cout << "Total Lists: " << FriendList::getListCounter() << endl;
        cout << "Total Friends: " << Friend::getFriendCounter() << endl;
        
        for (auto& list : lists) {
            cout << "\nList: " << list.getListName() << endl;
            cout << "Size: " << list.getSize() << "/" << list.getCapacity() << endl;
            list.calculateStatistics();
        }
    }

    // Save data to file
    void saveToFile() {
        ofstream file(dataFile);
        if (file.is_open()) {
            file << "Friend List Management System Data" << endl;
            file << "==================================" << endl;
            file << "Generated on: " << __DATE__ << " " << __TIME__ << endl;
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

void demonstrateFriendListSystem() {
    cout << "FRIEND LIST MANAGEMENT SYSTEM DEMONSTRATION" << endl;
    cout << "===========================================" << endl;

    FriendListManagementSystem flms;

    // Create friend lists
    flms.createList("Close Friends", 50);
    flms.createList("Work Friends", 30);
    flms.createList("School Friends", 40);

    // Create friends
    Friend f1("Alice Johnson", 25, "555-0101", "alice@email.com", 9);
    Friend f2("Bob Smith", 30, "555-0102", "bob@email.com", 7);
    Friend f3("Carol Davis", 28, "555-0103", "carol@email.com", 8);
    Friend f4("David Wilson", 35, "555-0104", "david@email.com", 6);
    Friend f5("Eve Brown", 27, "555-0105", "eve@email.com", 9);

    // Add friends to lists
    flms.addFriendToList("Close Friends", f1);
    flms.addFriendToList("Close Friends", f3);
    flms.addFriendToList("Close Friends", f5);
    flms.addFriendToList("Work Friends", f2);
    flms.addFriendToList("Work Friends", f4);
    flms.addFriendToList("School Friends", f1);
    flms.addFriendToList("School Friends", f2);

    // Demonstrate operator overloading
    cout << "\n=== OPERATOR OVERLOADING DEMONSTRATIONS ===" << endl;
    
    // Arithmetic operators
    Friend combined = f1 + f2;
    cout << "Combined friend: " << combined << endl;
    
    Friend subtracted = f1 - f2;
    cout << "Subtracted friend: " << subtracted << endl;
    
    Friend multiplied = f1 * 2;
    cout << "Multiplied friend: " << multiplied << endl;
    
    // Increment/Decrement
    ++f1;
    cout << "After increment: " << f1 << endl;
    
    f2++;
    cout << "After post-increment: " << f2 << endl;
    
    // Function call operator
    cout << "Friendship score: " << f1() << "%" << endl;
    
    // Type conversion
    string friendStr = static_cast<string>(f1);
    cout << "As string: " << friendStr << endl;
    
    int level = static_cast<int>(f1);
    cout << "As integer: " << level << endl;

    // Search functionality
    flms.searchFriend("Alice Johnson");
    flms.searchFriend("Unknown Person");

    // Generate report
    flms.generateReport();

    // Save data
    flms.saveToFile();
}

/*
==========================================
PRACTICE DRY RUNS - FRIEND FUNCTIONS & OPERATOR OVERLOADING
==========================================

Practice Problem 1: Simple Friend Function
-----------------------------------------
Create a class with private data and a friend function.
Friend function should access and modify private members.

Practice Problem 2: Operator Overloading Basics
---------------------------------------------
Overload +, -, *, / operators for a simple Number class.
Include proper error handling for division by zero.

Practice Problem 3: Friend Operator Overloading
---------------------------------------------
Create friend functions for operator overloading.
Demonstrate with a Point class (x, y coordinates).

Practice Problem 4: Static Members with Friends
---------------------------------------------
Use static members to track object count.
Create friend function to access static data.

Practice Problem 5: Template Friend Functions
-------------------------------------------
Create template friend function that works with different types.
Demonstrate with multiple data types.

Practice Problem 6: Exception Handling with Operators
---------------------------------------------------
Throw exceptions in operator overloads.
Handle invalid operations gracefully.

Practice Problem 7: Complex Operator Overloading
----------------------------------------------
Overload multiple operators for a Complex class.
Include comparison operators and stream operators.

Practice Problem 8: Friend Classes
---------------------------------
Create two classes where one is friend of another.
Demonstrate cross-class access to private members.

Practice Problem 9: Operator Overloading with Inheritance
-------------------------------------------------------
Create base and derived classes with operator overloading.
Demonstrate virtual functions with operators.

Practice Problem 10: Smart Pointer Operators
------------------------------------------
Overload operators for a simple smart pointer class.
Include dereference and arrow operators.
*/

// ==========================================
// PRACTICE SOLUTIONS
// ==========================================

// Practice 1: Simple Friend Function
class SimpleClass {
private:
    int data;
    string name;
public:
    SimpleClass(int d, string n) : data(d), name(n) {}
    
    friend void modifyData(SimpleClass& obj, int newData);
    friend void displayData(const SimpleClass& obj);
    
    int getData() const { return data; }
    string getName() const { return name; }
};

void modifyData(SimpleClass& obj, int newData) {
    obj.data = newData; // Access private member
}

void displayData(const SimpleClass& obj) {
    cout << "Name: " << obj.name << ", Data: " << obj.data << endl;
}

// Practice 2: Operator Overloading Basics
class Number {
private:
    double value;
public:
    Number(double v = 0.0) : value(v) {}
    
    Number operator+(const Number& other) const {
        return Number(value + other.value);
    }
    
    Number operator-(const Number& other) const {
        return Number(value - other.value);
    }
    
    Number operator*(const Number& other) const {
        return Number(value * other.value);
    }
    
    Number operator/(const Number& other) const {
        if (other.value == 0) {
            throw runtime_error("Division by zero");
        }
        return Number(value / other.value);
    }
    
    friend ostream& operator<<(ostream& os, const Number& num) {
        os << num.value;
        return os;
    }
    
    double getValue() const { return value; }
};

// Practice 3: Friend Operator Overloading
class Point {
private:
    int x, y;
public:
    Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal) {}
    
    friend Point operator+(const Point& p1, const Point& p2);
    friend Point operator-(const Point& p1, const Point& p2);
    friend bool operator==(const Point& p1, const Point& p2);
    friend ostream& operator<<(ostream& os, const Point& p);
    
    int getX() const { return x; }
    int getY() const { return y; }
};

Point operator+(const Point& p1, const Point& p2) {
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator-(const Point& p1, const Point& p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}

bool operator==(const Point& p1, const Point& p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// Practice 4: Static Members with Friends
class StaticCounter {
private:
    string name;
    static int totalCount;
    static vector<string> allNames;
public:
    StaticCounter(string n) : name(n) {
        totalCount++;
        allNames.push_back(name);
    }
    
    ~StaticCounter() {
        totalCount--;
        auto it = find(allNames.begin(), allNames.end(), name);
        if (it != allNames.end()) {
            allNames.erase(it);
        }
    }
    
    friend void displayStats();
    friend int getTotalCount();
};

int StaticCounter::totalCount = 0;
vector<string> StaticCounter::allNames;

void displayStats() {
    cout << "Total count: " << StaticCounter::totalCount << endl;
    cout << "All names: ";
    for (const auto& name : StaticCounter::allNames) {
        cout << name << " ";
    }
    cout << endl;
}

int getTotalCount() {
    return StaticCounter::totalCount;
}

// Practice 5: Template Friend Functions
template<typename T>
class TemplateClass {
private:
    T data;
public:
    TemplateClass(T d) : data(d) {}
    
    template<typename U>
    friend void swapData(TemplateClass<T>& obj1, TemplateClass<U>& obj2);
    
    friend ostream& operator<<(ostream& os, const TemplateClass<T>& obj) {
        os << obj.data;
        return os;
    }
    
    T getData() const { return data; }
};

template<typename T, typename U>
void swapData(TemplateClass<T>& obj1, TemplateClass<U>& obj2) {
    // Note: This is a simplified version - actual swap would need same types
    cout << "Swapping " << obj1.data << " and " << obj2.data << endl;
}

// Practice 6: Exception Handling with Operators
class SafeNumber {
private:
    int value;
public:
    SafeNumber(int v = 0) : value(v) {}
    
    SafeNumber operator/(const SafeNumber& other) const {
        if (other.value == 0) {
            throw invalid_argument("Division by zero not allowed");
        }
        return SafeNumber(value / other.value);
    }
    
    SafeNumber operator%(const SafeNumber& other) const {
        if (other.value == 0) {
            throw invalid_argument("Modulo by zero not allowed");
        }
        return SafeNumber(value % other.value);
    }
    
    friend ostream& operator<<(ostream& os, const SafeNumber& num) {
        os << num.value;
        return os;
    }
    
    int getValue() const { return value; }
};

// Practice 7: Complex Operator Overloading
class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    bool operator==(const Complex& other) const {
        return (real == other.real && imag == other.imag);
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;
    }
    
    double getReal() const { return real; }
    double getImag() const { return imag; }
};

// Practice 8: Friend Classes
class FriendClassA {
private:
    int secretData;
    string secretName;
public:
    FriendClassA(int data, string name) : secretData(data), secretName(name) {}
    
    friend class FriendClassB;
    
    void display() const {
        cout << "ClassA: " << secretName << " = " << secretData << endl;
    }
};

class FriendClassB {
public:
    void accessFriendData(FriendClassA& obj) {
        cout << "ClassB accessing ClassA: " << obj.secretName 
             << " = " << obj.secretData << endl;
        obj.secretData *= 2; // Can modify private member
    }
    
    void displayFriendData(const FriendClassA& obj) {
        cout << "ClassB displaying ClassA: " << obj.secretName 
             << " = " << obj.secretData << endl;
    }
};

// Practice 9: Operator Overloading with Inheritance
class BaseShape {
protected:
    string name;
public:
    BaseShape(string n) : name(n) {}
    virtual ~BaseShape() {}
    
    virtual double area() const = 0;
    virtual void display() const {
        cout << "Shape: " << name << endl;
    }
    
    bool operator==(const BaseShape& other) const {
        return name == other.name;
    }
    
    friend ostream& operator<<(ostream& os, const BaseShape& shape) {
        shape.display();
        return os;
    }
};

class Circle : public BaseShape {
private:
    double radius;
public:
    Circle(double r) : BaseShape("Circle"), radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    void display() const override {
        cout << "Circle with radius " << radius << ", area: " << area() << endl;
    }
    
    bool operator==(const Circle& other) const {
        return BaseShape::operator==(other) && radius == other.radius;
    }
};

// Practice 10: Smart Pointer Operators
template<typename T>
class SimpleSmartPtr {
private:
    T* ptr;
    static int refCount;
public:
    SimpleSmartPtr(T* p = nullptr) : ptr(p) {
        if (ptr) refCount++;
    }
    
    ~SimpleSmartPtr() {
        if (ptr) {
            refCount--;
            if (refCount == 0) {
                delete ptr;
            }
        }
    }
    
    T& operator*() {
        if (!ptr) throw runtime_error("Dereferencing null pointer");
        return *ptr;
    }
    
    T* operator->() {
        if (!ptr) throw runtime_error("Accessing null pointer");
        return ptr;
    }
    
    bool operator!() const {
        return ptr == nullptr;
    }
    
    friend ostream& operator<<(ostream& os, const SimpleSmartPtr<T>& smart) {
        if (smart.ptr) {
            os << "SmartPtr[" << *smart.ptr << "]";
        } else {
            os << "SmartPtr[null]";
        }
        return os;
    }
    
    static int getRefCount() { return refCount; }
};

template<typename T>
int SimpleSmartPtr<T>::refCount = 0;

// ==========================================
// PRACTICE DEMONSTRATION
// ==========================================

void demonstratePracticeProblems() {
    cout << "\n=== FRIEND & OPERATOR OVERLOADING PRACTICE DEMONSTRATION ===\n";
    
    // Practice 1: Simple Friend Function
    cout << "\n1. Simple Friend Function:";
    SimpleClass sc1(42, "Test");
    displayData(sc1);
    modifyData(sc1, 100);
    displayData(sc1);
    
    // Practice 2: Operator Overloading Basics
    cout << "\n2. Operator Overloading Basics:";
    Number n1(10.5), n2(2.0);
    cout << "n1: " << n1 << ", n2: " << n2 << endl;
    cout << "n1 + n2: " << (n1 + n2) << endl;
    cout << "n1 * n2: " << (n1 * n2) << endl;
    try {
        cout << "n1 / n2: " << (n1 / n2) << endl;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
    // Practice 3: Friend Operator Overloading
    cout << "\n3. Friend Operator Overloading:";
    Point p1(3, 4), p2(1, 2);
    cout << "p1: " << p1 << ", p2: " << p2 << endl;
    cout << "p1 + p2: " << (p1 + p2) << endl;
    cout << "p1 == p2: " << (p1 == p2) << endl;
    
    // Practice 4: Static Members with Friends
    cout << "\n4. Static Members with Friends:";
    StaticCounter sc2("Alice");
    StaticCounter sc3("Bob");
    displayStats();
    cout << "Total count: " << getTotalCount() << endl;
    
    // Practice 5: Template Friend Functions
    cout << "\n5. Template Friend Functions:";
    TemplateClass<int> tc1(42);
    TemplateClass<string> tc2("Hello");
    cout << "tc1: " << tc1 << ", tc2: " << tc2 << endl;
    swapData(tc1, tc2);
    
    // Practice 6: Exception Handling with Operators
    cout << "\n6. Exception Handling with Operators:";
    SafeNumber sn1(10), sn2(0);
    try {
        SafeNumber result = sn1 / sn2;
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
    // Practice 7: Complex Operator Overloading
    cout << "\n7. Complex Operator Overloading:";
    Complex c1(3, 4), c2(1, 2);
    cout << "c1: " << c1 << ", c2: " << c2 << endl;
    cout << "c1 + c2: " << (c1 + c2) << endl;
    cout << "c1 * c2: " << (c1 * c2) << endl;
    cout << "c1 == c2: " << (c1 == c2) << endl;
    
    // Practice 8: Friend Classes
    cout << "\n8. Friend Classes:";
    FriendClassA fca(42, "Secret");
    FriendClassB fcb;
    fca.display();
    fcb.accessFriendData(fca);
    fca.display();
    
    // Practice 9: Operator Overloading with Inheritance
    cout << "\n9. Operator Overloading with Inheritance:";
    Circle circle1(5.0);
    Circle circle2(5.0);
    cout << "circle1: " << circle1;
    cout << "circle1 == circle2: " << (circle1 == circle2) << endl;
    
    // Practice 10: Smart Pointer Operators
    cout << "\n10. Smart Pointer Operators:";
    SimpleSmartPtr<int> smart1(new int(42));
    SimpleSmartPtr<int> smart2(new int(100));
    cout << "smart1: " << smart1 << endl;
    cout << "*smart1: " << *smart1 << endl;
    cout << "Ref count: " << SimpleSmartPtr<int>::getRefCount() << endl;
}

// ==========================================
// TRICKY DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class Friend {
    int level;
public:
    Friend(int l = 5) : level(l) {}
    Friend operator+(const Friend& f) {
        return Friend(level + f.level + 1);
    }
    friend ostream& operator<<(ostream& os, const Friend& f) {
        return os << "Level" << f.level;
    }
};
int main() {
    Friend f1(3), f2(4);
    cout << f1 + f2;
    return 0;
}
Answer: Level8

Problem 2: What will be the output?
class List {
    static int count;
    int* data;
public:
    List() { 
        count++; 
        data = new int[count];
        cout << "List" << count; 
    }
    ~List() { 
        delete[] data; 
        cout << "~List" << count; 
    }
};
int List::count = 0;
int main() {
    List l1, l2;
    { List l3; }
    return 0;
}
Answer: List1List2List3~List3~List2~List1

Problem 3: What will be the output?
class MagicBox {
    int data;
public:
    MagicBox(int x) : data(x) {}
    MagicBox operator()(int y) {
        return MagicBox(data + y + 10);
    }
    friend ostream& operator<<(ostream& os, const MagicBox& box) {
        return os << "Box(" << box.data << ")";
    }
};
int main() {
    MagicBox box(5);
    cout << box(3);
    return 0;
}
Answer: Box(18)
*/

int main() {
    demonstrateFriendListSystem();
    return 0;
} 