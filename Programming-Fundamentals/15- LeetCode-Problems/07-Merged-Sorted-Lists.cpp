    // Description: You are given the heads of two sorted linked lists list1 and list2.
    // Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.
    // Return the head of the merged linked list.
    // Example 1:
    // Input: list1 = [1,2,4], list2 = [1,3,4]
    // Output: [1,1,2,3,4,4]
    // Example 2:
    // Input: list1 = [], list2 = []
    // Output: []
    // Example 3:
    // Input: list1 = [], list2 = [0]
    // Output: [0]






        /**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            // Base cases
            if (!list1) return list2;
            if (!list2) return list1;
    
            ListNode* curr = list1;
            ListNode* curr1 = list2;
            ListNode* sorted;
    
            // Choose the smaller node to start
            if (curr->val <= curr1->val) {
                sorted = curr;
                sorted->next = mergeTwoLists(curr->next, curr1);
            } else {
                sorted = curr1;
                sorted->next = mergeTwoLists(curr, curr1->next);
            }
    
            return sorted;
        }
    };
    