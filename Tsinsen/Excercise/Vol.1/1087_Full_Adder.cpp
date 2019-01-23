#include <iostream>
#include <sstream>

#define SIZE 120

int tik(std::string tmp,int *data)
{
	size_t len = tmp.length();
	std::string::iterator p = tmp.end() - 1;
	for(size_t i = 0;i < len;i++)
	{
		data[i] = *p - '0';
		p--;
	}
	return len;
}

int adder(int *a,int *b,int *c,int m,int n)
{
	int r;
	int i;
	r = i = 0;
	while(i < m && i < n)
	{
		c[i] = (a[i] + b[i] + r) % 10;
		r = (a[i] + b[i] + r) / 10;
		i++;
	}
	while(i < m)
	{
		c[i] = (a[i] + r) % 10;
		r = (a[i] + r) / 10;
		i++;
	}
	while(i < n)
	{
		c[i] = (b[i] + r) % 10;
		r = (b[i] + r) / 10;
		i++;
	}
	if(r != 0)
		c[i] = r;
	else
		i--;
	return i;
}

int main()
{
	int m,n,i;
	std::string tmp;
	int a[SIZE] = {0};
	int b[SIZE] = {0};
	int c[SIZE] = {0};
	std::cin>>tmp;
	m = tik(tmp,a);
	std::cin>>tmp;
	n = tik(tmp,b);
	for(i = adder(a,b,c,m,n);i >= 0;i--)
		std::cout<<c[i];
	std::cout<<std::endl;
	return 0;
}
