#include <iostream>
void fibonacci(long long int *data,long long int n,long long int a,long long int b,long long int c,long long int d)
{
	data[1] = 1;
	data[2] = 1;
	for(long long int i = 3;i <= n;i++)
		data[i] = (data[i - 1] + data[i - 2]) % (a * b * c * d);
}

int main()
{
	long long int s,t,a,b,c,d,i;
	std::cin>>s>>t>>a>>b>>c>>d;
	long long int *data = new long long int [t + 1];
	fibonacci(data,t,a,b,c,d);
	for(i = s;i <= t;i++)
	{
		if(data[i] % a != 0 && data[i] % b != 0 && data[i] % c != 0 && data[i] % d != 0)
			std::cout<<i;
		if(i != t)
			std::cout<<" ";
	}
	std::cout<<std::endl;
	delete [] data;
	return 0;
}
