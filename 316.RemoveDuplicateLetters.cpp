/*
 Given a string which contains only lowercase letters, remove duplicate letters 
 so that every letter appear once and only once. You must make sure your result is 
 the smallest in lexicographical order among all possible results.

Example:

Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb" 
*/

/*Runtime: 20 ms. Your runtime beats 10.61% of cpp submissions.*/

class Solution {
public:
    string removeDuplicateLetters(string s) {
        /*idea: use a stack. 
        first build a dictionary to count how many times each letter appears in the string, 
        then try to push each letter c on to the stack. 
        if c is not in the stack,  while the top of the the stack t > c, and counter[c] > 0, 
        pop t. and then push c
        */
        int n = s.length();
        
        if (n==0){
            return "";
        }
        
        stack<char> myStack;
        unordered_map<char, int> counter;
        unordered_map<char, bool> myMap; //auxiliary data structure, to record whether a char exist in the stack
        
        //build the counter
        for (int i=0; i<n; i++){
            char c = s[i];
            if ( counter.find(c) == counter.end() ){
                counter[c] = 1;
            }else{
                counter[c]++;
            }
        }
        
        for (int i=0; i<n; i++){
            char c = s[i];
            counter[c]--;
            if (myMap.find(c) == myMap.end()){
                //c is not in the stack, try to push it onto the stack.
                //but first pop the front of the stack t if: t>c && the string contains t after c
                while ( !myStack.empty() && myStack.top() > c && counter[myStack.top()]>0 ){
                    myMap.erase(myStack.top());
                    myStack.pop();
                }
                
                //push into stack
                myStack.push(c);
                myMap[c] = true;
            }
        }
        
        //generate the result
        int resSize = myStack.size();
        string res(resSize, '0');
        for (int i=resSize-1; i>=0; i--){
            res[i] = myStack.top();
            myStack.pop();
        }
        
        return res;
        
    }
};
