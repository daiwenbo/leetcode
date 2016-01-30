/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/* Your runtime beats 0.27% of cpp submissions */

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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root){
            return res;
        }
        
        stack<TreeNode*> s;
        s.push(root);
        
        while(!s.empty()){
            //visit stack top
            TreeNode* u = s.top();
            s.pop();
            res.push_back(u->val);
            if (u->right) s.push(u->right);
            if (u->left) s.push(u->left);
        }
        
        return res;
    }
};
