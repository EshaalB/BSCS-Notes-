/*
==========================================
BANK MANAGEMENT SYSTEM QUESTION
==========================================

PROBLEM STATEMENT:
------------------
Create a comprehensive Bank Management System with the following requirements:

1. Base Class: Account (accountNumber, balance, accountType)
2. Derived Classes: 
   - SavingsAccount (interestRate, minimumBalance)
   - CheckingAccount (overdraftLimit, transactionFee)
   - FixedDepositAccount (depositAmount, maturityDate, interestRate)
3. Customer Class: (customerId, name, address, phone, accounts)
4. Transaction Class: (transactionId, amount, type, date, description)
5. Features:
   - Open/Close accounts
   - Deposit/Withdraw money
   - Transfer between accounts
   - Calculate interest
   - Generate statements
   - Handle different account types
   - Transaction history
   - File handling for data persistence

IMPLEMENTATION REQUIREMENTS:
- Use inheritance hierarchy with virtual functions
- Implement encapsulation with proper access modifiers
- Use constructors and destructors
- Implement static members for tracking
- Use friend functions for cross-class operations
- Implement operator overloading for comparisons
- Use templates for generic operations
- Handle exceptions for invalid operations
- Use smart pointers for memory management
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <stdexcept>
using namespace std;

// ==========================================
// EXCEPTION CLASSES
// ==========================================

class BankException : public exception {
private:
    string message;
public:
    BankException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class TransactionException : public exception {
private:
    string message;
public:
    TransactionException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ==========================================
// TRANSACTION CLASS
// ==========================================

class Transaction {
private:
    string transactionId;
    double amount;
    string type; // "DEPOSIT", "WITHDRAW", "TRANSFER", "INTEREST"
    string date;
    string description;
    static int transactionCounter;

public:
    Transaction(double amt, string t, string desc) 
        : amount(amt), type(t), description(desc) {
        transactionCounter++;
        transactionId = "TXN" + to_string(transactionCounter);
        
        // Get current date
        time_t now = time(0);
        char* dt = ctime(&now);
        date = string(dt);
        date.pop_back(); // Remove newline
    }

    // Getters
    string getTransactionId() const { return transactionId; }
    double getAmount() const { return amount; }
    string getType() const { return type; }
    string getDate() const { return date; }
    string getDescription() const { return description; }

    // Display transaction
    void display() const {
        cout << "Transaction ID: " << transactionId << endl;
        cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "Type: " << type << endl;
        cout << "Date: " << date << endl;
        cout << "Description: " << description << endl;
    }

    static int getTransactionCounter() { return transactionCounter; }

    // Operator overloading
    bool operator==(const Transaction& other) const {
        return transactionId == other.transactionId;
    }

    friend ostream& operator<<(ostream& os, const Transaction& txn);
};

int Transaction::transactionCounter = 0;

ostream& operator<<(ostream& os, const Transaction& txn) {
    os << txn.transactionId << " - " << txn.type << " $" << txn.amount;
    return os;
}

// ==========================================
// BASE CLASS: ACCOUNT
// ==========================================

class Account {
protected:
    string accountNumber;
    double balance;
    string accountType;
    string customerId;
    vector<Transaction> transactions;
    static int accountCounter;

public:
    Account(string custId, string type, double initialBalance = 0.0) 
        : customerId(custId), accountType(type), balance(initialBalance) {
        accountCounter++;
        accountNumber = "ACC" + to_string(accountCounter);
        
        if (initialBalance > 0) {
            addTransaction(initialBalance, "DEPOSIT", "Initial deposit");
        }
    }

    virtual ~Account() {
        cout << "Account " << accountNumber << " destroyed" << endl;
    }

    // Virtual functions for polymorphism
    virtual void deposit(double amount) {
        if (amount <= 0) {
            throw BankException("Deposit amount must be positive");
        }
        balance += amount;
        addTransaction(amount, "DEPOSIT", "Cash deposit");
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) {
            throw BankException("Withdrawal amount must be positive");
        }
        if (amount > balance) {
            throw BankException("Insufficient funds");
        }
        balance -= amount;
        addTransaction(amount, "WITHDRAW", "Cash withdrawal");
    }

    virtual void calculateInterest() {
        // Base class - no interest calculation
        cout << "No interest calculation for base account type" << endl;
    }

    // Add transaction to history
    void addTransaction(double amount, string type, string description) {
        transactions.emplace_back(amount, type, description);
    }

    // Display account information
    virtual void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Number of Transactions: " << transactions.size() << endl;
    }

    // Display transaction history
    void displayTransactionHistory() const {
        cout << "\nTransaction History for Account " << accountNumber << ":" << endl;
        cout << "==========================================" << endl;
        for (const auto& txn : transactions) {
            txn.display();
            cout << "------------------------" << endl;
        }
    }

    // Getters
    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    string getAccountType() const { return accountType; }
    string getCustomerId() const { return customerId; }

    // Static function
    static int getAccountCounter() { return accountCounter; }

    // Operator overloading
    bool operator==(const Account& other) const {
        return accountNumber == other.accountNumber;
    }

    bool operator<(const Account& other) const {
        return balance < other.balance;
    }

    friend ostream& operator<<(ostream& os, const Account& account);
};

int Account::accountCounter = 0;

ostream& operator<<(ostream& os, const Account& account) {
    os << account.accountNumber << " - " << account.accountType << " - $" << account.balance;
    return os;
}

// ==========================================
// DERIVED CLASS: SAVINGS ACCOUNT
// ==========================================

class SavingsAccount : public Account {
private:
    double interestRate;
    double minimumBalance;
    static int savingsAccountCounter;

public:
    SavingsAccount(string custId, double initialBalance, double rate = 0.05, double minBal = 100.0) 
        : Account(custId, "Savings", initialBalance), interestRate(rate), minimumBalance(minBal) {
        savingsAccountCounter++;
    }

    ~SavingsAccount() {
        savingsAccountCounter--;
    }

    // Override deposit method
    void deposit(double amount) override {
        Account::deposit(amount);
        cout << "Deposited $" << amount << " to savings account" << endl;
    }

    // Override withdraw method with minimum balance check
    void withdraw(double amount) override {
        if (balance - amount < minimumBalance) {
            throw BankException("Withdrawal would violate minimum balance requirement");
        }
        Account::withdraw(amount);
        cout << "Withdrew $" << amount << " from savings account" << endl;
    }

    // Override interest calculation
    void calculateInterest() override {
        double interest = balance * interestRate;
        balance += interest;
        addTransaction(interest, "INTEREST", "Interest credited");
        cout << "Interest of $" << interest << " credited to savings account" << endl;
    }

    // Override display method
    void display() const override {
        Account::display();
        cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
        cout << "Minimum Balance: $" << minimumBalance << endl;
    }

    // Getters
    double getInterestRate() const { return interestRate; }
    double getMinimumBalance() const { return minimumBalance; }

    // Static function
    static int getSavingsAccountCounter() { return savingsAccountCounter; }

    friend ostream& operator<<(ostream& os, const SavingsAccount& account);
};

int SavingsAccount::savingsAccountCounter = 0;

ostream& operator<<(ostream& os, const SavingsAccount& account) {
    os << "Savings: " << account.getAccountNumber() << " - $" << account.getBalance();
    return os;
}

// ==========================================
// DERIVED CLASS: CHECKING ACCOUNT
// ==========================================

class CheckingAccount : public Account {
private:
    double overdraftLimit;
    double transactionFee;
    static int checkingAccountCounter;

public:
    CheckingAccount(string custId, double initialBalance, double overdraft = 500.0, double fee = 2.0) 
        : Account(custId, "Checking", initialBalance), overdraftLimit(overdraft), transactionFee(fee) {
        checkingAccountCounter++;
    }

    ~CheckingAccount() {
        checkingAccountCounter--;
    }

    // Override withdraw method with overdraft facility
    void withdraw(double amount) override {
        if (amount <= 0) {
            throw BankException("Withdrawal amount must be positive");
        }
        
        double totalAmount = amount + transactionFee;
        if (balance + overdraftLimit < totalAmount) {
            throw BankException("Withdrawal exceeds overdraft limit");
        }
        
        balance -= totalAmount;
        addTransaction(amount, "WITHDRAW", "Cash withdrawal");
        addTransaction(transactionFee, "FEE", "Transaction fee");
        cout << "Withdrew $" << amount << " (Fee: $" << transactionFee << ") from checking account" << endl;
    }

    // Override display method
    void display() const override {
        Account::display();
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
        cout << "Transaction Fee: $" << transactionFee << endl;
    }

    // Getters
    double getOverdraftLimit() const { return overdraftLimit; }
    double getTransactionFee() const { return transactionFee; }

    // Static function
    static int getCheckingAccountCounter() { return checkingAccountCounter; }

    friend ostream& operator<<(ostream& os, const CheckingAccount& account);
};

int CheckingAccount::checkingAccountCounter = 0;

ostream& operator<<(ostream& os, const CheckingAccount& account) {
    os << "Checking: " << account.getAccountNumber() << " - $" << account.getBalance();
    return os;
}

// ==========================================
// DERIVED CLASS: FIXED DEPOSIT ACCOUNT
// ==========================================

class FixedDepositAccount : public Account {
private:
    double depositAmount;
    string maturityDate;
    double interestRate;
    bool isMatured;
    static int fixedDepositCounter;

public:
    FixedDepositAccount(string custId, double amount, double rate = 0.08, string maturity = "2024-12-31") 
        : Account(custId, "Fixed Deposit", amount), depositAmount(amount), 
          maturityDate(maturity), interestRate(rate), isMatured(false) {
        fixedDepositCounter++;
    }

    ~FixedDepositAccount() {
        fixedDepositCounter--;
    }

    // Override deposit method - no additional deposits allowed
    void deposit(double amount) override {
        throw BankException("Additional deposits not allowed in fixed deposit account");
    }

    // Override withdraw method - only after maturity
    void withdraw(double amount) override {
        if (!isMatured) {
            throw BankException("Cannot withdraw before maturity date");
        }
        if (amount > balance) {
            throw BankException("Insufficient funds");
        }
        Account::withdraw(amount);
        cout << "Withdrew $" << amount << " from fixed deposit account" << endl;
    }

    // Override interest calculation
    void calculateInterest() override {
        if (!isMatured) {
            double interest = depositAmount * interestRate;
            balance += interest;
            addTransaction(interest, "INTEREST", "Fixed deposit interest");
            cout << "Interest of $" << interest << " credited to fixed deposit account" << endl;
        }
    }

    // Mature the account
    void matureAccount() {
        isMatured = true;
        calculateInterest();
        cout << "Fixed deposit account matured on " << maturityDate << endl;
    }

    // Override display method
    void display() const override {
        Account::display();
        cout << "Deposit Amount: $" << depositAmount << endl;
        cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
        cout << "Maturity Date: " << maturityDate << endl;
        cout << "Matured: " << (isMatured ? "Yes" : "No") << endl;
    }

    // Getters
    double getDepositAmount() const { return depositAmount; }
    string getMaturityDate() const { return maturityDate; }
    double getInterestRate() const { return interestRate; }
    bool getIsMatured() const { return isMatured; }

    // Static function
    static int getFixedDepositCounter() { return fixedDepositCounter; }

    friend ostream& operator<<(ostream& os, const FixedDepositAccount& account);
};

int FixedDepositAccount::fixedDepositCounter = 0;

ostream& operator<<(ostream& os, const FixedDepositAccount& account) {
    os << "Fixed Deposit: " << account.getAccountNumber() << " - $" << account.getBalance();
    return os;
}

// ==========================================
// CUSTOMER CLASS
// ==========================================

class Customer {
private:
    string customerId;
    string name;
    string address;
    string phone;
    vector<shared_ptr<Account>> accounts;
    static int customerCounter;

public:
    Customer(string n, string addr, string ph) 
        : name(n), address(addr), phone(ph) {
        customerCounter++;
        customerId = "CUST" + to_string(customerCounter);
    }

    ~Customer() {
        customerCounter--;
    }

    // Add account
    void addAccount(shared_ptr<Account> account) {
        accounts.push_back(account);
        cout << "Account added for customer " << name << endl;
    }

    // Remove account
    void removeAccount(string accountNumber) {
        auto it = find_if(accounts.begin(), accounts.end(),
            [accountNumber](const shared_ptr<Account>& acc) {
                return acc->getAccountNumber() == accountNumber;
            });
        
        if (it != accounts.end()) {
            accounts.erase(it);
            cout << "Account " << accountNumber << " removed for customer " << name << endl;
        } else {
            throw BankException("Account not found for this customer");
        }
    }

    // Get account by number
    shared_ptr<Account> getAccount(string accountNumber) {
        for (auto& account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;
    }

    // Display customer information
    void display() const {
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
        cout << "Number of Accounts: " << accounts.size() << endl;
    }

    // Display all accounts
    void displayAccounts() const {
        cout << "\nAccounts for Customer " << name << ":" << endl;
        cout << "================================" << endl;
        for (const auto& account : accounts) {
            account->display();
            cout << "------------------------" << endl;
        }
    }

    // Getters
    string getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    int getAccountCount() const { return accounts.size(); }

    // Static function
    static int getCustomerCounter() { return customerCounter; }

    // Operator overloading
    bool operator==(const Customer& other) const {
        return customerId == other.customerId;
    }

    friend ostream& operator<<(ostream& os, const Customer& customer);
};

int Customer::customerCounter = 0;

ostream& operator<<(ostream& os, const Customer& customer) {
    os << customer.customerId << " - " << customer.name;
    return os;
}

// ==========================================
// TEMPLATE CLASS FOR GENERIC OPERATIONS
// ==========================================

template<typename T>
class BankManager {
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

    shared_ptr<T> findItem(string id) {
        for (auto& item : items) {
            // This requires items to have getId() method
            // For demonstration, we'll use a simple approach
            if (typeid(*item) == typeid(Customer)) {
                Customer* customer = dynamic_cast<Customer*>(item.get());
                if (customer && customer->getCustomerId() == id) return item;
            }
        }
        return nullptr;
    }

    void displayAll() {
        for (auto& item : items) {
            item->display();
            cout << "------------------------" << endl;
        }
    }

    int getCount() const { return items.size(); }
};

// ==========================================
// BANK MANAGEMENT SYSTEM CLASS
// ==========================================

class BankManagementSystem {
private:
    BankManager<Customer> customerManager;
    vector<shared_ptr<Account>> allAccounts;
    string dataFile;

public:
    BankManagementSystem(string filename = "bank_data.txt") : dataFile(filename) {}

    ~BankManagementSystem() {
        cout << "Bank Management System shutting down..." << endl;
    }

    // Create customer
    void createCustomer(string name, string address, string phone) {
        try {
            auto customer = make_shared<Customer>(name, address, phone);
            customerManager.addItem(customer);
            cout << "Customer created successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error creating customer: " << e.what() << endl;
        }
    }

    // Create savings account
    void createSavingsAccount(string customerId, double initialBalance) {
        try {
            auto customer = customerManager.findItem(customerId);
            if (!customer) {
                throw BankException("Customer not found");
            }

            auto account = make_shared<SavingsAccount>(customerId, initialBalance);
            customer->addAccount(account);
            allAccounts.push_back(account);
            cout << "Savings account created successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error creating savings account: " << e.what() << endl;
        }
    }

    // Create checking account
    void createCheckingAccount(string customerId, double initialBalance) {
        try {
            auto customer = customerManager.findItem(customerId);
            if (!customer) {
                throw BankException("Customer not found");
            }

            auto account = make_shared<CheckingAccount>(customerId, initialBalance);
            customer->addAccount(account);
            allAccounts.push_back(account);
            cout << "Checking account created successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error creating checking account: " << e.what() << endl;
        }
    }

    // Create fixed deposit account
    void createFixedDepositAccount(string customerId, double amount) {
        try {
            auto customer = customerManager.findItem(customerId);
            if (!customer) {
                throw BankException("Customer not found");
            }

            auto account = make_shared<FixedDepositAccount>(customerId, amount);
            customer->addAccount(account);
            allAccounts.push_back(account);
            cout << "Fixed deposit account created successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error creating fixed deposit account: " << e.what() << endl;
        }
    }

    // Deposit money
    void deposit(string accountNumber, double amount) {
        try {
            for (auto& account : allAccounts) {
                if (account->getAccountNumber() == accountNumber) {
                    account->deposit(amount);
                    return;
                }
            }
            throw BankException("Account not found");
        } catch (const exception& e) {
            cout << "Error depositing money: " << e.what() << endl;
        }
    }

    // Withdraw money
    void withdraw(string accountNumber, double amount) {
        try {
            for (auto& account : allAccounts) {
                if (account->getAccountNumber() == accountNumber) {
                    account->withdraw(amount);
                    return;
                }
            }
            throw BankException("Account not found");
        } catch (const exception& e) {
            cout << "Error withdrawing money: " << e.what() << endl;
        }
    }

    // Transfer money
    void transfer(string fromAccount, string toAccount, double amount) {
        try {
            shared_ptr<Account> fromAcc = nullptr, toAcc = nullptr;
            
            for (auto& account : allAccounts) {
                if (account->getAccountNumber() == fromAccount) {
                    fromAcc = account;
                }
                if (account->getAccountNumber() == toAccount) {
                    toAcc = account;
                }
            }

            if (!fromAcc || !toAcc) {
                throw BankException("One or both accounts not found");
            }

            fromAcc->withdraw(amount);
            toAcc->deposit(amount);
            cout << "Transfer of $" << amount << " completed successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error transferring money: " << e.what() << endl;
        }
    }

    // Calculate interest for all accounts
    void calculateInterestForAll() {
        cout << "\nCalculating interest for all accounts..." << endl;
        for (auto& account : allAccounts) {
            account->calculateInterest();
        }
    }

    // Generate bank report
    void generateReport() {
        cout << "\n=== BANK MANAGEMENT SYSTEM REPORT ===" << endl;
        cout << "Total Customers: " << Customer::getCustomerCounter() << endl;
        cout << "Total Accounts: " << Account::getAccountCounter() << endl;
        cout << "Savings Accounts: " << SavingsAccount::getSavingsAccountCounter() << endl;
        cout << "Checking Accounts: " << CheckingAccount::getCheckingAccountCounter() << endl;
        cout << "Fixed Deposit Accounts: " << FixedDepositAccount::getFixedDepositCounter() << endl;
        cout << "Total Transactions: " << Transaction::getTransactionCounter() << endl;
        
        cout << "\nAll Customers:" << endl;
        customerManager.displayAll();
        
        cout << "\nAll Accounts:" << endl;
        for (auto& account : allAccounts) {
            account->display();
            cout << "------------------------" << endl;
        }
    }

    // Save data to file
    void saveToFile() {
        ofstream file(dataFile);
        if (file.is_open()) {
            file << "Bank Management System Data" << endl;
            file << "===========================" << endl;
            file << "Generated on: " << ctime(&time(0)) << endl;
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

void demonstrateBankManagement() {
    cout << "BANK MANAGEMENT SYSTEM DEMONSTRATION" << endl;
    cout << "====================================" << endl;

    BankManagementSystem bms;

    // Create customers
    bms.createCustomer("John Doe", "123 Main St", "555-0101");
    bms.createCustomer("Jane Smith", "456 Oak Ave", "555-0102");
    bms.createCustomer("Bob Johnson", "789 Pine Rd", "555-0103");

    // Create accounts
    bms.createSavingsAccount("CUST1", 1000.0);
    bms.createCheckingAccount("CUST1", 500.0);
    bms.createSavingsAccount("CUST2", 2000.0);
    bms.createFixedDepositAccount("CUST3", 5000.0);

    // Perform transactions
    bms.deposit("ACC1", 500.0);
    bms.withdraw("ACC1", 200.0);
    bms.deposit("ACC2", 300.0);
    bms.transfer("ACC1", "ACC2", 100.0);

    // Calculate interest
    bms.calculateInterestForAll();

    // Generate report
    bms.generateReport();

    // Save data
    bms.saveToFile();
}

/*
==========================================
PRACTICE DRY RUNS - BANK MANAGEMENT
==========================================

Practice Problem 1: Simple Account Class
---------------------------------------
Create a simple Account class with:
- accountNumber (string)
- balance (double)
- deposit() and withdraw() methods
- display() method

Practice Problem 2: Account Inheritance
--------------------------------------
Create SavingsAccount and CheckingAccount classes:
- Inherit from Account
- Add interest rate for savings
- Add overdraft limit for checking
- Override withdraw() methods

Practice Problem 3: Static Account Counter
-----------------------------------------
Add static counter to track total accounts.
Create static method to get total count.

Practice Problem 4: Operator Overloading
---------------------------------------
Overload + operator to add balances.
Overload == operator to compare accounts.
Overload << operator for output.

Practice Problem 5: Exception Handling
-------------------------------------
Create custom exceptions for insufficient funds.
Throw exception when withdrawal exceeds balance.

Practice Problem 6: Template Account Manager
-------------------------------------------
Create template class to manage any type of account.
Implement add, remove, find operations.

Practice Problem 7: Friend Function
----------------------------------
Create friend function to calculate total bank balance.
Access private members of Account classes.

Practice Problem 8: Virtual Functions
------------------------------------
Create base Account with virtual calculateInterest().
Implement different interest calculations in derived classes.

Practice Problem 9: Smart Pointers
---------------------------------
Use shared_ptr for account management.
Demonstrate automatic memory management.

Practice Problem 10: Transaction History
---------------------------------------
Create Transaction class with vector storage.
Implement add, display, and search operations.
*/

// ==========================================
// PRACTICE SOLUTIONS
// ==========================================

// Practice 1: Simple Account Class
class SimpleAccount {
private:
    string accountNumber;
    double balance;
public:
    SimpleAccount(string accNum, double bal) : accountNumber(accNum), balance(bal) {
        cout << "Account created: " << accountNumber << endl;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        }
    }
    
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        } else {
            cout << "Insufficient funds or invalid amount" << endl;
        }
    }
    
    void display() const {
        cout << "Account: " << accountNumber << ", Balance: $" << balance << endl;
    }
    
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
};

// Practice 2: Account Inheritance
class BaseAccount {
protected:
    string accountNumber;
    double balance;
public:
    BaseAccount(string accNum, double bal) : accountNumber(accNum), balance(bal) {}
    virtual ~BaseAccount() {}
    
    virtual void deposit(double amount) {
        if (amount > 0) balance += amount;
    }
    
    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
    }
    
    virtual void display() const {
        cout << "Account: " << accountNumber << ", Balance: $" << balance << endl;
    }
    
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
};

class SimpleSavingsAccount : public BaseAccount {
private:
    double interestRate;
public:
    SimpleSavingsAccount(string accNum, double bal, double rate) 
        : BaseAccount(accNum, bal), interestRate(rate) {}
    
    void calculateInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Interest added: $" << interest << endl;
    }
    
    void display() const override {
        cout << "Savings Account: " << accountNumber << ", Balance: $" << balance 
             << ", Rate: " << (interestRate * 100) << "%" << endl;
    }
};

class SimpleCheckingAccount : public BaseAccount {
private:
    double overdraftLimit;
public:
    SimpleCheckingAccount(string accNum, double bal, double overdraft) 
        : BaseAccount(accNum, bal), overdraftLimit(overdraft) {}
    
    void withdraw(double amount) override {
        if (amount > 0 && (balance - amount) >= -overdraftLimit) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        } else {
            cout << "Withdrawal exceeds overdraft limit" << endl;
        }
    }
    
    void display() const override {
        cout << "Checking Account: " << accountNumber << ", Balance: $" << balance 
             << ", Overdraft: $" << overdraftLimit << endl;
    }
};

// Practice 3: Static Account Counter
class AccountCounter {
private:
    string accountNumber;
    static int totalAccounts;
public:
    AccountCounter(string accNum) : accountNumber(accNum) {
        totalAccounts++;
    }
    ~AccountCounter() {
        totalAccounts--;
    }
    static int getTotal() { return totalAccounts; }
};
int AccountCounter::totalAccounts = 0;

// Practice 4: Operator Overloading
class AccountOp {
private:
    string accountNumber;
    double balance;
public:
    AccountOp(string accNum, double bal) : accountNumber(accNum), balance(bal) {}
    
    AccountOp operator+(const AccountOp& other) const {
        return AccountOp("COMBINED", balance + other.balance);
    }
    
    bool operator==(const AccountOp& other) const {
        return accountNumber == other.accountNumber;
    }
    
    friend ostream& operator<<(ostream& os, const AccountOp& acc) {
        os << "Account[" << acc.accountNumber << ": $" << acc.balance << "]";
        return os;
    }
    
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
};

// Practice 5: Exception Handling
class BankException : public exception {
private:
    string message;
public:
    BankException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class AccountException {
private:
    string accountNumber;
    double balance;
public:
    AccountException(string accNum, double bal) : accountNumber(accNum), balance(bal) {}
    
    void withdraw(double amount) {
        if (amount > balance) {
            throw BankException("Insufficient funds in account " + accountNumber);
        }
        balance -= amount;
    }
    
    double getBalance() const { return balance; }
};

// Practice 6: Template Account Manager
template<typename T>
class AccountManager {
private:
    vector<T*> accounts;
public:
    void addAccount(T* account) {
        accounts.push_back(account);
    }
    
    void removeAccount(string accountNumber) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if ((*it)->getAccountNumber() == accountNumber) {
                delete *it;
                accounts.erase(it);
                break;
            }
        }
    }
    
    T* findAccount(string accountNumber) {
        for (auto account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;
    }
    
    void displayAll() {
        for (auto account : accounts) {
            account->display();
        }
    }
    
    ~AccountManager() {
        for (auto account : accounts) {
            delete account;
        }
    }
};

// Practice 7: Friend Function
class AccountFriend {
private:
    string accountNumber;
    double balance;
    static vector<AccountFriend*> allAccounts;
public:
    AccountFriend(string accNum, double bal) : accountNumber(accNum), balance(bal) {
        allAccounts.push_back(this);
    }
    
    friend double calculateTotalBalance() {
        double total = 0.0;
        for (auto account : allAccounts) {
            total += account->balance;
        }
        return total;
    }
    
    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
};
vector<AccountFriend*> AccountFriend::allAccounts;

// Practice 8: Virtual Functions
class VirtualAccount {
protected:
    string accountNumber;
    double balance;
public:
    VirtualAccount(string accNum, double bal) : accountNumber(accNum), balance(bal) {}
    virtual ~VirtualAccount() {}
    
    virtual double calculateInterest() const {
        return 0.0; // Base class no interest
    }
    
    virtual void display() const {
        cout << "Account: " << accountNumber << ", Balance: $" << balance << endl;
    }
};

class VirtualSavings : public VirtualAccount {
private:
    double interestRate;
public:
    VirtualSavings(string accNum, double bal, double rate) 
        : VirtualAccount(accNum, bal), interestRate(rate) {}
    
    double calculateInterest() const override {
        return balance * interestRate;
    }
    
    void display() const override {
        cout << "Savings: " << accountNumber << ", Balance: $" << balance 
             << ", Interest: $" << calculateInterest() << endl;
    }
};

class VirtualFixed : public VirtualAccount {
private:
    double interestRate;
public:
    VirtualFixed(string accNum, double bal, double rate) 
        : VirtualAccount(accNum, bal), interestRate(rate) {}
    
    double calculateInterest() const override {
        return balance * interestRate * 0.5; // Fixed deposit interest
    }
    
    void display() const override {
        cout << "Fixed: " << accountNumber << ", Balance: $" << balance 
             << ", Interest: $" << calculateInterest() << endl;
    }
};

// Practice 9: Smart Pointers
class SmartAccount {
private:
    string accountNumber;
    double balance;
public:
    SmartAccount(string accNum, double bal) : accountNumber(accNum), balance(bal) {
        cout << "Smart Account created: " << accountNumber << endl;
    }
    
    ~SmartAccount() {
        cout << "Smart Account destroyed: " << accountNumber << endl;
    }
    
    void display() const {
        cout << "Smart Account: " << accountNumber << ", Balance: $" << balance << endl;
    }
    
    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
};

// Practice 10: Transaction History
class SimpleTransaction {
private:
    string transactionId;
    double amount;
    string type;
    static int transactionCounter;
public:
    SimpleTransaction(double amt, string t) : amount(amt), type(t) {
        transactionCounter++;
        transactionId = "TXN" + to_string(transactionCounter);
    }
    
    void display() const {
        cout << "Transaction: " << transactionId << ", Amount: $" << amount 
             << ", Type: " << type << endl;
    }
    
    string getTransactionId() const { return transactionId; }
    double getAmount() const { return amount; }
    string getType() const { return type; }
};
int SimpleTransaction::transactionCounter = 0;

class TransactionHistory {
private:
    vector<SimpleTransaction> transactions;
public:
    void addTransaction(double amount, string type) {
        transactions.emplace_back(amount, type);
    }
    
    void displayAll() {
        for (const auto& txn : transactions) {
            txn.display();
        }
    }
    
    SimpleTransaction* findTransaction(string transactionId) {
        for (auto& txn : transactions) {
            if (txn.getTransactionId() == transactionId) {
                return &txn;
            }
        }
        return nullptr;
    }
    
    double getTotalAmount() {
        double total = 0.0;
        for (const auto& txn : transactions) {
            total += txn.getAmount();
        }
        return total;
    }
};

// ==========================================
// PRACTICE DEMONSTRATION
// ==========================================

void demonstrateBankPracticeProblems() {
    cout << "\n=== BANK PRACTICE PROBLEMS DEMONSTRATION ===\n";
    
    // Practice 1: Simple Account
    cout << "\n1. Simple Account Class:";
    SimpleAccount acc1("ACC001", 1000.0);
    acc1.deposit(500.0);
    acc1.withdraw(200.0);
    acc1.display();
    
    // Practice 2: Account Inheritance
    cout << "\n2. Account Inheritance:";
    SimpleSavingsAccount sav1("SAV001", 2000.0, 0.05);
    SimpleCheckingAccount chk1("CHK001", 1500.0, 500.0);
    sav1.calculateInterest();
    sav1.display();
    chk1.withdraw(1800.0); // Within overdraft limit
    chk1.display();
    
    // Practice 3: Static Account Counter
    cout << "\n3. Static Account Counter:";
    AccountCounter ac1("ACC001");
    AccountCounter ac2("ACC002");
    cout << "Total accounts: " << AccountCounter::getTotal() << endl;
    
    // Practice 4: Operator Overloading
    cout << "\n4. Operator Overloading:";
    AccountOp ao1("ACC001", 1000.0);
    AccountOp ao2("ACC002", 2000.0);
    AccountOp ao3("ACC001", 1000.0);
    cout << "ao1: " << ao1 << endl;
    cout << "ao1 + ao2: " << (ao1 + ao2) << endl;
    cout << "ao1 == ao2: " << (ao1 == ao2) << endl;
    cout << "ao1 == ao3: " << (ao1 == ao3) << endl;
    
    // Practice 5: Exception Handling
    cout << "\n5. Exception Handling:";
    try {
        AccountException ae1("ACC001", 500.0);
        ae1.withdraw(600.0); // This will throw exception
    } catch (const BankException& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    // Practice 6: Template Account Manager
    cout << "\n6. Template Account Manager:";
    AccountManager<SimpleAccount> manager;
    manager.addAccount(new SimpleAccount("ACC001", 1000.0));
    manager.addAccount(new SimpleAccount("ACC002", 2000.0));
    manager.displayAll();
    SimpleAccount* found = manager.findAccount("ACC001");
    if (found) found->display();
    
    // Practice 7: Friend Function
    cout << "\n7. Friend Function:";
    AccountFriend af1("ACC001", 1000.0);
    AccountFriend af2("ACC002", 2000.0);
    cout << "Total balance: $" << calculateTotalBalance() << endl;
    
    // Practice 8: Virtual Functions
    cout << "\n8. Virtual Functions:";
    VirtualAccount* va1 = new VirtualSavings("SAV001", 1000.0, 0.05);
    VirtualAccount* va2 = new VirtualFixed("FIX001", 5000.0, 0.08);
    va1->display();
    va2->display();
    delete va1;
    delete va2;
    
    // Practice 9: Smart Pointers
    cout << "\n9. Smart Pointers:";
    {
        shared_ptr<SmartAccount> smart1 = make_shared<SmartAccount>("ACC001", 1000.0);
        shared_ptr<SmartAccount> smart2 = make_shared<SmartAccount>("ACC002", 2000.0);
        smart1->display();
        smart2->display();
        cout << "Smart pointers will be automatically destroyed" << endl;
    }
    
    // Practice 10: Transaction History
    cout << "\n10. Transaction History:";
    TransactionHistory history;
    history.addTransaction(1000.0, "DEPOSIT");
    history.addTransaction(500.0, "WITHDRAWAL");
    history.addTransaction(200.0, "TRANSFER");
    history.displayAll();
    cout << "Total transaction amount: $" << history.getTotalAmount() << endl;
}

// ==========================================
// TRICKY DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class Base {
    int x;
public:
    Base(int val) : x(val) { cout << "Base(" << x << ")"; }
    virtual ~Base() { cout << "~Base(" << x << ")"; }
};
class Derived : public Base {
    int y;
public:
    Derived(int val1, int val2) : Base(val1), y(val2) { cout << "Derived(" << y << ")"; }
    ~Derived() { cout << "~Derived(" << y << ")"; }
};
int main() {
    Base* ptr = new Derived(10, 20);
    delete ptr;
    return 0;
}
Answer: Base(10)Derived(20)~Derived(20)~Base(10)

Problem 2: What will be the output?
class Account {
    static int count;
    int id;
public:
    Account() { id = ++count; cout << "Account" << id; }
    ~Account() { cout << "~Account" << id; }
};
int Account::count = 0;
int main() {
    Account a1, a2;
    { Account a3; }
    return 0;
}
Answer: Account1Account2Account3~Account3~Account2~Account1

Problem 3: What will be the output?
class Bank {
    int balance;
public:
    Bank(int b) : balance(b) {}
    Bank operator+(const Bank& other) {
        return Bank(balance + other.balance + 100);
    }
    friend ostream& operator<<(ostream& os, const Bank& bank) {
        return os << "Bank($" << bank.balance << ")";
    }
};
int main() {
    Bank b1(1000), b2(2000);
    cout << b1 + b2;
    return 0;
}
Answer: Bank($3100)
*/

int main() {
    demonstrateBankManagement();
    return 0;
} 