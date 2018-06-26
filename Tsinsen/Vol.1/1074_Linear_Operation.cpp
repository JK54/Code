#include <iostream>

void multi(int **data,int *x,int n)
{
	int i,j,tmp;
	for(i = 0;i < n;i++)
	{
		tmp = 0;
		for(j = 0;j < n;j++)
			tmp += data[i][j] * x[j];
		std::cout<<tmp<<std::endl;
	}
}

int main()
{
	int n,i,j,**data,*x;
	std::cin>>n;
	data = new int *[n];
	x = new int [n];
	for(i = 0;i < n;i++)
		data[i] = new int [n];
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)	
			std::cin>>data[i][j];
	for(i = 0;i < n;i++)
		std::cin>>x[i];
	multi(data,x,n);
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
	delete [] x;
	return 0;
}
