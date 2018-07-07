#include <iostream>

int find(int a,int *data)
{
	int i = a - 1;
	while(data[i] >= 0)
		i = data[i];
	return i;
}

void uniset(int *data,int a,int b)
{
	int i = find(a,data);
	int j = find(b,data);
	if(i == j)
		return ;
	if(j < 0)
	{
		data[b - 1] = i;
		data[i] += j;
	}
	else
	{
		data[i] += data[j];
		data[j] = a - 1;
	}
}

int main()
{

	int i,n,m,*data;
	int *a,*b,result;
	std::cin>>n>>m;
	data = new int [n];
	a = new int [m];
	b = new int [m];
	for(i = 0;i < n;i++)
		data[i] = -1;
	for(i = 0;i < m;i++)
		std::cin>>a[i]>>b[i];
	for(i = 0;i < m;i++)
	{
		if(a[i] > b[i])
			std::swap(a[i],b[i]);
		if(a[i] != b[i])
			uniset(data,a[i],b[i]);
	}
	for(i = 0,result = 0;i < n;i++)
		if(data[i] < 0)
			result++;
	std::cout<<result<<std::endl;
	delete [] a;
	delete [] b;
	delete [] data;
	return 0;
}
