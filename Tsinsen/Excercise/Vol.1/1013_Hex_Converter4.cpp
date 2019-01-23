#include <iostream>
#include <string.h>
#include <math.h>

int main()
{
	char str[8];
	int i,j;
	long long  tmp,result;
	std::cin>>str;
	i = 0;
	j = strlen(str);
	result = 0;
	while(i < j && strcmp(str,"0") != 0)
	{
		if(str[i] > '0' && str[i] < '9')
			tmp = str[i] - '0';
		else
			tmp = str[i] - 'A' + 10;
		result += pow(16,j - i - 1) * tmp;
		i++;
	}
	std::cout<<result<<std::endl;
	return 0;
}
