/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it 
represented by array nums. You are asked to burst all the balloons. 
If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. 
Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent. 

Find the maximum coins you can collect by bursting the balloons wisely. 
Note: 
 (1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
 (2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100 

Example: 
Given [3, 1, 5, 8] 
Return 167 
    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

/* Runtime: 56 ms. Your runtime beats 10.49% of cpp submissions*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        /*DP: dp[i][j] is the max value of bursting ballons in the range of [i, j].
        recursive: dp[i][j] = max( dp[i][j], dp[i][k-1]+dp[k+1][j]+nums[i-1]*nums[k]*nums[j+1] )
         k is any ballon within range [i, j]
        */
        
        int n = nums.size();
        
        //augment the input array
        nums.push_back(1);
        nums.insert(nums.begin(), 1);

        //the DP array
        vector< vector<int> > dp( n+2, vector<int>(n+2, 0) );
        
        for (int length=1; length<=n; length++){
            cout<<"length: "<<length<<". "<<endl;;
            for (int i=1; i<=n-length+1; i++){
                //i is the start of range
                int j = i + length - 1; // j is the end of range, inclusive
                for (int k=i; k<=j; k++){
                    //k is the ballon to burst
                    int value = dp[i][k-1] + dp[k+1][j] + nums[i-1]*nums[k]*nums[j+1];
                    if (value > dp[i][j]){
                        dp[i][j] = value;
                    }
                }
            }
        }
        
        return dp[1][n];
    }
};
