#include <iostream>  
using namespace std;  
// Conditional Statements are used to execute a block of code if a condition is true.
int main() {  
    // if else statement
    int age;
    cout << "Enter your age: ";
    cin >> age;
    if (age >= 18) {
        cout << "You are an adult" << endl;
    } else {
        cout << "You are not an adult" << endl;
    }

    // if else if statement
    int marks;
    cout << "Enter your marks: ";
    cin >> marks;
    if (marks >= 90) {
        cout << "You got A grade" << endl;
    } else if (marks >= 80) {
    return 0; 

    // Switch statement
    // Default is optional 
    //We can also make nested switch but it is not recommended
    // Continue is not valid in switch 
    // Break is used to stop the execution of the switch statement
    // We can also use exit to terminate the program 
    int day;
    cout << "Enter the day number: ";
    cin >> day;
    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;  
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl;
            break;
        default:
            cout << "Invalid day" << endl;
            break;
    }
    return 0;
}


    // nested if else statement
    int marks;
    cout << "Enter your marks: ";
    cin >> marks;
    if (marks >= 90) {
        cout << "You got A grade" << endl;
    } else if (marks >= 80) {
        cout << "You got B grade" << endl;
    } else if (marks >= 70) {       
        cout << "You got C grade" << endl;
    } else if (marks >= 60) {
        cout << "You got D grade" << endl;
    } else {
        cout << "You got F grade" << endl;
    }
    return 0;
}
 