#include <iostream>
using namespace std;
// lets take an example we are asked to find max from a 1000 numbers 
// we can do this by using a loop and a variable to store the max value
// but this is not efficient and it is not a good practice
// so we use arrays to store the numbers and then find the max value
// arrays are a collection of similar data types
// arrays are stored in contiguous memory locations
// arrays are indexed from 0 to n-1
// arrays are of fixed size
// arrays are declared with the data type and the size of the array
int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    // 1st method (index based access)
    cout << arr[0] << endl; // 1
    cout << arr[1] << endl; // 2
    cout << arr[2] << endl; // 3
    cout << arr[3] << endl; // 4
    cout << arr[4] << endl; // 5
    // 2nd method (for loop)
    for(int i = 0; i < 5; i++){  
        cout << arr[i] << endl;
    }
    // 3rd method (for each loop)
    for(int i : arr){  
        cout << i << endl;
    }
    // 4th method (while loop)
    int i = 0;
    while(i < 5){
        cout << arr[i] << endl;
        i++;
    }
// intialization 
int newArr [100] = {0};
// 100 is the size of the array
// 0 is the value of the array
// if we don't provide the size of the array, it will be automatically  determined by the compiler and give garbage 

// Bad Practice  
// we should not use a variable to define the size of the array because it will be difficult to maintain and it will be difficult to debug
// int size = 10;
// int arr[size] = {0};
// int arr[size] = {1, 2, 3, 4, 5};
// int arr[size] = {1, 2, 3, 4, 5};

    return 0;
}