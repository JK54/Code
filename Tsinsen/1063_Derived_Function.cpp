#include <iostream>
#include <math.h>
int deriative(int n,int *an,int x0)
{
	int i,j,sum = an[1],tmp;
	for(i = 2;i <= n;i++)
	{
		tmp = x0;
		for(j = 2;j <= i - 1;j++)
			tmp = (tmp * x0) % 9999;
		tmp = (tmp * (i * an[i] % 9999))% 9999 + 9999;
		sum = sum % 9999 + tmp;
	}
	std::cout<<(sum % 9999)<<std::endl;
	return sum % 9999;
}

int main()
{
	int i,n,*an,x0,result;
	std::cin>>n>>x0;
	an = new int[n + 1];
	for(i = 0;i <= n;i++)
		std::cin>>an[i];
	result = deriative(n,an,x0);
	delete [] an;
	return 0;
}
