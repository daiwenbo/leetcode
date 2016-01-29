/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        
        int buy, sell, max_profit, min_location;
        buy = sell = 0;
        max_profit = 0;
        min_location = 0;
        
        for (int i=0; i<n; i++){
            if (prices[i] < prices[min_location]){
                min_location = i;
            }
            
            int cur_profit = prices[i] - prices[min_location];
            
            if (cur_profit > max_profit){
                max_profit = cur_profit;
                buy = min_location;
                sell = i;
            }
        }
        
        cout<<"Buy and sell at: "<<buy<<" "<<sell;
        
        return max_profit;
    }
};
