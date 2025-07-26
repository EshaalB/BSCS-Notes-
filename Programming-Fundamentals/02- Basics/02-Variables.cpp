#include <iostream>  
using namespace std;  

int main() {  
   int a = 10;
   float b = 10.5;
   double c = 10.5;
   char d = 'a';
   bool e = true;
   string f = "Hello";
   cout << a << endl; // 10 
   cout << b << endl; // 10.5
   cout << c << endl; // 10.5
   cout << d << endl; // a
   cout << e << endl; // 1
   cout << f << endl; // Hello  

   cout << sizeof(a) << endl; // 4
   cout << sizeof(b) << endl; // 4
   cout << sizeof(c) << endl; // 8
   cout << sizeof(d) << endl; // 1
   cout << sizeof(e) << endl; // 1
   cout << sizeof(f) << endl; // 2
   
}
 // Data Types:
 // int: integer (whole numbers) has 4 bytes
 // float: floating point numbers has 4 bytes
 // double: double precision floating point numbers has 8 bytes
 // char: single character has 1 byte
 // bool: boolean (true or false) has 1 byte
//  string: sequence of characters has 2 bytes
// Variables are declared using a data type and a name.

// Note : Name variables differently from the data types and keep them meaningful.