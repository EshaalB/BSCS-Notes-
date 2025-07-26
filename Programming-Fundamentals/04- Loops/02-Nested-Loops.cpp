 #include <iostream>
 using namespace std;

 //Nested loop is a loop inside a loop
 //The inner loop will be executed for each iteration of the outer loop
 //The outer loop will be executed for each iteration of the inner loop

 int main() {
    // nested loop
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            cout << i << " " << j << endl;
        }
    }
    // Patterns using nested loops
    // used to build better logic and better understanding of loops
    //If we start from 0 then dont use <= , use < as it would print extra value 

    // Note : we can also add characters the main is that we need to convert it to char 
    // char ch = 'A'+row -1 ;
    // char ch = 'A'+n-i;

    // Example 1: Print a square pattern of stars
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
 }
 