 #include <iostream>
 using namespace std;

 //Scope is the region of the program where a variable is defined
 //It is the region of the program where a variable is accessible

 
 //Global scope is the region of the program where a variable is defined outside of any function
 int g= 10; // global variable

 int main() { // local scope is the region of the program where a variable is defined inside of a function
    // local variable
    int a = 10;
    int b = 20;
    int c = 30;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << g << endl;
    return 0;
 }











 