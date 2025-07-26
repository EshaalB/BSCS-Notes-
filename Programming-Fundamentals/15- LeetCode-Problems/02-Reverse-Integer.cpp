/*
LeetCode Problem: Reverse Integer
================================

Problem Statement:
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x 
causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], 
then return 0.

Example:
Input: x = 123
Output: 321

Input: x = -123
Output: -321

Input: x = 120
Output: 21

Constraints:
- -2^31 <= x <= 2^31 - 1

Approaches:
1. Mathematical Approach: O(log n) time, O(1) space
2. String Conversion: O(log n) time, O(log n) space
*/

#include <iostream>
#include <climits>
#include <string>
using namespace std;

class Solution {
public:
    // Approach 1: Mathematical Approach (Optimal)
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    int reverse_Math(int x) {
        int reversed = 0;
        
        while (x != 0) {
            int digit = x % 10;
            x /= 10;
            
            // Check for overflow before multiplying
            if (reversed > INT_MAX / 10 || 
                (reversed == INT_MAX / 10 && digit > 7)) {
                return 0;
            }
            
            // Check for underflow before multiplying
            if (reversed < INT_MIN / 10 || 
                (reversed == INT_MIN / 10 && digit < -8)) {
                return 0;
            }
            
            reversed = reversed * 10 + digit;
        }
        
        return reversed;
    }
    
    // Approach 2: String Conversion
    // Time Complexity: O(log n)
    // Space Complexity: O(log n)
    int reverse_String(int x) {
        // Handle negative numbers
        bool isNegative = x < 0;
        long long absX = abs((long long)x);
        
        // Convert to string
        string numStr = to_string(absX);
        
        // Reverse the string
        int left = 0, right = numStr.length() - 1;
        while (left < right) {
            swap(numStr[left], numStr[right]);
            left++;
            right--;
        }
        
        // Convert back to integer
        long long result = stoll(numStr);
        
        // Apply sign
        if (isNegative) {
            result = -result;
        }
        
        // Check for overflow
        if (result > INT_MAX || result < INT_MIN) {
            return 0;
        }
        
        return (int)result;
    }
    
    // Approach 3: Using Long Long (Simpler overflow handling)
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    int reverse_LongLong(int x) {
        long long reversed = 0;
        
        while (x != 0) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        
        // Check for overflow
        if (reversed > INT_MAX || reversed < INT_MIN) {
            return 0;
        }
        
        return (int)reversed;
    }
};

int main() {
    Solution solution;
    
    // Test cases
    vector<int> testCases = {
        123,        // Expected: 321
        -123,       // Expected: -321
        120,        // Expected: 21
        0,          // Expected: 0
        1534236469, // Expected: 0 (overflow)
        -2147483648, // Expected: 0 (overflow)
        2147483647,  // Expected: 0 (overflow)
        123456789,   // Expected: 987654321
        -123456789,  // Expected: -987654321
        100,         // Expected: 1
        -100         // Expected: -1
    };
    
    cout << "=== REVERSE INTEGER PROBLEM ===\n\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        int x = testCases[i];
        cout << "Test Case " << (i + 1) << ":\n";
        cout << "Input: " << x << endl;
        
        // Test all three approaches
        int result1 = solution.reverse_Math(x);
        int result2 = solution.reverse_String(x);
        int result3 = solution.reverse_LongLong(x);
        
        cout << "Math Approach Result: " << result1 << endl;
        cout << "String Approach Result: " << result2 << endl;
        cout << "Long Long Approach Result: " << result3 << endl;
        
        // Verify all results are the same
        if (result1 == result2 && result2 == result3) {
            cout << "✓ All approaches agree" << endl;
        } else {
            cout << "✗ Results differ!" << endl;
        }
        
        cout << endl;
    }
    
    // Edge cases demonstration
    cout << "=== EDGE CASES ANALYSIS ===\n";
    cout << "INT_MAX: " << INT_MAX << endl;
    cout << "INT_MIN: " << INT_MIN << endl;
    cout << "INT_MAX / 10: " << INT_MAX / 10 << endl;
    cout << "INT_MIN / 10: " << INT_MIN / 10 << endl;
    cout << "Last digit of INT_MAX: " << INT_MAX % 10 << endl;
    cout << "Last digit of INT_MIN: " << INT_MIN % 10 << endl << endl;
    
    // Performance comparison
    cout << "=== PERFORMANCE COMPARISON ===\n";
    cout << "1. Mathematical Approach: O(log n) time, O(1) space (RECOMMENDED)\n";
    cout << "2. String Conversion: O(log n) time, O(log n) space\n";
    cout << "3. Long Long Approach: O(log n) time, O(1) space\n\n";
    
    cout << "Key Insights:\n";
    cout << "- Mathematical approach is most efficient\n";
    cout << "- Overflow checking is crucial\n";
    cout << "- Handle negative numbers properly\n";
    cout << "- Consider edge cases like 0 and single digits\n";
    
    return 0;
}

/*
LEARNING POINTS:
================

1. Integer Overflow Handling:
   - Check overflow before multiplication
   - Use INT_MAX and INT_MIN constants
   - Consider the last digit separately
   - Use long long for intermediate calculations

2. Mathematical Approach:
   - Extract digits using modulo (%)
   - Build reversed number digit by digit
   - Check overflow at each step
   - Handle negative numbers by working with absolute value

3. String Approach:
   - Convert to string for easy manipulation
   - Reverse string using two pointers
   - Convert back to integer
   - Handle overflow after conversion

4. Edge Cases:
   - Zero input
   - Single digit numbers
   - Numbers that cause overflow when reversed
   - Negative numbers
   - Numbers ending with zeros

5. Optimization Tips:
   - Mathematical approach is most efficient
   - Avoid string operations when possible
   - Use bit manipulation for overflow checking
   - Early return for zero input

6. Common Mistakes:
   - Not handling overflow properly
   - Forgetting to handle negative numbers
   - Not considering edge cases
   - Using int for intermediate calculations that might overflow
*/ 