#include <vector>
using namespace std;    

// 860. Lemonade Change

// You are given an integer array bills where bills[i] is the bill the ith customer pays, and all the customers are standing in a queue. Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill. You must provide every customer with the correct change.

// Note that you do not have any change in hand at first.

// Given an integer array bills where bills[i] is the bill the ith customer pays, return true if you can provide every customer with the correct change, or false otherwise.

// Example 1:

// Input: bills = [5,5,5,10,20]
// Output: true

// Example 2:

// Input: bills = [10,10]
// Output: false

// Constraints:

// 1 <= bills.length <= 10^5
// bills[i] is either 5, 10, or 20.

// Solution:

// We can use a greedy algorithm to solve this problem. We will keep track of the number of $5 and $10 bills we have. If the customer pays with a $10 bill, we will give them a $5 bill. If the customer pays with a $20 bill, we will give them a $10 bill and a $5 bill. If we cannot give the correct change, we will return false.

// Time Complexity: O(n)
// Space Complexity: O(1)

class Solution {
    public:
        bool lemonadeChange(vector<int>& bills) {
            int five = 0;
            int ten = 0;
            int twenty = 0;
            int size = bills.size();
            
            for (int i = 0; i < size; i++) {
                if (bills[i] < 5) return false;
    
                if (bills[i] == 5) {
                    five++;
                }
                else if (bills[i] == 10) {
                    if (five >= 1) {
                        five--;
                        ten++;
                    } else {
                        return false;
                    }
                }
                else if (bills[i] == 20) {
                    if (ten >= 1 && five >= 1) {
                        ten--;
                        five--;
                        twenty++;
                    }
                    else if (five >= 3) {
                        five -= 3;
                        twenty++;
                    }
                    else {
                        return false;
                    }
                }
            }
            return true;
        }
    };
    