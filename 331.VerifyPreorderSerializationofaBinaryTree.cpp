/*
One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, 
we record the node's value. If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string 
"9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder 
traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.
You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true

Example 2:
"1,#"
Return false

Example 3:
"9,#,#,1"
Return false
*/

/* Runtime: 20 ms. Your runtime beats 8.31% of cpp submissions.*/

class Solution {
public:
    bool isValidSerialization(string preorder) {
        vector<string> nodes;
        
        //parse the input string into a vector of nodes
        size_t start = 0;
        size_t found = preorder.find_first_of(",");
        while(found!=string::npos){
            string tmp = preorder.substr(start, found-start);
            nodes.push_back(tmp);
            start = found+1;
            found = preorder.find_first_of(",", start);
        }
        nodes.push_back( preorder.substr(start) );
        
        vector<string> s;
        for (auto node : nodes){
            //push it onto the stack
            s.push_back(node);
            
            int len = s.size();
            while (len >= 3 && 
                s[len-1] == "#" &&
                s[len-2] == "#" &&
                s[len-3] != "#"){
                //replace these 3 nodes with a "#"
                s.pop_back();
                s.pop_back();
                s.pop_back();
                s.push_back("#");
                
                len = s.size();
            }
        }
        
        //debug
        for (auto left:s){
            cout<<left<<endl;
        }
        
        return s.size()==1 && s[0] == "#";
    }
};
