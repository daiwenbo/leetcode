/* Given a binary tree and a sum, determine if the tree has a root-to-leaf path such 
that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/

/*Rumtime: 12ms. Your runtime beats 10.07% of cpp submissions.*/

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
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        //dfs
        
        stack<TreeNode*> s;
        s.push(root);
        
        while ( !s.empty() ){
            TreeNode* u = s.top(); s.pop();
            
            if (!u->left && !u->right){
                if (u->val==sum) return true;
            }
            
            if (u->right){
                u->right->val += u->val;
                s.push(u->right);
            }
            
            if (u->left){
                u->left->val += u->val;
                s.push(u->left);
            }
        }
        
        return false;
    }
};
