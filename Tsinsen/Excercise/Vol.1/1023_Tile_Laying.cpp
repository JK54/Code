#include <iostream>

#define LEN1 1
#define LEN2 2
int Method(int n)
{
	if(n == 0)
		return 1;
	else if(n < 0)
		return 0;
	else
		return Method(n - LEN1) + Method(n - LEN2);
}

int main()
{
	int n;
	std::cin>>n;
	std::cout<<(Method(n))<<std::endl;
}
