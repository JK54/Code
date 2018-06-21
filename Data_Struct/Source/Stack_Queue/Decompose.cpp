#include <iostream>

int decompose(int money,int value[],int count[])
{
	if(money == 0)
	{
		for(int i = 0;i <6;i++)
			std::cout<<value[i]<<" : "<<count[i]<<std::endl;
		return 0;
	}
	else if(money < 0)
	{
		std::cout<<"invalid value"<<std::endl;
		return 1;
	}
	else
	{
		int i = 0;
		while(money < value[i])
			i++;
		count[i]++;
		decompose(money - value[i],value,count);
	}
	return 0;
}

int main()
{
	int value[] = {100,50,20,10,5,1};
	int count[6] = {0};
	int tmp;
	std::cin>>tmp;
	decompose(tmp,value,count);
}
