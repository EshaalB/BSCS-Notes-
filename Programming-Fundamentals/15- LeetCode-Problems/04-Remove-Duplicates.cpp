#include <iostream>
#include <vector>
using namespace std;
class Solution {
    // My own solution      
    public:
        int removeDuplicates(vector<int>& nums) {
            if (nums.empty()) return 0;
    
            vector<int> temp;
            temp.push_back(nums[0]);
    
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] != nums[i - 1]) {
                    temp.push_back(nums[i]);
                }
            }
            for (int i = 0; i < temp.size(); i++) {
                nums[i] = temp[i];
            }
    
            return temp.size();
        }
    };
// A better solution 
class Solution2  {
    public:
        int removeDuplicates(vector<int>& nums) {
            if (nums.empty()) return 0;
    
            int k = 1;  // Index for the next unique element
    
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] != nums[i - 1]) {
                    nums[k] = nums[i];
                    k++;
                }
            }
    
            return k;
        }
    };
         