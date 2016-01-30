/*Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?*/

/*Your runtime beats 11.08% of cpp submission*/

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root){
            return res;
        }
        
        stack<TreeNode*> s;
        unordered_map<TreeNode*, bool> visitedNodes;
        
        //push root
        s.push(root);
        while (!s.empty()){
            TreeNode* u = s.top();
            //if u is leaf node or both of u's children has been visited
            //pop u
            bool visited_right = !u->right || 
                u->right && visitedNodes.find(u->right) != visitedNodes.end();
            bool visited_left = !u->left ||
                u->left && visitedNodes.find(u->left) != visitedNodes.end();
            
            if ( visited_right && visited_left ){
                res.push_back(u->val);
                visitedNodes[u] = true;
                s.pop();
            }else{
                if (!visited_right && u->right){
                    s.push(u->right);
                }
                if (!visited_left && u->left){
                    s.push(u->left);
                }
            }
        }
        
        return res;
    }
};

/*another clean solution: */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if(root==NULL)return ret;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty())
        {
            TreeNode *curr=st.top();
            st.pop();
            if(curr->left)st.push(curr->left);
            if(curr->right)st.push(curr->right);
            ret.push_back(curr->val);
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};
