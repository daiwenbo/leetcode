/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"
*/

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        return recursive(n);
    }
    
    vector<string> recursive(int n){
        vector<string> res;
        if (n==1){
            res.push_back("()");
            return res;
        }
        
        if (n==2){
            res.push_back("()()");
            res.push_back("(())");
            return res;
        }
        
        if (n>=3){
            vector<string> preRes = recursive(n-1);
            
            string resEntry;
            
            int preResSize = preRes.size();
            for (int i=0; i<preResSize; i++){
                resEntry = "()"+preRes[i];
                res.push_back(resEntry);
                
                if (i!=0){
                    //special case for preRes[0]: it's always a series of non-overlapping ()
                    resEntry = preRes[i]+"()";
                    res.push_back(resEntry);  
                }

                resEntry = "("+preRes[i]+")";
                res.push_back(resEntry);
            }
            
            return res;
        }
    }
};
