#include <iostream>

#define LEN 10
int main()
{
	int INA,p;
	char result[LEN];
	std::cin>>INA>>p;
	int i = LEN - 1,j;
	int tmp;
	while(INA != 0)
	{
		tmp = INA % p; 
		INA = INA / p;
		if(tmp < 10)
			result[i--] = tmp + '0';
		else
		{
			result[i--] = tmp  - 10 + 'A';
		}
	}
	for(j = i + 1;j < LEN;j++)
		std::cout<<result[j];
	std::cout<<std::endl;
}
