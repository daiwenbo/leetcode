/*
Given a string array words, find the maximum value of length(word[i]) * length(word[j]) 
where the two words do not share common letters. 
You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.
*/

/*Runtime: 124 ms, Your runtime beats 73.48% of cpp submissions.*/

class Solution {
public:
    int maxProduct(vector<string>& words) {
        /*bit manipulation, complexity: O(m*n) or O(n^2), which ever larger. 
        m is the average length of words*/
        
        int n = words.size();
        vector<int> bits(n, 0);
        //first convert each word into bit representation
        for (int i=0; i<n; i++){
            string word = words[i];
            for (int j=0; j<word.length(); j++){
                bits[i] |= 1<<(word[j]-'a');
            }
        }
        
        //check each word-pair, if they have no letter intersection, check their length product
        int maxLength = 0;
        for (int i=0; i<n-1; i++){
            for (int j=i+1; j<n; j++){
                //check words[i] and words[j]
                int bitAnd = bits[i]&bits[j];
                if (bitAnd == 0){
                    //they have no letter intersection
                    int length = words[i].length()*words[j].length();
                    if ( length > maxLength ){
                        maxLength = length;
                    }
                }
            }
        }
        
        return maxLength;
    }
};
