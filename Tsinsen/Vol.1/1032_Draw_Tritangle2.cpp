#include <iostream>

void draw_triangle(int n)
{
	int i,j;
	for(i = 1;i <= n;i++)
	{
		for(j = 2 * i - 1;j > i;j--)
			std::cout<<char('A' + j - i );
		for(j = 0;j < i;j++)
			std::cout<<char('A' + j);
		std::cout<<std::endl;
	}
}

int main()
{
	int HEIGHT;
	std::cin>>HEIGHT;
	draw_triangle(HEIGHT);
	return 0;
}
