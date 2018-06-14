#include <iostream>
#include <string.h>
#include <math.h>

int main()
{
	char str[8];
	int i,j;
	int tmp,result;
	std::cin>>str;
	i = 0;
	j = strlen(str);
	while(i < j)
	{
		if(str[i] > '0' && str[i] < '9')
			tmp = str[i] - '0';
		else
			tmp = str[i] - 'A' + 10;
		result += pow(16,i) * tmp;
		i++;
	}
	std::cout<<result<<std::endl;
	return 0;
}
