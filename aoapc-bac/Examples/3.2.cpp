#include <iostream>
#include <cstring>

int main()
{
	int i,j,n,k,*a;
	std::cin>>n>>k;
	a = new int[n];
	std::memset(a,0,sizeof(int) * n);
	for(i = 0;i < k;i++)
		for(j = 0;j < n;j++)
			if((j + 1) % (i + 1) == 0)
				a[j] = !a[j];
	for(i = 0;i < n;i++)
		if(a[i])
			std::cout<<(i + 1)<<" ";
	std::cout<<std::endl;
	delete [] a;
	return 0;
}
