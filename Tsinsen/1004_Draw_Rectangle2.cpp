#include <iostream>

int main()
{
	int i,j,k = 0,l;
	int WIDTH,HEIGHT;
	std::cin>>HEIGHT>>WIDTH;
	for(j = 0;j < HEIGHT;j++)
	{
		for(i = 0,l = k;i < WIDTH;i++)
		{
			if(l > 0)
			{
				std::cout<<static_cast<char>('A' + l--);
			}
			else
				std::cout<<char('A' + i - k);
		}
		std::cout<<std::endl;
		//k mark the index of 'A' in the graph
		k++;
	}
	return 0;
}
