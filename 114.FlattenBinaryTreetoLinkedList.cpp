/*
 Given a binary tree, flatten it to a linked list in-place.

For example,
Given
         1
        / \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

Hints:
If you notice carefully in the flattened tree, each node's right child points 
to the next node of a pre-order traversal.
*/

/*Runtime: 8ms. Your runtime beats 10.02% of cpp submissions.*/

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
    void flatten(TreeNode* root) {
        if (!root) return;
        
        flatten(root->left);
        flatten(root->right);
        
        //swap left and right
        //if !root->left, then the tree has already been flattened
        if (root->left){
            TreeNode* tmp = root->right;
            root->right = root->left;
            root->left = NULL;
            
            TreeNode* x = root;
            while(x->right){
                x = x->right;
            }
            
            x->right = tmp;
        }
        
    }
};
