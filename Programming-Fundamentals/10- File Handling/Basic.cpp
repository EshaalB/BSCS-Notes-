/*
File Handling in C++ - Basic Operations
=======================================

File handling allows us to:
1. Read data from files
2. Write data to files
3. Create new files
4. Modify existing files
5. Delete files

This program demonstrates the most common file operations with detailed explanations.
*/

#include <iostream>
#include <fstream>  // Required for file operations
#include <string>
using namespace std;

int main() {
    cout << "=== FILE HANDLING BASICS ===\n\n";
    
    // ========================================
    // 1. WRITING TO A FILE (OUTPUT)
    // ========================================
    cout << "1. Writing to a file...\n";
    
    // Create an output file stream object
    // ofstream = output file stream
    // "data.txt" = name of the file to create/write to
    ofstream outFile("data.txt");
    
    // Check if file opened successfully
    if (outFile.is_open()) {
        cout << "   ✓ File 'data.txt' opened successfully for writing\n";
        
        // Write different types of data to the file
        outFile << "Hello from C++ File Handling!\n";  // String
        outFile << "This is line 2\n";                 // Another string
        outFile << 42 << endl;                         // Integer
        outFile << 3.14 << endl;                       // Float
        outFile << "Final line\n";                     // Last string
        
        // Always close the file when done writing
        outFile.close();
        cout << "   ✓ Data written and file closed\n";
    } else {
        cout << "   ✗ Error: Could not open file for writing\n";
        return 1;  // Exit program with error code
    }
    
    cout << endl;
    
    // ========================================
    // 2. READING FROM A FILE (INPUT)
    // ========================================
    cout << "2. Reading from the file...\n";
    
    // Create an input file stream object
    // ifstream = input file stream
    ifstream inFile("data.txt");
    
    if (inFile.is_open()) {
        cout << "   ✓ File 'data.txt' opened successfully for reading\n";
        cout << "   File contents:\n";
        cout << "   --------------------\n";
        
        string line;  // Variable to store each line
        
        // Read file line by line
        // getline() reads one line at a time
        // Returns true if line was read, false if end of file
        while (getline(inFile, line)) {
            cout << "   " << line << endl;
        }
        
        cout << "   --------------------\n";
        inFile.close();
        cout << "   ✓ File closed after reading\n";
    } else {
        cout << "   ✗ Error: Could not open file for reading\n";
    }
    
    cout << endl;
    
    // ========================================
    // 3. APPENDING TO A FILE
    // ========================================
    cout << "3. Appending to the file...\n";
    
    // Open file in append mode
    // ios::app = append mode (adds to end of file)
    // Without ios::app, it would overwrite the entire file
    ofstream appendFile("data.txt", ios::app);
    
    if (appendFile.is_open()) {
        cout << "   ✓ File opened in append mode\n";
        
        // Add new content to the end of the file
        appendFile << "\n--- APPENDED CONTENT ---\n";
        appendFile << "This line was added later\n";
        appendFile << "Appending is useful for logs\n";
        
        appendFile.close();
        cout << "   ✓ Content appended and file closed\n";
    } else {
        cout << "   ✗ Error: Could not open file for appending\n";
    }
    
    cout << endl;
    
    // ========================================
    // 4. READING NUMBERS FROM FILE
    // ========================================
    cout << "4. Creating a file with numbers...\n";
    
    // Create a new file with numbers
    ofstream numberFile("numbers.txt");
    if (numberFile.is_open()) {
        numberFile << "10 20 30 40 50\n";  // Space-separated numbers
        numberFile << "1.5 2.5 3.5\n";     // Floating point numbers
        numberFile.close();
        cout << "   ✓ Numbers file created\n";
    }
    
    cout << "   Reading numbers from file...\n";
    ifstream readNumbers("numbers.txt");
    if (readNumbers.is_open()) {
        int num;
        double decimal;
        
        cout << "   Integers: ";
        // Read integers until end of line
        while (readNumbers >> num) {
            cout << num << " ";
        }
        
        cout << "\n   Decimals: ";
        // Reset file pointer to beginning
        readNumbers.clear();  // Clear error flags
        readNumbers.seekg(0); // Go to beginning of file
        
        // Skip first line and read second line
        string temp;
        getline(readNumbers, temp);  // Skip first line
        
        // Read floating point numbers
        while (readNumbers >> decimal) {
            cout << decimal << " ";
        }
        
        cout << endl;
        readNumbers.close();
    }
    
    cout << endl;
    
    // ========================================
    // 5. FILE MODES EXPLANATION
    // ========================================
    cout << "5. File Modes Summary:\n";
    cout << "   • ios::out    - Write mode (default for ofstream)\n";
    cout << "   • ios::in     - Read mode (default for ifstream)\n";
    cout << "   • ios::app    - Append mode (add to end)\n";
    cout << "   • ios::trunc  - Truncate mode (clear file first)\n";
    cout << "   • ios::binary - Binary mode (not text)\n";
    cout << endl;
    
    // ========================================
    // 6. ERROR HANDLING EXAMPLE
    // ========================================
    cout << "6. Error handling example...\n";
    
    // Try to open a non-existent file
    ifstream errorFile("nonexistent.txt");
    if (!errorFile.is_open()) {
        cout << "   ✓ Correctly detected that 'nonexistent.txt' doesn't exist\n";
    }
    
    // ========================================
    // 7. PRACTICAL EXAMPLE: STUDENT RECORDS
    // ========================================
    cout << "\n7. Practical Example: Student Records\n";
    
    // Write student records
    ofstream studentFile("students.txt");
    if (studentFile.is_open()) {
        studentFile << "Alice,Computer Science,3.8\n";
        studentFile << "Bob,Mathematics,3.5\n";
        studentFile << "Charlie,Physics,3.9\n";
        studentFile.close();
        cout << "   ✓ Student records written\n";
    }
    
    // Read and display student records
    ifstream readStudents("students.txt");
    if (readStudents.is_open()) {
        cout << "   Student Records:\n";
        cout << "   Name     | Major              | GPA\n";
        cout << "   ---------|-------------------|-----\n";
        
        string name, major;
        double gpa;
        char comma;  // To read the comma separator
        
        while (getline(readStudents, name, ',') && 
               getline(readStudents, major, ',') && 
               readStudents >> gpa) {
            
            cout << "   " << name << "      | " << major;
            // Add spacing for alignment
            for (int i = major.length(); i < 18; i++) {
                cout << " ";
            }
            cout << "| " << gpa << endl;
            
            // Clear any remaining characters (like newline)
            readStudents.ignore();
        }
        
        readStudents.close();
    }
    
    cout << "\n=== FILE HANDLING COMPLETE ===\n";
    cout << "Check the generated files: data.txt, numbers.txt, students.txt\n";
    
    return 0;
}

/*
SUMMARY OF KEY CONCEPTS:
========================

1. File Streams:
   - ofstream: Output file stream (for writing)
   - ifstream: Input file stream (for reading)
   - fstream: File stream (for both reading and writing)

2. Important Methods:
   - open(): Opens a file
   - close(): Closes a file
   - is_open(): Checks if file is open
   - getline(): Reads a line of text
   - >> operator: Reads formatted data
   - << operator: Writes formatted data

3. File Modes:
   - ios::out: Write mode
   - ios::in: Read mode
   - ios::app: Append mode
   - ios::trunc: Truncate mode

4. Best Practices:
   - Always check if file opened successfully
   - Always close files when done
   - Use appropriate error handling
   - Choose the right file mode for your needs

5. Common Operations:
   - Writing text: outFile << "text"
   - Reading text: getline(inFile, stringVariable)
   - Reading numbers: inFile >> numberVariable
   - Appending: ofstream file("name.txt", ios::app)
*/
