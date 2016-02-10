/*Given two binary trees, write a function to check if they are equal or not.
Two binary trees are considered equal if they are structurally identical and the nodes have the same value. 
*/

/*Runtime: 0 ms. Your runtime beats 3.61% of cpp submissions.*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 /*recursive*/
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p==NULL && q==NULL){
            return true;
        }
        
        if (p && q && p->val==q->val){
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
        
        return false;
    }
};
 
/*bfs approach*/
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //do a tree traversal lock-step, check whether they are equal
        
        //handle NULL first
        if (p==NULL && q==NULL){
            return true;
        }else if (p==NULL || q==NULL){
            return false;
        }else if (p->val != q->val) {
            return false;
        }
        
        //bfs
        queue<TreeNode*> tree1;
        queue<TreeNode*> tree2;
        tree1.push(p);
        tree2.push(q);
        
        while ( !tree1.empty() && !tree2.empty() ){
            TreeNode* u1 = tree1.front(); tree1.pop();
            TreeNode* u2 = tree2.front(); tree2.pop();
            
            if (u1->left && u2->left && u1->left->val != u2->left->val){
                return false;
            }
            if (u1->right && u2->right && u1->right->val != u2->right->val){
                return false;
            }
            
            int oneIsNull = u1->left==NULL;
            int twoIsNull = u2->left==NULL;
            if (oneIsNull+twoIsNull==1){
                return false;
            }
            
            oneIsNull = u1->right==NULL;
            twoIsNull = u2->right==NULL;
            if (oneIsNull+twoIsNull==1){
                return false;
            }
            
            //now push their children
            if (u1->left) tree1.push(u1->left);
            if (u1->right) tree1.push(u1->right);
            if (u2->left) tree2.push(u2->left);
            if (u2->right) tree2.push(u2->right);
        }
        
        if ( !tree1.empty() || !tree2.empty() ){
            //cout<<"diff length"<<endl;
            return false;
        }
        
        return true;
    }
};
