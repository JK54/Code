#include <iostream>	
#include <stdlib.h>
#include <algorithm>
int main()
{
	std::string str,*result;
	int i,j,k,n,len;
	std::cin>>str>>n;
	len = str.length();
	result = new std::string [len];
	for(i = 0,k = 0;i < n;i ++)
	{
		for(j = i;j + n <= len;j += n)
			result[k++] = str.substr(j,n);
	}
	sort(result,result + k);
	for(i = 0;i < k;i++)
		std::cout<<result[i]<<" ";
	std::cout<<std::endl;
	delete [] result;
	return 0;
}
