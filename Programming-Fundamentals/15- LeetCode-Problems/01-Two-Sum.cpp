/*
LeetCode Problem: Two Sum
========================

Problem Statement:
Given an array of integers nums and an integer target, return indices of the two numbers 
such that they add up to target. You may assume that each input would have exactly one 
solution, and you may not use the same element twice.

Example:
Input: nums = [2, 7, 11, 15], target = 9
Output: [0, 1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Constraints:
- 2 <= nums.length <= 10^4
- -10^9 <= nums[i] <= 10^9
- -10^9 <= target <= 10^9
- Only one valid answer exists.

Approaches:
1. Brute Force: O(n²) time, O(1) space
2. Hash Map: O(n) time, O(n) space
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Approach 1: Brute Force
    // Time Complexity: O(n²)
    // Space Complexity: O(1)
    vector<int> twoSum_BruteForce(vector<int>& nums, int target) {
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        
        return {}; // No solution found
    }
    
    // Approach 2: Hash Map (Optimal)
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    vector<int> twoSum_HashMap(vector<int>& nums, int target) {
        unordered_map<int, int> numMap;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in map
            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            
            // Store current number and its index
            numMap[nums[i]] = i;
        }
        
        return {}; // No solution found
    }
    
    // Approach 3: Two Pointers (requires sorted array)
    // Time Complexity: O(n log n) due to sorting
    // Space Complexity: O(n) to store original indices
    vector<int> twoSum_TwoPointers(vector<int>& nums, int target) {
        int n = nums.size();
        
        // Create vector of pairs (value, original_index)
        vector<pair<int, int>> indexedNums;
        for (int i = 0; i < n; i++) {
            indexedNums.push_back({nums[i], i});
        }
        
        // Sort by values
        sort(indexedNums.begin(), indexedNums.end());
        
        // Two pointers approach
        int left = 0, right = n - 1;
        
        while (left < right) {
            int sum = indexedNums[left].first + indexedNums[right].first;
            
            if (sum == target) {
                return {indexedNums[left].second, indexedNums[right].second};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return {}; // No solution found
    }

    // Approach 4 : My own Logic 
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> temp ;
        int size = nums.size();
        for (int i =0; i<size;i++)
         {
            for (int j =i+1 ; j<size;j++)
            {
                if (nums[i]+nums[j]==target){
                   temp.push_back(i);
                     temp.push_back(j);
                }
            }
         }
         return temp;
    }
};

// Helper function to print vector
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution solution;
    
    // Test cases
    vector<vector<int>> testNums = {
        {2, 7, 11, 15},
        {3, 2, 4},
        {3, 3},
        {1, 5, 8, 10, 13, 17},
        {-1, -2, -3, -4, -5}
    };
    
    vector<int> testTargets = {9, 6, 6, 18, -8};
    
    cout << "=== TWO SUM PROBLEM ===\n\n";
    
    for (int i = 0; i < testNums.size(); i++) {
        cout << "Test Case " << (i + 1) << ":\n";
        cout << "Input: nums = ";
        printVector(testNums[i]);
        cout << ", target = " << testTargets[i] << endl;
        
        // Test all three approaches
        vector<int> result1 = solution.twoSum_BruteForce(testNums[i], testTargets[i]);
        vector<int> result2 = solution.twoSum_HashMap(testNums[i], testTargets[i]);
        vector<int> result3 = solution.twoSum_TwoPointers(testNums[i], testTargets[i]);
        vector<int> result4 = solution.twoSum(testNums[i], testTargets[i]);
        cout << "Brute Force Result: ";
        printVector(result1);
        cout << endl;
        
        cout << "Hash Map Result: ";
        printVector(result2);
        cout << endl;
        
        cout << "Two Pointers Result: ";
        printVector(result3);
        cout << endl;
        
        // Verify results
        if (!result1.empty()) {
            cout << "Verification: " << testNums[i][result1[0]] << " + " 
                 << testNums[i][result1[1]] << " = " 
                 << (testNums[i][result1[0]] + testNums[i][result1[1]]) << endl;
        }
        
        cout << endl;
    }
    
    // Performance comparison
    cout << "=== PERFORMANCE COMPARISON ===\n";
    cout << "1. Brute Force: O(n²) time, O(1) space\n";
    cout << "2. Hash Map: O(n) time, O(n) space (RECOMMENDED)\n";
    cout << "3. Two Pointers: O(n log n) time, O(n) space\n\n";
    
    cout << "Key Insights:\n";
    cout << "- Hash Map approach is optimal for most cases\n";
    cout << "- Brute Force is simple but inefficient\n";
    cout << "- Two Pointers requires sorting but uses less space than Hash Map\n";
    cout << "- Hash Map trades space for time efficiency\n";
    
    return 0;
}

/*
LEARNING POINTS:
================

1. Hash Map Usage:
   - Use unordered_map for O(1) average lookup time
   - Store complement (target - current) to find pairs
   - Key insight: If we've seen the complement before, we found our pair

2. Time-Space Trade-offs:
   - Brute Force: Simple but O(n²) time
   - Hash Map: Fast O(n) time but uses extra space
   - Two Pointers: Good for sorted data, O(n log n) due to sorting

3. Edge Cases:
   - Handle cases where no solution exists
   - Consider duplicate elements
   - Handle negative numbers

4. Optimization Tips:
   - Use unordered_map instead of map for better average performance
   - Early return when solution is found
   - Consider input constraints when choosing approach

5. Common Patterns:
   - Complement-based searching
   - Index-value pairing
   - Two-pointer technique
*/ 