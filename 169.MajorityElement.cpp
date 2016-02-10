/*
Given an array of size n, find the majority element. The majority element is the 
element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
*/

/*runtime: 16ms. Your runtime beats 84.24% of cpp submissions*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //Boyer-Moore
        int n = nums.size();
        
        int majority;
        
        int count = 0;
        for (int i=0; i<n; i++){
            if (count==0){
                majority = nums[i];
            }
            
            if (majority == nums[i]){
                count++;
            }else{
                count--;
            }
        }
        
        //now, majority might be the answer, but double check
        /*question: under what circumstance, majority is not the answer?*/
        
        count = 0;
        for (int i=0; i<n; i++){
            if (nums[i] == majority){
                count++;
            }
        }
        if (count > n/2){
            return majority;
        }
    }
};
