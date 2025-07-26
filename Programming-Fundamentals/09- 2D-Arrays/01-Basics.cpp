#include <iostream>
using namespace std;
 // 2D Arrays are arrays of arrays
 // They are used to store data in a table format
 // They are declared with the data type and the size of the array
 // They are indexed from 0 to n-1
 // They are of fixed size
 // They are declared with the data type and the size of the array
 // They are indexed from 0 to n-1
 // They are of fixed size

 int main(){
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // 3 is the number of rows
    // 3 is the number of columns
    // 1 is the value of the array
    // 2 is the value of the array
    // 3 is the value of the array
    // 4 is the value of the array

    // 1st method (index based access)
    cout << arr[0][0] << endl; // 1
    cout << arr[0][1] << endl; // 2
    cout << arr[0][2] << endl; // 3
    cout << arr[1][0] << endl; // 4
    cout << arr[1][1] << endl; // 5
    cout << arr[1][2] << endl; // 6
    cout << arr[2][0] << endl; // 7

    // 2nd method (for loop)
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << arr[i][j] << endl;
        }
    }

    // 3rd method (for each loop)       
    for(int i : arr){
        cout << i << endl; 
    }

    // 4th method (while loop)
    int i = 0;
    while(i < 3){
        int j = 0;
        while(j < 3){       
            cout << arr[i][j] << endl;  
            j++;
        }
        i++;
    }

    return 0;
 }
