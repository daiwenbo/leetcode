/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

/*Your runtime beats 6.16% of cpp submissions*/ 

class Solution {
public:
    int rob(vector<int>& nums) {
        /*DP: array a[i]: the max value by considering robbing house i 
        (not necessarily rob it)*/
        int num_house = nums.size();
        
        if (num_house == 0){
            return 0;
        }else if (num_house == 1){
            return nums[0];
        }
        
        vector<int> a(num_house, 0);
        a[0] = nums[0];
        a[1] = max(nums[0], nums[1]);
        
        for (int i=2; i<num_house; i++){
            a[i] = max(a[i-2]+nums[i], a[i-1]);
        }
        
        return a[num_house-1];
    }
};
