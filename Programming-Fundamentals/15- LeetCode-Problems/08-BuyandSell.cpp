// Description: You are given an array prices where prices[i] is the price of a given stock on the ith day.
// You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
// Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

// Example 1:
// Input: prices = [7,1,5,3,6,4]
// Output: 5
// Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.

// Example 2:
// Input: prices = [7,6,4,3,1]
// Output: 0
// Explanation: In this case, no transactions are done and the max profit = 0.



class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int buy =prices[0];
            int sell =0; 
            int profit =0;
            int max =0;
            int size = prices.size();
            for (int i=1;i<size;i++){
                if(prices[i]<buy)  buy = prices[i];
                else{
                       sell= prices[i];
                       profit = sell -buy;
                      if (profit>max)  max=profit;
                }
            }
            return max;
        }
    };