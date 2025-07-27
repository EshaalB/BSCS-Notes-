/*
=========================================
URGENT PACKAGE DELIVERY SYSTEM QUESTION
=========================================

PROBLEM STATEMENT:
------------------
Create a comprehensive Urgent Package Delivery System with the following requirements:

1. Base Class: Package (packageId, sender, recipient, weight, priority)
2. Derived Classes:
   - ExpressPackage (deliveryTime, trackingNumber)
   - OvernightPackage (deliveryDate, specialHandling)
   - SameDayPackage (pickupTime, deliveryZone)
   - InternationalPackage (country, customsInfo)
3. DeliverySystem Class: (packages vector, deliveryVehicles)
4. Features:
   - Create different types of urgent packages
   - Schedule deliveries based on priority
   - Track package status
   - Calculate delivery costs
   - Generate delivery reports

IMPLEMENTATION REQUIREMENTS:
- Use inheritance hierarchy with virtual functions
- Implement encapsulation with proper access modifiers
- Use constructors and destructors
- Implement static members for tracking
- Use friend functions for cross-class operations
- Implement operator overloading for comparisons
- Use templates for generic operations
- Handle exceptions for invalid operations
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
using namespace std;

// ==========================================
// EXCEPTION CLASSES
// ==========================================

class PackageException : public exception {
private:
    string message;
public:
    PackageException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class DeliveryException : public exception {
private:
    string message;
public:
    DeliveryException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ==========================================
// BASE CLASS: PACKAGE
// ==========================================

class Package {
protected:
    int packageId;
    string sender;
    string recipient;
    double weight;
    int priority; // 1-10 scale (10 = highest priority)
    string status; // "Pending", "In Transit", "Delivered", "Failed"
    static int packageCounter;

public:
    Package(string s, string r, double w, int p = 5)
        : sender(s), recipient(r), weight(w), priority(p), status("Pending") {
        packageCounter++;
        packageId = packageCounter;
        
        if (priority < 1 || priority > 10) {
            throw PackageException("Priority must be between 1 and 10");
        }
        
        if (weight <= 0) {
            throw PackageException("Weight must be positive");
        }
    }

    virtual ~Package() {
        packageCounter--;
    }

    // Virtual functions for polymorphism
    virtual void display() const {
        cout << "Package ID: " << packageId << endl;
        cout << "Sender: " << sender << endl;
        cout << "Recipient: " << recipient << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Priority: " << priority << "/10" << endl;
        cout << "Status: " << status << endl;
    }

    virtual double calculateCost() const {
        return weight * 10.0; // Base cost calculation
    }

    virtual string getDeliveryType() const {
        return "Standard";
    }

    // Getters
    int getPackageId() const { return packageId; }
    string getSender() const { return sender; }
    string getRecipient() const { return recipient; }
    double getWeight() const { return weight; }
    int getPriority() const { return priority; }
    string getStatus() const { return status; }

    // Setters
    void setSender(string s) { sender = s; }
    void setRecipient(string r) { recipient = r; }
    void setWeight(double w) { 
        if (w <= 0) {
            throw PackageException("Weight must be positive");
        }
        weight = w; 
    }
    void setPriority(int p) { 
        if (p < 1 || p > 10) {
            throw PackageException("Priority must be between 1 and 10");
        }
        priority = p; 
    }
    void setStatus(string s) { status = s; }

    // Static function
    static int getPackageCounter() { return packageCounter; }

    // Operator overloading
    bool operator==(const Package& other) const {
        return packageId == other.packageId;
    }

    bool operator!=(const Package& other) const {
        return !(*this == other);
    }

    bool operator<(const Package& other) const {
        return priority < other.priority;
    }

    bool operator>(const Package& other) const {
        return priority > other.priority;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const Package& pkg);
};

int Package::packageCounter = 0;

ostream& operator<<(ostream& os, const Package& pkg) {
    os << "Package[" << pkg.packageId << "]: " << pkg.sender << " -> " << pkg.recipient 
       << " (Priority: " << pkg.priority << ", Status: " << pkg.status << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: EXPRESS PACKAGE
// ==========================================

class ExpressPackage : public Package {
private:
    int deliveryTime; // Hours
    string trackingNumber;
    static int expressCounter;

public:
    ExpressPackage(string s, string r, double w, int p, int time, string tracking)
        : Package(s, r, w, p), deliveryTime(time), trackingNumber(tracking) {
        expressCounter++;
    }

    ~ExpressPackage() {
        expressCounter--;
    }

    // Override display function
    void display() const override {
        Package::display();
        cout << "Type: Express Delivery" << endl;
        cout << "Delivery Time: " << deliveryTime << " hours" << endl;
        cout << "Tracking Number: " << trackingNumber << endl;
    }

    // Override cost calculation
    double calculateCost() const override {
        return Package::calculateCost() + (deliveryTime * 5.0); // Express fee
    }

    // Override delivery type
    string getDeliveryType() const override {
        return "Express";
    }

    // Getters
    int getDeliveryTime() const { return deliveryTime; }
    string getTrackingNumber() const { return trackingNumber; }

    // Setters
    void setDeliveryTime(int time) { 
        if (time <= 0) {
            throw PackageException("Delivery time must be positive");
        }
        deliveryTime = time; 
    }
    void setTrackingNumber(string tracking) { trackingNumber = tracking; }

    // Static function
    static int getExpressCounter() { return expressCounter; }

    friend ostream& operator<<(ostream& os, const ExpressPackage& pkg);
};

int ExpressPackage::expressCounter = 0;

ostream& operator<<(ostream& os, const ExpressPackage& pkg) {
    os << "ExpressPackage[" << pkg.getPackageId() << "]: " << pkg.getSender() 
       << " -> " << pkg.getRecipient() << " (" << pkg.deliveryTime << "h)";
    return os;
}

// ==========================================
// DERIVED CLASS: OVERNIGHT PACKAGE
// ==========================================

class OvernightPackage : public Package {
private:
    string deliveryDate;
    bool specialHandling;
    static int overnightCounter;

public:
    OvernightPackage(string s, string r, double w, int p, string date, bool special = false)
        : Package(s, r, w, p), deliveryDate(date), specialHandling(special) {
        overnightCounter++;
    }

    ~OvernightPackage() {
        overnightCounter--;
    }

    // Override display function
    void display() const override {
        Package::display();
        cout << "Type: Overnight Delivery" << endl;
        cout << "Delivery Date: " << deliveryDate << endl;
        cout << "Special Handling: " << (specialHandling ? "Yes" : "No") << endl;
    }

    // Override cost calculation
    double calculateCost() const override {
        double cost = Package::calculateCost() + 25.0; // Overnight fee
        if (specialHandling) {
            cost += 15.0; // Special handling fee
        }
        return cost;
    }

    // Override delivery type
    string getDeliveryType() const override {
        return "Overnight";
    }

    // Getters
    string getDeliveryDate() const { return deliveryDate; }
    bool getSpecialHandling() const { return specialHandling; }

    // Setters
    void setDeliveryDate(string date) { deliveryDate = date; }
    void setSpecialHandling(bool special) { specialHandling = special; }

    // Static function
    static int getOvernightCounter() { return overnightCounter; }

    friend ostream& operator<<(ostream& os, const OvernightPackage& pkg);
};

int OvernightPackage::overnightCounter = 0;

ostream& operator<<(ostream& os, const OvernightPackage& pkg) {
    os << "OvernightPackage[" << pkg.getPackageId() << "]: " << pkg.getSender() 
       << " -> " << pkg.getRecipient() << " (" << pkg.deliveryDate << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: SAME DAY PACKAGE
// ==========================================

class SameDayPackage : public Package {
private:
    string pickupTime;
    string deliveryZone;
    static int sameDayCounter;

public:
    SameDayPackage(string s, string r, double w, int p, string pickup, string zone)
        : Package(s, r, w, p), pickupTime(pickup), deliveryZone(zone) {
        sameDayCounter++;
    }

    ~SameDayPackage() {
        sameDayCounter--;
    }

    // Override display function
    void display() const override {
        Package::display();
        cout << "Type: Same Day Delivery" << endl;
        cout << "Pickup Time: " << pickupTime << endl;
        cout << "Delivery Zone: " << deliveryZone << endl;
    }

    // Override cost calculation
    double calculateCost() const override {
        return Package::calculateCost() + 50.0; // Same day fee
    }

    // Override delivery type
    string getDeliveryType() const override {
        return "Same Day";
    }

    // Getters
    string getPickupTime() const { return pickupTime; }
    string getDeliveryZone() const { return deliveryZone; }

    // Setters
    void setPickupTime(string time) { pickupTime = time; }
    void setDeliveryZone(string zone) { deliveryZone = zone; }

    // Static function
    static int getSameDayCounter() { return sameDayCounter; }

    friend ostream& operator<<(ostream& os, const SameDayPackage& pkg);
};

int SameDayPackage::sameDayCounter = 0;

ostream& operator<<(ostream& os, const SameDayPackage& pkg) {
    os << "SameDayPackage[" << pkg.getPackageId() << "]: " << pkg.getSender() 
       << " -> " << pkg.getRecipient() << " (Zone: " << pkg.deliveryZone << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: INTERNATIONAL PACKAGE
// ==========================================

class InternationalPackage : public Package {
private:
    string country;
    string customsInfo;
    static int internationalCounter;

public:
    InternationalPackage(string s, string r, double w, int p, string c, string customs)
        : Package(s, r, w, p), country(c), customsInfo(customs) {
        internationalCounter++;
    }

    ~InternationalPackage() {
        internationalCounter--;
    }

    // Override display function
    void display() const override {
        Package::display();
        cout << "Type: International Delivery" << endl;
        cout << "Country: " << country << endl;
        cout << "Customs Info: " << customsInfo << endl;
    }

    // Override cost calculation
    double calculateCost() const override {
        return Package::calculateCost() + 100.0; // International fee
    }

    // Override delivery type
    string getDeliveryType() const override {
        return "International";
    }

    // Getters
    string getCountry() const { return country; }
    string getCustomsInfo() const { return customsInfo; }

    // Setters
    void setCountry(string c) { country = c; }
    void setCustomsInfo(string info) { customsInfo = info; }

    // Static function
    static int getInternationalCounter() { return internationalCounter; }

    friend ostream& operator<<(ostream& os, const InternationalPackage& pkg);
};

int InternationalPackage::internationalCounter = 0;

ostream& operator<<(ostream& os, const InternationalPackage& pkg) {
    os << "InternationalPackage[" << pkg.getPackageId() << "]: " << pkg.getSender() 
       << " -> " << pkg.getRecipient() << " (" << pkg.country << ")";
    return os;
}

// ==========================================
// DELIVERY SYSTEM CLASS
// ==========================================

class DeliverySystem {
private:
    vector<shared_ptr<Package>> packages;
    vector<string> deliveryVehicles;
    static int systemCounter;

public:
    DeliverySystem() {
        systemCounter++;
        // Initialize delivery vehicles
        deliveryVehicles = {"Truck-001", "Van-002", "Motorcycle-003", "Bicycle-004"};
    }

    ~DeliverySystem() {
        systemCounter--;
    }

    // Add package
    void addPackage(shared_ptr<Package> pkg) {
        packages.push_back(pkg);
    }

    // Remove package
    void removePackage(int packageId) {
        auto it = find_if(packages.begin(), packages.end(),
            [packageId](const shared_ptr<Package>& p) { 
                return p->getPackageId() == packageId; 
            });
        
        if (it != packages.end()) {
            packages.erase(it);
        } else {
            throw DeliveryException("Package not found");
        }
    }

    // Find package by ID
    shared_ptr<Package> findPackage(int packageId) {
        for (auto& pkg : packages) {
            if (pkg->getPackageId() == packageId) {
                return pkg;
            }
        }
        return nullptr;
    }

    // Get packages by priority
    vector<shared_ptr<Package>> getPackagesByPriority(int priority) {
        vector<shared_ptr<Package>> result;
        for (auto& pkg : packages) {
            if (pkg->getPriority() == priority) {
                result.push_back(pkg);
            }
        }
        return result;
    }

    // Get packages by status
    vector<shared_ptr<Package>> getPackagesByStatus(string status) {
        vector<shared_ptr<Package>> result;
        for (auto& pkg : packages) {
            if (pkg->getStatus() == status) {
                result.push_back(pkg);
            }
        }
        return result;
    }

    // Sort packages by priority (highest first)
    void sortByPriority() {
        sort(packages.begin(), packages.end(),
            [](const shared_ptr<Package>& a, const shared_ptr<Package>& b) {
                return a->getPriority() > b->getPriority();
            });
    }

    // Sort packages by weight
    void sortByWeight() {
        sort(packages.begin(), packages.end(),
            [](const shared_ptr<Package>& a, const shared_ptr<Package>& b) {
                return a->getWeight() < b->getWeight();
            });
    }

    // Update package status
    void updatePackageStatus(int packageId, string status) {
        auto pkg = findPackage(packageId);
        if (pkg) {
            pkg->setStatus(status);
        } else {
            throw DeliveryException("Package not found");
        }
    }

    // Calculate total revenue
    double calculateTotalRevenue() const {
        double total = 0.0;
        for (const auto& pkg : packages) {
            total += pkg->calculateCost();
        }
        return total;
    }

    // Display all packages
    void displayAllPackages() const {
        cout << "\n=== ALL PACKAGES ===" << endl;
        cout << "Total Packages: " << packages.size() << endl;
        cout << "================================" << endl;
        
        for (const auto& pkg : packages) {
            pkg->display();
            cout << "Cost: $" << fixed << setprecision(2) << pkg->calculateCost() << endl;
            cout << "------------------------" << endl;
        }
    }

    // Display packages by type
    void displayPackagesByType(string type) {
        cout << "\n=== " << type << " PACKAGES ===" << endl;
        int count = 0;
        for (const auto& pkg : packages) {
            if (pkg->getDeliveryType() == type) {
                pkg->display();
                cout << "Cost: $" << fixed << setprecision(2) << pkg->calculateCost() << endl;
                cout << "------------------------" << endl;
                count++;
            }
        }
        cout << "Total " << type << " packages: " << count << endl;
    }

    // Display high priority packages
    void displayHighPriorityPackages() {
        cout << "\n=== HIGH PRIORITY PACKAGES (8-10) ===" << endl;
        int count = 0;
        for (const auto& pkg : packages) {
            if (pkg->getPriority() >= 8) {
                pkg->display();
                cout << "Cost: $" << fixed << setprecision(2) << pkg->calculateCost() << endl;
                cout << "------------------------" << endl;
                count++;
            }
        }
        cout << "Total high priority packages: " << count << endl;
    }

    // Generate delivery report
    void generateReport() {
        cout << "\n=== DELIVERY SYSTEM REPORT ===" << endl;
        cout << "Total Packages: " << packages.size() << endl;
        cout << "Express Packages: " << ExpressPackage::getExpressCounter() << endl;
        cout << "Overnight Packages: " << OvernightPackage::getOvernightCounter() << endl;
        cout << "Same Day Packages: " << SameDayPackage::getSameDayCounter() << endl;
        cout << "International Packages: " << InternationalPackage::getInternationalCounter() << endl;
        cout << "Total Revenue: $" << fixed << setprecision(2) << calculateTotalRevenue() << endl;
        cout << "Available Vehicles: " << deliveryVehicles.size() << endl;
    }

    // Getters
    int getPackageCount() const { return packages.size(); }
    int getVehicleCount() const { return deliveryVehicles.size(); }

    // Static function
    static int getSystemCounter() { return systemCounter; }

    // Operator overloading
    DeliverySystem& operator+=(shared_ptr<Package> pkg) {
        addPackage(pkg);
        return *this;
    }

    DeliverySystem& operator-=(int packageId) {
        removePackage(packageId);
        return *this;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const DeliverySystem& system);
};

int DeliverySystem::systemCounter = 0;

ostream& operator<<(ostream& os, const DeliverySystem& system) {
    os << "DeliverySystem: " << system.packages.size() << " packages, " 
       << system.deliveryVehicles.size() << " vehicles";
    return os;
}

// ==========================================
// TEMPLATE CLASS FOR GENERIC OPERATIONS
// ==========================================

template<typename T>
class PackageManager {
private:
    vector<shared_ptr<T>> items;

public:
    void addItem(shared_ptr<T> item) {
        items.push_back(item);
    }

    void removeItem(shared_ptr<T> item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    void displayAll() {
        for (const auto& item : items) {
            item->display();
            cout << "------------------------" << endl;
        }
    }

    int getCount() const { return items.size(); }

    // Calculate total cost
    double getTotalCost() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item->calculateCost();
        }
        return total;
    }
};

// ==========================================
// DEMONSTRATION FUNCTION
// ==========================================

void demonstrateDeliverySystem() {
    cout << "URGENT PACKAGE DELIVERY SYSTEM DEMONSTRATION" << endl;
    cout << "============================================" << endl;

    DeliverySystem system;

    // Create different types of packages
    auto expressPkg = make_shared<ExpressPackage>(
        "John Doe", "Jane Smith", 2.5, 9, 4, "EXP123456"
    );

    auto overnightPkg = make_shared<OvernightPackage>(
        "Alice Johnson", "Bob Wilson", 1.8, 8, "2024-01-16", true
    );

    auto sameDayPkg = make_shared<SameDayPackage>(
        "Charlie Brown", "Diana Prince", 0.5, 10, "14:00", "Downtown"
    );

    auto internationalPkg = make_shared<InternationalPackage>(
        "Eve Adams", "Frank Miller", 5.0, 7, "Canada", "Electronics"
    );

    auto regularPkg = make_shared<Package>(
        "Grace Lee", "Henry Ford", 3.2, 5
    );

    // Add packages to system
    system += expressPkg;
    system += overnightPkg;
    system += sameDayPkg;
    system += internationalPkg;
    system += regularPkg;

    // Update some package statuses
    system.updatePackageStatus(1, "In Transit");
    system.updatePackageStatus(2, "Delivered");
    system.updatePackageStatus(3, "In Transit");

    // Display all packages
    system.displayAllPackages();

    // Display packages by type
    system.displayPackagesByType("Express");
    system.displayPackagesByType("Overnight");
    system.displayPackagesByType("Same Day");
    system.displayPackagesByType("International");

    // Display high priority packages
    system.displayHighPriorityPackages();

    // Generate report
    system.generateReport();

    // Demonstrate operator overloading
    cout << "\n=== OPERATOR OVERLOADING DEMONSTRATIONS ===" << endl;
    
    // Comparison operators
    if (*expressPkg < *sameDayPkg) {
        cout << "Express package has lower priority than same day package" << endl;
    }
    
    if (*internationalPkg > *regularPkg) {
        cout << "International package has higher priority than regular package" << endl;
    }
    
    // System operators
    cout << "System: " << system << endl;
}

// ==========================================
// TRICKY DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class Package {
    static int count;
    int id;
public:
    Package() { id = ++count; cout << "Package" << id; }
    ~Package() { cout << "~Package" << id; }
};
int Package::count = 0;
int main() {
    Package p1, p2;
    { Package p3; }
    return 0;
}
Answer: Package1Package2Package3~Package3~Package2~Package1

Problem 2: What will be the output?
class Express {
    int time;
public:
    Express(int t = 4) : time(t) {}
    Express operator+(const Express& e) {
        return Express(time + e.time + 1);
    }
    friend ostream& operator<<(ostream& os, const Express& exp) {
        return os << "Time:" << exp.time;
    }
};
int main() {
    Express e1(3), e2(5);
    cout << e1 + e2;
    return 0;
}
Answer: Time:9

Problem 3: What will be the output?
class Delivery {
    int packages;
public:
    Delivery(int p = 0) : packages(p) {}
    Delivery operator+=(int p) {
        packages += p + 2;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const Delivery& del) {
        return os << "Packages:" << del.packages;
    }
};
int main() {
    Delivery d(5);
    d += 3;
    cout << d;
    return 0;
}
Answer: Packages:10
*/

int main() {
    demonstrateDeliverySystem();
    return 0;
} 