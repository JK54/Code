#include <iostream>

int cal(int x,int y,int z)
{
	switch(z)
	{
	case 1:return x + y;
	case 2:return x - y;
	case 3:return x * y;
	case 4:return x / y;
	case 5:return x % y;
	case 6:for(int i = std::min(x,y);i >= 1;i--)
		   {
		   	if(x % i == 0 && y % i == 0)
				return i;
		   }
	case 7:
		   for(int i = std::max(x,y);;i++)
		   {
		   	if(i % x == 0 && i % y == 0)
				return i;
		   }
	default:
		   std::cout<<"invalid z"<<std::endl;
	}
	return -1;
}

int main()
{
	int x,y,z;
	std::cin>>x>>y>>z;
	std::cout<<cal(x,y,z)<<std::endl;
	return 0;
}
