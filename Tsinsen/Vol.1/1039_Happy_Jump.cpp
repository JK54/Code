#include <iostream>
#include <cmath>
void jump(int *data,int *result,int n)
{
	int i,j,tmp;
	for(i = 1;i < n;i++)
		result[i - 1] = std::fabs(data[i] - data[i - 1]);
	for(i = 0;i < n - 1;i++)
	{
		for(j = i + 1;j < n - 1;j++)
		{
			if(result[i] > result[j])
			{
				tmp = result[i];
				result[i] = result[j];
				result[j] = tmp;
			}
		}
	}
	for(i = 0;i < n - 1;i++)
		if(i + 1 != result[i])
		{
			std::cout<<"I'm unhappy!!"<<std::endl;
			return;
		}
	std::cout<<"I'm happy!!"<<std::endl;
}

int main()
{
	int n;
	int *data,*result;
	std::cin>>n;
	data = new int[n];
	result = new int[n - 1];
	for(int i = 0;i < n;i++)
		std::cin>>data[i];
	jump(data,result,n);
	delete [] data;
	delete [] result;
	return 0;
}
