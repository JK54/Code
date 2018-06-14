#include <iostream>

int main()
{
	int i,n,*data,a,pos;
	std::cin>>n;
	data = new int [n];
	for(i = 0;i < n;i++)
		std::cin>>data[i];
	std::cin>>a;
	pos = -1;
	for(i = 1;i <= n;i++)
	{
		if(data[i - 1] == a)
		{
			pos = i;
			break;
		}
	}
	std::cout<<pos<<std::endl;
	delete [] data;
	return 0;
}
