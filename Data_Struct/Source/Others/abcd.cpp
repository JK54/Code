#include <iostream>

bool abcd(int a,int b,int c,int d)
{
	if((a*1000 + b*100 + c*10 + d) % 13 == 0)
		if((1000*b + 100*c +10*d + a )%11 == 0)
			if((1000*c + 100*d + 10 *a +b) % 9 ==0)
				if((1000*d + 100*a + 10*b + c) %7 == 0)
					return true;
	return false;
}

int main()
{
	int a,b,c,d;
	a = b = c= d = 1;
	for(int i = 143;i < 10000;i++)
	{
		a = i /1000;
		b = i % 1000/100;
		c = i %1000%100/10;
		d = i %1000%100%10;
		if(abcd(a,b,c,d))
			break;
	}
	std::cout<<a<<b<<c<<d<<std::endl;
}
