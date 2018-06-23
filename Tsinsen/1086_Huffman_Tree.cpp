#include <iostream>

int CostOfHuff(int *data,int n)
{
	int i,min,secmin,cost;
	cost = 0;
	while(n != 1)
	{
		if(data[0] > data[1])
		{
			min = 0;
			secmin = 1;
		}
		else
		{
			min = 1;
			secmin = 0;
		}
		for(i = 0;i < n;i++)
		{
			if(data[min] > data[i])
			{
				secmin = min;
				min = i;
			}
			else if(data[secmin] >= data[min] && data[secmin] > data[i])
				secmin = i;
		}
		i = std::min(secmin,min);
		data[i] += data[std::max(secmin,min)];
		cost += data[i];
		for(i = std::max(secmin,min);i < n - 1;i++)
			data[i] = data[i + 1];
		n--;
	}
	return cost;
}

int main()
{
	int n,*data;
	std::cin>>n;
	data = new int [n];
	for(int i = 0;i < n;i++)
		std::cin>>data[i];
	std::cout<<CostOfHuff(data,n)<<std::endl;
	delete [] data;
	return 0;
}
