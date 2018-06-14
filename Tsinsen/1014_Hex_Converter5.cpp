#include <iostream>
#include <string.h>
#include <math.h>

#define LEN 8
#define LEN_OCT 12
#define ORIGIN_HEX 16
#define WANTED_HEX 8
int main()
{
	int i,j,k,n;
	int tmp;
	std::cout<<"input num of hex digit"<<std::endl;
	std::cin>>n;
	int *result = new int[n];
	char **result2 = new char*[n];
	char **str  = new char*[n];
	for(i = 0;i < n ;i++)
	{
		 str[i] = new char[LEN];
		 result2[i] = new char[LEN_OCT];
	}
	for(k = 0 ;k < n; k++)
		std::cin>>str[k];
	k = 0;
	while(k < n)
	{
		i = 0;
		j = strlen(str[k]);
		while(i < j)
		{
			if(str[k][i] > '0' && str[k][i] < '9')
				tmp = str[k][i] - '0';
			else
				tmp = str[k][i] - 'A' + 10;
			result[k] += pow(ORIGIN_HEX,i) * tmp;
			i++;
		}
		i = LEN_OCT - 1;
		while(result[k] != 0)
		{
			result2[k][i--] = result[k] % WANTED_HEX + '0';
			result[k] /= WANTED_HEX;
		}
		for(j = i + 1; j <LEN_OCT;j++)
			std::cout<<result2[k][j];
		std::cout<<std::endl;
		k++;
	}
	delete [] result;
	delete [] result2;
	delete [] str;
	return 0;
}
