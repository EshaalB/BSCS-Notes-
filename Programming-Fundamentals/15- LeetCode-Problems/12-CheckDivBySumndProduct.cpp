#include <iostream>
using namespace std;

//Description: You are given a positive integer n. If n is divisible by either the sum or the product of its digits, return true; otherwise, return false.
//Example 1:
//Input: n = 12
//Output: true
//Explanation: The sum of the digits is 3, and the product of the digits is 2. Since 12 is divisible by 3, we return true.

class Solution {
    public:
        bool checkDivisibility(int n) {
            int digitSum=0;
            int digitProduct=1;
                int temp=n;
            while (temp!=0){
                int remain = temp%10;
                digitSum+= remain;
                 digitProduct*= remain;
                 temp/=10;
            }
            int res =digitSum+digitProduct;
            if (n%res)return false;
            return true;
        }
    };