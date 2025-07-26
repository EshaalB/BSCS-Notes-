#include <iostream>
using namespace std;

int main() {
  int a = 10;
  int b = -10;
  cout << a << endl; // 10  
  cout << b << endl; // -10
  cout << sizeof(a) << endl; // 4
  cout << sizeof(b) << endl; // 4

  unsigned int c = -10;
  cout << c << endl; // 4294967286
  cout << sizeof(c) << endl; // 4
  return 0;
}
// How are data stored in the memory?
//Data is stored in the memory in the form of bits and bytes.
// 1 byte = 8 bits
// 1 bit = 0 or 1
// 1 byte = 00000000 to 11111111
// 1 byte = 0 to 255
// 1 byte = 0 to 255

// We start filling from the rightmost bit to the leftmost bit.

// In case of characters, we use ASCII values to store the characters.
// Compiler will detect for data type and store the data accordingly.

// How are negative numbers stored in the memory?
// we ignore the negative sign convert the number to positive and store the data.
// then we take 2's complement of the data. which is inverse of the data and add 1 to it.

// If we try to print usigned negative number it gives us garbage value.