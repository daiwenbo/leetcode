/*Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25
*/
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
    int sumNumbers(TreeNode* root) {
        if (!root){
            return 0;
        }
        int sum = 0;
        dfsVisit(root, sum);
        
        return sum;
    }
    
    void dfsVisit(TreeNode* node, int& sum){
        //dfsVisit node's children
        if (node->left){
            node->left->val += node->val*10;
            dfsVisit(node->left, sum);
        }
        if (node->right){
            node->right->val += node->val*10;
            dfsVisit(node->right, sum);
        }
        
        //if this is a leaf, add its value into sum
        if (!node->left && !node->right){
            sum += node->val;
            cout<<"Adding value: "<<node->val<<endl;
        }
        
    }
};
