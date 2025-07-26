/*
LeetCode Problem: Palindrome Number
==================================

Problem Statement:
Given an integer x, return true if x is a palindrome, and false otherwise.

Example:
Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-.

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Constraints:
- -2^31 <= x <= 2^31 - 1

Approaches:
1. String Conversion: O(log n) time, O(log n) space
2. Mathematical Approach: O(log n) time, O(1) space
3. Half Reversal: O(log n) time, O(1) space (Optimal)
*/

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    // Approach 1: String Conversion
    // Time Complexity: O(log n)
    // Space Complexity: O(log n)
    bool isPalindrome_String(int x) {
        // Negative numbers are not palindromes
        if (x < 0) return false;
        
        // Convert to string
        string numStr = to_string(x);
        
        // Check palindrome using two pointers
        int left = 0, right = numStr.length() - 1;
        while (left < right) {
            if (numStr[left] != numStr[right]) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
    
    // Approach 2: Mathematical Approach (Full Reversal)
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    bool isPalindrome_Math(int x) {
        // Negative numbers are not palindromes
        if (x < 0) return false;
        
        // Single digit numbers are palindromes
        if (x < 10) return true;
        
        // Reverse the entire number
        int original = x;
        int reversed = 0;
        
        while (x != 0) {
            int digit = x % 10;
            reversed = reversed * 10 + digit;
            x /= 10;
        }
        
        return original == reversed;
    }
    
    // Approach 3: Half Reversal (Optimal)
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    bool isPalindrome_HalfReversal(int x) {
        // Negative numbers are not palindromes
        if (x < 0) return false;
        
        // Numbers ending with 0 (except 0 itself) are not palindromes
        if (x != 0 && x % 10 == 0) return false;
        
        // Single digit numbers are palindromes
        if (x < 10) return true;
        
        int reversed = 0;
        
        // Reverse only half of the number
        while (x > reversed) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        
        // For even digits: x == reversed
        // For odd digits: x == reversed / 10 (middle digit is in reversed)
        return x == reversed || x == reversed / 10;
    }
    
    // Approach 4: Using Long Long (Handles overflow)
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    bool isPalindrome_LongLong(int x) {
        // Negative numbers are not palindromes
        if (x < 0) return false;
        
        long long original = x;
        long long reversed = 0;
        
        while (x != 0) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        
        return original == reversed;
    }
};

int main() {
    Solution solution;
    
    // Test cases
    vector<int> testCases = {
        121,        // Expected: true
        -121,       // Expected: false
        10,         // Expected: false
        12321,      // Expected: true
        12345,      // Expected: false
        0,          // Expected: true
        1,          // Expected: true
        1234321,    // Expected: true
        123456,     // Expected: false
        1001,       // Expected: true
        1000,       // Expected: false
        99999,      // Expected: true
        123321,     // Expected: true
        123456789,  // Expected: false
        2147483647  // Expected: false
    };
    
    cout << "=== PALINDROME NUMBER PROBLEM ===\n\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        int x = testCases[i];
        cout << "Test Case " << (i + 1) << ":\n";
        cout << "Input: " << x << endl;
        
        // Test all four approaches
        bool result1 = solution.isPalindrome_String(x);
        bool result2 = solution.isPalindrome_Math(x);
        bool result3 = solution.isPalindrome_HalfReversal(x);
        bool result4 = solution.isPalindrome_LongLong(x);
        
        cout << "String Approach Result: " << (result1 ? "true" : "false") << endl;
        cout << "Math Approach Result: " << (result2 ? "true" : "false") << endl;
        cout << "Half Reversal Result: " << (result3 ? "true" : "false") << endl;
        cout << "Long Long Result: " << (result4 ? "true" : "false") << endl;
        
        // Verify all results are the same
        if (result1 == result2 && result2 == result3 && result3 == result4) {
            cout << "✓ All approaches agree" << endl;
        } else {
            cout << "✗ Results differ!" << endl;
        }
        
        cout << endl;
    }
    
    // Edge cases demonstration
    cout << "=== EDGE CASES ANALYSIS ===\n";
    cout << "Negative numbers: Always false\n";
    cout << "Zero: Always true\n";
    cout << "Single digits: Always true\n";
    cout << "Numbers ending with 0 (except 0): Always false\n";
    cout << "Even vs Odd digits: Both handled correctly\n\n";
    
    // Performance comparison
    cout << "=== PERFORMANCE COMPARISON ===\n";
    cout << "1. String Conversion: O(log n) time, O(log n) space\n";
    cout << "2. Mathematical Approach: O(log n) time, O(1) space\n";
    cout << "3. Half Reversal: O(log n) time, O(1) space (RECOMMENDED)\n";
    cout << "4. Long Long Approach: O(log n) time, O(1) space\n\n";
    
    cout << "Key Insights:\n";
    cout << "- Half reversal is most efficient\n";
    cout << "- Negative numbers are never palindromes\n";
    cout << "- Numbers ending with 0 (except 0) are never palindromes\n";
    cout << "- Only need to reverse half the digits\n";
    cout << "- Handle odd and even digit counts differently\n";
    
    return 0;
}

/*
LEARNING POINTS:
================

1. Palindrome Properties:
   - Negative numbers are never palindromes
   - Single digit numbers are always palindromes
   - Numbers ending with 0 (except 0) are never palindromes
   - Even and odd digit counts need different handling

2. Half Reversal Technique:
   - Only reverse half the digits
   - Compare original half with reversed half
   - For odd digits, middle digit is in reversed half
   - More efficient than full reversal

3. Mathematical Approach:
   - Extract digits using modulo (%)
   - Build reversed number
   - Compare with original
   - Handle overflow with long long

4. String Approach:
   - Convert to string for easy comparison
   - Use two pointers to check palindrome
   - Simple but uses extra space

5. Edge Cases:
   - Negative numbers
   - Zero
   - Single digits
   - Numbers ending with zeros
   - Large numbers (overflow)

6. Optimization Tips:
   - Half reversal is most efficient
   - Early return for negative numbers
   - Early return for numbers ending with 0
   - Use mathematical approach over string when possible

7. Common Mistakes:
   - Not handling negative numbers
   - Not considering numbers ending with 0
   - Full reversal when half is sufficient
   - Not handling overflow properly
*/ 