#include <iostream>

int maxprofit(int a[],int n)
{
	if(a == nullptr || n < 2)
		return -1;
	int maxprofit,minprice;
	maxprofit = 0,minprice = a[0];
	for(int i = 1;i < n;i++)
	{
		if(a[i] < minprice)
			minprice = a[i];
		if(maxprofit < a[i] - minprice)
			maxprofit = a[i] - minprice;
	}
	return maxprofit;
}

int main()
{
	int a[] = {9,11,8,5,7,12,16,14};
	std::cout<<maxprofit(a,sizeof(a) / sizeof(a[0]))<<std::endl;
}
