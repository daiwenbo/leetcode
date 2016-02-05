/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/*Your runtime beats 11.17% of cpp submissions*/

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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        
        stack<TreeNode*> s;
        TreeNode* cur = root;
        
        while (cur || !s.empty()){
            while (cur){
                s.push(cur);
                cur = cur->left;
            }
            
            cur = s.top();
            res.push_back(cur->val);
            s.pop();
            
            cur = cur->right;
        }
        
        return res;
    }
};
