#include <iostream>

int main()
{
	int i,j;
	int odd;
	for(i = 0; i < 64;i++)
	{
		odd = 0;
		for(j = 5;j >= 0;j--)
		{
			if((i >> j & 1) == 1)
				odd += 1;
		}
		//judge the bits of "1" is odd or not
		if(odd % 2 != 0)
		{
			for(j = 5;j >= 0; j --)
				std::cout<<((i>>j) & 1);
			std::cout<<std::endl;
		}
	}
	return 0;
}
