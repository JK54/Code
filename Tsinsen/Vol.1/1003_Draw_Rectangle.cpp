#include <iostream>
#include <string.h>

#define WIDTH 18
#define HEIGHT 25
int main()
{
	int i,j;
	int direction[WIDTH];
	char w[] = "ABCDEFGHIJKLMNOPQR";
	direction[0] = 1;
	for(i = 1; i < WIDTH;i++)
		direction[i] = -1;
	std::cout<<w<<std::endl;
	for(j = 1;j < HEIGHT;j++)
	{
		for(i = 0;i < WIDTH;i++)
		{
			if((w[i] + direction[i] < 'A'))
				direction[i] = 1;
			w[i] = char(w[i] + direction[i]);

		}
		std::cout<<w<<std::endl;
	}
	return 0;
}
