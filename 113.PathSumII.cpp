/*
 Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return
[
   [5,4,11,2],
   [5,8,4,5]
]
*/

/*Rumtime: 24ms. Your runtime beats 5.80% of cpp submissions.*/

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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        //do a recursive dfs, cal the sum along the way
        vector<vector<int>> res;
        if (!root) return res;
        
        int curSum = 0;
        vector<int> tmp;
        dfsVisit(root, sum, curSum, tmp, res);
        
        return res;
    }
    
    void dfsVisit(TreeNode* root, int sum, int curSum, vector<int> tmp, vector< vector<int> >& res){
        if (!root) return;
        
        tmp.push_back(root->val);
        curSum += root->val;
        if (isLeaf(root) && sum == curSum){
            res.push_back(tmp);
        }
        
        dfsVisit(root->left, sum, curSum, tmp, res);
        dfsVisit(root->right, sum, curSum, tmp, res);
    }
    
    bool isLeaf(TreeNode* n){
        return n && !n->left && !n->right;
    }
    
    void printList(vector<int>& v){
        for (auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }
};
