/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
*/

/*Your runtime beats 29.28% of cpp submissions.*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root){
            return "";
        }
        
        vector<string> tmp;
        //bfs
        tmp.push_back(int2string(root->val));
        queue<TreeNode*> bfsQ;
        bfsQ.push(root);
        
        while(!bfsQ.empty()){
            TreeNode* u = bfsQ.front(); 
            bfsQ.pop();
            
            if (!u->left){
                tmp.push_back("null");
            }else{
                tmp.push_back(int2string(u->left->val));
                bfsQ.push(u->left);
            }
            
            if (!u->right){
                tmp.push_back("null");
            }else{
                tmp.push_back(int2string(u->right->val));
                bfsQ.push(u->right);
            }
        }
        
        //remove the trailing null
        while (tmp.back() == "null"){
            tmp.erase(tmp.end()-1);
        }
        
        //output it
        stringstream ss;
        for(int i=0; i<tmp.size(); i++){
            ss<<tmp[i]<<" ";
        }
        
        return ss.str();
    }
    
    string int2string(int i){
        stringstream ss;
        ss<<i;
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        //parse the input string
        if (data==""){
            return NULL;
        }
        
        queue<TreeNode*> q;
        
        stringstream ss(data);
        string node;
        ss>>node;
        
        //creat the root
        TreeNode* root = new TreeNode(atoi(node.c_str()));
        root->left = NULL;
        root->right = NULL;
        q.push(root);
        
        bool isLeft  = true;
        while (ss>>node){
            //creat a need node
            
            TreeNode* newNode = NULL;
            if (node!="null"){
                newNode = new TreeNode(atoi(node.c_str()));
                q.push(newNode);
            }
            
            if (isLeft){
                q.front()->left = newNode;
                isLeft = false;
            }else{
                //the new node is the right child of the node that is currently at the head of q
                q.front()->right = newNode;
                isLeft = true;
                q.pop();
            }
        }
        
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
