#include <iostream>

int main()
{
	int INA;
	char table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char result[3];
	std::cin>>INA;
	int i = 2;
	while(INA != 0)
	{
		result[i--] = table[INA % 16];
		INA /= 16;
	}
	for(i = 0;i <= 2;i++)
		std::cout<<result[i];
	std::cout<<std::endl;
}
