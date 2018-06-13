#include <iostream>

#define WIDTH 25
#define HEIGHT 18
int main()
{
	char element[WIDTH];
	int i,j,k = 0,l;
	//init array
	for(i = 0;i < WIDTH; i++)
		element[i] = 'A' + i;
	for(j = 0;j < HEIGHT;j++)
	{
		for(i = 0,l = k;i < WIDTH;i++)
		{
			if(l > 0)
			{
				std::cout<<element[l--];
			}
			else
				std::cout<<element[i - k];
		}
		std::cout<<std::endl;
		//k mark the index of 'A' in the graph
		k++;
	}
	return 0;
}
