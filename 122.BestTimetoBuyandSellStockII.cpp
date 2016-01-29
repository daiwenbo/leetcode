/*Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many t
ransactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int max_profit = 0;
        
        if (!n){
            return max_profit;
        }
        
        
        for (int i=n-1; i>0; i--){
            int diff = prices[i]-prices[i-1];
            if (diff > 0){
                max_profit += diff;
            }
        }
        
        return max_profit;
    }
};
