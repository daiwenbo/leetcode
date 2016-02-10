/*
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top? 
*/

/*Runtime: 0 ms*/

class Solution {
public:
    int climbStairs(int n) {
        /*idea: DP, dp[i]: distict ways to reach step i. 
        dp[i] = dp[i-1]+dp[i-2];
        dp[1] = 1; dp[2] = 2;
        */
        
        if (n<=1){
            return 1;
        }
        
        vector<int> dp(n+1, 1);
        
        //can use only 3 variables, instead of the array!
        for (int i=2; i<=n; i++){
            dp[i] = dp[i-1]+dp[i-2];
        }
        
        return dp[n];
    }

};
