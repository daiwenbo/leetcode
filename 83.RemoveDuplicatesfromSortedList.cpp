/*
 Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3. 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
 /*Runtime: 16 ms. Your runtime beats 6.83% of cpp submissions.*/
 
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return NULL;
        
        ListNode* x = head;
        
        while (x){
            if (x->next && x->val == x->next->val){
                //a duplicated node, remove x->next
                ListNode* tmp = x->next;
                x->next = x->next->next;
                delete tmp;
            }else{
                x = x->next;
            }
        }
        
        return head;
    }
};
