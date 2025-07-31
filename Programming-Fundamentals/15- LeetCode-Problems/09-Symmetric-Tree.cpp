#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <sstream>

using namespace std;    

//description : Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

//example 1:
//Input: root = [1,2,2,3,4,4,3]
//Output: true

//example 2:
//Input: root = [1,2,2,null,3,null,3]
//Output: false

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

 class Solution {
    public:
        bool isSymmetric(TreeNode* root) {
            if (!root) return false;
            return isMirror (root->left,root->right);
    
        }
        bool isMirror(TreeNode* leftRoot,TreeNode* rightRoot){
            if(!leftRoot && !rightRoot) return true;
               if(!leftRoot || !rightRoot) return false;
    
    
            return leftRoot->val ==rightRoot->val && isMirror (leftRoot->left,rightRoot->right) && isMirror (leftRoot->right,rightRoot->left);
        }
    };