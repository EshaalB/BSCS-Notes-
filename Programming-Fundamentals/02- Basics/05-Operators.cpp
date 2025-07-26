#include <iostream>
using namespace std;
// Operators are used to perform operations on variables and values.
int main() {
    // Arithmetic Operators
    int a = 10;
    int b = 20;
    cout << a + b << endl; // 30
    cout << a - b << endl; // -10
    cout << a * b << endl; // 200
    cout << a / b << endl; // 0
    cout << a % b << endl; // 10

    // Assignment Operators
    int c = 10;
    int d = 20;
    cout << c = d << endl; // 20
    cout << c += d << endl; // 30
    cout << c -= d << endl; // 10
    cout << c *= d << endl; // 200
    cout << c /= d << endl; // 0

    // Comparison/Relational Operators
    int e = 10;
    int f = 20;
    cout << e == f << endl; // 0
    cout << e != f << endl; // 1
    cout << e > f << endl; // 0
    cout << e < f << endl; // 1
    cout << e >= f << endl; // 0

    // Logical Operators
    int g = 10;
    int h = 20;
    cout << g && h << endl; // 1 AND operator
    cout << g || h << endl; // 1 OR operator
    cout << !g << endl; // 0 NOT operator

    // Bitwise Operators    
    int i = 10;
    int j = 20;
    cout << i & j << endl; // 0 AND operator
    cout << i | j << endl; // 30 OR operator
    cout << i ^ j << endl; // 30 XOR operator
    cout << ~i << endl; // -11 NOT operator
    cout << i << i << endl; // 10 Left shift operator
    cout << i >> j << endl; // 10 Right shift operator

    // Increment and Decrement Operators
    //Prefix and Postfix
    int k = 10;
    cout << k++ << endl; // 10
    cout << k-- << endl; // 11
    cout << ++k << endl; // 12
    cout << --k << endl; // 11  


    //Ternary Operator
    int n = 10;
    int o = 20;
    cout << (n > o ? n : o) << endl; // 20

    //Comma Operator
    int p = 10;
    int q = 20;
    cout << (p, q) << endl; // 20

  
    return 0;
}
 