/*
2D ARRAYS PRACTICE QUESTIONS
============================

This file contains various practice problems using 2D arrays:
- Matrix operations
- Pattern printing
- Spiral traversal
- Diagonal operations
- Transpose
- Matrix multiplication
- Magic square
- Pascal's triangle
- Saddle point
- Boundary traversal
*/

#include <iostream>
#include <iomanip>
using namespace std;

// Function to print matrix
void printMatrix(int matrix[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to transpose matrix
void transposeMatrix(int matrix[][10], int rows, int cols) {
    int transpose[10][10];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
    
    cout << "Transposed Matrix:" << endl;
    printMatrix(transpose, cols, rows);
}

// Function to multiply matrices
void multiplyMatrices(int matrix1[][10], int matrix2[][10], int rows1, int cols1, int cols2) {
    int result[10][10] = {0};
    
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    cout << "Matrix Multiplication Result:" << endl;
    printMatrix(result, rows1, cols2);
}

// Function to print spiral traversal
void spiralTraversal(int matrix[][10], int rows, int cols) {
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    
    cout << "Spiral Traversal: ";
    while (top <= bottom && left <= right) {
        // Print top row
        for (int i = left; i <= right; i++) {
            cout << matrix[top][i] << " ";
        }
        top++;
        
        // Print right column
        for (int i = top; i <= bottom; i++) {
            cout << matrix[i][right] << " ";
        }
        right--;
        
        // Print bottom row
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                cout << matrix[bottom][i] << " ";
            }
            bottom--;
        }
        
        // Print left column
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                cout << matrix[i][left] << " ";
            }
            left++;
        }
    }
    cout << endl;
}

// Function to print diagonal elements
void printDiagonals(int matrix[][10], int size) {
    cout << "Main Diagonal: ";
    for (int i = 0; i < size; i++) {
        cout << matrix[i][i] << " ";
    }
    cout << endl;
    
    cout << "Anti-Diagonal: ";
    for (int i = 0; i < size; i++) {
        cout << matrix[i][size - 1 - i] << " ";
    }
    cout << endl;
}

// Function to create magic square
void createMagicSquare(int size) {
    int magic[10][10] = {0};
    int row = 0, col = size / 2;
    
    for (int num = 1; num <= size * size; num++) {
        magic[row][col] = num;
        
        int nextRow = (row - 1 + size) % size;
        int nextCol = (col + 1) % size;
        
        if (magic[nextRow][nextCol] != 0) {
            nextRow = (row + 1) % size;
            nextCol = col;
        }
        
        row = nextRow;
        col = nextCol;
    }
    
    cout << "Magic Square of size " << size << "x" << size << ":" << endl;
    printMatrix(magic, size, size);
}

// Function to create Pascal's triangle
void createPascalTriangle(int rows) {
    int pascal[10][10] = {0};
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                pascal[i][j] = 1;
            } else {
                pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
            }
        }
    }
    
    cout << "Pascal's Triangle:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            cout << setw(4) << pascal[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to find saddle point
void findSaddlePoint(int matrix[][10], int rows, int cols) {
    bool found = false;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool isSaddle = true;
            
            // Check if it's minimum in its row
            for (int k = 0; k < cols; k++) {
                if (matrix[i][k] < matrix[i][j]) {
                    isSaddle = false;
                    break;
                }
            }
            
            // Check if it's maximum in its column
            if (isSaddle) {
                for (int k = 0; k < rows; k++) {
                    if (matrix[k][j] > matrix[i][j]) {
                        isSaddle = false;
                        break;
                    }
                }
            }
            
            if (isSaddle) {
                cout << "Saddle point found at (" << i << "," << j << "): " << matrix[i][j] << endl;
                found = true;
            }
        }
    }
    
    if (!found) {
        cout << "No saddle point found." << endl;
    }
}

// Function to print boundary elements
void printBoundary(int matrix[][10], int rows, int cols) {
    cout << "Boundary Elements: ";
    
    // Top row
    for (int j = 0; j < cols; j++) {
        cout << matrix[0][j] << " ";
    }
    
    // Right column (excluding first and last elements)
    for (int i = 1; i < rows - 1; i++) {
        cout << matrix[i][cols - 1] << " ";
    }
    
    // Bottom row (in reverse, excluding first element)
    if (rows > 1) {
        for (int j = cols - 1; j >= 0; j--) {
            cout << matrix[rows - 1][j] << " ";
        }
    }
    
    // Left column (in reverse, excluding first and last elements)
    for (int i = rows - 2; i > 0; i--) {
        cout << matrix[i][0] << " ";
    }
    
    cout << endl;
}

int main() {
    cout << "2D ARRAYS PRACTICE QUESTIONS" << endl;
    cout << "============================" << endl;
    
    int choice;
    
    cout << "\nChoose a practice question (1-12): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. Matrix Input and Display
        cout << "\n=== 1. Matrix Input and Display ===" << endl;
        int rows, cols;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;
        
        int matrix[10][10];
        cout << "Enter " << rows * cols << " elements:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Matrix:" << endl;
        printMatrix(matrix, rows, cols);
    }
    
    else if (choice == 2) {
        // 2. Matrix Transpose
        cout << "\n=== 2. Matrix Transpose ===" << endl;
        int rows, cols;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;
        
        int matrix[10][10];
        cout << "Enter " << rows * cols << " elements:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Original Matrix:" << endl;
        printMatrix(matrix, rows, cols);
        
        transposeMatrix(matrix, rows, cols);
    }
    
    else if (choice == 3) {
        // 3. Matrix Multiplication
        cout << "\n=== 3. Matrix Multiplication ===" << endl;
        int rows1, cols1, cols2;
        cout << "Enter rows of first matrix: ";
        cin >> rows1;
        cout << "Enter columns of first matrix: ";
        cin >> cols1;
        cout << "Enter columns of second matrix: ";
        cin >> cols2;
        
        int matrix1[10][10], matrix2[10][10];
        
        cout << "Enter elements of first matrix:" << endl;
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols1; j++) {
                cin >> matrix1[i][j];
            }
        }
        
        cout << "Enter elements of second matrix:" << endl;
        for (int i = 0; i < cols1; i++) {
            for (int j = 0; j < cols2; j++) {
                cin >> matrix2[i][j];
            }
        }
        
        cout << "First Matrix:" << endl;
        printMatrix(matrix1, rows1, cols1);
        
        cout << "Second Matrix:" << endl;
        printMatrix(matrix2, cols1, cols2);
        
        multiplyMatrices(matrix1, matrix2, rows1, cols1, cols2);
    }
    
    else if (choice == 4) {
        // 4. Spiral Traversal
        cout << "\n=== 4. Spiral Traversal ===" << endl;
        int rows, cols;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;
        
        int matrix[10][10];
        cout << "Enter " << rows * cols << " elements:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Matrix:" << endl;
        printMatrix(matrix, rows, cols);
        
        spiralTraversal(matrix, rows, cols);
    }
    
    else if (choice == 5) {
        // 5. Diagonal Elements
        cout << "\n=== 5. Diagonal Elements ===" << endl;
        int size;
        cout << "Enter size of square matrix: ";
        cin >> size;
        
        int matrix[10][10];
        cout << "Enter " << size * size << " elements:" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Matrix:" << endl;
        printMatrix(matrix, size, size);
        
        printDiagonals(matrix, size);
    }
    
    else if (choice == 6) {
        // 6. Magic Square
        cout << "\n=== 6. Magic Square ===" << endl;
        int size;
        cout << "Enter size of magic square (odd number): ";
        cin >> size;
        
        if (size % 2 == 1) {
            createMagicSquare(size);
        } else {
            cout << "Magic square can only be created for odd sizes." << endl;
        }
    }
    
    else if (choice == 7) {
        // 7. Pascal's Triangle
        cout << "\n=== 7. Pascal's Triangle ===" << endl;
        int rows;
        cout << "Enter number of rows: ";
        cin >> rows;
        
        createPascalTriangle(rows);
    }
    
    else if (choice == 8) {
        // 8. Saddle Point
        cout << "\n=== 8. Saddle Point ===" << endl;
        int rows, cols;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;
        
        int matrix[10][10];
        cout << "Enter " << rows * cols << " elements:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Matrix:" << endl;
        printMatrix(matrix, rows, cols);
        
        findSaddlePoint(matrix, rows, cols);
    }
    
    else if (choice == 9) {
        // 9. Boundary Traversal
        cout << "\n=== 9. Boundary Traversal ===" << endl;
        int rows, cols;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;
        
        int matrix[10][10];
        cout << "Enter " << rows * cols << " elements:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Matrix:" << endl;
        printMatrix(matrix, rows, cols);
        
        printBoundary(matrix, rows, cols);
    }
    
    else if (choice == 10) {
        // 10. Matrix Pattern - Identity Matrix
        cout << "\n=== 10. Identity Matrix ===" << endl;
        int size;
        cout << "Enter size of identity matrix: ";
        cin >> size;
        
        int matrix[10][10] = {0};
        for (int i = 0; i < size; i++) {
            matrix[i][i] = 1;
        }
        
        cout << "Identity Matrix:" << endl;
        printMatrix(matrix, size, size);
    }
    
    else if (choice == 11) {
        // 11. Matrix Pattern - Upper Triangular
        cout << "\n=== 11. Upper Triangular Matrix ===" << endl;
        int size;
        cout << "Enter size of matrix: ";
        cin >> size;
        
        int matrix[10][10];
        cout << "Enter " << size * size << " elements:" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Original Matrix:" << endl;
        printMatrix(matrix, size, size);
        
        cout << "Upper Triangular Matrix:" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i <= j) {
                    cout << setw(4) << matrix[i][j] << " ";
                } else {
                    cout << setw(4) << "0" << " ";
                }
            }
            cout << endl;
        }
    }
    
    else if (choice == 12) {
        // 12. Matrix Pattern - Lower Triangular
        cout << "\n=== 12. Lower Triangular Matrix ===" << endl;
        int size;
        cout << "Enter size of matrix: ";
        cin >> size;
        
        int matrix[10][10];
        cout << "Enter " << size * size << " elements:" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> matrix[i][j];
            }
        }
        
        cout << "Original Matrix:" << endl;
        printMatrix(matrix, size, size);
        
        cout << "Lower Triangular Matrix:" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i >= j) {
                    cout << setw(4) << matrix[i][j] << " ";
                } else {
                    cout << setw(4) << "0" << " ";
                }
            }
            cout << endl;
        }
    }
    
    else {
        cout << "Invalid choice! Please enter 1-12." << endl;
    }
    
    return 0;
}
