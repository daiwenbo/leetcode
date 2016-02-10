/*
 Given an array nums, write a function to move all 0's to the end of it while maintaining 
 the relative order of the non-zero elements.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].
Note:
    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
*/

/*Runtime: 16 ms. Your runtime beats 93.31% of cpp submissions.*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        /*idea: quick sort*/
        int n = nums.size();
        
        int pivot = 0;
        int i = -1;
        int j = 0;
        
        while (j<=n-1){
            if ( nums[j]!=pivot ){
                //swap i and j
                i++;
                int tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
            j++;
        }
    }
};
