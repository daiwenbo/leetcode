/*
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.
*/

/*Your runtime beats 66.74% of cpp submissions*/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        /*ynamic programming: array cc[i]: min coin count to reach amount i
        optimal structure: c[i] = min(c[i-1]+1), for each amount i, it needs
        minimal c[i-v]+1 coins. condition: i-v >=0, for each coin value v
        */
        int num_coins = coins.size();
        
        const int MAX = amount+1;
        vector<int> cc(amount+1, MAX);
        cc[0] = 0;
        for (int i=1; i<= amount; i++){
            for (int j = 0; j<num_coins; j++){
                if (i-coins[j] >= 0){
                    cc[i] = min(cc[i], cc[i-coins[j]]+1);
                }
            }
        }
        
        return cc[amount]==MAX?-1:cc[amount];
    }
};
