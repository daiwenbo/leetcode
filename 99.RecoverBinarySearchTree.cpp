/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
*/
/*Your runtime beats 31.98% of cpp submissions.*/

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
    void recoverTree(TreeNode* root) {
        //perform a in-order traversal, find the location where wrong order happens
        //two possible situations: (1) there is 1 wrong ordering: swap these two
        // (2) there are 2 wrong orderings: ba...yx: swap b and x;
        
        TreeNode* recentNode = NULL;
        vector<TreeNode*> wrongPtrs; //store the two pointers that needs to be swapped
        int wrongCount = 0;
        
        inorder(root, recentNode, wrongPtrs, wrongCount);

        //swap
        int tmp = wrongPtrs[0]->val;
        wrongPtrs[0]->val = wrongPtrs[1]->val;
        wrongPtrs[1]->val = tmp;
        
    }
    
    void inorder(TreeNode* root, TreeNode*& recentNode, vector<TreeNode*>& wrongPtrs, int& wrongCount){
        if (!root){
            //do nothing
            return; 
        }else{
            inorder(root->left, recentNode, wrongPtrs, wrongCount);
            //root node, should be: recent < root
            
            if (recentNode && recentNode->val > root->val){
                if (wrongCount==0){
                    //this is first wrong order, recode the recend and current root
                    wrongPtrs.push_back(recentNode);
                    wrongPtrs.push_back(root);
                    wrongCount++;
                }else{
                    //this is the second wrong order, replace the second item in "wrongPtrs" with current root;
                    wrongPtrs.pop_back();
                    wrongPtrs.push_back(root);
                }
            }
            recentNode = root;
            
            inorder(root->right, recentNode, wrongPtrs, wrongCount);  
        }
    }
    
    
};
