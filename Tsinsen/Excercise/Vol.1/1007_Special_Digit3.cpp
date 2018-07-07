#include <iostream>

int main()
{
	int IA;
	int i;
	int a,b,c,d,e,f;
	std::cin>>IA;
	for(i = 10000; i <= 99999;i++)
	{
		a = i / 10000;
		b = i / 1000 % 10;
		c = i / 100 % 10;
		d = i / 10 % 10;
		f = i % 10;
		if(a == f && b == d && IA == a + b + c + d + f)
			std::cout<<i<<std::endl;
	}
	for(i = 100000; i <= 999999;i++)
	{
		a = i / 100000;
		b = i / 10000 % 10;
		c = i / 1000 % 10;
		d = i / 100 % 10;
		e = i / 10 % 10;
		f = i % 10;
		if(a == f && b == e && c == d && IA == a + b + c + d + e + f)
			std::cout<<i<<std::endl;
	}
	return 0;
}
