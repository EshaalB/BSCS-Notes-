/*
FILE HANDLING PRACTICE QUESTIONS
================================

This file contains various practice problems using file handling:
- Student record management
- Inventory system
- Log file processing
- Data analysis
- File encryption/decryption
- CSV processing
- Binary file operations
- File statistics
- Search and replace
- File comparison
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Structure for student record
struct Student {
    string name;
    int rollNo;
    string course;
    double gpa;
};

// Structure for inventory item
struct InventoryItem {
    string name;
    int quantity;
    double price;
    string category;
};

// Function to write student records to file
void writeStudentRecords() {
    ofstream file("students.txt");
    if (file.is_open()) {
        file << "Alice,1001,Computer Science,3.8\n";
        file << "Bob,1002,Mathematics,3.5\n";
        file << "Charlie,1003,Physics,3.9\n";
        file << "Diana,1004,Chemistry,3.7\n";
        file << "Eve,1005,Computer Science,3.6\n";
        file.close();
        cout << "Student records written to file." << endl;
    }
}

// Function to read and display student records
void readStudentRecords() {
    ifstream file("students.txt");
    if (file.is_open()) {
        string line;
        cout << "\nStudent Records:" << endl;
        cout << setw(20) << "Name" << setw(10) << "Roll No" << setw(20) << "Course" << setw(10) << "GPA" << endl;
        cout << string(60, '-') << endl;
        
        while (getline(file, line)) {
            string name, course, gpaStr, rollStr;
            int rollNo;
            double gpa;
            
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            
            name = line.substr(0, pos1);
            rollStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
            course = line.substr(pos2 + 1, pos3 - pos2 - 1);
            gpaStr = line.substr(pos3 + 1);
            
            rollNo = stoi(rollStr);
            gpa = stod(gpaStr);
            
            cout << setw(20) << name << setw(10) << rollNo << setw(20) << course << setw(10) << fixed << setprecision(2) << gpa << endl;
        }
        file.close();
    }
}

// Function to search student by roll number
void searchStudent(int rollNo) {
    ifstream file("students.txt");
    if (file.is_open()) {
        string line;
        bool found = false;
        
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            string rollStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
            
            if (stoi(rollStr) == rollNo) {
                cout << "Student found: " << line << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Student with roll number " << rollNo << " not found." << endl;
        }
        file.close();
    }
}

// Function to write inventory data
void writeInventoryData() {
    ofstream file("inventory.txt");
    if (file.is_open()) {
        file << "Laptop,50,999.99,Electronics\n";
        file << "Mouse,200,25.50,Electronics\n";
        file << "Keyboard,150,45.00,Electronics\n";
        file << "Book,1000,15.99,Books\n";
        file << "Pen,5000,2.50,Stationery\n";
        file << "Paper,2000,10.00,Stationery\n";
        file.close();
        cout << "Inventory data written to file." << endl;
    }
}

// Function to calculate inventory value
void calculateInventoryValue() {
    ifstream file("inventory.txt");
    if (file.is_open()) {
        string line;
        double totalValue = 0.0;
        
        cout << "\nInventory Analysis:" << endl;
        cout << setw(15) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Total Value" << endl;
        cout << string(50, '-') << endl;
        
        while (getline(file, line)) {
            string name, quantityStr, priceStr, category;
            
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            
            name = line.substr(0, pos1);
            quantityStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
            priceStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
            category = line.substr(pos3 + 1);
            
            int quantity = stoi(quantityStr);
            double price = stod(priceStr);
            double itemValue = quantity * price;
            totalValue += itemValue;
            
            cout << setw(15) << name << setw(10) << quantity << setw(10) << fixed << setprecision(2) << price 
                 << setw(15) << itemValue << endl;
        }
        
        cout << string(50, '-') << endl;
        cout << "Total Inventory Value: $" << fixed << setprecision(2) << totalValue << endl;
        file.close();
    }
}

// Function to create log file
void createLogFile() {
    ofstream file("app.log", ios::app);
    if (file.is_open()) {
        file << "2024-01-15 10:30:15 - Application started\n";
        file << "2024-01-15 10:30:20 - User login successful\n";
        file << "2024-01-15 10:35:45 - Data processing completed\n";
        file << "2024-01-15 10:40:12 - File saved successfully\n";
        file << "2024-01-15 10:45:30 - Application closed\n";
        file.close();
        cout << "Log entries written to file." << endl;
    }
}

// Function to analyze log file
void analyzeLogFile() {
    ifstream file("app.log");
    if (file.is_open()) {
        string line;
        int totalEntries = 0;
        int errorCount = 0;
        int successCount = 0;
        
        while (getline(file, line)) {
            totalEntries++;
            if (line.find("error") != string::npos || line.find("Error") != string::npos) {
                errorCount++;
            } else if (line.find("successful") != string::npos || line.find("completed") != string::npos) {
                successCount++;
            }
        }
        
        cout << "\nLog File Analysis:" << endl;
        cout << "Total entries: " << totalEntries << endl;
        cout << "Success entries: " << successCount << endl;
        cout << "Error entries: " << errorCount << endl;
        cout << "Other entries: " << totalEntries - successCount - errorCount << endl;
        
        file.close();
    }
}

// Function to encrypt file content
void encryptFile(string filename) {
    ifstream inputFile(filename);
    ofstream outputFile(filename + ".encrypted");
    
    if (inputFile.is_open() && outputFile.is_open()) {
        char ch;
        while (inputFile.get(ch)) {
            // Simple encryption: shift each character by 3 positions
            if (isalpha(ch)) {
                if (isupper(ch)) {
                    ch = ((ch - 'A' + 3) % 26) + 'A';
                } else {
                    ch = ((ch - 'a' + 3) % 26) + 'a';
                }
            }
            outputFile.put(ch);
        }
        inputFile.close();
        outputFile.close();
        cout << "File encrypted successfully." << endl;
    }
}

// Function to decrypt file content
void decryptFile(string filename) {
    ifstream inputFile(filename);
    ofstream outputFile(filename + ".decrypted");
    
    if (inputFile.is_open() && outputFile.is_open()) {
        char ch;
        while (inputFile.get(ch)) {
            // Simple decryption: shift each character back by 3 positions
            if (isalpha(ch)) {
                if (isupper(ch)) {
                    ch = ((ch - 'A' - 3 + 26) % 26) + 'A';
                } else {
                    ch = ((ch - 'a' - 3 + 26) % 26) + 'a';
                }
            }
            outputFile.put(ch);
        }
        inputFile.close();
        outputFile.close();
        cout << "File decrypted successfully." << endl;
    }
}

// Function to get file statistics
void getFileStats(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file.seekg(0, ios::end);
        long fileSize = file.tellg();
        file.seekg(0, ios::beg);
        
        string line;
        int lineCount = 0;
        int wordCount = 0;
        int charCount = 0;
        
        while (getline(file, line)) {
            lineCount++;
            charCount += line.length();
            
            // Count words
            bool inWord = false;
            for (char ch : line) {
                if (isalpha(ch) && !inWord) {
                    wordCount++;
                    inWord = true;
                } else if (!isalpha(ch)) {
                    inWord = false;
                }
            }
        }
        
        cout << "\nFile Statistics for " << filename << ":" << endl;
        cout << "File size: " << fileSize << " bytes" << endl;
        cout << "Number of lines: " << lineCount << endl;
        cout << "Number of words: " << wordCount << endl;
        cout << "Number of characters: " << charCount << endl;
        
        file.close();
    }
}

// Function to search and replace in file
void searchAndReplace(string filename, string searchStr, string replaceStr) {
    ifstream inputFile(filename);
    ofstream outputFile(filename + ".temp");
    
    if (inputFile.is_open() && outputFile.is_open()) {
        string line;
        int replacements = 0;
        
        while (getline(inputFile, line)) {
            size_t pos = 0;
            while ((pos = line.find(searchStr, pos)) != string::npos) {
                line.replace(pos, searchStr.length(), replaceStr);
                pos += replaceStr.length();
                replacements++;
            }
            outputFile << line << endl;
        }
        
        inputFile.close();
        outputFile.close();
        
        // Replace original file with modified content
        remove(filename.c_str());
        rename((filename + ".temp").c_str(), filename.c_str());
        
        cout << "Search and replace completed. " << replacements << " replacements made." << endl;
    }
}

int main() {
    cout << "FILE HANDLING PRACTICE QUESTIONS" << endl;
    cout << "================================" << endl;
    
    int choice;
    
    cout << "\nChoose a practice question (1-10): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. Student Record Management
        cout << "\n=== 1. Student Record Management ===" << endl;
        writeStudentRecords();
        readStudentRecords();
        
        int rollNo;
        cout << "\nEnter roll number to search: ";
        cin >> rollNo;
        searchStudent(rollNo);
    }
    
    else if (choice == 2) {
        // 2. Inventory System
        cout << "\n=== 2. Inventory System ===" << endl;
        writeInventoryData();
        calculateInventoryValue();
    }
    
    else if (choice == 3) {
        // 3. Log File Processing
        cout << "\n=== 3. Log File Processing ===" << endl;
        createLogFile();
        analyzeLogFile();
    }
    
    else if (choice == 4) {
        // 4. File Encryption
        cout << "\n=== 4. File Encryption ===" << endl;
        string filename;
        cout << "Enter filename to encrypt: ";
        cin >> filename;
        
        // Create a sample file first
        ofstream sampleFile(filename);
        if (sampleFile.is_open()) {
            sampleFile << "This is a secret message that needs to be encrypted.\n";
            sampleFile << "It contains sensitive information.\n";
            sampleFile.close();
        }
        
        encryptFile(filename);
        cout << "Original file content:" << endl;
        ifstream originalFile(filename);
        string line;
        while (getline(originalFile, line)) {
            cout << line << endl;
        }
        originalFile.close();
    }
    
    else if (choice == 5) {
        // 5. File Decryption
        cout << "\n=== 5. File Decryption ===" << endl;
        string filename;
        cout << "Enter encrypted filename: ";
        cin >> filename;
        
        decryptFile(filename);
    }
    
    else if (choice == 6) {
        // 6. File Statistics
        cout << "\n=== 6. File Statistics ===" << endl;
        string filename;
        cout << "Enter filename to analyze: ";
        cin >> filename;
        
        getFileStats(filename);
    }
    
    else if (choice == 7) {
        // 7. Search and Replace
        cout << "\n=== 7. Search and Replace ===" << endl;
        string filename, searchStr, replaceStr;
        cout << "Enter filename: ";
        cin >> filename;
        cout << "Enter text to search: ";
        cin >> searchStr;
        cout << "Enter replacement text: ";
        cin >> replaceStr;
        
        searchAndReplace(filename, searchStr, replaceStr);
    }
    
    else if (choice == 8) {
        // 8. Binary File Operations
        cout << "\n=== 8. Binary File Operations ===" << endl;
        
        // Write binary data
        ofstream binaryFile("data.bin", ios::binary);
        if (binaryFile.is_open()) {
            int numbers[] = {10, 20, 30, 40, 50};
            binaryFile.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
            binaryFile.close();
            cout << "Binary data written to file." << endl;
        }
        
        // Read binary data
        ifstream readBinaryFile("data.bin", ios::binary);
        if (readBinaryFile.is_open()) {
            int numbers[5];
            readBinaryFile.read(reinterpret_cast<char*>(numbers), sizeof(numbers));
            cout << "Binary data read: ";
            for (int i = 0; i < 5; i++) {
                cout << numbers[i] << " ";
            }
            cout << endl;
            readBinaryFile.close();
        }
    }
    
    else if (choice == 9) {
        // 9. CSV Processing
        cout << "\n=== 9. CSV Processing ===" << endl;
        
        // Create CSV file
        ofstream csvFile("data.csv");
        if (csvFile.is_open()) {
            csvFile << "Name,Age,City,Salary\n";
            csvFile << "John,25,New York,50000\n";
            csvFile << "Jane,30,Los Angeles,60000\n";
            csvFile << "Mike,35,Chicago,55000\n";
            csvFile << "Sarah,28,Boston,52000\n";
            csvFile.close();
            cout << "CSV file created." << endl;
        }
        
        // Read and process CSV
        ifstream readCsvFile("data.csv");
        if (readCsvFile.is_open()) {
            string line;
            bool firstLine = true;
            
            cout << "\nCSV Data:" << endl;
            while (getline(readCsvFile, line)) {
                if (firstLine) {
                    firstLine = false;
                    continue; // Skip header
                }
                
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                size_t pos3 = line.find(',', pos2 + 1);
                
                string name = line.substr(0, pos1);
                string age = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string city = line.substr(pos2 + 1, pos3 - pos2 - 1);
                string salary = line.substr(pos3 + 1);
                
                cout << "Name: " << name << ", Age: " << age << ", City: " << city << ", Salary: " << salary << endl;
            }
            readCsvFile.close();
        }
    }
    
    else if (choice == 10) {
        // 10. File Comparison
        cout << "\n=== 10. File Comparison ===" << endl;
        
        // Create two similar files
        ofstream file1("file1.txt");
        ofstream file2("file2.txt");
        
        if (file1.is_open() && file2.is_open()) {
            file1 << "Hello World\n";
            file1 << "This is file 1\n";
            file1 << "Line 3\n";
            file1.close();
            
            file2 << "Hello World\n";
            file2 << "This is file 2\n";
            file2 << "Line 3\n";
            file2.close();
            
            cout << "Two files created for comparison." << endl;
        }
        
        // Compare files
        ifstream compareFile1("file1.txt");
        ifstream compareFile2("file2.txt");
        
        if (compareFile1.is_open() && compareFile2.is_open()) {
            string line1, line2;
            int lineNumber = 1;
            bool identical = true;
            
            while (getline(compareFile1, line1) && getline(compareFile2, line2)) {
                if (line1 != line2) {
                    cout << "Difference at line " << lineNumber << ":" << endl;
                    cout << "File1: " << line1 << endl;
                    cout << "File2: " << line2 << endl;
                    identical = false;
                }
                lineNumber++;
            }
            
            if (identical) {
                cout << "Files are identical." << endl;
            } else {
                cout << "Files are different." << endl;
            }
            
            compareFile1.close();
            compareFile2.close();
        }
    }
    
    else {
        cout << "Invalid choice! Please enter 1-10." << endl;
    }
    
    return 0;
} 