/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
*/

/*
Runtime: 608 ms. Your runtime beats 11.67% of cpp submissions.
*/

class NumArray {
public:
    int n;
    vector<int> sum;

    NumArray(vector<int> &nums) {
        n = nums.size();
        
        if (n>0) sum.resize(n, nums[0]);
        
        for (int i=1; i<n; i++){
            sum[i] = sum[i-1] + nums[i];
        }
    }

    int sumRange(int i, int j) {
        return i>0?sum[j]-sum[i-1]:sum[j];
    }
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);
