#include <iostream>
#include <string.h>

void print(char *w,int n)
{
	for(int i = 0; i < n;i++)
		std::cout<<w[i];
	std::cout<<std::endl;
}
int main()
{
	int i,j;
	int width,height;
	std::cin>>height>>width;
	int *direction = new int [width];
	char *w = new char [width];
	direction[0] = 1;
	for(i = 1;i < width;i++)
		direction[i] = -1;
	direction[0] = 1;
	for(i = 1; i < width;i++)
		direction[i] = -1;
	for(i = 0;i < width;i++)
		w[i] = static_cast<char>('A' + i);
	print(w,width);
	for(j = 1;j < height;j++)
	{
		for(i = 0;i < width;i++)
		{
			if((w[i] + direction[i] < 'A'))
				direction[i] = 1;
			else if(w[i] + direction[i] > 'Z')
				w[i] = 'A';
			w[i] = char(w[i] + direction[i]);
		}
		print(w,width);
	}
	delete [] direction;
	delete [] w;
	return 0;
}
