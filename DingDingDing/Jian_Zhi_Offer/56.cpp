#include <iostream>

int findfirstnonzerobit(int num)
{
	int indexbit = 0;
	while(num != 0)
	{
		if(num & 1)
			break;
		indexbit++;
		num >>= 1;
	}
	return indexbit;
}

void findtwounique(int data[],int len,int &num1,int &num2)
{
	if(data == nullptr || len < 2)
		return;
	int xoresult = 0;
	for(int i = 0;i < len;i++)
		xoresult ^= data[i];
	int indexnonzerobit = findfirstnonzerobit(xoresult);
	num1 = num2 = 0;
	for(int i = 0;i < len;i++)
	{
		if((data[i] >> indexnonzerobit) & 1)
			num1 ^= data[i];
		else
			num2 ^= data[i];
	}
}

int main()
{
	int a[] = {2,4,3,6,3,2,5,5};
	int num1,num2;
	findtwounique(a,sizeof(a)/sizeof(a[0]),num1,num2);
	std::cout<<num1<<std::endl;
	std::cout<<num2<<std::endl;
}
