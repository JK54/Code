#include <iostream>
#include <string.h>
void laying(int index,int sum,int n,int &num1,int &numf,int mark1[])
{
	if(sum == n)
	{
		numf++;
		for(int i = 0;i <= n;i++)
		{
			if(mark1[i] == 1)
				num1++;
		}
		return;
	}
	for(int i = 1;i <= 3;i++)
	{
		if(i == 1 && mark1[index] != 1 && sum + i <= n)
		{
			mark1[index + 1] = 1;
			sum += 1;
			laying(index + 1,sum,n,num1,numf,mark1);
			sum -=1;
			mark1[index + 1] = 0;
		}
		else if(i != 1 && sum + i <= n)
		{
			sum += i;
			laying(index + 1,sum,n,num1,numf,mark1);
			sum -=i;
		}
	}
}

int main()
{
	int n,*mark1;
	int num1,numf,sum,index;
	num1 = numf = sum = index = 0;
	std::cin>>n;
	mark1 = new int [n + 1];
	memset(mark1,0,n + 1);
	laying(index,sum,n,num1,numf,mark1);
	std::cout<<numf<<std::endl;
	std::cout<<num1<<std::endl;
	delete [] mark1;
	return 0;
}
