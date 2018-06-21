#include <iostream>

#define LEN1 1
#define LEN2 2
int Method(int n,int &num,bool flag)
{
	if(n == 0)
	{
		if(flag == true)	
			num++;
		return 1;
	}
	else if(n < 0)
		return 0;
	else
	{
		if(flag == true)
		{
			num++;
			return Method(n - 2,num,false) + Method(n - 3,num,false);
		}
		else
			return Method(n - 1,num,true) + Method(n - 2,num,false) + Method(n - 3,num,false);
	}
}

int main()
{
	int m,n,result;
	bool flag = false;
	m = 0;
	std::cin>>n;
	result = Method(n,m,flag);
	std::cout<<result<<'\n'<<m<<std::endl;
}
