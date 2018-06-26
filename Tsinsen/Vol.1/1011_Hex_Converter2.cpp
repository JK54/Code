#include <iostream>

#define LEN 10
int main()
{
	int INA,i,j;
	i = LEN - 1;
	char table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char result[LEN];
	std::cin>>INA;
	if(INA == 0)
	{
		std::cout<<"0"<<std::endl;
		return 0;
	}
	while(INA != 0)
	{
		result[i--] = table[INA % 16];
		INA /= 16;
	}
	for(j = i + 1;j < LEN;j++)
		std::cout<<result[j];
	std::cout<<std::endl;
	return 0;
}
