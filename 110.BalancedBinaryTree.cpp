/*
Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of 
the two subtrees of every node never differ by more than 1. 
*/

/*Runtime: 12 ms. Your runtime beats 81.58% of cpp submissions.*/

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
    bool isBalanced(TreeNode* root) {
        if (!root){
            return true;
        }

        return isBalanced(root->left) && 
            isBalanced(root->right) && 
            abs(getHeight(root->left)-getHeight(root->right))<=1; 
    }
    
    int getHeight(TreeNode* root){
        if (!root){
            return 0;
        }else{
            return 1 + max( getHeight(root->left), getHeight(root->right) );
        }
    }
    
    int max(int a, int b){
        return a>b?a:b;
    }
};
