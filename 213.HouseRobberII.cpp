/*Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

/*Your runtime beats 7.61% of cpp submissions.*/

class Solution {
public:
    int rob(vector<int>& nums) {
        /*DP: array a_include0[i]: consider house 0 and i, the max value, i<n-1
         array a_not_include0[i]: not consider house 0, consider house i, the max value, i<n
         */
        int num_house = nums.size();
        if (num_house == 0){
            return 0;
        }else if (num_house == 1){
            return nums[0];
        }
        
        vector<int> a_include0(num_house, 0);
        vector<int> a_not_include0(num_house, 0);
        a_include0[0] = nums[0];
        a_include0[1] = max(nums[0], nums[1]);
        
        a_not_include0[0] = 0;
        a_not_include0[1] = nums[1];
        
        for (int i=2; i<num_house-1; i++){
            a_include0[i] = max(a_include0[i-2]+nums[i], a_include0[i-1]);
        }
        
        for (int i=2; i<num_house; i++){
            a_not_include0[i] = max(a_not_include0[i-2]+nums[i], a_not_include0[i-1]);
        }
        
        return max(a_include0[num_house-2], a_not_include0[num_house-1]);
    }
};
