/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
Note: You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? 
How would you optimize the kthSmallest routine?

Hint:
    Try to utilize the property of a BST.
    What if you could modify the BST node's structure?
    The optimal runtime complexity is O(height of BST).
*/

/*Rumtime: 28ms. Your runtime beats 3.64% of cpp submissions.*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        //non-recursive approach for in-order traversal
        if (!root) return 0;
        
        stack<TreeNode*> s;
        s.push(root);
        
        int count = 0;
        while (!s.empty()){
            //go all the way down to the left most node
            TreeNode* x = s.top();
            while (x->left){
                s.push(x->left);
                x = x->left;
            }
            
            //now visit the top of stack
            while ( !s.empty() ){
                TreeNode* u = s.top();
                s.pop();
                //visit u
                cout<<u->val<<" ";
                if (++count==k) return u->val;
                
                if (u->right){
                    s.push(u->right);
                    break;
                }
            }
            
        }
    }
};
