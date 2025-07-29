 #include <iostream>
 #include <stack>
 #include <string>
 // Description: Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 // An input string is valid if:
 // 1. Open brackets must be closed by the same type of brackets.
 // 2. Open brackets must be closed in the correct order.
 // 3. Every close bracket has a corresponding open bracket of the same type.
 // Example 1:
 // Input: s = "()"
 // Output: true
 // Example 2:
 // Input: s = "()[]{}"
 // Output: true
 

 using namespace std;

 class Solution {
    public:
        bool isValid(string s) {
            std::stack<char> stk;
    
            for (char ch : s) {
                if (ch == '(' || ch == '[' || ch == '{') {
                    stk.push(ch);
                } else {
                    if (stk.empty()) return false; 
                    char top = stk.top();
                    if ((top == '(' && ch == ')') ||
                        (top == '[' && ch == ']') ||
                        (top == '{' && ch == '}')) {
                        stk.pop();
                    } else {
                        return false;  
                    }
                }
            }
    
            return stk.empty();  
        }
    };