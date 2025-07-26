#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout << "IF-ELSE STATEMENTS PRACTICE QUESTIONS" << endl;
    cout << "=====================================" << endl;
    
    int choice;
    
    cout << "\nChoose a practice question (1-8): ";
    cin >> choice;
    
    if (choice == 1) {
        // 1. Even or Odd Number
        cout << "\n=== 1. Even or Odd Number ===" << endl;
        int num;
        cout << "Enter a number: ";
        cin >> num;
        
        if (num % 2 == 0) {
            cout << num << " is Even" << endl;
        } else {
            cout << num << " is Odd" << endl;
        }
    }
    
    else if (choice == 2) {
        // 2. Triangle Validation
        cout << "\n=== 2. Triangle Validation ===" << endl;
        double a, b, c;
        
        cout << "Enter three sides of triangle: ";
        cin >> a >> b >> c;
        
        if (a + b > c && b + c > a && a + c > b) {
            cout << "Valid Triangle" << endl;
            
            // Check triangle type
            if (a == b && b == c) {
                cout << "Equilateral Triangle" << endl;
            } else if (a == b || b == c || a == c) {
                cout << "Isosceles Triangle" << endl;
            } else {
                cout << "Scalene Triangle" << endl;
            }
        } else {
            cout << "Not a Valid Triangle" << endl;
        }
    }
    
    else if (choice == 3) {
        // 3. Positive, Negative, or Zero
        cout << "\n=== 3. Positive, Negative, or Zero ===" << endl;
        int num;
        
        cout << "Enter a number: ";
        cin >> num;
        
        if (num > 0) {
            cout << num << " is Positive" << endl;
        } else if (num < 0) {
            cout << num << " is Negative" << endl;
        } else {
            cout << num << " is Zero" << endl;
        }
    }
    
    else if (choice == 4) {
        // 4. Ascending or Descending Order
        cout << "\n=== 4. Ascending or Descending Order ===" << endl;
        int a, b, c;
        
        cout << "Enter three numbers: ";
        cin >> a >> b >> c;
        
        if (a < b && b < c) {
            cout << "Numbers are in Ascending Order" << endl;
        } else if (a > b && b > c) {
            cout << "Numbers are in Descending Order" << endl;
        } else {
            cout << "Numbers are neither in ascending nor descending order" << endl;
        }
    }
    
    else if (choice == 5) {
        // 5. Type Casting Practice
        cout << "\n=== 5. Type Casting Practice ===" << endl;
        double num;
        
        cout << "Enter a decimal number: ";
        cin >> num;
        
        int intPart = static_cast<int>(num);
        double decimalPart = num - intPart;
        
        cout << "Original number: " << num << endl;
        cout << "Integer part: " << intPart << endl;
        cout << "Decimal part: " << decimalPart << endl;
        
        if (decimalPart == 0) {
            cout << "The number is a whole number" << endl;
        } else {
            cout << "The number has decimal places" << endl;
        }
    }
    
    else if (choice == 6) {
        // 6. Quadratic Formula
        cout << "\n=== 6. Quadratic Formula ===" << endl;
        double a, b, c;
        
        cout << "Enter coefficients (a, b, c) for ax^2 + bx + c = 0: ";
        cin >> a >> b >> c;
        
        if (a == 0) {
            cout << "This is not a quadratic equation (a cannot be 0)" << endl;
        } else {
            double discriminant = b*b - 4*a*c;
            
            if (discriminant > 0) {
                double x1 = (-b + sqrt(discriminant)) / (2*a);
                double x2 = (-b - sqrt(discriminant)) / (2*a);
                cout << "Two real roots: x1 = " << x1 << ", x2 = " << x2 << endl;
            } else if (discriminant == 0) {
                double x = -b / (2*a);
                cout << "One real root: x = " << x << endl;
            } else {
                cout << "No real roots (complex roots)" << endl;
            }
        }
    }
    
    else if (choice == 7) {
        // 7. Calculator (Minimum)
        cout << "\n=== 7. Simple Calculator ===" << endl;
        double num1, num2;
        char operation;
        
        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter operation (+, -, *, /): ";
        cin >> operation;
        cout << "Enter second number: ";
        cin >> num2;
        
        if (operation == '+') {
            cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
        } else if (operation == '-') {
            cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
        } else if (operation == '*') {
            cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
        } else if (operation == '/') {
            if (num2 != 0) {
                cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
            } else {
                cout << "Error: Division by zero!" << endl;
            }
        } else {
            cout << "Invalid operation!" << endl;
        }
    }
    
    else if (choice == 8) {
        // 8. Body Fat Calculator
        cout << "\n=== 8. Body Fat Calculator ===" << endl;
        char gender;
        double weight, height, age, bodyFat;
        
        cout << "Enter gender (M/F): ";
        cin >> gender;
        cout << "Enter weight (kg): ";
        cin >> weight;
        cout << "Enter height (cm): ";
        cin >> height;
        cout << "Enter age: ";
        cin >> age;
        
        // Using BMI-based estimation (simplified)
        double bmi = weight / pow(height/100, 2);
        
        if (gender == 'M' || gender == 'm') {
            bodyFat = (1.20 * bmi) + (0.23 * age) - 16.2;
        } else if (gender == 'F' || gender == 'f') {
            bodyFat = (1.20 * bmi) + (0.23 * age) - 5.4;
        } else {
            cout << "Invalid gender input!" << endl;
        }
        
        if (gender == 'M' || gender == 'm' || gender == 'F' || gender == 'f') {
            cout << "Your estimated body fat percentage: " << bodyFat << "%" << endl;
            
            if (gender == 'M' || gender == 'm') {
                if (bodyFat < 6) {
                    cout << "Body fat category: Essential fat" << endl;
                } else if (bodyFat < 14) {
                    cout << "Body fat category: Athletes" << endl;
                } else if (bodyFat < 18) {
                    cout << "Body fat category: Fitness" << endl;
                } else if (bodyFat < 25) {
                    cout << "Body fat category: Average" << endl;
                } else {
                    cout << "Body fat category: Obese" << endl;
                }
            } else {
                if (bodyFat < 14) {
                    cout << "Body fat category: Essential fat" << endl;
                } else if (bodyFat < 21) {
                    cout << "Body fat category: Athletes" << endl;
                } else if (bodyFat < 25) {
                    cout << "Body fat category: Fitness" << endl;
                } else if (bodyFat < 32) {
                    cout << "Body fat category: Average" << endl;
                } else {
                    cout << "Body fat category: Obese" << endl;
                }
            }
        }
    }
    
    else {
        cout << "Invalid choice! Please enter 1-8." << endl;
    }
    
    return 0;
}
