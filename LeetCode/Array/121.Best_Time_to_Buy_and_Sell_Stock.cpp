#include <iostream>
#include <vector>
#include <limits.h>

class Solution {
public:
    int maxProfit_brute(std::vector<int>& prices) 
	{
		int size = prices.size();
		int maxprofit = 0;
		for(int i = 0;i < size;i++)
			for(int j = i + 1;j < size;j++)
				maxprofit = maxprofit > prices[j] - prices[i] ? maxprofit : prices[j] - prices[i];
    	return maxprofit;
	}

	int maxProfit(std::vector<int> &prices)
	{
		int size;
		int minprice,maxprofit;
		minprice = INT_MAX;
		maxprofit = 0;
		size = prices.size();
		for(int i = 0; i < size;i++)
		{
			if(minprice > prices[i])
				minprice = prices[i];
			else if(maxprofit < prices[i] - minprice)
				maxprofit = prices[i] - minprice;
		}
		return maxprofit;
	}
};
