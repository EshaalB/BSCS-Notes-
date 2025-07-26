#include <iostream>
using namespace std;

// Function is a block of code that performs a specific task
// It is used to avoid repetition of code
// It is used to make the code more readable and maintainable
// It is used to make the code more efficient

  //User defined functions
int add(int a, int b) { // function declaration
    return a + b; // function body
} // function definition
int sub(int a, int b) { // function declaration
    return a - b;
} // function definition    

//parts of function
// return type (int, float, double, char, string, bool)
// function name (add, sub, mul, div, mod)
// parameters (int a, int b)
// function body
// function call



int main() {
    //Built in functions
     pow(2,3);
     sqrt(16);
     sin(30);
     cos(30);
     tan(30);
     log(10);
     exp(1); 

     cout << add(10, 20) << endl; // function call
     cout << sub(10, 20) << endl; // function call
    
    return 0;
}

// Function call stack is a stack of function calls
// It is used to store the return address of the function
// It is used to store the local variables of the function
// It is used to store the parameters of the function

// How it works ?
// 1. When a function is called, the return address is pushed onto the stack first thing will be picked last thing will be pushed
// 2. The local variables are pushed onto the stack
// 3. The parameters are pushed onto the stack
// 4. The function body is executed and the return value is pushed onto the stack   
// 5. The return value is popped from the stack
// 6. The return address is popped from the stack






