#include <iostream>
#include <iomanip>
#include <cstring>

int kmp(char *decimal,int len)
{
	int i,pos;
	for(i = 0,pos = 0;i < len;i++)
	{
	
	}
	return pos;
}
void divi(int a,int b)
{
	int integral;
	char decimal[3000];
	int len,div1,div2;
	std::memset(decimal,0,sizeof(decimal));
	len = 0,div1 = a,div2 = b;
	integral = div1 / div2;
	div1 = div1 % div2;
	while(kmp(decimal,len))
	{
		while(div1 < div2)
			div1 = (div1 << 2) + (div1 << 1);
		decimal[++len] = div1/div2;
		div1 = div1 % div2;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	int a,b;
	while(std::cin>>a>>b)
		divi(a,b);
	return 0;
}
