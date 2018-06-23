#include <iostream>

int getnext(int *data,int n)
{
	int result = 0;
	int *tmp = new int [n];
	while(n > 0)
	{
		result += data[n - 1];
		for(int i = n - 2;i >= 0;i--)
			tmp[i] = data[i + 1] - data[i];
		n--;
		for(int i = 0;i < n;i++)
			data[i] = tmp[i];
	}
	delete [] tmp;
	return result;
}

int main()
{
	int n,*data;
	std::cin>>n;
	data = new int [n];
	for(int i = 0;i < n;i++)
		std::cin>>data[i];
	std::cout<<getnext(data,n)<<std::endl;
	delete [] data;
	return 0;
}
