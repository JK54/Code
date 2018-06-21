#include <iostream>

int method(int n)
{
	if(n == 0)
		return 1;
	else if(n < 0)
		return 0;
	else
		return method(n - 1) + method(n - 2) + method(n -3 );
}

int main()
{
	int n,result;;
	std::cin>>n;
	if(n < 4 || n >= 20)
		result = 0;
	else
		result = method(n);
	std::cout<<result<<std::endl;
	return 0;
}
