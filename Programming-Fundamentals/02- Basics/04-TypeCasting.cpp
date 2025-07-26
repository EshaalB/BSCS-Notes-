#include <iostream>
using namespace std;
// Typecasting is the process of converting one data type to another.
int main() {
   //Implicit Typecasting
   int a = 10;
   float b = 10.5;
   cout << a + b << endl; // 20.5
   //Explicit Typecasting
   int c = 10;
   int d = 20;
   // static_cast<type>(expression)
   cout << static_cast<float>(c) + d << endl; // 30.0
   cout << static_cast<int>(c) + d << endl; // 30
   cout << static_cast<int>(c) + static_cast<int>(d) << endl; // 30
   cout << static_cast<int>(c) + d << endl; // 30
}
 