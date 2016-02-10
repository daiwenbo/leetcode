/*
Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).
For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, 
so the function should return 3.
*/

/*Runtime: 4ms. Your runtime beats 52.19% of cpp submissions.*/

class Solution {
public:
    int hammingWeight(uint32_t n) {
        //try to do better than naive while loop
        int count = 0;
        while (n!=0){
            n -= n&-n; //n&-n is the last set bit
            count++;
        }
        
        return count;
    }
};
