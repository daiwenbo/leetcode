/*
 Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion? 
*/


/*128 ms. Your runtime beats 82.66% of cpp submissions.*/

class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n<=0) return false;
        
        //what is the max int number that is power of 3?
        int max_power3 = pow(3, int (log10(0x7fffffff)/log10(3)) );
        
        return max_power3%n == 0;
    }
};
